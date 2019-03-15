#include <stdio.h>
#include <string.h>

int check_charater(char *c)
{
	int i =0;
	char ch[200]={0,};
	int cnt =0;
	strncpy(ch,c,strlen(c));

	for(i=0;ch[i];i++)
	{
		if((ch[i]>0x40)&&(ch[i]<0x5A))
			cnt++;
	}
	return cnt;
}

int main(void)
{
	char c[200]={0,};
	strcpy(c,"Damn it! Where is my Important Pointer ?");

	printf("%s\n",c);
	printf("의 대문자 개수는 %d입니다.\n",check_charater(c));
	return 0;
}
