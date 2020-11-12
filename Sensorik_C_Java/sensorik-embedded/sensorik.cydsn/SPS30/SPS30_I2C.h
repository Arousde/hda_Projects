/* ========================================
 *
 * Copyright Felix Ohms, 2019
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * ========================================
*/

#ifndef SPS30_I2C
#define SPS30_I2C

#include "../src/event.h"
#include "sps30.h"
#include "common.h"

/**
 * Initialises the SPS30 sensor and starts its measurement.
 *
 * @return True if successful, false otherwise.
 */
bool SPS30_Init();

/**
 * Reads measurements from the SPS30 sensor.
 *
 * @param m Struct in which to write the measurements.
 * @param data Data structure for communicating measurements to BLE module via I2C.
 * @return True if successful, false otherwise.
 */
bool SPS30_Read_Data(struct sps30_measurement* m);

#endif /* SPS30_I2C */

/* [] END OF FILE */
