#include <iostream>
#include <stdlib.h>
#include <string.h>

//private 안되는 케이스

using namespace std;
class Person
{
private:
	int age;
	char name[32];
	char job[32];
public:
	int getAge(void);
	void setAge(int old);

	char *getName(void);
	void setName(char *nm);
	
	char *getJob(void);
	void setJob(char *j);
	
};

void Person::setAge(int old)
{
	age = old;
}

int Person::getAge(void)
{
	return age;
}

void Person::setName(char *nm)
{
	strcpy(name,nm);
}

char *Person::getName(void)
{
	return name;
}

void Person::setJob(char *j)
{
	strcpy(job,j);
}
char *Person::getJob(void)
{
	return job;
}

int main(void)
{
	char data[32] = "나바보";
	Person p = Person();

	p.setAge(41);
	cout<<"age= "<<p.getAge()<<endl;

	p.setName("김민호");
	cout<<"name= "<<p.getName()<<endl;

	p.setJob("백수");
	cout<<"Job= "<<p.getJob()<<endl;

	p.age = 23;
	strcpy(p.name,data);
	strcpy(p.job,"바보");

	cout<<"age = "<<p.getAge()<<endl;
	cout<<"name = "<<p.getName()<<endl;
	cout<<"job = "<<p.getJob()<<endl;

	return 0;
}
