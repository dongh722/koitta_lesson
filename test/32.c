#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define PI 3.141592i

double my_sin(double x,int n)
{
	double sum=0;
	int i,j;
	double a =x-0.001;
	long fac =1;
	for(i=0;i<n;i++)
	{

		for (j=(i-1);j>=0;j--)
			fac *= (j+1);

		switch(i%4)
		{
			case 0:
				sum += (sin(a)/(double)fac)*pow((x-a),i);
				break;
			case 1:
				sum += (cos(a)/(double)fac)*pow((x-a),i);
				break;
			case 2:
				sum += (-sin(a)/(double)fac)*pow((x-a),i);
				break;
			case 3:
				sum += (-cos(a)/(double)fac)*pow((x-a),i);
			break;
		}
	}
	return sum;
}

int main(void)
{
	srand(time(NULL));
	double x = (rand()/1000);
	printf("임의의 x에 대한 sin값은 %f my_sin값은 %f\n",sin(x),my_sin(x,10));
		return 0;
}

