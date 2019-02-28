#include <iostream>
#include <string.h>

using namespace std;

class Car
{
private:
	int speed;
	char color[32];
public:	
	Car(void);
	Car(int sp,char *c);
	void setSpeed(int s);
	int getSpeed(void);
	void setColor(char *c);
	char *getColor(void);
};

//생성자는 return 타입을 쓰면 안된다.
Car::Car(void)
{
	cout<<"I'm Car Default Constructor!!!"<<endl;
}

Car::Car(int sp,char *c)
{
	speed = sp;
	strncpy(color,c,strlen(c));
	cout<< "I'm Car Default constructor too"<<endl;
}

void Car::setSpeed(int s)
{
	speed =s;
}

int Car::getSpeed(void)
{
	return speed;
}

void Car::setColor(char *c)
{
	strcpy(color,c);
}

char *Car::getColor(void)
{
	return color;
}

int main(void)
{
	Car c =Car();
	cout<<"speed= "<<c.getSpeed()<<endl;
	cout<<"color= "<<c.getColor()<<endl;

	c.setSpeed(180);
	cout <<"speed= "<<c.getSpeed()<<endl;

	c.setColor("파랑");
	cout << "색상 = "<<c.getColor()<<endl;
 
	Car c2 = Car(300,"빨강");
	cout<<"speed= "<<c.getSpeed()<<endl;
	cout<<"color= "<<c.getColor()<<endl;
	return 0;
}
