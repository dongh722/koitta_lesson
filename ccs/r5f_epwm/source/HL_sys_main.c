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
#include "HL_sci.h"
#include "HL_etpwm.h"
#include <string.h>
#include <stdio.h>
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
#define MAX 50
volatile int32_t delay;
int32_t etpwm1B_duty=0, etpwm4A_duty =0, etpwm6B_duty;
uint8 receive_data =0;

void catch_command(void);
void wait(uint32 time);
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    int32_t flag =0;
    int32_t tmp = MAX;
    sciInit();
    etpwmInit();

    for(;;)
    {
        etpwmStartTBCLK();
        if(!(sciREG1->FLR & (uint32)SCI_RX_INT) && flag ==0)
        {
            wait(100000);

            if(etpwm4A_duty>=(tmp + 50))
                etpwm4A_duty =0;
            else
                etpwm4A_duty++;
            etpwmSetCmpA(etpwmREG4,etpwm4A_duty);

            wait(100000);

            if(etpwm6B_duty>=(tmp + 50))
                etpwm6B_duty =0;
            else
                etpwm6B_duty++;
            etpwmSetCmpB(etpwmREG6,etpwm6B_duty);

            wait(100000);

            if(etpwm1B_duty>=(tmp + 50))
                etpwm1B_duty =0;
            else
                etpwm1B_duty++;
            etpwmSetCmpB(etpwmREG1,etpwm1B_duty);
        }
        else if(!(sciREG1->FLR & (uint32)SCI_RX_INT) && flag ==1)
        {
            wait(100000);

             if(etpwm4A_duty>=tmp)
                 etpwm4A_duty =0;
             else
                 etpwm4A_duty++;
             etpwmSetCmpA(etpwmREG4,etpwm4A_duty);

             wait(100000);

             if(etpwm6B_duty>=tmp)
                 etpwm6B_duty =0;
             else
                 etpwm6B_duty++;
             etpwmSetCmpB(etpwmREG6,etpwm6B_duty);

             wait(100000);

             if(etpwm1B_duty>=tmp)
                 etpwm1B_duty =0;
             else
                 etpwm1B_duty++;
             etpwmSetCmpB(etpwmREG1,etpwm1B_duty);
        }
        else
        {
            catch_command();
            if(receive_data == '5')
             {
                flag =1;
                etpwm4A_duty = tmp -20;
                etpwm6B_duty = tmp -20;
                etpwm1B_duty = tmp -20;
              }
             else if(receive_data == '0')
              {
                 flag =0;
                 etpwm4A_duty = 0;
                 etpwm6B_duty = 0;
                 etpwm1B_duty =0;
               }
        }
        etpwmStopTBCLK();
    }
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
void catch_command(void)
{
   while((sciREG1->FLR & 0x4)==0x4);
    receive_data = sciReceiveByte(sciREG1);
}

void wait(uint32 time)
{
    uint32 i = 0;
    for(i = time;i>0;i--);
}
/* USER CODE END */
