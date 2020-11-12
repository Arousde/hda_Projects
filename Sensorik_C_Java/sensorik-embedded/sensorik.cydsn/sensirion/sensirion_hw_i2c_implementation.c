/*
 * Copyright (c) 2018, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "sensirion_arch_config.h"
#include "sensirion_i2c.h"

#include "common.h"
#include "project.h"

/*
 * INSTRUCTIONS
 * ============
 *
 * Implement all functions where they are marked as IMPLEMENT.
 * Follow the function specification in the comments.
 */

/**
 * Initialize all hard- and software components that are needed for the I2C
 * communication.
 */
void sensirion_i2c_init() {
    // IMPLEMENT
    // Initialised in main.c
    // For initialisation procedure, see
}

/**
 * Execute one read transaction on the I2C bus, reading a given number of bytes.
 * If the device does not acknowledge the read command, an error shall be
 * returned.
 *
 * @param address 7-bit I2C address to read from.
 * @param data    Pointer to the buffer where the data is to be stored.
 * @param count   Number of bytes to read from I2C and store in the buffer.
 * @returns 0 on success, error code otherwise.
 */
int8_t sensirion_i2c_read(uint8_t address, uint8_t* data, uint16_t count) {
    // IMPLEMENT
    uint32 err;
    I2C_Master_I2CMasterClearStatus();  // Clear the I2C Masters status to get it ready for next use

    // Notify the I2C slave of the read operation
    err = I2C_Master_I2CMasterSendStart(address, I2C_Master_I2C_READ_XFER_MODE, 50);
    if(err != I2C_Master_I2C_MSTR_NO_ERROR){  // Check if an error has occurred
        I2C_Master_I2CMasterSendStop(50);     // End the transmission
        return err;                           // Return the error code
    }

    // For each byte that should be read
    for(uint16_t i = 0; i < count - 1; i++){
        // Read a single byte while signaling the I2C slave to continue writing
        err = I2C_Master_I2CMasterReadByte(I2C_Master_I2C_ACK_DATA, data, 50);
        if(err != I2C_Master_I2C_MSTR_NO_ERROR){  // Check if an error has occurred
            I2C_Master_I2CMasterSendStop(50);     // End the transmission
            return err;                           // Return the error code
        }
        data++;  // Increment the buffer to write the next byte to
    }

    // Read a single byte while signaling the I2C slave to stop writing
    err = I2C_Master_I2CMasterReadByte(I2C_Master_I2C_NAK_DATA, data, 50);
    if(err != I2C_Master_I2C_MSTR_NO_ERROR){  // Check if an error has occurred
        I2C_Master_I2CMasterSendStop(50);     // End the transmission
        return err;                           // Return the error code
    }

    // End the transmission
    I2C_Master_I2CMasterSendStop(50);
    if(err != I2C_Master_I2C_MSTR_NO_ERROR){  // Check if an error has occurred
        return err;                           // Return the error code
    }

    // Read operation finished successfully
    return 0;
}

/**
 * Execute one write transaction on the I2C bus, sending a given number of
 * bytes. The bytes in the supplied buffer must be sent to the given address. If
 * the I2C slave device does not acknowledge any of the bytes, an error shall be
 * returned.
 *
 * @param address 7-bit I2C address to write to.
 * @param data    pointer to the buffer containing the data to write.
 * @param count   number of bytes to read from the buffer and send over I2C.
 * @returns 0 on success, error code otherwise.
 */
int8_t sensirion_i2c_write(uint8_t address, const uint8_t* data, uint16_t count) {
    // IMPLEMENT
    //PRINTF("Writing to address %#X\r\n", address);
    
    uint32 err;
    I2C_Master_I2CMasterClearStatus();  // Clear the I2C Masters status to get it ready for next use

    // Notify the I2C slave of the write operation
    err = I2C_Master_I2CMasterSendStart(address, I2C_Master_I2C_WRITE_XFER_MODE, 50);
    if(err != I2C_Master_I2C_MSTR_NO_ERROR){  // Check if an error has occurred
        I2C_Master_I2CMasterSendStop(50);     // End the transmission
        return err;                           // Return the error code
    }

    // For each byte that should be written
    for(uint16_t i = 0; i < count; i++){
        // Write a single byte
        err = I2C_Master_I2CMasterWriteByte(*data, 50);
        if(err != I2C_Master_I2C_MSTR_NO_ERROR){  // Check if an error has occurred
            I2C_Master_I2CMasterSendStop(50);     // End the transmission
            return err;                           // Return the error code
        }
        data++;  // Increment the buffer to read the next byte from
    }

    // End the transmission
    err = I2C_Master_I2CMasterSendStop(50);
    if(err != I2C_Master_I2C_MSTR_NO_ERROR){  // Check if an error has occurred
        return err;                           // Return the error code
    }

    // Write operation finished successfully
    return 0;
}

/**
 * Sleep for a given number of microseconds. The function should delay the
 * execution for at least the given time, but may also sleep longer.
 *
 * Despite the unit, a <10 millisecond precision is sufficient.
 *
 * @param useconds the sleep time in microseconds.
 */
void sensirion_sleep_usec(uint32_t useconds) {
    // IMPLEMENT
    CyDelay(useconds / 1000);
}
