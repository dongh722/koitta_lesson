#include <iostream>
#include <string.h>

using namespace std;

class Academy
{
	char *name;
	char *phone;
public:
	Academy(char *n,char *p);
	~Academy(void);
	void delMem(void);
	void showInfo(void);
};

Academy::Academy(char *n, char *p)
{
	name = new char[strlen(n) +1];
	strncpy(name,n,strlen(n));
	
	phone =new char[strlen(p) +1];
	strncpy(phone,p,strlen(p));
}

Academy::~Academy(void)
{
	cout << "Delete Memory"<<endl;
	delete []name;
	delete []phone;
}

void Academy::showInfo(void)
{
	cout<<"name : "<<name<<endl;
	cout<<"Phone : "<<phone<<endl;
}

int main(void)
{
	Academy a("KOITT","02-1544-4661");
	a.showInfo();	
	return 0;
}
