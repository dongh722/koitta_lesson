#include <stdio.h>

#define SAMPLING_DELTA 0.001
double integral(int st, int end)
{
	int i;
	double sum=0;
	double x1 =0;
	double x2 =0;
	for(i=(st/SAMPLING_DELTA)+1;i<=(end/SAMPLING_DELTA);i++)
	{
		x1=(double)i*SAMPLING_DELTA;
		x2=(double)(i-1)*SAMPLING_DELTA;
		sum += ((3*x1*x1+7*x1)+(3*x2*x2+7*x2))*SAMPLING_DELTA/2;
	}
	return sum;
}

int main(void)
{
	int result =0;

	printf("1~2까지 3*x^2 +7*x의 정정분 값은 %f이다.\n",integral(1,2));
	return 0;
}
