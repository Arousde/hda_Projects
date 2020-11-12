/*!
 * @file Adafruit_SGP30.h
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
 * Written by Ladyada for Adafruit Industries.
 * (edited by Maximilian Reinheimer istmxrein)
 *
 * BSD license, all text here must be included in any redistribution.
 *
*/

#ifndef SGP30_H
#define SGP30_H

#include "project.h"
#include "common.h"

// the i2c address
#define SGP30_I2CADDR_DEFAULT 0x58     ///< SGP30 has only one I2C address

// commands and constants
#define SGP30_FEATURESET       0x0020  ///< The required set for this library
#define SGP30_CRC8_POLYNOMIAL  0x31    ///< Seed for SGP30's CRC polynomial
#define SGP30_CRC8_INIT        0xFF    ///< Init value for CRC
#define SGP30_WORD_LEN         2       ///< 2 bytes per word

/*!  
 *  @brief  Class that stores state and functions for interacting with 
 *          SGP30 Gas Sensor 
 */
uint8_t SGP30begin();

uint8_t IAQinit(void);

/** @brief Get Data from Sensor */
uint8_t IAQmeasure();

uint8_t getIAQBaseline();

uint8_t setIAQBaseline(uint16_t eco2_base, uint16_t tvoc_base);

uint8_t setHumidity(const double relativeHumidity, const double temperature);

/** The 48-bit serial number, this value is set when you call {@link begin()} **/
uint16_t serialnumber[3];

uint16_t tvoc;      //Total Volatile Organic Compounds in ppb
uint16_t eCO2;      //equivalent CO2 in ppm

uint16_t eco2_base;
uint16_t tvoc_base;

uint8_t
readWordFromCommand(uint8_t command[], uint8_t commandLength, uint16_t delay, uint16_t* readdata, uint8_t readlen);

uint8_t generateCRC(uint8_t data[], uint8_t datalen);

void printSGP30Baseline();

/**
 * Initialse the SGP30 sensor
 * @return true if successful , false otherwise
 */
bool SGP30_Init();

#endif /*ADAFRUIT_SGP30_H */ 
