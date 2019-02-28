/** @file HL_sys_main.c
*   @brief Application main file
*   @date 07-July-2017
*   @version 04.07.00
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
#include "HL_sci.h"
#include "HL_adc.h"
#include "HL_system.h"

#define SIZE1 12
#define SIZE2 9
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
uint8 TXT1[SIZE1]= {'\r','\n','|','\t','c','h','.','I','D','=','0','x'};
uint8 TXT2[SIZE2] = {'\t','v','a','l','u','e','=','0','x'};
adcData_t adc_data[2];

void sci_display_txt(sciBASE_t  *,uint8 *, uint32);
void sci_display_data(sciBASE_t *,uint8 *, uint32);
void wait(uint32 delay);
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    uint32 ch_cnt = 0;
    uint32 id = 0;
    uint32 value = 0;

    gioInit();
    gioSetDirection(gioPORTB,0x01);
    sciInit();

    adcInit();
    adcStartConversion(adcREG1,adcGROUP1);
    gioSetBit(gioPORTB,0,0);

    for(;;)
    {
        gioSetBit(gioPORTB,0,1);
        while((adcIsConversionComplete(adcREG1,adcGROUP1))==0)
            ;
        ch_cnt = adcGetData(adcREG1, adcGROUP1,&adc_data[0]);

        id = adc_data[0].id;
        value = adc_data[0].value;

        gioSetBit(gioPORTB,0,0);

        sci_display_txt(sciREG1, &TXT1[0],SIZE1);
        sci_display_data(sciREG1,(uint8 *)&id,4);
        sci_display_txt(sciREG1, &TXT2[0],SIZE1);
        sci_display_data(sciREG1,(uint8 *)&value,4);

        wait(0x100000);
    }
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
void wait(uint32 delay)
{
    int i;

    for (i = 0; i < delay; i++)
        ;
}

void sci_display_data(sciBASE_t *sci, uint8 *data, uint32 len)
{
    uint8 data1 =0;
    uint8 data2 =0;

    while(len--)
    {
        data1 = *data++;
        data2 = data1;
        data1 &= ~(0xF0);
        data2 &= ~(0x0F);
        data2= data1>>4;

        if(data1 <= 0x9)
            data1 += 0x30;
        else if(data1>0x9 && data1<=0xF)
            data1 +=0x37;
        else
            data1 = '0';

        if(data2 <= 0x9)
            data2 += 0x30;
        else if(data2>0x9 && data2<=0xF)
            data2 +=0x37;
        else
            data2 = 0x30;

        while((sciREG1->FLR &0x4)==0x4)
            ;
        sciSendByte(sciREG1,data2);

        while((sciREG1->FLR &0x4)==0x4)
            ;
        sciSendByte(sciREG1,data1);
    }
}

void sci_display_txt(sciBASE_t *sci, uint8 *txt, uint32 len)
{
    while(len--)
    {
        while((sciREG1->FLR &0x4)==0x4)
            ;
        sciSendByte(sciREG1,*(txt++)+'0');


    }
}
/* USER CODE END */
