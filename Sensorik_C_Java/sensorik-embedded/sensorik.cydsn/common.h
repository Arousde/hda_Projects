/* ========================================
 *
 * Copyright Felix Ohms, 2019
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * ========================================
*/

/* [] END OF FILE */

#ifndef COMMON_H
#define COMMON_H

#include "project.h"
#include <stdlib.h>

#include <stdio.h>                      //!< e.g. for printf


// Own includes

#include "help.h"                       //!< print help text
#include "../src/event.h"               //!< print help text
#include "../src/swsign.h"              //!< some SW setting and signature

// Globals
#define TERMINAL_BUFFER_SIZE 512        //!< size of terminal buffer
char _buffer[TERMINAL_BUFFER_SIZE];     //!< buffer (global) for sprintf

#define EZI2C_SLAVE_ADDRESS (0x08u)     // EZI2C Slave primary address

#define sleep(x) CyDelay(x*1000);       // define sleep
#define usleep(x) CyDelay(x);           // define usleep

static uint32 tickSinceStart = 0;       // Time tick since start (in seconds), enough to timestamp 136 years

#define DATA_INTERVAL 2000              // Interval to poll the sensors in ms

#define SENSOR_INIT_RETRIES 10          // How many times initialising a sensor should be retried

/**
 * Initialise all components needed for I2C communication.
 */
#define I2CSTART() I2C_Master_Start();

/**
 * A boolean to use c++ style since c doesn't have a boolean.
 */
typedef enum{
    false,
    true
} bool;

/**
 * Send a set number of bytes to the specified address via I2C.
 *
 * @param adress The address to write to.
 * @param buffer Pointer to the buffer containing the data to write.
 * @param length How many bytes should be written.
 */
void writeI2C(uint32_t adress, uint8_t* buffer, uint8_t length);

/**
 * Read a set number of bytes from the specified address via I2C.
 *
 * @param adress The address to read from.
 * @param buffer Pointer to the buffer to store the read data.
 * @param length How many bytes should be read.
 */
uint32_t readI2C(uint32_t adress, uint8_t* buffer, uint8_t length);


#define LED_ON  (1u)                    //!< LED value on
#define LED_OFF (0u)                    //!< LED value off

#define USRLED(x) ( Pin_3_4_Write(x) )  //!< Macro for user LED


/**
 * \def PRINTF
 * Macro for convenience. Wraps printf to the requires sprintf(...)
 * and *_PutString()
 *
 * Enter the required function depending on your UART, e.g. UART_UartPutString();
 * @see _buffer
 * Cave! _buffer length must not exeeded by the total length of output!
 *
 * @author Ralf S. Mayer
 * @date 2019-04-06
 * @see https://stackoverflow.com/questions/20639632/how-to-wrap-printf-into-a-function-or-macro
 */
#define PRINTF(f_, ...) sprintf( _buffer, (f_), ##__VA_ARGS__);\
                        Serial_Terminal_UartPutString( _buffer );

/**
 * \def PUTC
 * Macro for convenience. Wraps the required *_PutChar()
 *
 * Enter the required function depending on your UART, e.g. UART_UartPutChar();
 *
 * @author Ralf S. Mayer
 * @date 2019-04-06
 */
#define PUTC(x) ( Serial_Terminal_UartPutChar(x) );

/**
 * Blinking LED
 */
void blinkLED();


#endif /* COMMON_H */
