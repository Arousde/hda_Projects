/* ========================================
 *
 * Copyright Felix Ohms, 2019
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * ========================================
 * 
 * For documentation, see SHT31.h
 */

#include "SHT31.h"
#include "common.h"

bool SHT31_Init() {
    // See if there is a SHT31 sensor connected
    int err = sht_probe();

    for(short i = 1; err != STATUS_OK; i++){
        // Try 10x to get the sensor, then return false
        PRINTF("SHT31 sensor probing failed, ");
        if(i >= SENSOR_INIT_RETRIES){
            // 10th time reached, aborting
            PRINTF("aborting\r\n\r\n");
            return false;
        }
        PRINTF("retrying %d more times\r\n", SENSOR_INIT_RETRIES - i);
        sleep(1);
        err = sht_probe();
    }

    // SHT31 initialisation successful
    PRINTF("SHT31 sensor probing successful\r\n\r\n");
    return true;
}

int SHT31_Measure(float* temperature_, float* humidity_) {
    // Variables to store the data from the sensor
    int32_t temperature, humidity;

    // Get measurements from the sensor
    int err = sht_measure_blocking_read(&temperature, &humidity);

    if(err == STATUS_OK){
        // Get the measurement into a form that can be returned
        if(temperature_ != NULL){                     // Avoid writing to a nullptr
            *temperature_ = temperature / 1000.0;     // Use this to work with further
        }

        if(humidity_ != NULL){                        // Avoid writing to a nullptr
            *humidity_ = humidity / 1000.0;           // Use this to work with further
        }

        // Write the appropriate event
        eventWriteSHT31TempHum(temperature, humidity);

        // If there were no errors, return 0
        return 0;
    }
    else {
        // An error occurred during the measurement
        Serial_Terminal_UartPutString("Error reading measurement from SHT31.\r\n");
        return err;
    }
}

int SHT31_Ready_Measurement() {
    // Tell the sensor to start a measurement
    int err = sht_measure();

    if(err != STATUS_OK){
        // An error occurred during the measurement start
        Serial_Terminal_UartPutString("An error occurred while starting a measurement from SHT31.\r\n");
        return err;
    }
    return 0;
}

int SHT31_Read_Measurement(float* temperature_, float* humidity_) {
    // Variables to store the data from the sensor
    int32_t temperature, humidity;

    // Get measurements from the sensor
    int err = sht_read(&temperature, &humidity);

    if(err == STATUS_OK){
        // Get the measurement into a form that can be returned
        if(temperature_ != NULL){                     // Avoid writing to a nullptr
            *temperature_ = temperature / 1000.0;     // Use this to work with further
        }

        if(humidity_ != NULL){                        // Avoid writing to a nullptr
            *humidity_ = humidity / 1000.0;           // Use this to work with further
        }

        // Write the appropriate event
        eventWriteSHT31TempHum(temperature, humidity);

        // If there were no errors, return 0
        return 0;
    }
    else {
        // An error occurred during the measurement
        Serial_Terminal_UartPutString("Error reading measurement from SHT31.\r\n");
        return err;
    }
}

/* [] END OF FILE */
