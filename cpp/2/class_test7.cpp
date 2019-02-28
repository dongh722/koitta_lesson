#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

class Person
{
private:
	int age;
	char name[32];
	char job[32];
public:
	Person(void);
	Person(int ag,char *nam, char *j);
	int getAge(void);
	void setAge(int old);

	char *getName(void);
	void setName(char *nm);
	
	char *getJob(void);
	void setJob(char *j);
	
};

Person::Person(void)
{
	char ch[32]="남자";
	char ch2[32]="천사";
	cout<<"Constructor1"<<endl;
	age = 10;

	memset(name,0x0,sizeof(name));
	memset(job,0x0,sizeof(job));

	strncpy(name,ch,strlen(ch));
	strncpy(job,ch2,strlen(ch2));
}

Person::Person(int ag, char *nam, char *j)
{
	cout<<"constructor2"<<endl;

	memset(name,0x0,sizeof(name));
	memset(job,0x0,sizeof(job));

	age = ag;
	strncpy(name,nam,strlen(nam));
	strncpy(job,j,strlen(j));
}


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
	memset(name,0x0,sizeof(name));
	strncpy(name,nm,strlen(nm));
}

char *Person::getName(void)
{
	return name;
}

void Person::setJob(char *j)
{
	memset(job,0x0,sizeof(job));
	strncpy(job,j,strlen(j));
}
char *Person::getJob(void)
{
	return job;
}

int main(void)
{
	char data[32] = "나바보";
//생성자는 쓰지 않아도 동작한다.
	Person p;
	cout<<"안쓴상태"<<endl;
	cout<<"age= "<<p.getAge()<<endl;
	cout<<"name= "<<p.getName()<<endl;
	cout<<"Job= "<<p.getJob()<<endl;

	Person p4 = Person();
	cout<<"age ="<<p4.getAge()<<endl;
	cout<<"name ="<<p4.getName()<<endl;
	cout<<"job ="<<p4.getJob()<<endl;

	char name[32] ="나나나";
	char job[32] ="블크";
	Person p3 = Person(32,name,job);
	cout<<"age ="<<p3.getAge()<<endl;
	cout<<"name ="<<p3.getName()<<endl;
	cout<<"job ="<<p3.getJob()<<endl;	
	return 0;
}
