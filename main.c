/******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for the PSOC™ Control C1 MCU: ACMP (Analog
*              Comparator) Example for ModusToolbox.
*              Comparator block(ANACMP-1) is configured to receive divided
*              Reference voltage on positive input (IN-P) pin. Users may then
*              modify the voltage to negative input pin (IN-N) pin (Port 2.6)
*              and watch the user LED toggle according to ANACMP1:CMP_OUT change.
*
* Related Document: See README.md
*
******************************************************************************
* (c) 2026, Infineon Technologies AG, or an affiliate of Infineon
* Technologies AG. All rights reserved.
* This software, associated documentation and materials ("Software") is
* owned by Infineon Technologies AG or one of its affiliates ("Infineon")
* and is protected by and subject to worldwide patent protection, worldwide
* copyright laws, and international treaty provisions. Therefore, you may use
* this Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software. If no license
* agreement applies, then any use, reproduction, modification, translation, or
* compilation of this Software is prohibited without the express written
* permission of Infineon.
*
* Disclaimer: UNLESS OTHERWISE EXPRESSLY AGREED WITH INFINEON, THIS SOFTWARE
* IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING, BUT NOT LIMITED TO, ALL WARRANTIES OF NON-INFRINGEMENT OF
* THIRD-PARTY RIGHTS AND IMPLIED WARRANTIES SUCH AS WARRANTIES OF FITNESS FOR A
* SPECIFIC USE/PURPOSE OR MERCHANTABILITY.
* Infineon reserves the right to make changes to the Software without notice.
* You are responsible for properly designing, programming, and testing the
* functionality and safety of your intended application of the Software, as
* well as complying with any legal requirements related to its use. Infineon
* does not guarantee that the Software will be free from intrusion, data theft
* or loss, or other breaches ("Security Breaches"), and Infineon shall have
* no liability arising out of any Security Breaches. Unless otherwise
* explicitly approved by Infineon, the Software may not be used in any
* application where a failure of the Product or any consequences of the use
* thereof can reasonably be expected to result in personal injury.
*****************************************************************************/

#include <stdio.h>
#include "cybsp.h"
#include "cy_utils.h"
#include "cy_retarget_io.h"

/*******************************************************************************
* Defines
*******************************************************************************/
/* Define macro to enable/disable printing of debug messages */
#define ENABLE_DEBUG_PRINT              (0)

/* Define macro to set the loop count before printing debug messages */
#if ENABLE_DEBUG_PRINT
#define DEBUG_LOOP_COUNT_MAX                (1U)
#endif

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
* This is the main function. It sets up the comparator to receive Reference
* voltage on IN-P pin.Bit field CMP_OUT of ANACMP1 register changes its state
* based on the input applied on IN-N pad. The input to Comparator pin IN-N (Pin 2.6)
* can be modified to see ANACMP1:CMP_OUT register status to change. An LED is
* toggled depending upon the register status.
*
* Parameters:
*  none
*
* Return:
*  int
*
*******************************************************************************/

int main(void)
{
    cy_rslt_t result;

    #if ENABLE_DEBUG_PRINT
    /* Assign false to disable printing of debug messages*/
    static volatile bool debug_printf = true;
    /* Initialize the current loop count to zero */
    static uint32_t debug_loop_count_high = 0;
    static uint32_t debug_loop_count_low = 0;
    #endif

    /* Initialize the device and board peripherals */
    result = cybsp_init();
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Initialize retarget-io to use the debug UART port */
    result = cy_retarget_io_init(CYBSP_DEBUG_UART_HW);
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    #if ENABLE_DEBUG_PRINT
    printf("Initialization done\r\n");
    #endif

    /* Users may now apply inputs on P2.6 and evaluate USER LED output */
    while(1U)
    {
        /* Toggle USER LED depending on comparator output */
        if((COMPARATOR->ANACMP1) & COMPARATOR_ANACMP1_CMP_OUT_Msk)
        {
            #if ENABLE_DEBUG_PRINT
            debug_loop_count_high++;
            if (debug_printf && debug_loop_count_high == DEBUG_LOOP_COUNT_MAX)
            {
                debug_printf = false;
                /* Print message after the loop has run DEBUG_LOOP_COUNT_MAX times */
                printf("Turns LED ON because comparator output is high\r\n");
            }
            #endif
            /* Output low turns LED ON when comparator output is high */
            Cy_GPIO_SetOutputLow(CYBSP_USER_LED_PORT, CYBSP_USER_LED_PIN);
        }
        else
        {
            #if ENABLE_DEBUG_PRINT
            debug_loop_count_low++;
            if (debug_printf && debug_loop_count_low == DEBUG_LOOP_COUNT_MAX)
            {
                debug_printf = false;
                /* Print message after the loop has run DEBUG_LOOP_COUNT_MAX times */
                printf("Turns LED OFF because comparator output is low\r\n");
            }
            #endif
            /* Output low turns LED OFF when comparator output is low */
            Cy_GPIO_SetOutputHigh(CYBSP_USER_LED_PORT, CYBSP_USER_LED_PIN);
        }
        /* Infinite loop */
    }
}

/* [] END OF FILE */
