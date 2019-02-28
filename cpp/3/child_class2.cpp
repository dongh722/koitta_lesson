#include <iostream>
#include <string.h>

using namespace std;

class Samsung
{
private:
	int asset;
	char real_estate[20];
public:
	Samsung(int a,char *r);
	int getAsset(void);
	char *getReal(void);
};

Samsung::Samsung(int a, char *r)
{
	asset = a;
	strncpy(real_estate,r,strlen(r)); 
}

int Samsung::getAsset(void)
{
	return asset;
}

char *Samsung::getReal(void)
{
	return real_estate;
}

class Samchild : public Samsung
{
private:
	char prop_name[20];
public:
	Samchild(int a,char *r,char *p);
	char *getProp(void);
	void showInfo(void);
};

Samchild::Samchild(int a,char *r,char *p) : Samsung(a,r)
{
	strncpy(prop_name,p,strlen(p));
}

char *Samchild::getProp(void)
{
	return prop_name;
}

void Samchild::showInfo(void)
{
	cout<<"property : "<<getProp()<<endl;
	cout<<"asset : "<<getAsset()<<endl;
	cout<<"real : " <<getReal()<<endl;
}

int main(void)
{
	Samchild SS(20000,"Samsung","나");
	SS.showInfo();
	return 0;
}
