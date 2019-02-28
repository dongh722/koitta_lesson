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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HL_gio.h"
#include "HL_sci.h"
#include "HL_ecap.h"
#include "HL_etpwm.h"
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
void wait(uint32 delay);
void sci_display(sciBASE_t *sci, uint8 *text, uint32 len);
void put_pwm(void);
void calculate_persent(uint16 data);
void calv_bldc(void);
void disp_set(char *str);

volatile uint16 pwm_data =0;

char buf[128];
unsigned int buf_len;
volatile int throttle;
int aileron;
int elevator;
int rudder;
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    sciInit();

    sprintf(buf, "SCI Init Success\n\r\0");
    buf_len = strlen(buf);
    sci_display(sciREG1, (uint8 *)buf, buf_len);

    gioInit();

    sprintf(buf, "GIO Init Success\n\r\0");
    buf_len = strlen(buf);
    sci_display(sciREG1, (uint8 *)buf, buf_len);

    etpwmStartTBCLK();
    calv_bldc();

    ecapInit();

    sprintf(buf, "ECAP Init Success\n\r\0");
    buf_len = strlen(buf);
    sci_display(sciREG1, (uint8 *)buf, buf_len);

    _enable_interrupt_();

    ecapStartCounter(ecapREG1);
    ecapStartCounter(ecapREG2);
    ecapStartCounter(ecapREG3);
    ecapStartCounter(ecapREG4);

    ecapEnableCapture(ecapREG1);
    ecapEnableCapture(ecapREG2);
    ecapEnableCapture(ecapREG3);
    ecapEnableCapture(ecapREG4);

   for(;;)
    {
       put_pwm();
       wait(100);
       calculate_persent(pwm_data);
    }

/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
void wait(uint32 delay)
{
    int i;
    for(i = 0; i < delay; i++)
        ;
}

void sci_display(sciBASE_t *sci, uint8 *text, uint32 len)
{
    while(len--)
    {
        while((sciREG1->FLR & 0x4) == 4)
            ;
        sciSendByte(sci, *text++);
    }
}

void put_pwm(void)
{
    if(throttle >=1000)
        pwm_data= throttle;
    etpwmSetCmpA(etpwmREG1,pwm_data);
}

void calv_bldc(void)
{
    wait(1000);

    etpwmSetCmpA(etpwmREG1,1000);
    wait(1000000);
    etpwmSetCmpA(etpwmREG1,2000);
    wait(1000000);
    etpwmSetCmpA(etpwmREG1,1000);
}

void calculate_persent(uint16 data)
{
    char tmp[128] = {0,};
    float persent =0;
    unsigned int buf_len;

    persent = (float)pwm_data/20000.0;
    sprintf(tmp,"pwm persent = %f\n\r",persent);
    buf_len = strlen(tmp);

    sci_display(sciREG1, (uint8 *)tmp, buf_len);
    wait(100000);
}

void ecapNotification(ecapBASE_t *ecap, uint16 flags)
{
    uint32 cap[9];

    cap[0] = ecapGetCAP1(ecapREG1);
    cap[1] = ecapGetCAP2(ecapREG1);
    cap[3] = ecapGetCAP1(ecapREG2);
    cap[4] = ecapGetCAP2(ecapREG2);
    cap[5] = ecapGetCAP1(ecapREG3);
    cap[6] = ecapGetCAP2(ecapREG3);
    cap[7] = ecapGetCAP1(ecapREG4);
    cap[8] = ecapGetCAP2(ecapREG4);

    //channel1
    aileron = (cap[3]-cap[2])*1000 /VCLK3_FREQ /1000;
    //channel2
    elevator = (cap[1]-cap[0])*1000 /VCLK3_FREQ /1000;
    //channel 3
    throttle = (cap[1] - cap[0]) * 1000 /VCLK3_FREQ /1000;
    //channel4
    rudder = (cap[7]-cap[6])*1000 /VCLK3_FREQ /1000;

    if(throttle >1700)
        gioSetBit(gioPORTA, 4, 1);
    else
        gioSetBit(gioPORTA, 4, 0);

    sprintf(buf, "ch1 = %d ms\tch2= %d ms\t ch3 = %d ms\t ch4 = %d ms\n\r\0",aileron,elevator,throttle,rudder);
    buf_len = strlen(buf);
    sci_display(sciREG1, (uint8 *)buf, buf_len);

    wait(100000);
}
/* USER CODE END */
