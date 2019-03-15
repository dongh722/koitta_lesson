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
#include "HL_rti.h"
#include "HL_gio.h"
#include "HL_adc.h"
#include "HL_system.h"
#include "HL_etpwm.h"
#include <stdlib.h>

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

uint32 check_pwmvalue =0;
float32 now_deg[2] ={0,0};
float32 ang_val[2] ={0,0};
float32 ang_acc =0;
float32 mov_deg =0;

uint16 main_start_flag =0;
uint16 vel_acc_cal_flag =0;
adcData_t adc_data[8];
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    uint32 pwmvalue =0;

    gioInit();
    gioSetDirection(gioPORTB,0x01); //adc trigger port direction output

    adcInit();
    adcStartConversion(adcREG1,adcGROUP1);

    etpwmInit();
    etpwmStartTBCLK();

    rtiInit();
    rtiEnableNotification(rtiREG1,rtiNOTIFICATION_COMPARE0);
    _enable_IRQ_interrupt_();
    rtiStartCounter(rtiREG1, rtiCOUNTER_BLOCK0);


    gioSetBit(gioPORTB,0,1); //trigger high
    while((adcIsConversionComplete(adcREG1,adcGROUP1))==0)
        ;
    adcGetData(adcREG1, adcGROUP1,&adc_data[0]);
    srand(adc_data[0].value);   //cds 센서로 adc값을 받아와 임의의 seed값을 만든다.
    gioSetBit(gioPORTB,0,0); //trigger low
    wait(1000);

    for(;;)
    {
        main_start_flag =1;
        pwmvalue = rand()%2000;
        if(pwmvalue<1000)
            pwmvalue =1000;
        etpwmSetCmpA(etpwmREG1,pwmvalue);

        wait(100000);
    }
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
//rti 주기 100ms
void rtiNotification(rtiBASE_t *rtiREG,uint32 notification)
{
    if(main_start_flag)
    {
        check_pwmvalue = etpwmREG1->CMPA;

        now_deg[0] = (check_pwmvalue-1000)*180/1000;    //pwm 각도 변

        if(vel_acc_cal_flag)
        {
            ang_val[0] = (now_deg[0] - now_deg[1])/0.1;           //각속도
            ang_acc = (ang_val[0]-ang_val[1])/0.1;                //각가속도
            mov_deg += ang_val[0]*0.1; //회전 각도
        }

        now_deg[1]=now_deg[0];
        ang_val[1] = ang_val[0];
        vel_acc_cal_flag=1;
    }
}

void wait(uint32 delay)
{
    int wait_cnt;
    for(wait_cnt=0;wait_cnt<delay;wait_cnt++)
        ;
}
/* USER CODE END */
