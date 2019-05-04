#include <stdio.h>
#include <math.h>

typedef struct _complex_num
{
	double Re;
	double Im;

	struct _complex_num (*plus)(struct _complex_num, struct _complex_num);
	struct _complex_num (*minus)(struct _complex_num, struct _complex_num);
	struct _complex_num (*conmul)(double, struct _complex_num);
	struct _complex_num (*mul)(struct _complex_num, struct _complex_num);
	struct _complex_num (*euler)(double);
}Mycomplex;

void Mycomplex_Init(Mycomplex *);

Mycomplex Euler_formula(double degree)
{
	Mycomplex tmp;
	Mycomplex_Init(&tmp);
	double rad = degree*M_PI/180.0;
	tmp.Re = cos(rad);
	tmp.Im = sin(rad);

	return tmp;
}

Mycomplex Complex_plus(Mycomplex x,Mycomplex y)
{
	Mycomplex tmp;
	Mycomplex_Init(&tmp);
	tmp.Re = x.Re + y.Re;
	tmp.Im = x.Im + y.Im;

	return tmp;
}

Mycomplex Complex_minus(Mycomplex x,Mycomplex y)
{
	Mycomplex tmp;
	Mycomplex_Init(&tmp);
	tmp.Re = x.Re - y.Re;
	tmp.Im = x.Im - y.Im;
	return tmp;
}

Mycomplex Complex_const_mul(double con,Mycomplex x)
{
	Mycomplex tmp;
	Mycomplex_Init(&tmp);
	tmp.Re = con*x.Re;
	tmp.Im = con*x.Im;
	return tmp;
}

Mycomplex Complex_mul(Mycomplex x,Mycomplex y)
{
	Mycomplex tmp;
	Mycomplex_Init(&tmp);
	tmp.Re = x.Re * y.Re - x.Im * y.Im;
	tmp.Im = x.Re * y.Im + x.Im * y.Re;

	return tmp;
}

void Mycomplex_Init(Mycomplex *x)
{
	x->plus = Complex_plus;
	x->minus = Complex_minus;
	x->conmul = Complex_const_mul;
	x->mul = Complex_mul;
	x->euler = Euler_formula;
}

int main(void)
{
	Mycomplex res;
	Mycomplex_Init(&res);

	Mycomplex tmp1;
	Mycomplex_Init(&tmp1);

	Mycomplex tmp2;
	Mycomplex_Init(&tmp2);

	tmp1 = tmp1.euler(45.0);
	tmp2 = tmp2.euler(30.0);

	res=res.mul(tmp1,tmp2);
	printf("sin(75) = %lf, Im(e^(45도i)*e^(30도i)) = %lf\n",sin(75.0*M_PI/180.0),res.Im);
	printf("cos(75) = %lf, Rm(e^(45도i)*e^(30도i)) = %lf\n",cos(75.0*M_PI/180.0),res.Re);
	
	printf("\n");

	tmp2 = tmp2.euler(-30.0);
	res=res.mul(tmp1,tmp2);
	printf("sin(15) = %lf, Im(e^(45도i)*e^(-30도i)) = %lf\n",sin(15.0*M_PI/180.0),res.Im);
	printf("cos(15) = %lf, Im(e^(45도i)*e^(-30도i)) = %lf\n",sin(15.0*M_PI/180.0),res.Re);
	
	return 0;
}
