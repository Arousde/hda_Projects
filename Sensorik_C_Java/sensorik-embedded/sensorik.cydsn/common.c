/* ========================================
 *
 * Copyright Felix Ohms, 2019
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * ========================================
*/

#include "project.h"
#include "common.h"


/**
 * Send a set number of bytes to the specified address via I2C.
 *
 * @param adress The address to write to.
 * @param buffer Pointer to the buffer containing the data to write.
 * @param length How many bytes should be written.
 */
void writeI2C(uint32_t adress, uint8_t* buffer, uint8_t length) {
    I2C_Master_I2CMasterClearStatus();

    uint32_t err = I2C_Master_I2CMasterWriteBuf(adress, buffer, length, I2C_Master_I2C_MODE_COMPLETE_XFER);
    if(err == I2C_Master_I2C_MSTR_NO_ERROR){
        while((I2C_Master_I2CMasterStatus() & I2C_Master_I2C_MSTAT_WR_CMPLT) == 0u){
        }

    }
}

/**
 * Read a set number of bytes from the specified address via I2C.
 *
 * @param adress The address to read from.
 * @param buffer Pointer to the buffer to store the read data.
 * @param length How many bytes should be read.
 */
uint32_t readI2C(uint32_t adress, uint8_t* buffer, uint8_t length) {
    I2C_Master_I2CMasterClearStatus();

    uint32_t err = I2C_Master_I2CMasterReadBuf(adress, buffer, length, I2C_Master_I2C_MODE_COMPLETE_XFER);
    if(err == I2C_Master_I2C_MSTR_NO_ERROR){
        while((I2C_Master_I2CMasterStatus() & I2C_Master_I2C_MSTAT_RD_CMPLT) == 0u){
        }
    }

    return I2C_Master_I2CMasterGetReadBufSize();
}


/**
 * Blinking LED
 */
void blinkLED() {
    uint8 i;
    for(i = 0; i < 5; i++){
        Pin_3_4_Write(LED_ON);
        CyDelay(100);
        Pin_3_4_Write(LED_OFF);
        CyDelay(100);
    }
}
