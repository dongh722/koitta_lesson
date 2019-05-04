#include <iostream>

using namespace std;

class Vector
{
private:
	int x, y, z;
public:
	Vector(int x,int y, int z);
	void showVector(void);
	Vector operator*(Vector &p);
};

Vector::Vector(int x,int y,int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector Vector::operator*(Vector &p)
{
	Vector tmp(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);
	return tmp;
}

void Vector::showVector(void)
{
	cout<<'('<<x<<','<<y<<','<<z<<')';
}

int main(void)
{
	Vector p1(7,4,3);
	Vector p2(2,4,6);
	Vector p3 = p1*p2;
	p1.showVector();
	cout<<" * ";
	p2.showVector();
	cout<<" = ";
	p3.showVector();
	cout<<endl;

	return 0;
}
