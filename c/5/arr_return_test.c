#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int init_arr(int (*arr)[2])
{
	int i,j;

	srand(time(NULL));

	for(i =0;i<2;i++)
		for(j=0;j<2;j++)
		{	
			arr[i][j] = rand() %9 +1;
			printf("arr[%d][%d] = %d\n",i,j,arr[i][j]);
		}

}

void test(void)
{
	printf("test\n");
}

#if 0
// 이것은 지역 변수를 return 하고 있습니다.
int (*cant_ret_arr(void))[2]
{
	int arr[2][2] = {0,};
	int_arr(arr);
	return arr;
}
#endif

// int(*)[2] arr_ret(void)
int (*arr_ret(void))[2]
{
	static int arr[2][2] = {0,};
	init_arr(arr);
	return arr;
}

//int (*)[2] (*)(void) 반환 형식
//void (*p)(void) 인자 형식
//int(*)[2] (void) (*arr_pof(void(*p)(void))
int (*(*arr_pof(void(*p)(void)))(void))[2]
{
	printf("arr_pof\n");
	p();
	return arr_ret;
}

int main(void)
{
	int i,j;
	int (*p)[2];
	p = arr_ret();

	for(i = 0;i<2;i++)
		for(j=0;j<2;j++)
			printf("p[%d][%d] = %d\n",i,j,p[i][j]);



	#if 0
	p = cant_ret_arr();
	printf("p[0][0] = %d\n",p[0][0]);
	#endif

	p = arr_pof(test)();
	
	for(i = 0;i<2;i++)
		for(j=0;j<2;j++)
			printf("p[%d][%d] = %d\n",i,j,p[i][j]);
	return 0; 
}
