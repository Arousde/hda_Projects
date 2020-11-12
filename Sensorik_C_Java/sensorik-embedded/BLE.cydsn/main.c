/**
* main.c
* @author arous oussema
*/


#include <project.h>

#include "BLEProcess.h"
#include "HandleLowPower.h"
#include "../src/event.h"


// I2C slave address of the Main Psoc Chip
#define I2C_SLAVE_ADDRESS  (0x08u)

// Flag if a BLe device is connected, set by the BLE module
extern uint8 deviceConnected;

// Flag if a connected device should be notified on data updates, set by the BLE module
extern uint8 startNotification;

// Flag if the advertisement over BLE should be started again, set by the BLE module
extern uint8 restartAdvertisement;

// Buffer for the I2C Master to write sensor events to
uint8_t dataBuf[EVENT_BUFFER_SIZE];


// Function declarations
int main();

void InitializeSystem(void);

void HandleSensorData(void);


/**
 * Initialises the system and handles BLE & I2C activity.
 *
 * param void
 *
 * @return int 0 on success, error code otherwise.
 *
*/
int main() {
    /* This function will initialize the system resources such as BLE and I2C */
    InitializeSystem();

    for(;;){
        /* Process Event callback to handle BLE events. The events generated and
         * used for this application are inside the 'CustomEventHandler' routine
         */
        CyBle_ProcessEvents();

        if(TRUE == deviceConnected){
            /* After the connection, send new connection parameter to the Client device
             * to run the BLE communication on desired interval. This affects the data rate
             * and power consumption. High connection interval will have lower data rate but
             * lower power consumption. Low connection interval will have higher data rate at
             * expense of higher power. This function is called only once per connection.
             */
            UpdateConnectionParam();

            if(CYBLE_BLESS_STATE_ECO_STABLE == CyBle_GetBleSsState()){

                HandleSensorData();
            }
        }

        if(restartAdvertisement){
            /* Reset 'restartAdvertisement' flag*/
            restartAdvertisement = FALSE;

            /* Start Advertisement and enter Discoverable mode*/
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);

            /* Process the new event */
            CyBle_ProcessEvents();
        }

        #ifdef ENABLE_LOW_POWER_MODE
        /* Put system to Deep sleep, including BLESS, and wakeup on interrupt.
         * The source of the interrupt can be either BLESS Link Layer in case of
         * BLE advertisement and connection or by User Button press during BLE
         * disconnection
         */
        HandleLowPowerMode();
        #endif
    }

    return 0;
}

/**
 * Reads event data from the I2C master & handles the individual events.
 */
void HandleSensorData() {
    // Read event data buffer from I2C master
    uint32_t err = I2C_Master_I2CMasterReadBuf(I2C_SLAVE_ADDRESS, dataBuf, EVENT_BUFFER_SIZE,
                                               I2C_Master_I2C_MODE_COMPLETE_XFER);

    // Make sure there were no errors
    if(err == I2C_Master_I2C_MSTR_NO_ERROR){
        while(0u == (I2C_Master_I2CMasterStatus() & I2C_Master_I2C_MSTAT_RD_CMPLT)){
            CyBle_ProcessEvents();
        }

        uint8 type;
        uint8 stype;
        uint16 len;
        void* pCurrDataBuf = getStartPtr();         // current data buffer, init!
        void* pNextDataBuf = 0;                 // current data buffer

        // Loop through all available events until an EOF event
        do {
            // Get next event or 0 on EOF
            pNextDataBuf = readEvent(pCurrDataBuf, &type, &stype, &len);
            // Handle event types
            if(type == EVTYP_EOF){
                // If the event is an EOF event, break the loop
                break;
            }

            // Handle all other sensor types
            switch(type){
                case EVTYP_AIR_QUALITY:{
                    // Air quality event (organic compounds & equivalent co2)
                    psEvtAirQuality_t psAirQuality = (psEvtAirQuality_t)pCurrDataBuf;

                    if(startNotification & TVOC_CCCD_NTF_BIT_MASK){
                        updateCharValueNot((uint8_t * ) & psAirQuality->tvoc, TVOC_DATA_LEN,
                                           CYBLE_AIRQUALITY_TVOC_CHAR_HANDLE);
                    }
                    else {
                        updateCharValue((uint8_t * ) & psAirQuality->tvoc, TVOC_DATA_LEN,
                                        CYBLE_AIRQUALITY_TVOC_CHAR_HANDLE);
                    }

                    if(startNotification & ECO2_CCCD_NTF_BIT_MASK){
                        updateCharValueNot((uint8_t * ) & psAirQuality->eCO2, ECO2_DATA_LEN,
                                           CYBLE_AIRQUALITY_ECO2_CHAR_HANDLE);
                    }
                    else {
                        updateCharValue((uint8_t * ) & psAirQuality->eCO2, ECO2_DATA_LEN,
                                        CYBLE_AIRQUALITY_ECO2_CHAR_HANDLE);
                    }

                    break;
                }

                case EVTYP_TEMP_HUM:{
                    // Temperature & humidity event
                    psEvtTempHum_t psTempHum = (psEvtTempHum_t)pCurrDataBuf;

                    if(startNotification & TEMP_CCCD_NTF_BIT_MASK){
                        updateCharValueNot((uint8_t * ) & psTempHum->temperature, TEMP_DATA_LEN,
                                           CYBLE_TEMPERATURE_TEMP_CHAR_HANDLE);
                    }
                    else {
                        updateCharValue((uint8_t * ) & psTempHum->temperature, TEMP_DATA_LEN,
                                        CYBLE_TEMPERATURE_TEMP_CHAR_HANDLE);
                    }

                    if(startNotification & HUM_CCCD_NTF_BIT_MASK){
                        updateCharValueNot((uint8_t * ) & psTempHum->humidity, HUM_DATA_LEN,
                                           CYBLE_HUMIDITY_HUM_CHAR_HANDLE);
                    }
                    else {
                        updateCharValue((uint8_t * ) & psTempHum->humidity, HUM_DATA_LEN,
                                        CYBLE_HUMIDITY_HUM_CHAR_HANDLE);
                    }

                    break;
                }

                case EVTYP_PARTICULATES:{
                    // Particulates event
                    psEvtParticulates_t sParticulates = (psEvtParticulates_t)pCurrDataBuf;

                    uint8_t* mass = (uint8_t * ) & sParticulates->MC_PM1p0;
                    uint8_t* amount = (uint8_t * ) & sParticulates->NC_PM0p5;
                    uint8_t* tps = (uint8_t * ) & sParticulates->typical_particle_size;

                    if(startNotification & MASS_CCCD_NTF_BIT_MASK){
                        updateCharValueNot(mass, MASS_DATA_LEN, CYBLE_PARTICULATES_MASS_CHAR_HANDLE);
                    }
                    else {
                        updateCharValue(mass, MASS_DATA_LEN, CYBLE_PARTICULATES_MASS_CHAR_HANDLE);
                    }

                    if(startNotification & AMOUNT_CCCD_NTF_BIT_MASK){
                        updateCharValueNot(amount, AMOUNT_DATA_LEN, CYBLE_PARTICULATES_AMOUNT_CHAR_HANDLE);
                    }
                    else {
                        updateCharValue(amount, AMOUNT_DATA_LEN, CYBLE_PARTICULATES_AMOUNT_CHAR_HANDLE);
                    }

                    if(startNotification & TPS_CCCD_NTF_BIT_MASK){
                        updateCharValueNot(tps, TPS_DATA_LEN, CYBLE_PARTICULATES_TPS_CHAR_HANDLE);
                    }
                    else {
                        updateCharValue(tps, TPS_DATA_LEN, CYBLE_PARTICULATES_TPS_CHAR_HANDLE);
                    }

                    break;
                }

                    // Add more events here for further handling

                default:    // Should not happen, unknown event
                    break;
            } // End switch
            pCurrDataBuf = pNextDataBuf;  // Set next pointer
        } while(pNextDataBuf != 0); // do-while, end on EOF event
    }
    else {
        // TODO: Add error handling for I2C master
    }
}


/**
 * Starts the components used in the project
 *
 * @param void
 *
 * @param void
 *
*/
void InitializeSystem(void) {
    /* Enable global interrupt mask */
    CyGlobalIntEnable;

    /* Start BLE component and register the CustomEventHandler function. This
    * function exposes the events from BLE component for application use */
    CyBle_Start(GeneralEventHandler);

    /* Begin I2C master component operation */
    I2C_Master_Start();

    setDataPtr(dataBuf);

    // !!! Save storage start address and size !!!
    setStorageStartPtr(dataBuf, EVENT_BUFFER_SIZE);
}
