/* ========================================
 *
 * Copyright Ralf S. Mayer, 2019
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "help.h"

// +++++++++++++++++++++++++++++
// +++ define help text here +++
// +++++++++++++++++++++++++++++
//#define _HELP_  "\r\nHelp for >C149-OLED_UART<:\r\n"
#define _HELP_  "\r\n(C-149) I2C-Event help\r\n"
#define _HELP1_ "\th,H help\r\n"
#define _HELP2_ "\tL LED on, l LED off\r\n"
#define _HELP3_ "\tb LED blink\r\n"
#define _HELP4_ "\tt show tick, T write tick event\r\n"
#define _HELP5_ "\te event storage, E show events\r\n"

/**
 * Put help strings on output. No changes required here, unless mor help-items.
 * @param funcPutString
 *        e.g. UART_UartPutString
 * @see http://www.lab4inf.fh-muenster.de/lab4inf/docs/Prog-in-C/11-Zeiger-auf-Funktionen.pdf
 * @see Fpp_t
 * @version 1.0
 * @author Ralf S. Mayer
 * @date 2017-03-06
 */
void prtHelp(Fpp_t funcPutString) {
    #ifdef _HELP_
    funcPutString(_HELP_);
    #endif //
    #ifdef _HELP1_
    funcPutString(_HELP1_);
    #endif //
    #ifdef _HELP2_
    funcPutString(_HELP2_);
    #endif //
    #ifdef _HELP3_
    funcPutString(_HELP3_);
    #endif //
    #ifdef _HELP4_
    funcPutString(_HELP4_);
    #endif //
    #ifdef _HELP5_
    funcPutString(_HELP5_);
    #endif //
    #ifdef _HELP6_
    funcPutString( _HELP6_ );
    #endif //
    #ifdef _HELP7_
    funcPutString( _HELP7_ );
    #endif //
    #ifdef _HELP8_
    funcPutString( _HELP8_ );
    #endif //
    #ifdef _HELP9_
    funcPutString( _HELP9_ );
    #endif //
    #ifdef _HELP10_
    funcPutString( _HELP10_ );
    #endif //
    #ifdef _HELP11_
    funcPutString( _HELP11_ );
    #endif //
    #ifdef _HELP12_
    funcPutString( _HELP12_ );
    #endif //
    // etc. for more _HELPn_
}

/* [] END OF FILE */
