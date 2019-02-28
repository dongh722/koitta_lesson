#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void non_goto_test(void)
{
	int i,j,k;
	int flag=0;	
	for(i=0;i<5;i++)
	{
		for(i = 0;i<5;i++)
		{
			for(j=0;j<5;j++)
			{
				if(i==1 && j==4 && k==0)
				{
					printf("Error Accurance!\n");
					flag =true;
				}
				
				if(flag)
				{
					printf("non_goto\n");
					break;
				}
			}
			
			if(flag)
			{
				printf("non_goto\n");
				break;
			}
		}
		
		if(flag)
		{
			printf("non_goto\n");
			break;
		}
	}
}

void goto_test(void)
{
	int i,j,k;

	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			for(k=0;k<4;k++)
			{
				if(i==1 &&j==4 && k==0)
				{
					printf("Error Accurance!\n");
					goto finish;
				}
			}
		}
	}
	printf("Exit Normally\n");
	return;

finish:
		printf("Error Mandler\n");
}

int main(void)
{
	non_goto_test();
	goto_test();

	return 0;
}
