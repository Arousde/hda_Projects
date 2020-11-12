/* ========================================
 *
 * Copyright Felix Ohms, 2019
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * ========================================
*/

#include "SPS30_I2C.h"

/**
 * Initialises the SPS30 sensor and starts its measurement.
 *
 * @return True if successful, false otherwise.
 */
bool SPS30_Init() {
    uint8_t auto_clean_days = 4; // Auto clean interval for SPS30
    int16_t err; // Last received error code

    // Try 10x to get the sensor, then return false
    for(short i = 1; sps30_probe() != 0; i++){
        PRINTF("SPS30 sensor probing failed, ");
        if(i >= SENSOR_INIT_RETRIES){
            // 10th time reached, aborting
            PRINTF("aborting\r\n\r\n");
            return false;
        }
        // Retry up to SENSOR_INIT_RETRIES times
        PRINTF("retrying %d more times\r\n", SENSOR_INIT_RETRIES - i);
        sleep(1);
    }
    PRINTF("SPS30 sensor probing successful\r\n");

    // Set auto cleaning interval
    err = sps30_set_fan_auto_cleaning_interval_days(auto_clean_days);
    if(err){
        // An error occurred while setting the cleaning interval
        PRINTF("Error %d setting the auto-clean interval for the SPS30\r\n", err);
        return false;
    }

    // Start the measurement
    err = sps30_start_measurement();
    if(err < 0){
        // An error occurred while starting the measurement
        PRINTF("error starting measurement from SPS sensor\r\n");
        return false;
    }

    // SPS30 initialisation successful
    PRINTF("SPS30 measurements started\r\n\r\n");

    return true;
}

/**
 * Reads measurements from the SPS30 sensor.
 *
 * @param m Struct in which to write the measurements.
 * @param data Data structure for communicating measurements to BLE module via I2C.
 * @return True if successful, false otherwise.
 */
bool SPS30_Read_Data(struct sps30_measurement* m) {
    int16_t err; // Last received error code
    uint16_t data_ready; // Flag if the SPS30 has the next measurement ready to be read
    short counter = 0;

    // Make sure the data is ready to be read
    do {
        err = sps30_read_data_ready(&data_ready); // Get data ready flag
        if(err < 0){
            // Data ready flag cannot be read
            PRINTF("Error %d reading data-ready flag from SPS30\r\n", err);
        }
        else if(!data_ready){
            // Data is not ready
            PRINTF("SPS30 data not ready, no new measurement available\r\n");
        }
        else {
            // Data is ready to be read
            break;
        }

        // Add a retry, wait some time before retrying
        counter++;
        usleep(100);
        // Abort if it takes too long
    } while(counter < 10);

    // Read the measurement
    err = sps30_read_measurement(m);
    if(err < 0){
        PRINTF("Error reading measurement from SPS30\r\n");
        return false;
    }

    // Fill I2C Buffer with appropriate measurements
    /*if(data != NULL){
        // Mass concentration in μg/m^3
        data->MC_PM1p0 = m->mc_1p0 * 1000000;   // PM1.0  < 1.0 μm (Micrometer)
        data->MC_PM2p5 = m->mc_2p5 * 1000000;   // PM2.5  < 2.5 μm
        data->MC_PM4p0 = m->mc_4p0 * 1000000;   // PM4.0  < 4.0 μm
        data->MC_PM10p0 = m->mc_10p0 * 1000000; // PM10.0 < 10.0 μm
        // Amount per cm^3
        data->NC_PM0p5 = m->nc_0p5 * 1000000;   // PM0.5  < 0.5 μm
        data->NC_PM1p0 = m->nc_1p0 * 1000000;   // PM1.0  < 1.0 μm
        data->NC_PM2p5 = m->nc_2p5 * 1000000;   // PM2.5  < 2.5 μm
        data->NC_PM4p0 = m->nc_4p0 * 1000000;   // PM4.0  < 4.0 μm
        data->NC_PM10p0 = m->nc_10p0 * 1000000; // PM10.0 < 10.0 μm
        data->typical_particle_size = m->typical_particle_size * 1000000;
    }*/

    // Write the appropriate event
    eventWriteSPS30Particulates(m->mc_1p0 * 1000000, m->mc_2p5 * 1000000, m->mc_4p0 * 1000000, m->mc_10p0 * 1000000,
                                m->nc_0p5 * 1000000, m->nc_1p0 * 1000000, m->nc_2p5 * 1000000, m->nc_4p0 * 1000000,
                                m->nc_10p0 * 1000000, m->typical_particle_size * 1000000);

    // Measurement successful
    return true;
}

/* [] END OF FILE */
