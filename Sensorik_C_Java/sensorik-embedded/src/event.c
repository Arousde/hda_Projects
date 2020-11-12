/* ========================================
 *
 * Copyright Ralf Mayer, Felix Ohms, Maximilian Reinheimer, 2019
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
 */

 /**
 * @file event.c
 * @brief Provides eventstructure for data serialisation
 * 
 */

#include "event.h"
#include <stdio.h>
#include <string.h>
#include <project.h>    // only needed for UART ...

static uint8* pDataPtr;         //!< pointer to storage (dynamic during write)
static uint8* pDataStartPtr;    //!< storage start address
static uint32 storageSize;      //!< size of event storage

static char buf32[32];          //!< message buffer

// +++ some message utilities +++

/**
 * Structure for event type messages
 * @see MESSAGE
 * @todo Don't forget to add new event types if any
 */
static defMsg_t evtTypeMsg[] =
    {
        MESSAGE(EVTYP_HEADONLY),
        MESSAGE(EVTYP_ID),
        MESSAGE(EVTYP_STRING),
        MESSAGE(EVTYP_TEMPERATURE),
        MESSAGE(EVTYP_HUMIDITY),
        MESSAGE(EVTYP_TEMP_HUM),
        MESSAGE(EVTYP_PRESSURE),
        MESSAGE(EVTYP_PARTICULATES),
        MESSAGE(EVTYP_DATA),
        MESSAGE(EVTYP_AIR_QUALITY),
        MESSAGE(EVTYP_EOF)
    };

/**
 * Structure for event sub type messages
 * @see MESSAGE
 * @todo Don't forget to add new event types if any
 */
static defMsg_t evtSubTypeMsg[] =
    {
        MESSAGE(EVSUBTYP_CURR_VER),
        MESSAGE(EVSUBTYP_UNSPEC),
        MESSAGE(EVSUBTYP_NUMBER),
        MESSAGE(EVSUBTYP_TS),
        MESSAGE(EVSUBTYP_SECOND),
        MESSAGE(EVSUBTYP_SHT31),
        MESSAGE(EVSUBTYP_HTU21D),
        MESSAGE(EVSUBTYP_SGU30),
        MESSAGE(EVSUBTYP_SPS30),
        MESSAGE(EVSUBTYP_SDS011),
        MESSAGE(EVSUBTYP_BMP280),
        MESSAGE(EVSUBTYP_BME280),
        MESSAGE(EVSUBTYP_SGP30),
        MESSAGE(EVSUBTYP_EOF)
    };

// +++ event write and read functions +++

/**
 * Display event types and subtypes by name
 * Needs <project.h>
 *
 * @author R. S. Mayer
 * @date 2019-05-23
 */
void displayEvtSubevtTypes() {
    Serial_Terminal_UartPutString("Event Types\r\n");
    uint i;
    for(i = 0; i < sizeof(evtTypeMsg) / sizeof(defMsg_t); i++){
        Serial_Terminal_UartPutString(evtTypeMsg[i].defName);
        Serial_Terminal_UartPutString("\r\n");
    }
    Serial_Terminal_UartPutString("Event Subtypes\r\n");
    for(i = 0; i < sizeof(evtSubTypeMsg) / sizeof(defMsg_t); i++){
        Serial_Terminal_UartPutString(evtSubTypeMsg[i].defName);
        Serial_Terminal_UartPutString("\r\n");
    }
}

/**
 * Get define macro name for event type number.
 * @param type event type
 * @return define name or "not found"
 *
 * @author R. S. Mayer
 * @date 2019-05-23
 */
char* getEvtTypeName(uint8 type) {
    uint i;
    for(i = 0; i < sizeof(evtTypeMsg) / sizeof(defMsg_t); i++){
        if(evtTypeMsg[i].defNr == type){    // found event type
            return evtTypeMsg[i].defName;       // return name
        }
    }

    // event type not found
    sprintf(buf32, "evt type %d not found", type);
    return buf32;
}

/**
 * Get define macro name for event subtype number.
 * @param type event type
 * @return define name or "not found"
 *
 * @author R. S. Mayer
 * @date 2019-01-08
 * @date 2019-05-23
 */
char* getEvtSubTypeName(uint8 type) {
    uint i;
    for(i = 0; i < sizeof(evtSubTypeMsg) / sizeof(defMsg_t); i++){
        if(evtSubTypeMsg[i].defNr == type){    // found event type
            return evtSubTypeMsg[i].defName;       // return name
        }
    }

    // event type not found
    sprintf(buf32, "evt subtype %d not found", type);
    return buf32;
}

/**
 * Write EOF event. Does not increment internal pointer.
 * internal (protected) function
 *
 * @author Ralf S. Mayer
 * @date 2019-01-06
 */
static void writeEOF() {
    psEvtHead_t psHead = (psEvtHead_t)pDataPtr;  // set to actual storage
    psHead->evtType = EVTYP_EOF;               // write type
    psHead->evtSubtype = EVSUBTYP_EOF;            // write subtype
    psHead->evtLen = sizeof(sEvtHead_t);      // write event length
    // don't increment pointer. Next event shall write on this address
}

/**
 * Set data pointer
 * @param pDataAddr new address
 * @return old address
 *
 * Remark: Using void* is a little bit 'dirty'. Use it with care!
 *
 * @author Ralf S. Mayer
 * @date 2019-01-06
 */
void* setDataPtr(void* pDataAddr) {
    uint8* oldAddr = pDataPtr;
    pDataPtr = pDataAddr;
    writeEOF();
    return oldAddr;
}

/**
 * Get data pointer
 * @return address
 *
 * @author Ralf S. Mayer
 * @date 2019-01-06
 */
void* getDataPtr() {
    return pDataPtr;
}

/**
 * Set storage start pointer and size
 * @param pAddr storage start address
 * @param size storage total size (bytes)
 * @return old address
 *
 * Remark: Using void* is a little bit 'dirty'. Use it with care!
 *
 * @author Ralf S. Mayer
 * @date 2019-01-07
 */
void* setStorageStartPtr(void* pAddr, uint32 size) {
    uint8* oldAddr = pDataStartPtr;     // save old address
    pDataStartPtr = pAddr;              // set new address
    storageSize = size;                 // set size
    return oldAddr;                     // return old address
}

/**
 * Get storage start pointer
 * @return storage start pointer
 */
void* getStartPtr() {
    return pDataStartPtr;
}

/**
 * Get storage size
 * @return storage size (bytes)
 */
uint32 getStorageSize() {
    return storageSize;
}

/**
 * Get free storage size
 * @return free storage size (bytes)
 */
uint32 getFreeStorageSize() {
    return storageSize - (pDataPtr - pDataStartPtr);
}

/**
 * Resets the event buffer, effectively emptying it.
 */
void resetEventBuffer() {
    //PRINTF("  Resetting event buffer...   ");
    //unsigned int freedBytes = getStorageSize() - getFreeStorageSize();
    setDataPtr(pDataStartPtr);
    //PRINTF("Done, %d bytes have been freed.\r\n", freedBytes);
}

/**
 * Write Header only event
 * @param type event type
 * @param subtype event subtype
 * @return new address, i.e. next free
 *
 * @author Ralf S. Mayer
 * @date 2019-01-06
 */
void* writeHeadEvt(uint8 type, uint8 subtype) {
    psEvtHead_t psHead = (psEvtHead_t)pDataPtr;  // Set to actual storage
    psHead->evtType = type;                      // Write type
    psHead->evtSubtype = subtype;                // Write subtype
    psHead->evtLen = sizeof(sEvtHead_t);         // Write event length
    pDataPtr += psHead->evtLen;                  // Increment pointer
    writeEOF();                                  // Write EOF event
    return pDataPtr;                             // Return new (next free) addr
}

/**
 * Print event header to string buffer
 * @param[in] ptr2evt pointer to event
 * @param[in,out] buf buffer to string (>= 16 + 10 + define name length byte),
 *    >= 64 bytes recommended
 * @see evtTypeMsg
 * @return ptr to string buffer
 *
 * @author Ralf S. Mayer
 * @date 2019-01-08
 */
char* printEvtHead(void* ptr2evt, char* buf) {
    psEvtHead_t psHead = (psEvtHead_t)ptr2evt;  // Set pointer to evt header
    sprintf(buf, "t: %s, s: %s, len: %d",
            getEvtTypeName(psHead->evtType),
            getEvtSubTypeName(psHead->evtSubtype),
            psHead->evtLen);
    return buf;
}

/**
 * Write Air Quality Event. Internal (protected) function
 * @param subtype event subtype
 * @param eCO2 eCO2
 * @param tvoc TVOC
 * @return Adress of Event
 *
 * @author Maximilian Reinheimer
 * @date 2019-6-6
 */
void* writeAirQualityEvt(uint16 subtype, uint16_t eCO2, uint16_t tvoc) {
    // Make sure there is enough free storage space in the event buffer for this event
    if(getFreeStorageSize() < sizeof(sEvtAirQuality_t)){
        // To avoid overflowing and subsequently crashing, don't write the event
        PRINTF("Event buffer full, cannot write AirQuality event of size %d with remaining buffer size of %lu.\r\n",
               sizeof(sEvtAirQuality_t), getFreeStorageSize());
        return pDataPtr;
    }

    // set to actual storage
    psEvtAirQuality_t psAirQuality = (psEvtAirQuality_t)pDataPtr;
    psAirQuality->sEvtHead.evtType = EVTYP_AIR_QUALITY; // Write type
    psAirQuality->sEvtHead.evtSubtype = subtype;        // Write subtype
    psAirQuality->eCO2 = eCO2;
    psAirQuality->tvoc = tvoc;
    // write event length
    psAirQuality->sEvtHead.evtLen = sizeof(sEvtAirQuality_t);
    pDataPtr += psAirQuality->sEvtHead.evtLen;  // Increment pointer
    writeEOF();                                 // write EOF event
    return pDataPtr;                            // Return new (next free) addr
}


/**
 * Write ID event. Internal (protected) function
 * @param subtype event subtype
 * @param id event number
 * @return new address, i.e. next free
 *
 * @author Ralf S. Mayer
 * @date 2019-05-23
 */
void* writeIDevt(uint16 subtype, uint32 id) {
    // set to actual storage
    psEvtID_t psID = (psEvtID_t)pDataPtr;
    psID->sEvtHead.evtType = EVTYP_ID;    // Write type
    psID->sEvtHead.evtSubtype = subtype;  // Write subtype
    psID->evtID = id;
    // write event length
    psID->sEvtHead.evtLen = sizeof(sEvtID_t);
    pDataPtr += psID->sEvtHead.evtLen;      // Increment pointer
    writeEOF();                             // Write EOF event
    return pDataPtr;                        // Return new (next free) addr
}

/**
 * Write version ID event
 * @param id of SW (event/subevnet types) version
 * @return new address, i.e. next free
 *
 * @author Ralf S. Mayer
 * @date 2019-0523
 */
void* writeVersionIDevt(uint32 id) {
    return writeIDevt(EVSUBTYP_CURR_VER, id);
}

/**
 * Write number ID event
 * @param id event number
 * @return new address, i.e. next free
 *
 * @author Ralf S. Mayer
 * @date 2019-01-06
 */
void* writeNumberIDevt(uint32 id) {
    return writeIDevt(EVSUBTYP_NUMBER, id);
//    psEvtID_t psID              = (psEvtID_t) pDataPtr;
//    psID->sEvtHead.evtType      = EVTYP_ID;         // write type
//    psID->sEvtHead.evtSubtype   = EVSUBTYP_NUMBER;  // write subtype
//    psID->evtID                 = id;
//    // write event length
//    psID->sEvtHead.evtLen       = sizeof(sEvtID_t);
//    pDataPtr += psID->sEvtHead.evtLen;              // increment pointer
//    writeEOF();                                     // write EOF event
//    return pDataPtr;                            // return new (next free) addr
}

/**
 * Write timestamp ID event
 * @param ts time stamp
 * @return new address, i.e. next free
 *
 * @author Ralf S. Mayer
 * @date 2019-01-06
 */
void* writeTimestampIDevt(uint32 ts) {
    return writeIDevt(EVSUBTYP_TS, ts);
//    psEvtID_t psID              = (psEvtID_t) pDataPtr;
//    psID->sEvtHead.evtType      = EVTYP_ID;         // write type
//    psID->sEvtHead.evtSubtype   = EVSUBTYP_TS;      // write subtype
//    psID->evtID                 = ts;
//    // write event length
//    psID->sEvtHead.evtLen       = sizeof(sEvtID_t);
//    pDataPtr += psID->sEvtHead.evtLen;              // increment pointer
//    writeEOF();                                     // write EOF event
//    return pDataPtr;                            // return new (next free) addr
}

/**
 * Write seconds ID event
 * @param sec seconds since program start
 * @return new address, i.e. next free
 *
 * @author Ralf S. Mayer
 * @date 2019-01-08
 */
void* writeSecondsIDevt(uint32 sec) {
    return writeIDevt(EVSUBTYP_TS, sec);
//    psEvtID_t psID              = (psEvtID_t) pDataPtr;
//    psID->sEvtHead.evtType      = EVTYP_ID;         // write type
//    psID->sEvtHead.evtSubtype   = EVSUBTYP_SECOND;  // write subtype
//    psID->evtID                 = sec;
//    // write event length
//    psID->sEvtHead.evtLen       = sizeof(sEvtID_t);
//    pDataPtr += psID->sEvtHead.evtLen;              // increment pointer
//    writeEOF();                                     // write EOF event
//    return pDataPtr;                            // return new (next free) addr
}

/**
 * Write string event
 * @param string with length < 65536
 * @return new address, i.e. next free
 *
 * @author Ralf S. Mayer
 * @date 2019-01-06
 */
void* writeStringEvt(char* string) {
    // set to actual storage
    psEvtString_t psString = (psEvtString_t)pDataPtr;
    psString->sEvtHead.evtType = EVTYP_STRING;      // write type
    psString->sEvtHead.evtSubtype = EVSUBTYP_UNSPEC;   // write subtype
    uint16 strLen = strlen(string) + 1; // length of string + null termination
    uint16 size = strLen;  // size of string regarding alignment
    // check long word alignment
    if((strLen % 4) != 0){              // check LW alignment to 4 bytes
        uint16 sizeLW = strLen / 4 + 1;     // do alignment to LW
        size = sizeLW * 4;                  // new size aligned
    }
    // write event length
    psString->sEvtHead.evtLen = sizeof(sEvtHead_t) + size;
    strcpy(psString->str, string);        // copy string
    pDataPtr += psString->sEvtHead.evtLen;  // increment pointer
    writeEOF();                             // write EOF event
    return pDataPtr;                        // return new (next free) addr
}

/**
 * Dust event
 */
//void* writeDustEvt(uint16 subtype) {
//    // set to actual storage
//    psEvtDust_t psEvtDust = (psEvtDust_t)pDataPtr;
//    psEvtDust->sEvtHead.evtType = EVTYP_DUST;   // write type
//    psEvtDust->sEvtHead.evtSubtype = subtype;      // write subtype
//
//    // write event length
//    psEvtDust->sEvtHead.evtLen = sizeof(sEvtDust_t);
//    pDataPtr += psEvtDust->sEvtHead.evtLen;         // increment pointer
//    writeEOF();                                     // write EOF event
//    return pDataPtr;                            // return new (next free) addr
//}

/**
 * Data event (test)
 * @param subtype
 * @param pData Pointer to byte field
 * @param dataLen of data
 * @return new address, i.e. next free
 *
 * @author Ralf S. Mayer
 * @date 2019-05-23
 */
void* writeDataEvt(uint16 subtype, uint8* pData, uint16 dataLen) {
    // set to actual storage
    psEvtData_t psEvtData = (psEvtData_t)pDataPtr;
    psEvtData->sEvtHead.evtType = EVTYP_DATA;   // write type
    psEvtData->sEvtHead.evtSubtype = subtype;      // write subtype
    // round up to multiples of 4
    uint16 dLen = ((dataLen - 1) / 4 + 1) * 4;
    memcpy((uint8*)psEvtData->data, pData, dataLen);
    psEvtData->dataLen = dataLen;               // real payload length

    // write event length
    psEvtData->sEvtHead.evtLen =
        sizeof(sEvtData_t) + dLen - 4;         // 4 bytes already included
    pDataPtr += psEvtData->sEvtHead.evtLen;     // increment pointer
    writeEOF();                                 // write EOF event
    return pDataPtr;                            // return new (next free) addr
}


/**
 * Write a temperature & humidity event with a specified subtype.
 * The subtype indicates which sensor the measurements came from.
 *
 * @author Felix Ohms
 * @date 07.06.2019
 *
 * @param subtype The subtype of the event.
 * @param temperature The measured temperature, multiplied with 1000.
 * @param humidity The measured temperature, multiplied with 1000.
 * @return
 */
void* eventWriteTempHum(const uint8 subtype, const uint32_t temperature, const uint32_t humidity) {
    // Make sure there is enough free storage space in the event buffer for this event
    if(getFreeStorageSize() < sizeof(sEvtTempHum_t)){
        // To avoid overflowing and subsequently crashing, don't write the event
        PRINTF(
            "Event buffer full, cannot write TemperatureHumidity event of size %d with remaining buffer size of %lu.\r\n",
            sizeof(sEvtTempHum_t), getFreeStorageSize());
        return pDataPtr;
    }

    // Create the event
    psEvtTempHum_t eventTemperatureHumidity = (psEvtTempHum_t)pDataPtr;

    // Write the event header
    eventTemperatureHumidity->sEvtHead.evtType = EVTYP_TEMP_HUM;                   // Event type
    eventTemperatureHumidity->sEvtHead.evtSubtype = subtype;                       // Event subtype
    eventTemperatureHumidity->sEvtHead.evtLen = sizeof(sEvtTempHum_t);             // Event length

    // Write the event data
    eventTemperatureHumidity->temperature = temperature;
    eventTemperatureHumidity->humidity = humidity;

    // Increment event pointer
    pDataPtr += eventTemperatureHumidity->sEvtHead.evtLen;

    // Write EOF event to mark the end of all written events.
    // Everything in the buffer beyond this is free to write to and does not contain any usable data.
    writeEOF();

    // Return the next free address for the next event
    return pDataPtr;
}

/**
 * Write a temperature & humidity event with measurements from a SHT31 sensor.
 *
 * @author Felix Ohms
 * @date 07.06.2019
 *
 * @param temperature The measured temperature, multiplied with 1000.
 * @param humidity The measured temperature, multiplied with 1000.
 * @return
 */
void* eventWriteSHT31TempHum(const uint32_t temperature, const uint32_t humidity) {
    return eventWriteTempHum(EVSUBTYP_SHT31, temperature, humidity);
}

void* eventWriteParticulates(const uint8 subtype, const uint32_t MC_PM1p0, const uint32_t MC_PM2p5,
                             const uint32_t MC_PM4p0, const uint32_t MC_PM10p0, const uint32_t NC_PM0p5,
                             const uint32_t NC_PM1p0, const uint32_t NC_PM2p5, const uint32_t NC_PM4p0,
                             const uint32_t NC_PM10p0, const uint32_t typical_particle_size) {
    // Make sure there is enough free storage space in the event buffer for this event
    if(getFreeStorageSize() < sizeof(sEvtParticulates_t)){
        // To avoid overflowing and subsequently crashing, don't write the event
        PRINTF("Event buffer full, cannot write particulates event of size %d with remaining buffer size of %lu.\r\n",
               sizeof(sEvtParticulates_t), getFreeStorageSize());
        return pDataPtr;
    }

    // Create the event
    psEvtParticulates_t eventParticulates = (psEvtParticulates_t)pDataPtr;

    // Write the event header
    eventParticulates->sEvtHead.evtType = EVTYP_PARTICULATES;         // Event type
    eventParticulates->sEvtHead.evtSubtype = subtype;                // Event subtype
    eventParticulates->sEvtHead.evtLen = sizeof(sEvtParticulates_t);  // Event length

    // Write the event data
    // Mass concentration in μg/m^3
    eventParticulates->MC_PM1p0 = MC_PM1p0;   // PM1.0 < 1.0 μm (Micrometer)
    eventParticulates->MC_PM2p5 = MC_PM2p5;   // 1.0 μm < PM2.5  < 2.5 μm
    eventParticulates->MC_PM4p0 = MC_PM4p0;   // 2.5 μm < PM4.0  < 4.0 μm
    eventParticulates->MC_PM10p0 = MC_PM10p0; // 4.0 μm < PM10.0 < 10.0 μm
    // Amount per cm^3
    eventParticulates->NC_PM0p5 = NC_PM0p5;   // PM0.5 < 0.5 μm
    eventParticulates->NC_PM1p0 = NC_PM1p0;   // 0.5 μm < PM1.0  < 1.0 μm
    eventParticulates->NC_PM2p5 = NC_PM2p5;   // 1.0 μm < PM2.5  < 2.5 μm
    eventParticulates->NC_PM4p0 = NC_PM4p0;   // 2.5 μm < PM4.0  < 4.0 μm
    eventParticulates->NC_PM10p0 = NC_PM10p0; // 4.0 μm < PM10.0 < 10.0 μm
    eventParticulates->typical_particle_size = typical_particle_size;

    // Increment event pointer
    pDataPtr += eventParticulates->sEvtHead.evtLen;

    // Write EOF event to mark the end of all written events.
    // Everything in the buffer beyond this is free to write to and does not contain any usable data.
    writeEOF();

    // Return the next free address for the next event
    return pDataPtr;
}

void* eventWriteSPS30Particulates(const uint32_t MC_PM1p0, const uint32_t MC_PM2p5, const uint32_t MC_PM4p0,
                                  const uint32_t MC_PM10p0, const uint32_t NC_PM0p5, const uint32_t NC_PM1p0,
                                  const uint32_t NC_PM2p5, const uint32_t NC_PM4p0, const uint32_t NC_PM10p0,
                                  const uint32_t typical_particle_size) {
    return eventWriteParticulates(EVSUBTYP_SPS30, MC_PM1p0, MC_PM2p5, MC_PM4p0, MC_PM10p0, NC_PM0p5, NC_PM1p0, NC_PM2p5,
                                  NC_PM4p0, NC_PM10p0, typical_particle_size);
}

/**
 * Read event, get header info, return ptr to next event
 * @param[in] ptr2evt pointer to event or buffer start pointer
 * @see getStartPtr()
 * @param[out] pType ptr to event type
 * @param[out] pSType ptr to event subtype
 * @param[out] pLen ptr to event length (bytes)
 * @return ptr to next event or 0 if evt-typ/subtype is EOF
 *
 * @author Ralf S. Mayer
 * @date 2019-01-07
 */
void* readEvent(void* ptr2evt, uint8* pType, uint8* pSType, uint16* pLen) {
    void* ptr = 0;                              // Init ptr / value = EOF
    psEvtHead_t psHead = (psEvtHead_t)ptr2evt;  // Set pointer to evt header
    *(pType) = psHead->evtType;
    *(pSType) = psHead->evtSubtype;
    *(pLen) = psHead->evtLen;

    // Check this event for beeing EOF
    if((psHead->evtType != EVTYP_EOF) && (psHead->evtSubtype != EVSUBTYP_EOF)){   // Has next event
        ptr = ptr2evt + psHead->evtLen;         // ptr to next event
    }
    else {
        // If the event is an EOF event, set the pointer to nullptr to indicate it as the last event
        ptr = 0;      // See init
    }
    return ptr;
}

/* [] END OF FILE */
