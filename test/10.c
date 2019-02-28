#include <stdio.h>

typedef struct __im
{
	int data1;
	int data2;
}im;

void chg_data(im *s)
{
	int tmp = s->data1;
	s->data1 =s->data2;
	s->data2 =tmp;
}

int main(void)
{
	im s;
	s.data1 =3;
	s.data2 =4;

	printf("struct data1 = %d, data2 = %d\n",s.data1,s.data2);

	chg_data(&s);
	printf("after change\n");	
	printf("struct data1 = %d, data2 = %d\n",s.data1,s.data2);
}

