#include <iostream>

using namespace std;

class Vector
{
private:
	int x, y, z;

public:
	Vector(int x,int y, int z);
	void showXYZ(void);
	Vector operator+(Vector &p);
	Vector operator-(Vector &p);
	int inner(Vector &p);
	Vector operator*(int val);
	friend Vector operator*(int val,Vector &p);
	Vector outer(Vector &p);
};

Vector::Vector(int x, int y, int z)
{
	this->x =x;
	this->y =y;
	this->z =z;
}

void Vector::showXYZ(void)
{
	cout<<"("<< x<<", "<<y<<", "<<z<<") ";
}

int Vector::inner(Vector &p)
{
	return x*p.x +y*p.y +z*p.z;
}

Vector Vector::operator+(Vector &p)
{
	Vector tmp(x +p.x, y +p.y, z +p.z);
	return tmp;
}

Vector Vector::outer(Vector &p)
{
	Vector tmp(y*p.z -z*p.y,-(x*p.z -z*p.x),x*p.y -y*p.x);
	return tmp;
}

Vector Vector::operator-(Vector &p)
{
	Vector tmp(x -p.x, y -p.y, z -p.z);
	return tmp;
}

Vector Vector::operator*(int val)
{
	Vector tmp(x *val, y*val,z*val);
	return tmp;
}

Vector operator*(int val,Vector &p)
{
	return p * val;
}

int main(void)
{
	int result =0;

	Vector p1(7,4,3);
	Vector p2(2,4,6);
	Vector p3 =p1+p2;
	p1.showXYZ();
	cout<<"+ ";
	p2.showXYZ();
	cout<<"= ";
	p3.showXYZ();
	cout<<endl;

	p3 = p1-p2;
	p1.showXYZ();
	cout<<"- ";
	p2.showXYZ();
	cout<<"= ";
	p3.showXYZ();
	cout<<endl;

	p1.showXYZ();
	cout<<"* 3 = ";
	p3 = p1*3;
	p3.showXYZ();
	cout<<endl;

	cout<<"3 * ";
	p2.showXYZ();
	cout<<"= ";
	p3 = 3*p1;
	p3.showXYZ();
	cout<<endl;

	result = p1.inner(p2);
	p1.showXYZ();
	cout<<"* ";
	p2.showXYZ();
	cout<<"= "<<result<<endl;

	p3 = p1.outer(p2);
	p1.showXYZ();
	cout<<"X ";
	p2.showXYZ();
	cout<<"= ";
	p3.showXYZ();
	cout<<endl;
}
