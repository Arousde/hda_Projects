/* 
 * Copyright arous oussema
 *
*/
#ifndef BLEPROCESS_H
#define BLEPROCESS_H

#include "project.h"

/*************************Pre-processor directives****************************/
    
/* 'ENABLE_LOW_POWER_MODE' pre-processor directive enables the low power mode
 * handling in the firmware, ensuring low power consumption during project usage.
 * To disable, comment the following #define.
 * If disabled, prevent usage of the project with coin cell
 */
#define ENABLE_LOW_POWER_MODE

/****************************************************************************/

        
/**************************Function Declarations*****************************/

void CustomEventHandler(uint32 event, void* eventParam);

void SendDataOverCapSenseSliderNotification(uint8 sliderValue);

void SendDataOverCapSenseButtonNotification(uint8* buttonValue);

void UpdateConnectionParam(void);

/****************************************************************************/


/***************************Macro Definitions*******************************/

#define TRUE     1
#define FALSE    0
#define ZERO     0

/* EZ-BLE Chip Led States */
#define LED_ON   0
#define LED_OFF  1


/* Data length of CapSense Slider and Button data sent over notification */
#define TVOC_DATA_LEN       2
#define ECO2_DATA_LEN       2
#define HUM_DATA_LEN        4
#define TEMP_DATA_LEN       4
#define MASS_DATA_LEN       16
#define AMOUNT_DATA_LEN     20
#define TPS_DATA_LEN        4


/* Bit mask for notification bit in CCCD (Client Characteristic 
 * Configuration Descriptor) written by Client device.
 */
#define TVOC_CCCD_NTF_BIT_MASK              (0x01 << 0)
#define ECO2_CCCD_NTF_BIT_MASK              (0x01 << 1)
#define HUM_CCCD_NTF_BIT_MASK               (0x01 << 2)
#define TEMP_CCCD_NTF_BIT_MASK              (0x01 << 3)
#define AMOUNT_CCCD_NTF_BIT_MASK            (0x01 << 4)
#define MASS_CCCD_NTF_BIT_MASK              (0x01 << 5)
#define TPS_CCCD_NTF_BIT_MASK               (0x01 << 6)


/* Client Characteristic Configuration descriptor data length. This is defined
 * as per BLE spec.
 */
#define CCC_DATA_LEN                        2

/* Connection Update Parameter values to modify connection interval. These values
 * are sent as part of CyBle_L2capLeConnectionParamUpdateRequest() which requests
 * Client to update the existing Connection Interval to new value. Increasing
 * connection interval will reduce data rate but will also reduce power consumption.
 * These numbers will influence power consumption
 */

/* Minimum connection interval = CONN_PARAM_UPDATE_MIN_CONN_INTERVAL * 1.25 ms*/
#define CONN_PARAM_UPDATE_MIN_CONN_INTERVAL    40
/* Maximum connection interval = CONN_PARAM_UPDATE_MAX_CONN_INTERVAL * 1.25 ms */
#define CONN_PARAM_UPDATE_MAX_CONN_INTERVAL    42
/* Slave latency = Number of connection events */
#define CONN_PARAM_UPDATE_SLAVE_LATENCY        4
/* Supervision timeout = CONN_PARAM_UPDATE_SUPRV_TIMEOUT * 10*/
#define CONN_PARAM_UPDATE_SUPRV_TIMEOUT        200

/****************************************************************************/

/** @brief Handles Bluetooth Events*/
void GeneralEventHandler(uint32 event, void* eventParam);

/** @brief Sets Notification for given BLE characteristic */
void toggleNotification(CYBLE_GATTS_WRITE_REQ_PARAM_T* wrReqParam, uint16_t index, uint8_t bitmask, uint32_t handle);

/** @brief Disable Notification for a given characteristic */
void stopNotification(uint32_t handle);

/** @brief Sets Notification Value for a given characteristic */
void updateCharValueNot(uint8_t* data, uint16_t len, uint16_t attrHandle);

/** @brief Sets Value of characteristic */
void updateCharValue(uint8_t* data, uint16_t len, uint16_t attrHandle);

/** @brief Modify Connection for Low Power Operation */
void UpdateConnectionParam(void);


#endif /* BLEPROCESS_H*/

/* [] END OF FILE */
