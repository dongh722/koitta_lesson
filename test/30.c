#include <stdio.h>

double adc_to_volt(int adc)
{
	int tmp =0;

	tmp = adc<<16;
	tmp = tmp/(1<<16);

	return (double)tmp*10.0/(double)(1<<16);
}

int main(void)
{
	printf("12677 adc값의 voltage 값은 %f V\n",adc_to_volt(12677));
	return 0;
}
