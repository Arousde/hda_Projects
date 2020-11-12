/* 
 * Copyright arous oussema
 *
*/

#include "BLEProcess.h"

/**************************Variable Declarations*****************************/

/* 'deviceConnected' flag is used by application to know whether a Central device
 * has been connected. This is updated in BLE event callback
 */
uint8 deviceConnected = FALSE;

/* 'startNotification' flag is set when the central device writes to CCC (Client
 * Characteristic Configuration) to enable notifications
 */
uint8 startNotification = FALSE;

/* 'connectionHandle' is handle to store BLE connection parameters */
CYBLE_CONN_HANDLE_T connectionHandle;

/* 'restartAdvertisement' flag provided the present state of power mode in firmware */
uint8 restartAdvertisement = FALSE;

/* This flag is used to let application send a L2CAP connection update request
 * to Central device
 */
static uint8 isConnectionUpdateRequested = TRUE;

/* Connection Parameter update values. This values are used by the BLE component
 * to update the connector parameter, including connection interval, to desired
 * value
 */
static CYBLE_GAP_CONN_UPDATE_PARAM_T ConnectionParam =
    {
        CONN_PARAM_UPDATE_MIN_CONN_INTERVAL,
        CONN_PARAM_UPDATE_MAX_CONN_INTERVAL,
        CONN_PARAM_UPDATE_SLAVE_LATENCY,
        CONN_PARAM_UPDATE_SUPRV_TIMEOUT
    };

/* Status flag for the Stack Busy state. This flag is used to notify the application
 * whether there is stack buffer free to push more data or not
 */
uint8 busyStatus = 0;

/****************************************************************************/

    
/**
 * Toggles Notification for a given Ble characteristic
 *
 * @param wrReqParam Structure to store data written by Client
 * @param index Client Characteristic Configuration Descriptor Index 
 * @param notification Bitmask for the characteristic
 * @param handle Handle for the CCCD Descriptor  
 *
 * @return void 
 *
*/ 
void toggleNotification(CYBLE_GATTS_WRITE_REQ_PARAM_T* wrReqParam, uint16_t index, uint8_t bitmask, uint32_t handle) {

    CYBLE_GATT_HANDLE_VALUE_PAIR_T notificationCCCDhandle;

    /* Set flag so that application can start sending notifications.*/
    if(0x01 == wrReqParam->handleValPair.value.val[index]){
        startNotification = startNotification | bitmask;
    }
    else {
        startNotification = startNotification & (~bitmask);
    }
    /* Update CCCD handle with notification status data*/
    notificationCCCDhandle.attrHandle = handle;
    notificationCCCDhandle.value.val = wrReqParam->handleValPair.value.val;
    notificationCCCDhandle.value.len = CCC_DATA_LEN;

    /* Report data to BLE component for sending data when read by Central device */
    CyBle_GattsWriteAttributeValue(&notificationCCCDhandle, ZERO, &connectionHandle, CYBLE_GATT_DB_PEER_INITIATED);

}

/**
 * Disable notification for a given characteristic
 *
 * @param handle Handle to the CCCD Descriptor of the characteristic
 * 
 * @return void
*/
void stopNotification(uint32_t handle) {
    CYBLE_GATT_HANDLE_VALUE_PAIR_T notificationCCCDhandle;

    notificationCCCDhandle.attrHandle = handle;
    notificationCCCDhandle.value.val = 0;
    notificationCCCDhandle.value.len = CCC_DATA_LEN;

    /* Report data to BLE component for sending data when read by Central device */
    CyBle_GattsWriteAttributeValue(&notificationCCCDhandle, ZERO, &connectionHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
}


/**
 * Handle the BLE Events. Gets called by the BLE Stack
 * 
 * @param event BLE Event
 * @param eventParam Parameter of the current Event
 *
*/
void GeneralEventHandler(uint32 event, void* eventParam) {

    /* Structure to store data written by Client */
    CYBLE_GATTS_WRITE_REQ_PARAM_T* wrReqParam;

    /* Local variable to store the current CCCD value */

    switch(event){
        case CYBLE_EVT_STACK_ON:
            /* This event is generated when BLE stack is ON */
            restartAdvertisement = TRUE;

            break;


            /**********************************************************
            *                       GAP Events
            ***********************************************************/
        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
            if(CyBle_GetState() == CYBLE_STATE_DISCONNECTED){
                restartAdvertisement = TRUE;
            }
            break;

        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
            /* This event is received when device is connected over GAP layer */

            break;
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            /* This event is received when device is disconnected */
            restartAdvertisement = TRUE;

            break;

            /**********************************************************
            *                       GATT Events
            ***********************************************************/

        case CYBLE_EVT_GATT_CONNECT_IND:
            /* This event is received when device is connected over GATT level */

            /* Update attribute handle on GATT Connection*/
            connectionHandle = *(CYBLE_CONN_HANDLE_T*)eventParam;

            /* This flag is used in application to check connection status */
            deviceConnected = TRUE;

            BleLedBlue_Write(LED_ON);

            break;

        case CYBLE_EVT_GATT_DISCONNECT_IND:
            /* This event is received when device is disconnected. Update connection flag accordingly */
            deviceConnected = FALSE;

            /* Reset notification flag to prevent further notifications
             * being sent to Central device after next connection.
             */
            startNotification = FALSE;

            /* Update CCCD handle with notification status data */
            stopNotification(CYBLE_AIRQUALITY_TVOC_CCCD_DESC_HANDLE);

            /* Update CCCD handle with notification status data */
            stopNotification(CYBLE_AIRQUALITY_ECO2_CCCD_DESC_HANDLE);

            stopNotification(CYBLE_TEMPERATURE_TEMP_CCCD_DESC_HANDLE);

            stopNotification(CYBLE_HUMIDITY_HUM_CCCD_DESC_HANDLE);

            stopNotification(CYBLE_PARTICULATES_AMOUNT_CCCD_DESC_HANDLE);

            stopNotification(CYBLE_PARTICULATES_MASS_CCCD_DESC_HANDLE);

            stopNotification(CYBLE_PARTICULATES_TPS_CCCD_DESC_HANDLE);

            /* Reset the isConnectionUpdateRequested flag to allow sending
             * connection parameter update request in next connection
             */
            isConnectionUpdateRequested = TRUE;

            BleLedBlue_Write(LED_OFF);

            break;

        case CYBLE_EVT_GATTS_WRITE_REQ:

            /* When this event is triggered, the peripheral has received
             * a write command on the custom characteristic
             */

            /* Extract the write value from the event parameter */
            wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T*)eventParam;

            // Extract the characteristic the Client has written on and update Notification Parameter
            if(CYBLE_AIRQUALITY_TVOC_CCCD_DESC_HANDLE == wrReqParam->handleValPair.attrHandle){
                toggleNotification(wrReqParam,
                                   CYBLE_AIRQUALITY_TVOC_CCCD_DESC_INDEX,
                                   TVOC_CCCD_NTF_BIT_MASK,
                                   CYBLE_AIRQUALITY_TVOC_CCCD_DESC_HANDLE);
            }

            if(CYBLE_AIRQUALITY_ECO2_CCCD_DESC_HANDLE == wrReqParam->handleValPair.attrHandle){
                toggleNotification(wrReqParam,
                                   CYBLE_AIRQUALITY_ECO2_CCCD_DESC_INDEX,
                                   ECO2_CCCD_NTF_BIT_MASK,
                                   CYBLE_AIRQUALITY_ECO2_CCCD_DESC_HANDLE);
            }

            if(CYBLE_TEMPERATURE_TEMP_CCCD_DESC_HANDLE == wrReqParam->handleValPair.attrHandle){
                toggleNotification(wrReqParam,
                                   CYBLE_TEMPERATURE_TEMP_CCCD_DESC_INDEX,
                                   TEMP_CCCD_NTF_BIT_MASK,
                                   CYBLE_TEMPERATURE_TEMP_CCCD_DESC_HANDLE);
            }

            if(CYBLE_HUMIDITY_HUM_CCCD_DESC_HANDLE == wrReqParam->handleValPair.attrHandle){
                toggleNotification(wrReqParam,
                                   CYBLE_HUMIDITY_HUM_CCCD_DESC_INDEX,
                                   HUM_CCCD_NTF_BIT_MASK,
                                   CYBLE_HUMIDITY_HUM_CCCD_DESC_HANDLE);
            }

            if(CYBLE_PARTICULATES_MASS_CCCD_DESC_HANDLE == wrReqParam->handleValPair.attrHandle){
                toggleNotification(wrReqParam,
                                   CYBLE_PARTICULATES_MASS_CCCD_DESC_INDEX,
                                   MASS_CCCD_NTF_BIT_MASK,
                                   CYBLE_PARTICULATES_MASS_CCCD_DESC_HANDLE);
            }

            if(CYBLE_PARTICULATES_AMOUNT_CCCD_DESC_HANDLE == wrReqParam->handleValPair.attrHandle){
                toggleNotification(wrReqParam,
                                   CYBLE_PARTICULATES_AMOUNT_CCCD_DESC_INDEX,
                                   AMOUNT_CCCD_NTF_BIT_MASK,
                                   CYBLE_PARTICULATES_AMOUNT_CCCD_DESC_HANDLE);
            }

            if(CYBLE_PARTICULATES_TPS_CCCD_DESC_HANDLE == wrReqParam->handleValPair.attrHandle){
                toggleNotification(wrReqParam,
                                   CYBLE_PARTICULATES_TPS_CCCD_DESC_INDEX,
                                   TPS_CCCD_NTF_BIT_MASK,
                                   CYBLE_PARTICULATES_TPS_CCCD_DESC_HANDLE);
            }

            CyBle_GattsWriteRsp(connectionHandle);

            break;

        case CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_RSP:
            /* If L2CAP connection parameter update response received, reset application flag */
            isConnectionUpdateRequested = FALSE;
            break;


        case CYBLE_EVT_STACK_BUSY_STATUS:
            /* This event is generated when the internal stack buffer is full and no more
             * data can be accepted or the stack has buffer available and can accept data.
             * This event is used by application to prevent pushing lot of data to stack.
             */

            /* Extract the present stack status */
            busyStatus = *(uint8*)eventParam;
            break;

        default:
            break;
    }
}

/**
 * Updates the Notification Value of a specific characteristic
 *
 * @param data new Value of characteristic
 * @param len length of data
 * @param attrHandle Handle for the characteristic
*/ 
void updateCharValueNot(uint8_t* data, uint16_t len, uint16_t attrHandle) {

    CYBLE_GATTS_HANDLE_VALUE_NTF_T notificationHandle;

    if(busyStatus == CYBLE_STACK_STATE_FREE){
        notificationHandle.attrHandle = attrHandle;
        notificationHandle.value.val = data;
        notificationHandle.value.len = len;

        CyBle_GattsNotification(connectionHandle, &notificationHandle);
    }
}


/**
 * Updates the Value of a specific characteristic
 *
 * @param data new Value of characteristic
 * @param len length of data
 * @param attrHandle Handle for the characteristic
*/ 
void updateCharValue(uint8_t* data, uint16_t len, uint16_t attrHandle) {
    /* 'rgbHandle' stores RGB control data parameters */
    CYBLE_GATT_HANDLE_VALUE_PAIR_T charHandle;

    if(busyStatus == CYBLE_STACK_STATE_FREE){
        charHandle.attrHandle = attrHandle;
        charHandle.value.val = data;
        charHandle.value.len = len;

        CyBle_GattsWriteAttributeValue(&charHandle, 0, NULL, CYBLE_GATT_DB_LOCALLY_INITIATED);
    }
}


/**
 * Send the Connection Update Request to Client device after connection
 * and modify the connection interval for low power operation.
 *
 * @param void
 * @return void
 *
 */
void UpdateConnectionParam(void) {
    /* If device is connected and Update connection parameter not updated yet,
     * then send the Connection Parameter Update request to Client.
     */
    if(deviceConnected && isConnectionUpdateRequested){
        /* Reset the flag to indicate that connection Update request has been sent */
        isConnectionUpdateRequested = FALSE;

        /* Send Connection Update request with set Parameter */
        CyBle_L2capLeConnectionParamUpdateRequest(connectionHandle.bdHandle, &ConnectionParam);
    }
}

/* [] END OF FILE */
