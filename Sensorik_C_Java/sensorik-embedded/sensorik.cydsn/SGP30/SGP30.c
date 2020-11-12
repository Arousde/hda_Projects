/*
 * @file Adafruit_SGP30.cpp
 *
 * @mainpage Adafruit SGP30 gas sensor driver
 *
 * @section intro_sec Introduction
 *
 * This is the documentation for Adafruit's SGP30 driver for the
 * Arduino platform.  It is designed specifically to work with the
 * Adafruit SGP30 breakout: http://www.adafruit.com/products/3709
 *
 * These sensors use I2C to communicate, 2 pins (SCL+SDA) are required
 * to interface with the breakout.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 *
 * @section author Author
 * Written by Ladyada for Adafruit Industries.
 * (edited by Maximilian Reinheimer istmxrein)
 *
 * @section license License
 * BSD license, all text here must be included in any redistribution.
 *
 */

#include "project.h"
#include "SGP30.h"
#include "common.h"


/*!
 *  @brief  Setups the hardware and detects a valid SGP30. Initializes I2C
 *          then reads the serialnumber and checks that we are talking to an
 * SGP30
 *  @param  theWire
 *          Optional pointer to I2C interface, otherwise use Wire
 *  @return True if SGP30 found on I2C, False if something went wrong!
 */
uint8_t SGP30begin() {

    uint8_t command[2];
    command[0] = 0x36;
    command[1] = 0x82;
    if(!readWordFromCommand(command, 2, 10, serialnumber, 3)){
        return 0;
    }

    uint16_t featureset;
    command[0] = 0x20;
    command[1] = 0x2F;
    if(!readWordFromCommand(command, 2, 10, &featureset, 1)){
        return 0;
    }

    if(featureset != SGP30_FEATURESET){
        return 0;
    }
    if(!IAQinit()){
        return 0;
    }

    return 1;
}

/*!
 *   @brief  Commands the sensor to begin the IAQ algorithm. Must be called
 * after startup.
 *   @returns True if command completed successfully, false if something went
 *            wrong!
 */
uint8_t IAQinit(void) {
    uint8_t command[2];
    command[0] = 0x20;
    command[1] = 0x03;
    return readWordFromCommand(command, 2, 10, NULL, 0);
}

/*!
 *  @brief  Commands the sensor to take a single eCO2/VOC measurement. Places
 *          results in {@link TVOC} and {@link eCO2}
 *  
 *  @return True if command completed successfully, false if something went
 *          wrong!
 */
uint8_t IAQmeasure() {
    uint8_t command[2];
    command[0] = 0x20;
    command[1] = 0x08;
    uint16_t reply[2];
    if(!readWordFromCommand(command, 2, 12, reply, 2)){
        return 0;
    }
    tvoc = reply[1];
    eCO2 = reply[0];
    return 1;
}

/*!
 *   @brief  Request baseline calibration values for both CO2 and TVOC IAQ
 *           calculations. Places results in parameter memory locaitons.
 *   @param  eco2_base
 *           A pointer to a uint16_t which we will save the calibration
 *           value to
 *   @param  tvoc_base
 *           A pointer to a uint16_t which we will save the calibration value to
 *   @return True if command completed successfully, false if something went
 *           wrong!
 */
uint8_t getIAQBaseline() {
    uint8_t command[2];
    command[0] = 0x20;
    command[1] = 0x15;
    uint16_t reply[2];
    if(!readWordFromCommand(command, 2, 10, reply, 2)){
        return 0;
    }
    eco2_base = reply[0];
    tvoc_base = reply[1];
    return 1;
}

/*!
 *  @brief  Assign baseline calibration values for both CO2 and TVOC IAQ
 *          calculations.
 *  
 *  @return True if command completed successfully, false if something went
 *          wrong!
 */
uint8_t setIAQBaseline(uint16_t eco2_base, uint16_t tvoc_base) {
    uint8_t command[8];
    command[0] = 0x20;
    command[1] = 0x1e;
    command[2] = tvoc_base >> 8;
    command[3] = tvoc_base & 0xFF;
    command[4] = generateCRC(command + 2, 2);
    command[5] = eco2_base >> 8;
    command[6] = eco2_base & 0xFF;
    command[7] = generateCRC(command + 5, 2);

    return readWordFromCommand(command, 8, 10, NULL, 0);
}

/*!
 *  @brief  Set the absolute humidity value [mg/m^3] for compensation to increase
 *          precision of TVOC and eCO2.
 *  @param  absolute_humidity
 *          A uint32_t [mg/m^3] which we will be used for compensation.
 *          If the absolute humidity is set to zero, humidity compensation
 *          will be disabled.
 *  @return True if command completed successfully, false if something went
 *          wrong!
 */

/**
 * @brief  Set the absolute humidity value [mg/m^3] for compensation to increase
 *          precision of TVOC and eCO2.
 *          Calculates the absolute humidity to be used for compensation based on relative humidity,
 *          temperature & approximations.
 *
 * @param relativeHumidity The current relative humidity.
 * @param temperature The current temperature.
 * @return True if command completed successfully, false if something went wrong!
 */
uint8_t setHumidity(const double relativeHumidity, const double temperature) {
    // Calculate absolute humidity based on
    // https://www.vaisala.com/sites/default/files/documents/Humidity_Conversion_Formulas_B210973EN-F.pdf#page=12

    // Approximate constants for the temperature range
    double constants50Degrees[] = {6.116441, 7.59138, 240.726};
    double constants100Degrees[] = {6.004918, 7.337936, 229.3975};

    double absHum, pws, pw;
    uint32_t absolute_humidity;

    // Calculate saturation vapor pressure in hPa
    if((temperature >= -20) && (temperature < 50)){
        pws = constants50Degrees[0] *
              pow(10, (constants50Degrees[1] * temperature / (temperature + constants50Degrees[2])));
    }
    else if((temperature >= 50) && (temperature < 100)){
        pws = constants100Degrees[0] *
              pow(10, (constants100Degrees[1] * temperature / (temperature + constants100Degrees[2])));
    }
    else {
        PRINTF("Not operable temperature range.\r\n");
        return 0;
    }

    // Calculate vapour pressure in Pa
    pw = pws * relativeHumidity / 100;

    // Calculate absolute humidity in g/m^3
    absHum = 2.16679 * pw * 100 / (273.15 + temperature);

    PRINTF("  Absolute humidity: %.3fg/m^3\r\n", absHum);

    // Set absolute humidity in mg/m^3
    absolute_humidity = absHum * 1000;


    if(absolute_humidity > 256000){
        return 0;
    }

    uint16_t ah_scaled =
        (uint16_t)(((uint64_t)absolute_humidity * 256 * 16777) >> 24);
    uint8_t command[5];
    command[0] = 0x20;
    command[1] = 0x61;
    command[2] = ah_scaled >> 8;
    command[3] = ah_scaled & 0xFF;
    command[4] = generateCRC(command + 2, 2);

    return readWordFromCommand(command, 5, 10, NULL, 0);
}


/*!
 *  @brief  I2C low level interfacing
 */
uint8_t readWordFromCommand(uint8_t command[],
                            uint8_t commandLength,
                            uint16_t delayms,
                            uint16_t* readdata,
                            uint8_t readlen) {

    writeI2C(SGP30_I2CADDR_DEFAULT, command, commandLength);

    CyDelay(delayms);

    if(readlen == 0){
        return 1;
    }

    uint8_t replylen = readlen * (SGP30_WORD_LEN + 1);
    uint8_t replybuffer[replylen];

    ;

    if(readI2C(SGP30_I2CADDR_DEFAULT, replybuffer, replylen) != replylen){
        return 0;
    }

    for(uint8_t i = 0; i < readlen; i++){
        uint8_t crc = generateCRC(replybuffer + i * 3, 2);

        if(crc != replybuffer[i * 3 + 2]){
            return 0;
        }
        // success! store it
        readdata[i] = replybuffer[i * 3];
        readdata[i] <<= 8;
        readdata[i] |= replybuffer[i * 3 + 1];

    }
    return 1;
}

uint8_t generateCRC(uint8_t* data, uint8_t datalen) {
    // calculates 8-Bit checksum with given polynomial
    uint8_t crc = SGP30_CRC8_INIT;

    for(uint8_t i = 0; i < datalen; i++){
        crc ^= data[i];
        for(uint8_t b = 0; b < 8; b++){
            if(crc & 0x80){
                crc = (crc << 1) ^ SGP30_CRC8_POLYNOMIAL;
            }
            else {
                crc <<= 1;
            }
        }
    }
    return crc;
}


/**
 * Initialse the SGP30 sensor
 *
 * @return true if successful , false otherwise
 */
bool SGP30_Init() {
    bool init = false;

    PRINTF("Initialize SGP30\r\n");

    for(short i = 1; i < SENSOR_INIT_RETRIES; i++){
        PRINTF("*");
        if(!init){
            init = SGP30begin();
            CyDelay(900);
        }
        CyDelay(100);
    }

    if(init){
        // Print Serialnumber
        PRINTF("\r\nFound SGP30 serial #%d%d%d\r\n\r\n", serialnumber[0], serialnumber[1], serialnumber[2]);
        return true;
    }
    else {
        PRINTF("\r\nSGP30 INIT unsuccessful\r\n\r\n ");
        return false;
    }
}
