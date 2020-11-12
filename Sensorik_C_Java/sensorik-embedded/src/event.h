/**
 * Event handling (prototype)
 *
 * @author Ralf S. Mayer, Felix Ohms, Maximilian Reinheimer
 * @version 0.9
 * @date 2019-01-06
 */

#ifndef EVENT_H
#define EVENT_H

#include <cytypes.h>            //!< Datentypen

#include "swsign.h"
#include "../sensorik.cydsn/common.h"

/* +++ defines +++ */
#define STS_EVT_SUCCESS      0  //!< event handling OK
#define STS_EVT_FAIL         1  //!< event handling failed

// use unique event type numbers!
#define EVTYP_HEADONLY       0  //!< event type only header (for test)
#define EVTYP_ID             1  //!< event type for ID event
#define EVTYP_STRING         2  //!< event type for ID event
#define EVTYP_TEMPERATURE    8  //!< event type for temperature
#define EVTYP_HUMIDITY      16  //!< event type for humidity
#define EVTYP_TEMP_HUM      24  //!< event type for temperature and humidity
#define EVTYP_PRESSURE      32  //!< event type for pressure
#define EVTYP_PARTICULATES          64  //!< event type for particulates
#define EVTYP_DATA          42  //!< event type for byte data event
#define EVTYP_AIR_QUALITY  128  //!< event type for air quality
#define EVTYP_EOF          255  //!< event type end of file / end of data

// try to use unique subtype numbers
#define EVSUBTYP_CURR_VER  110  //!< event subtype for current version
#define EVSUBTYP_UNSPEC      0  //!< event EVTYP_ID: subevent type unspecified
#define EVSUBTYP_NUMBER      1  //!< event EVTYP_ID: subevent type number
#define EVSUBTYP_TS          2  //!< event EVTYP_ID: subevent type timestamp
#define EVSUBTYP_SECOND      3  //!< event EVTYP_ID: subevent type seconds
#define EVSUBTYP_SHT31      10  //!< event EVTYP_ID: subevent type sensor type
#define EVSUBTYP_HTU21D     11  //!< event EVTYP_ID: subevent type sensor type
#define EVSUBTYP_SGU30      12  //!< event EVTYP_ID: subevent type sensor type
#define EVSUBTYP_SPS30      13  //!< event EVTYP_ID: subevent type sensor type
#define EVSUBTYP_SDS011     14  //!< event EVTYP_ID: subevent type sensor type
#define EVSUBTYP_BMP280     15  //!< event EVTYP_ID: subevent type sensor type
#define EVSUBTYP_BME280     16  //!< event EVTYP_ID: subevent type sensor type
#define EVSUBTYP_SGP30      17  //!< event EVTYP_ID: subevent type sensor type
#define EVSUBTYP_EOF       255  //!< event subtype end of file / end of data
// you may play here also with bitpatterns to combine subevents ?
// ... but would complicate the things

/**
 * \def MESSAGE
 * @param NAME
 * Utility macro
 * expands to { NAME, "NAME" }
 */
#define MESSAGE(NAME)  { NAME, #NAME }

/***************************Macro Definitions*******************************/
//Size of the Event Buffer
#define EVENT_BUFFER_SIZE 2048

/**
 * Structure for define macro number and define name
 */
typedef struct{
    uint32 defNr;       // number
    char* defName;     // name
} defMsg_t;



/* ++++++++++++++++++++++ */
/* +++ event typedefs +++ */
/* ++++++++++++++++++++++ */


/**
 * Basic event header. Header is long word aligned (32 bit = 4 byte)
 */
typedef struct{
    // header
    uint8 evtType;        //!< event type
    uint8 evtSubtype;     //!< event subtype, e.g. for version
    uint16 evtLen;         //!< total length of event including header
} sEvtHead_t;

/**
 * Temperature & Humidity Event Structure
 *
 * @author Max Reinheimer
 * @author Felix Ohms
 * @date 05.06.2019
 */
typedef struct{
    // Event header
    sEvtHead_t sEvtHead;      // Event type (has a length of 4 bytes)
    // Event payload
    uint32_t temperature;     // Temperature (divide by 1000)
    uint32_t humidity;        // Humidity (divide by 1000)
} sEvtTempHum_t;

/**
 * Air Quality Event Structure
 *
 * @author Max Reinheimer
 * @author Felix Ohms
 * @date 05.06.2019
 */
typedef struct{
    // header
    sEvtHead_t sEvtHead; // event type (has a length of 4 bytes)
    // data
    uint16_t tvoc;      //Total Volatile Organic Compounds in ppb
    uint16_t eCO2;      //equivalent CO2 in ppm
} sEvtAirQuality_t;

/**
 * Basic event pattern with unstructure data array
 */
typedef struct{
    // header
    sEvtHead_t sEvtHead;       //!< event type (4 bytes)
    // data
    uint16 _dummy;         //!< general/unspecific use, dummy for longword alignment
    uint16 dataLen;        //!< length of data (payload)
    uint8 data[4];        //!< data byte wise (start of payload)
} sEvtData_t;

/**
 * Basic ID event using simple numbering or timestamp
 */
typedef struct{
    // header
    sEvtHead_t sEvtHead;       //!< event type (4 bytes)
    // data
    uint32 evtID;          //!< event number or timestamp
} sEvtID_t;

/**
 * Basic string (text) event
 */
typedef struct{
    // header
    sEvtHead_t sEvtHead;       //!< event type (4 bytes)
    // data
    char str[4];         //!< string byte wise (start of payload)
} sEvtString_t;

/**
 * Prototype for GridEye event
 * @ Modify it to your needs. Take care to LW alignment for efficiency!
 */
typedef struct{
    // header
    sEvtHead_t sEvtHead;           //!< event type (4 bytes)
    // data

    // Particulates, divide all by 10^6
    // Mass concentration in μg/m^3
    uint32_t MC_PM1p0;  // PM1.0  < 1.0 μm (Micrometer)
    uint32_t MC_PM2p5;  // PM2.5  < 2.5 μm
    uint32_t MC_PM4p0;  // PM4.0  < 4.0 μm
    uint32_t MC_PM10p0; // PM10.0 < 10.0 μm
    // Amount per cm^3
    uint32_t NC_PM0p5;  // PM0.5  < 0.5 μm
    uint32_t NC_PM1p0;  // PM1.0  < 1.0 μm
    uint32_t NC_PM2p5;  // PM2.5  < 2.5 μm
    uint32_t NC_PM4p0;  // PM4.0  < 4.0 μm
    uint32_t NC_PM10p0; // PM10.0 < 10.0 μm
    uint32_t typical_particle_size;
} sEvtParticulates_t;


/* ++++++++++++++++++++++++ */
/* +++ pointer typedefs +++ */
/* ++++++++++++++++++++++++ */

typedef sEvtHead_t* psEvtHead_t;    //!< type event header
typedef sEvtTempHum_t* psEvtTempHum_t; //!< type Temp Humidity header
typedef sEvtAirQuality_t* psEvtAirQuality_t; //!< type Air Quality header
typedef sEvtData_t* psEvtData_t;    //!< type data event
typedef sEvtID_t* psEvtID_t;      //!< type id event
typedef sEvtString_t* psEvtString_t;  //!< type string event
typedef sEvtParticulates_t* psEvtParticulates_t;    //!< type Particulates event

/* +++++++++++++++++++++++++++ */
/* +++ function prototypes +++ */
/* +++++++++++++++++++++++++++ */

/** @brief Display event types and subtypes by name */
void displayEvtSubevtTypes();

/** @brief Get define macro name for event type number */
char* getEvtTypeName(uint8 type);

/** @brief Get define macro name for event subtype number. */
char* getEvtSubTypeName(uint8 type);

/** @brief Set data pointer */
void* setDataPtr(void* pDataAddr);

/** @brief Get data pointer */
void* getDataPtr();

/** @brief Set storage start pointer and size */
void* setStorageStartPtr(void* pAddr, uint32 size);

/** @brief Get storage start pointer */
void* getStartPtr();

/** @brief Get storage size */
uint32 getStorageSize();

/** @brief Get free storage size */
uint32 getFreeStorageSize();

/**
 * Resets the event buffer, effectively emptying it.
 */
void resetEventBuffer();

/** @brief Write Header only event */
void* writeHeadEvt(uint8 type, uint8 subtype);

/** @brief Print event header to buffer */
char* printEvtHead(void* ptr2evt, char* buf);

/** @brief Write version ID event */
void* writeVersionIDevt(uint32 id);

/** @brief Write AIR Quality event */
void* writeAirQualityEvt(uint16 subtype, uint16_t eCO2, uint16_t tvoc);

/** @brief Write SENSOR SGP30 AIR Quality event */
void* writeSGP30AirQualityEvt(uint16_t eCO2, uint16_t tvoc);

/** @brief Write number ID event */
void* writeNumberIDevt(uint32 id);

/** @brief Write timestamp ID event */
void* writeTimestampIDevt(uint32 ts);

/** @brief Write seconds ID event @brief  */
void* writeSecondsIDevt(uint32 sec);

/** @brief Write string event */
void* writeStringEvt(char* string);

/** @brief Data event */
void* writeDataEvt(uint16 subtype, uint8* pData, uint16 dataLen);

/** @brief Write Ev tParticulates event */
//void* writeParticulatesEvt( );

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
void* eventWriteTempHum(const uint8 subtype, const uint32_t temperature, const uint32_t humidity);

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
void* eventWriteSHT31TempHum(const uint32_t temperature, const uint32_t humidity);

void* eventWriteParticulates(const uint8 subtype, const uint32_t MC_PM1p0, const uint32_t MC_PM2p5,
                             const uint32_t MC_PM4p0, const uint32_t MC_PM10p0, const uint32_t NC_PM0p5,
                             const uint32_t NC_PM1p0, const uint32_t NC_PM2p5, const uint32_t NC_PM4p0,
                             const uint32_t NC_PM10p0, const uint32_t typical_particle_size);

void* eventWriteSPS30Particulates(const uint32_t MC_PM1p0, const uint32_t MC_PM2p5, const uint32_t MC_PM4p0,
                                  const uint32_t MC_PM10p0, const uint32_t NC_PM0p5, const uint32_t NC_PM1p0,
                                  const uint32_t NC_PM2p5, const uint32_t NC_PM4p0, const uint32_t NC_PM10p0,
                                  const uint32_t typical_particle_size);


/** @brief Read event, get header info, return ptr to next event */
void* readEvent(void* ptr2evt, uint8* pType, uint8* pSType, uint16* pLen);

#endif // EVENT_H
/* [] END OF FILE */
