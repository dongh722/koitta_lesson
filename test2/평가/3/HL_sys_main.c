/** @file HL_sys_main.c 
*   @brief Application main file
*   @date 08-Feb-2017
*   @version 04.06.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2016 Texas Instruments Incorporated - www.ti.com  
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "HL_sys_common.h"

/* USER CODE BEGIN (1) */
#include "HL_gio.h"
#include "HL_adc.h"
#include "HL_system.h"
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
void wait(uint32);

adcData_t adc_data[8];
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    uint32 ch_cnt = 0;
    uint32 id = 0;
    uint32 value = 0;

    gioInit();
    gioSetDirection(gioPORTA,0x0001<<4); //led port direction output
    gioSetDirection(gioPORTB,0x01); //adc trigger port direction output

    adcInit();
    adcStartConversion(adcREG1,adcGROUP1);

    gioSetBit(gioPORTB,0,0);//trigger low

    for(;;)
    {
        gioSetBit(gioPORTB,0,1); //trigger high
        while((adcIsConversionComplete(adcREG1,adcGROUP1))==0)
            ;
        ch_cnt = adcGetData(adcREG1, adcGROUP1,&adc_data[0]);

        id = adc_data[0].id;
        value = adc_data[0].value;

        gioSetBit(gioPORTB,0,0);

        if((value>=128) && (id ==0))
            gioSetBit(gioPORTA,4,1);
        else
            gioSetBit(gioPORTA,4,0);
        wait(100000);
    }
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
void wait(uint32 delay)
{
    int wait_cnt;
    for(wait_cnt=0;wait_cnt<delay;wait_cnt++)
        ;
}
/* USER CODE END */
