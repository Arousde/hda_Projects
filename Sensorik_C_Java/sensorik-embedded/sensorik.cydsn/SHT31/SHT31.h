/* ========================================
 *
 * Copyright Felix Ohms, 2019
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * ========================================
 * 
 * The driver used for the GY-SHT31 sensor is from
 * https://github.com/Sensirion/embedded-sht
 * Driver license:
 *
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
 * 
 * ========================================
 */

#include "project.h"
#include "sht.h"
#include "common.h"

/**
 * Initialises the GY-SHT31 Temperature and Humidity sensor.
 * 
 * @returns 0 on success, error code otherwise.
 */
bool SHT31_Init();

/**
 * Measures the temperature and humidity using the GY-SHT31 Sensor.
 * Blocks during the duration of the measurement.
 * 
 * Temperature is in °C.
 * Humidity is in %.
 * 
 * If a nullpr is passed as an argument, that argument will be ignored but
 * the measurement will still be printed to the terminal, if specified.
 * 
 * @param temperature_  pointer to the double in which to write the current temperature.
 * @param humidity_     pointer to the double in which to write the current humidity.
 * @param console_out   true if the measurements should be written to the terminal.
 * @return              0 on success, error code otherwise.
 */
int SHT31_Measure(float* temperature_, float* humidity_);

/**
 * Starts a measurement. Use GY_SHT31_Read_Measurement() to read out the values,
 * once the measurement is done. The duration of the measurement is 15ms.
 * 
 * @return              0 on success, error code otherwise.
 */
int SHT31_Ready_Measurement();

/**
 * Reads out the results of a measurement that was previously started by
 * GY_SHT31_Ready_Measurement(). If the measurement is still in progress, this function
 * returns an error.
 * 
 * Temperature is in °C.
 * Humidity is in %.
 *
 * @param temperature_  pointer to the double in which to write the current temperature.
 * @param humidity_     pointer to the double in which to write the current humidity.
 * @param console_out   true if the measurements should be written to the terminal.
 * @return              0 on success, error code otherwise.
 */
int SHT31_Read_Measurement(float* temperature_, float* humidity_);

/* [] END OF FILE */
