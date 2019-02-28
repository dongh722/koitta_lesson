#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define SAMPLING_TIME 0.001

using namespace std;

class Sample
{
private:
	int time[256];
	int velocity[256];
public:
	Sample(void);
	Sample(int *time,int *velocity);
	void setTime(int *t);
	void setVel(int *v);
	void printData(void);

	friend double integral(Sample *a);
};

Sample::Sample(void)
{
	memset(time,0x0,sizeof(time));
	memset(velocity,0x0,sizeof(velocity));
}

Sample::Sample(int *time,int *velocity)
{
	int cnt =0;
	memset(this->time,0x0,sizeof(this->time));
	memset(this->velocity,0x0,sizeof(this->velocity));

	for(cnt =0;time[cnt];cnt++)
		this->time[cnt]=time[cnt];

	for(cnt =0;sizeof(velocity)/sizeof(int);cnt++)
		this->velocity[cnt]=velocity[cnt];
}

void Sample::setTime(int *t)
{
	int cnt = 0;

	for(cnt=0;cnt<256;cnt++)
		time[cnt]=t[cnt];
}
void Sample::setVel(int *v)
{
	int cnt =0;	

	for(cnt=0;cnt<256;cnt++)
		velocity[cnt] = v[cnt];
}

void Sample::printData(void)
{
	int cnt =0;

	for(cnt=0;cnt<256;cnt++)
	{
		cout<<"time = "<<time[cnt]<<" sample";
		cout<<", vel = "<<velocity[cnt]<<" m/s";
		cout<<endl;
	}
}

double integral(Sample *a)
{
	int cnt=0;
	int sum=0;
	double result =0;	
	for(cnt=1;cnt<256;cnt++)
	{
		sum += a->velocity[cnt]+a->velocity[cnt-1];
	}

	result = (double)sum*SAMPLING_TIME/2.0;
	return result;
}

int main(void)
{
	int cnt =0;
	int t[256];
	int v[256];
	double velu=0;
	srand(time(NULL));
	Sample s;
	for(cnt=0;cnt<256;cnt++)
	{
		t[cnt]=cnt+1;
		v[cnt]=rand()%201 -75;
	}

	s.setVel(v);
	s.setTime(t);

	s.printData();

	velu = integral(&s);
	cout<<"velue = "<<velu<<"m"<<endl;
	return 0;
}
