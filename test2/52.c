#include <stdio.h>
#include <math.h>
#include <glut.h>
#include <gl.h>
#include <glu.h>

#define DELTA 0.00025
#define PERIOD (M_PI*2.0000)
#define ORDER	100
#define NUMBER_OF_SAMPLE 1000
//15초 마다 0.1%씩 계산이 완료 됩니다.

double function(double x)
{
	if((x > -M_PI) && (x <= 0))
		return 0.000;
	else if((x>0) && (x <= M_PI))
		return 2.000;
	else if(x>M_PI)
		return function(x-PERIOD);
	else
		return function(x+PERIOD);
}

double integral(double start, double end,double (*func)(double))
{
	double sum=0;
	long cnt =0;
	long max;

	max =(long)((end-start)/DELTA);

	while(cnt<max)
	{
		sum += func(start+(double)cnt*DELTA)*DELTA;
		cnt++;
	}

	return sum;
}

int order_num =0;
double (*tmp_func)(double) =NULL;

double Sin_coef_func2(double x)
{
	return tmp_func(x)*sin(2.0*M_PI*(double)order_num*x/PERIOD);
}

double Cos_coef_func2(double x)
{
	return tmp_func(x)*cos(2.0*M_PI*(double)order_num*x/PERIOD);
}

double (*Sin_coef_func(double (*func)(double),int n))(double)
{
	order_num =n;
	tmp_func =func;
	return Sin_coef_func2;
}

double (*Cos_coef_func(double (*func)(double),int n))(double)
{
	order_num =n;
	tmp_func =func;
	return Cos_coef_func2;
}

void Find_Fourier_Coefficient(double (*func)(double),int n,double *coefficient_array)
{
	int cnt;
	double tmp =0;

	for(cnt =0;cnt<=n;cnt++)
	{
		if(cnt ==0)
		{
			tmp=integral(-PERIOD/2,PERIOD/2,func)/PERIOD;
			if(tmp>-DELTA && tmp<DELTA)
				tmp =0.000;
			*coefficient_array = tmp;
			*(coefficient_array+ORDER+1) = 0.000;
		}
		else
		{
			
			tmp =  integral(-PERIOD/2,PERIOD/2,Cos_coef_func(func,cnt))*2.0/PERIOD;
			if(tmp>-DELTA && tmp<DELTA)
				tmp =0.000;
			*(coefficient_array+cnt) = tmp;
			
			tmp= integral(-PERIOD/2,PERIOD/2,Sin_coef_func(func,cnt))*2.0/PERIOD;
			if(tmp>-DELTA && tmp<DELTA)
				tmp =0.000;
			*(coefficient_array+ORDER+1+cnt) =tmp;
			
		}
	}
}

double Fourier_Trans_Function(double (*func)(double),double x)
{
	int cnt;
	double coef[2][ORDER+1] ={{0,},{0,}};
	double sum=0;
	
	Find_Fourier_Coefficient(func,ORDER,coef[0]);

	for(cnt =0; cnt<=ORDER;cnt++)
	{
		if(cnt==0)
			sum += coef[0][0];
		else
			sum += coef[0][cnt]*cos(2.0*(double)cnt*M_PI*x/PERIOD) + coef[1][cnt]*sin(2.0*(double)cnt*M_PI*x/PERIOD);
	}

	return sum;
}

int main (void)
{
	long cnt;
	long cnt2 =0;
	cnt =-NUMBER_OF_SAMPLE/2;
	double tmp[10000] ={0,};
	double persent=0; 

	while(cnt<=NUMBER_OF_SAMPLE/2)
	{ 
		tmp[cnt2] = Fourier_Trans_Function(function,DELTA*100*cnt);
		cnt++;
		cnt2++;
		persent =(double)cnt2*100.000/(double)NUMBER_OF_SAMPLE;
		printf("cal %lf %%\n",persent);
	}
		cnt=-NUMBER_OF_SAMPLE/2;
		cnt2=0;

	while(cnt<=NUMBER_OF_SAMPLE/2)
	{

		glColor3f(0.0,1.0,1.0);
		printf("Original (%lf,%lf)\n",DELTA*100*cnt , function(DELTA*100*cnt));
		printf("Trans    (%lf,%lf)\n",DELTA*100*cnt , tmp[cnt2]);
		printf("\n");
		cnt++;
		cnt2++;
	}

	return 0;
}
