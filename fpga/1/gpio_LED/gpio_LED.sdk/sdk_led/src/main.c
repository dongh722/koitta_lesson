/*
 * main.c
 *
 *  Created on: 2019. 3. 20.
 *      Author: kiott01a
 */

#include <stdio.h>
#include <xgpio.h>
#include "xparameters.h"
#include "sleep.h"

int main(void)
{
		XGpio out;

		XGpio_Initialize(&out, XPAR_AXI_GPIO_0_DEVICE_ID);
		XGpio_SetDataDirection(&out, 1, 0x0);

		for(;;)
		{
				Xil_Out32(0x41200000, 0xFFFFFFFF);
				sleep(1);
				Xil_Out32(0x41200000, 0x0);
				sleep(1);
		}

		return 0;
}
