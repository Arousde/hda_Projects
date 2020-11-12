/* ========================================
 *
 * Copyright Felix Ohms, 2019
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * ========================================
 *
 * Keep this file as small and simple as possible.
 * It massively improves readability.
*/

// General libraries
#include <stdio.h>

// General project files
#include "project.h"
#include "help.h"
#include "common.h"
#include "../src/event.h"


// Sensors
// SHT31
#include "SHT31.h"

// SGP30
#include "SGP30.h"

// SPS30
#include "SPS30_I2C.h"

/**
 * Handles a character input on the terminal.
 *
 * @param ch The character that has been entered.
 */
void terminalInputChar(uint8 ch);

char dataBuf[EVENT_BUFFER_SIZE];     // 2k data buffer


/**
 * Interrupt service routine for UART_SCB internal interrupt.
 *
 * Triggered when a character is written to he terminal.
 *
 * @see _rx_char
 */
CY_ISR( isr_UART_RX_handler ){
    static uint8 _rx_char = 0;              //!< rx input character
    static uint8 _rx_char_cpy;
    _rx_char = Serial_Terminal_UartGetChar();
    /* clear interrupt source! */
    Serial_Terminal_CLEAR_INTR_RX( Serial_Terminal_GetRxInterruptSource());


    /* +++ UART char input +++
     * must be handled before next interrupt
     * (otherwise _rx_char is overwritten)
     */
    if(_rx_char != 0u)               /* got a UART char ... */
    {
        Serial_Terminal_SCB_IRQ_Disable();          /* Disable UART SCB internal interrupt */
        _rx_char_cpy = _rx_char;
        _rx_char = 0u;                  /* clear input */
        Serial_Terminal_SCB_IRQ_Enable();          /* Enable UART SCB internal interrupt */
    }

    terminalInputChar(_rx_char_cpy);  // Handle the entered character accordingly
}

/**
 * Interrupt service routine for SW1 user button interrupt.
 *
 * @see _rx_char
 */
CY_ISR( isr_SW1_handler ) {
    static int8 _sw1Flag = 0;               //!< User Button SW1 flag

    // read the pin state. 0: reseased, 1: pressed
    _sw1Flag = (Pin_3_7_Read()) ? (-1) : (1);
    /* clear interrupt source! Don't forget! */
    Pin_3_7_ClearInterrupt();


    // User Button pressed or released?
    if(_sw1Flag != 0){
        // print '+' for pressed and '-' for released on terminal
        Serial_Terminal_UartPutChar((_sw1Flag < 0) ? '-' : '+');
        _sw1Flag = 0;
    }
}

/**
 * Interrupt service routine for isr_tick interrupt.
 *
 * @see _rx_char
 */
CY_ISR( isr_time_tick_handler ) {
    tickSinceStart++;   // increment tick counter
    if((tickSinceStart % 2) == 0){
        USRLED(LED_ON);
    }else{
        USRLED(LED_OFF);
    }
    /* clear interrupt source! Don't forget! */
//    Timer_Tick_ClearInterrupt( Timer_Tick_INTR_MASK_CC_MATCH );
    Timer_Tick_ClearInterrupt( Timer_Tick_INTR_MASK_TC );
}


int main(void) {
    // Initialise general stuff for the project
    CyGlobalIntEnable; // Enable global interrupts.

    // UART
    Serial_Terminal_Start(); // Initialise the UART used for printing output to the terminal
    Serial_Terminal_SCB_IRQ_StartEx(isr_UART_RX_handler);    // Start UART SCB internal interrupt
    isr_SW1_StartEx(isr_SW1_handler); // Start User Button SW1 interrupt

    // I2C
    I2CSTART();     // Initialise the I2C Master
    EZI2C_Start();  // Initialise the I2C Slave

    // Timer
    Timer_Tick_Start();
    isr_tick_StartEx(isr_time_tick_handler);

    // Blink the LED on the board to give hardware feedback that the program started
    blinkLED();
    // Make space on the terminal for better readability where a restart occurs
    PRINTF("\r\n\r\nNew Run\r\n\r\n");

    /*************** Variable Definitions *******************/
    // Indicators whether each sensor is present
    bool SHT31 = false;
    bool SGP30 = false;
    bool SPS30 = false;

    bool SHT31newMeasurement = false;
    bool SGP30newMeasurement = false;
    bool SPS30newMeasurement = false;

    // Variables to store the last measurements of each sensor
    // SHT31
    float temperature = 0;
    float humidity = 0;
    // SPS30
    struct sps30_measurement m;
    // SPG30 is dynamic
    /******************************************************/


    /********** Initialise the individual sensors **********/
    // GY-SHT31  (temperature & humidity)
    SHT31 = SHT31_Init();
    // SGP30  (organic compounds & equivalent co2)
    SGP30 = SGP30_Init();
    // SPS30  (Particulates)
    SPS30 = SPS30_Init();
    /*******************************************************/

    sleep(1);

    /***************** Inititalize Events ******************/
    displayEvtSubevtTypes();                    // show evt types and subtypes
    // +++ Test event +++
    // !!! set data buffer to start address (for writing) !!!
    setDataPtr(dataBuf);
    // !!! Save storage start address and size !!!
    setStorageStartPtr(dataBuf, sizeof(dataBuf));
    /******************************************************/

    //set EZI2C Buffer
    EZI2C_EzI2CSetBuffer1(EVENT_BUFFER_SIZE, EVENT_BUFFER_SIZE, (uint8_t*)dataBuf);

    // Give the user some time to read the startup information
    PRINTF("\r\n");
    CyDelay(5000);

    /********************* Measure every couple seconds ***********************/
    for(uint32_t count = 31; true; count++){

        // TODO: remove this to store multiple events of the same type
        //resetEventBuffer();

        // Disable interrupts for the EZI2C Slave until measurements of all sensors are complete
        EZI2C_DisableInt();

        // Get the measurements
        if(SHT31){ // Check if the SHT31 sensor has been initialised successfully
            // Get measurements from the SHT31 sensor
            short err = SHT31_Measure(&temperature, &humidity);
            if(err == STATUS_OK){
                SHT31newMeasurement = true;
            }

        }

        if(SGP30){ // Check if the SGP30 sensor has been initialised successfully
            // Get measurements from the SGP30 sensor
            if(IAQmeasure()){
                writeAirQualityEvt(EVSUBTYP_SGP30, eCO2, tvoc);
                SGP30newMeasurement = true;
            }
            else {
                PRINTF("SPG30 measure failed\r\n");
            }
        }

        if(SPS30){  // Check if the SGP30 sensor has been initialised successfully
            // Get measurements from the SPS30 sensor
            if(SPS30_Read_Data(&m)){
                SPS30newMeasurement = true;
            }
        }


        // Enable interrupts for EZI2C since measurements are complete
        EZI2C_EnableInt();


        // Print the measurements to the terminal
        // Check if there is a new SHT31 measurement
        if(SHT31newMeasurement){
            // Reset the new SHT31 measurement flag
            SHT31newMeasurement = false;
            // Print the measurement to the terminal
            PRINTF("Temperature: %-.3fC\r\nHumidity:    %-.3f%% \r\n", temperature, humidity);
        }

        // Check if there is a new SGP30 measurement
        if(SGP30newMeasurement){
            // Reset the new SGP30 measurement flag
            SGP30newMeasurement = false;
            // Print the measurement to the terminal
            PRINTF("TVOC %dppb\teCO2: %dppm\r\n", tvoc, eCO2);
            // Every 30 steps print baseline value & set absolute humidity
            if((count % 30) == 0){
                if(getIAQBaseline()){
                    PRINTF("  Baseline values: eCO2: 0x%X & TVOC: 0x%X**\r\n", eco2_base, tvoc_base);
                    // Reset the counter
                    count  = 0;
                }
                else {
                    PRINTF("Failed to get Baselinereadings\r\n");
                }
                setHumidity(humidity, temperature);
            }
            else if(count == 31){
                // Only gets executed on the first loop
                setHumidity(humidity, temperature);
            }
        }

        // Check if there is a new SPS30 measurement
        if(SPS30newMeasurement){
            // Reset the new SPS30 measurement flag
            SPS30newMeasurement = false;
            // Print the measurement to the terminal
            PRINTF("Mass concentration:\r\n"
                   // Mass concentration in μg/m^3 (Micrograms per cubic meter);  μ = 10^-6
                   "\t%0.2f ug/m^3 MC PM1.0 \r\n" // PM1.0  < 1.0 μm (Micrometer)
                   "\t%0.2f ug/m^3 MC PM2.5\r\n"  // PM2.5  < 2.5 μm
                   "\t%0.2f ug/m^3 MC PM4.0\r\n"  // PM4.0  < 4.0 μm
                   "\t%0.2f ug/m^3 MC PM10.0\r\n" // PM10.0 < 10.0 μm
                   "Number concentration:\r\n"
                   // Amount per cm^3
                   "\t%0.2f #/cm^3 NC PM0.5\r\n"  // PM0.5  < 0.5 μm
                   "\t%0.2f #/cm^3 NC PM1.0\r\n"  // PM1.0  < 1.0 μm
                   "\t%0.2f #/cm^3 NC PM2.5\r\n"  // PM2.5  < 2.5 μm
                   "\t%0.2f #/cm^3 NC PM4.0\r\n"  // PM4.0  < 4.0 μm
                   "\t%0.2f #/cm^3 NC PM10.0\r\n" // PM10.0 < 10.0 μm
                   "\t%0.2fum typical particle size\r\n\r\n",
                   m.mc_1p0, m.mc_2p5, m.mc_4p0, m.mc_10p0, m.nc_0p5, m.nc_1p0,
                   m.nc_2p5, m.nc_4p0, m.nc_10p0, m.typical_particle_size);
        }

        PRINTF("\r\n");
        CyDelay(DATA_INTERVAL);
    }
}


/***************************************************************************/



void EZI2C_EZI2C_STRETCH_ISR_ExitCallback() {
    resetEventBuffer();
}


/**
 * Handles a character input on the terminal.
 *
 * @param ch The character that has been entered.
 */
void terminalInputChar(uint8 ch) {
    uint8 data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
    uint16 len = sizeof(data);


    if(ch){     // SAny input
//        PRINTF( "keyboard-Input is '%c'\r\n", ch );
        switch(ch){
            case 'h':   // +++ diplay help +++
            PRINTF("\r\n");
                PRINTF(_VERSTR_); // Show firmware id
                prtHelp(Serial_Terminal_UartPutString);  // show help
                break;
            case 'b':   // Blink LED
                blinkLED();
                break;
            case 'L':   // Turn LED on
                Pin_3_4_Write(LED_ON);
                break;
            case 'l':   // Turn LED off
                Pin_3_4_Write(LED_OFF);
                break;
            case 't':{ // Show time since start
                unsigned short years = tickSinceStart / 31536000;        // Years since start
                unsigned int days = (tickSinceStart / 86400) % 365;      // Days since start
                unsigned short hours = (tickSinceStart / 3600) % 24;     // Hours since start
                unsigned short minutes = (tickSinceStart / 60) % 60;     // Minutes since start
                unsigned short seconds = tickSinceStart % 60;            // Seconds since start
                // Print the elapsed time since start on format years:days:hours:minutes:seconds
                PRINTF("Time since start: %d:%03d:%02d:%02d:%02d\r\n", years, days, hours, minutes, seconds);
                break;
            }
            case 'T':   // Write tick event
                writeSecondsIDevt(tickSinceStart);
                break;
            case 'd':
            PRINTF("Write data event of len %d\r\n", len);
                writeDataEvt(EVSUBTYP_UNSPEC, data, len);
                len--;
                if(len == 0){               // Reset length (must be > 0)
                    len = sizeof(data);
                }
                break;
            case 'e':{ // Show event buffer size
                uint32 totalEventBytes = getStorageSize();                // # total bytes
                uint32 freeEventBytes = getFreeStorageSize();             // # free bytes
                uint32 usedEventBytes = totalEventBytes - freeEventBytes; // # used bytes
                PRINTF("Total event storage: %lu, free: %lu, used: %lu\r\n",
                       totalEventBytes, freeEventBytes, usedEventBytes);
            }
                break;
            case 'E':   // Show all events in the event buffer
            PRINTF("show events\r\n");
                uint8 type;
                uint8* pT = &type;    // Type and ptr
                uint8 stype;
                uint8* pST = &stype;   // Subtype and ptr
                uint16 len;
                uint16* pL = &len;     // Length and ptr
                void* pCurrDataBuf = getStartPtr();  // Current data buffer, init!
                void* pNextDataBuf = 0;              // Current data buffer

                // Loop through all available events until an EOF event
                do {
                    // Get next event or 0 on EOF
                    pNextDataBuf = readEvent(pCurrDataBuf, pT, pST, pL);
                    // Print event properties
                    PRINTF("%s\t%s\tlen:%d\r\n",
                           getEvtTypeName(type),
                           getEvtSubTypeName(stype),
                           *pL);
                    // Handle event types
                    switch(type){
                        case EVTYP_ID:
                            break;
                        case EVTYP_STRING:
                            break;
                        case EVTYP_DATA:{
                            psEvtData_t psEvtData = (psEvtData_t)pCurrDataBuf;
                            PRINTF("len %d:", psEvtData->dataLen);
                            uint i;
                            for(i = 0; i < psEvtData->dataLen; i++){
                                PRINTF(" %d", psEvtData->data[i]);
                            }
                            PRINTF("\r\n");
                        }
                            break;
                        case EVTYP_EOF:
                            break;

                        case EVTYP_AIR_QUALITY:{
                            psEvtAirQuality_t psAirQuality = (psEvtAirQuality_t)pCurrDataBuf;
                            PRINTF("TVOC: %d ppb\teCO2: %d ppm\r\n", psAirQuality->tvoc, psAirQuality->eCO2);
                            break;
                        }

                        case EVTYP_TEMP_HUM:{
                            // Temperature & humidity event
                            psEvtTempHum_t eventTemperatureHumidity = (psEvtTempHum_t)pCurrDataBuf;
                            PRINTF("Temperature: %-.3f°C\tHumidity: %-.3f%%\r\n",
                                   eventTemperatureHumidity->temperature / 1000.0,
                                   eventTemperatureHumidity->humidity / 1000.0);
                            break;
                        }

                        case EVTYP_PARTICULATES:{
                            psEvtParticulates_t eventParticulates = (psEvtParticulates_t)pCurrDataBuf;

                            PRINTF("Mass concentration:\r\n"
                                   // Mass concentration in μg/m^3 (Micrograms per cubic meter);  μ = 10^-6
                                   "\t%0.2f ug/m^3 MC PM1.0 \r\n" // PM1.0  < 1.0 μm (Micrometer)
                                   "\t%0.2f ug/m^3 MC PM2.5\r\n"  // PM2.5  < 2.5 μm
                                   "\t%0.2f ug/m^3 MC PM4.0\r\n"  // PM4.0  < 4.0 μm
                                   "\t%0.2f ug/m^3 MC PM10.0\r\n" // PM10.0 < 10.0 μm
                                   "Number concentration:\r\n"
                                   // Amount per cm^3
                                   "\t%0.2f #/cm^3 NC PM0.5\r\n"  // PM0.5  < 0.5 μm
                                   "\t%0.2f #/cm^3 NC PM1.0\r\n"  // PM1.0  < 1.0 μm
                                   "\t%0.2f #/cm^3 NC PM2.5\r\n"  // PM2.5  < 2.5 μm
                                   "\t%0.2f #/cm^3 NC PM4.0\r\n"  // PM4.0  < 4.0 μm
                                   "\t%0.2f #/cm^3 NC PM10.0\r\n" // PM10.0 < 10.0 μm
                                   "\t%0.2fum typical particle size\r\n\r\n",
                                   eventParticulates->MC_PM1p0 / 1000000.0, eventParticulates->MC_PM2p5 / 1000000.0,
                                   eventParticulates->MC_PM4p0 / 1000000.0, eventParticulates->MC_PM10p0 / 1000000.0,
                                   eventParticulates->NC_PM0p5 / 1000000.0, eventParticulates->NC_PM1p0 / 1000000.0,
                                   eventParticulates->NC_PM2p5 / 1000000.0, eventParticulates->NC_PM4p0 / 1000000.0,
                                   eventParticulates->NC_PM10p0 / 1000000.0,
                                   eventParticulates->typical_particle_size / 1000000.0);

                            break;
                        }

                            // Add here your further handling

                        default:
                            // should not happen!
                            // Event type not specified
                        PRINTF("ERR unknown evt-type %d\r\n", type);
                            break;
                    } // End event type switch
                    pCurrDataBuf = pNextDataBuf;    // Set pointer for the next event
                } while(pNextDataBuf != 0); // do-while, end on EOF event

                break;


            default:    // None of the defined inputs
//              PUTC( ch ); // print the character
            PRINTF("Unknown keyboard input: '%c'\r\n", ch);
                break;
        } // End input char switch
        // Reset input character
        ch = 0;                     // don' forget!
        PRINTF("\r\n");
    } // End if(ch) to get any input != 0
}
/* [] END OF FILE */
