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
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
#include "HL_system.h"
#include "HL_sci.h"
#include "HL_gio.h"
/* USER CODE END */
#define TSIZE 12
uint8 text[TSIZE]="0123456789\n\r";

void sci_display(sciBASE_t *sci,uint8 *text, uint32 len);

void wait(uint32 time);

int main(void)
{
/* USER CODE BEGIN (3) */
    sciInit();
    gioInit();
    sciSetBaudrate(sciREG1,9600);
    gioSetDirection(gioPORTA,0xFFFFFFFF);
    gioSetPort(gioPORTA,0x00000000);

    for(;;)
    {
        sci_display(sciREG1,text,TSIZE);
    }
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
void sci_display(sciBASE_t *sci, uint8 *tex, uint32 len)
{
       while(len--)
       {
           while((sciREG1->FLR & 0x4)==4);

           if((!(*tex-'0')%3) && (*tex != '0')&&(*tex>='0')&&(*tex<='9'))
               gioSetPort(gioPORTA,1<<(uint32)((*tex-'0')/3)+3);
           else
               gioSetPort(gioPORTA,0x00000000);

           sciSendByte(sciREG1,*(tex++));
           wait(3333333);
       }
}

void wait(uint32 time)
{
    uint32 i = 0;
    for(i = time;i>0;i--);
}
/* USER CODE END */
