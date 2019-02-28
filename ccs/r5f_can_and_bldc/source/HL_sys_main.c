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
#include "HL_can.h"
#include "HL_sci.h"
#include "HL_esm.h"
#include "HL_system.h"
#include "HL_sys_core.h"
#include "HL_etpwm.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#define DCNT    8 //data count
#define DSIZE   8
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
void wait(uint32 delay);
void disp_set(char *str);
void sciDisplayText(sciBASE_t *sci, uint8 *text, uint32 len);

uint32 cnt = 0;
uint32 err = 0;
uint32 tx_done = 0;
uint8 rx_data[DCNT] = {0,};
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    uint32 i = 0;
    uint32 tmp =0;
    char txt_buf[256] = {0};
    uint32 buf_len;

    sciInit();
    gioInit();
    disp_set("gio init success\n\r\0");

    _enable_IRQ_interrupt_();
    canInit();
    disp_set("can init success\n\r\0");

    etpwmInit();
    etpwmStartTBCLK();
    disp_set("pwm init success\n\r\0");

    canEnableErrorNotification(canREG1);
    disp_set("finish initialize\n\r\0");

    for(;;)
    {
        switch(rx_data[0]-'0')
        {
        case 7:
            for(i = 1;i<5;i++)
            {
                tmp += (rx_data[i]-48)*pow(10,cnt--);
                sprintf(txt_buf, "rx_data[%d] = 0x%x\n",i,rx_data[i]);
                buf_len = strlen(txt_buf);
                sciDisplayText(sciREG1,(uint8 *)txt_buf,buf_len);
            }

            etpwmREG1->CMPA = tmp;
            break;
        }
        memset(rx_data,0,sizeof(rx_data));
        cnt =3;

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

void disp_set(char *str)
{
    char txt_buf[256] = {0};
    unsigned int buf_len;
    sprintf(txt_buf, str);
    buf_len = strlen(txt_buf);
    sciDisplayText(sciREG1, (uint8 *)txt_buf, buf_len);
    wait(100000);
}

void sciDisplayText(sciBASE_t *sci, uint8 *text, uint32 len)
{
    while(len--)
    {
        while((sciREG1->FLR & 0x4) == 4)
            ;
        sciSendByte(sciREG1, *text++);
    }
}

void canMessageNotification(canBASE_t *node, uint32_t notification)
{
    char txt_buf[256] = {0,};
    uint32 buf_len;

    if(node == canREG1)
    {
        while(!canIsRxMessageArrived(canREG1, canMESSAGE_BOX2))
            ;

        canGetData(canREG1, canMESSAGE_BOX2, (uint8 *)&rx_data[0]);

        sprintf(txt_buf, "rx_data : %x\n", rx_data);
        buf_len = strlen(txt_buf);
        sciDisplayText(sciREG1,(uint8 *)txt_buf,buf_len);
    }
}
/* USER CODE END */
