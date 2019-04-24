/*
*copyright (C) 2013 - 2016  Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person
* obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without restriction,
* including without limitation the rights to use, copy, modify, merge,
* publish, distribute, sublicense, and/or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or (b) that interact
* with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in this
* Software without prior written authorization from Xilinx.
*
*/



#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#define I2C_FILE_NAME	"/dev/i2c-0" //vivodo에서 설정한 것

#define X_H					0
#define X_L					1
#define Y_H					2
#define Y_L					3
#define Z_H					4
#define Z_L					5

#define ACCEL_CONFIG		0x1c
#define INI_STATUS			0x3A

#define ACCEL_XOUT_H		0x3B
#define ACCEL_XOUT_L		0x3C
#define ACCEL_YOUT_H		0x3D
#define ACCEL_YOUT_L		0x3E
#define ACCEL_ZOUT_H		0x3F
#define ACCEL_ZOUT_L		0x40

#define TEMP_OUT_H			0x41
#define TEMP_OUT_L			0x42

#define GYRO_XOUT_H			0x43
#define GYRO_XOUT_L			0x44
#define GYRO_YOUT_H			0x45
#define GYRO_YOUT_L			0x46
#define GYRO_ZOUT_H			0x47
#define GYRO_ZOUT_L			0x48


#define I2C_SLV0_D0			0X63
#define I2C_SLV1_D0			0X64
#define I2C_SLV2_D0			0X65
#define I2c_SLV3_D0			0X66

#define PWR_MGMT_1			0x6B

#define FIFO_COUNTH			0x72
#define FIFO_COUNTL			0x73

#define WHO_AM_I			0x75

#define MPU6050_ADDR		0x68

#define AF_SEL_ACCEL_RANGE_2G	0 << 3
#define AF_SEL_ACCEL_RANGE_4G   1 << 3
#define AF_SEL_ACCEL_RANGE_8G   2 << 3
#define AF_SEL_ACCEL_RANGE_16G  3 << 3

int mpu6050_init(int addr)
{
	int fd;

	if((fd = open(I2C_FILE_NAME, O_RDWR))<0)
	{
		perror("Failed to open I2C Bus\n");
		return -1;
	}

    //slave로 구동시킬 것으로 명시
	if(ioctl(fd, I2C_SLAVE, MPU6050_ADDR) < 0)
	{
		perror("Failed to acquire Bus Access\n");
		return -1;
	}

	return fd;
}

inline void mpu6050_deinit(int fd)
{
	close(fd);
}

void mpu6050_write_reg(int fd, uint8_t reg, uint8_t val)
{
	uint8_t data[2];

	data[0] = reg;
	data[1] = val;

	if(write(fd, data, 2)!=2)
		perror("mpu6050 write error!");
}

uint16_t mpu6050_select_range(int fd, uint16_t range)
{
	int sense;

	mpu6050_write_reg(fd, ACCEL_CONFIG, range);
	switch(range)
	{
		case AF_SEL_ACCEL_RANGE_2G:
			sense = 0x4000;
			break;
		case AF_SEL_ACCEL_RANGE_4G:
			sense = 0x2000;
			break;
		case AF_SEL_ACCEL_RANGE_8G:
			sense = 0x1000;
			break;
		case AF_SEL_ACCEL_RANGE_16G:
			sense = 0x0800;
			break;
	}

	return sense;
}

uint8_t mpu6050_read_reg(int fd, uint8_t reg)
{
	unsigned char data[3];

	if(write(fd, data, 1)!=1)
	{
		perror("Error Sending read request via i2c\n");
		return -1;
	}

	if(read(fd, data, 1)!=1)
	{
		perror("Error Getting read request via i2c\n");
	}

	return data[0];
}	

inline void mpu6050_power_on(int fd)
{
	mpu6050_write_reg(fd, PWR_MGMT_1, 0x0);
}


int16_t mpu6050_read_reg_pair(int fd, uint8_t reg)
{
	uint8_t data[3];

	data[0] = reg;

	if(write(fd, data, 1)!=1)
	{
		perror("Error Sending read request via i2c\n");
		return -1;
	}

	if(read(fd, data, 2)!=2)
	{
		perror("Error Getting read request via i2c\n");
		return -1;
	}

	return (data[0] << 8) | data[1];
}

inline float mpu6050_get_temp(int fd)
{
	return (float)(mpu6050_read_reg_pair(fd, TEMP_OUT_H) / 340 + 36.53);
}	

int main(int argc, char **argv)
{
	float temper, acc_x, acc_y, acc_z;
	int16_t gyro_x, gyro_y, gyro_z;
	int fd, whoami = 0, sense;

	if((fd = mpu6050_init(MPU6050_ADDR))<0)
	{
		printf("Can't Init MPU6050\n");
		return -1;
	}

	sense = mpu6050_select_range(fd, AF_SEL_ACCEL_RANGE_16G);

	mpu6050_power_on(fd);

	whoami = mpu6050_read_reg(fd, WHO_AM_I);
	printf("Sensor ID: 0x%x\n", whoami);

	for(;;)
	{
		temper = mpu6050_get_temp(fd);
		acc_x = ((float)(mpu6050_read_reg_pair(fd, ACCEL_XOUT_H)))/sense;
		acc_y = ((float)(mpu6050_read_reg_pair(fd, ACCEL_YOUT_H)))/sense;
		acc_z = ((float)(mpu6050_read_reg_pair(fd, ACCEL_ZOUT_H)))/sense;
		printf("Temper:%.3f\tacc(x):%.3f\tacc(y):%.3f\tacc(z):%.3f\n", temper, acc_x, acc_y, acc_z);
		usleep(200000);
	}
	mpu6050_deinit(fd);
    return 0;
}
