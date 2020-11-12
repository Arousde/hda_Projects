/******************************************************************************
* File Name: HandleLowPower.h
*
* Version: 1.10
*
* Description:  This file contains macros and the declaration of functions 
* provided by the HandleLowPower.c file
*
* Related Document: CE210709 CapSense Linear Slider and Buttons.pdf
*
* Hardware Dependency: See CE210709 CapSense Linear Slider and Buttons.pdf
*
*******************************************************************************
* Copyright (2018), Cypress Semiconductor Corporation. All rights reserved.
*******************************************************************************
* This software, including source code, documentation and related materials
* (“Software”), is owned by Cypress Semiconductor Corporation or one of its
* subsidiaries (“Cypress”) and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software (“EULA”).
*
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Cypress’s integrated circuit products.
* Any reproduction, modification, translation, compilation, or representation
* of this Software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress 
* reserves the right to make changes to the Software without notice. Cypress 
* does not assume any liability arising out of the application or use of the 
* Software or any product or circuit described in the Software. Cypress does 
* not authorize its products for use in any products where a malfunction or 
* failure of the Cypress product may reasonably be expected to result in 
* significant property damage, injury or death (“High Risk Product”). By 
* including Cypress’s product in a High Risk Product, the manufacturer of such 
* system or application assumes all risk of such use and in doing so agrees to 
* indemnify Cypress against all liability.
*******************************************************************************/

/********************************************************************************
*	Contains  macros and function declaration used in the HandleLowPower.c file 
********************************************************************************/
#if !defined(HANDLELOWPOWER_H)
#define HANDLELOWPOWER_H

#include <project.h>

/****************************Macro Declarations******************************/
#define IMO_FREQUENCY_3MHZ            (3u)
#define IMO_FREQUENCY_12MHZ            (12u)
/****************************************************************************/

/**************************Function Declarations*****************************/
void HandleLowPowerMode(void);
/****************************************************************************/

/*************************Pre-processor directives****************************/
/* 'ENABLE_LOW_POWER_MODE' pre-processor directive enables the low power mode 
* handling in the firmware, ensuring low power consumption during project usage.
* To disable, comment the following #define. 
* If disabled, prevent usage of the project with coin cell */

#define ENABLE_LOW_POWER_MODE

#endif
/* [] END OF FILE */
