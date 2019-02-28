#include <stdio.h>

int volt_to_dac(double volt)
{
	return ((int)((1<<24)*volt)/24) &((1<<24)-1);
}

int main(void)
{
	printf("9.7v를 출력하기 위한 DAC값은 %d\n",volt_to_dac(9.7));
	return 0;
}
