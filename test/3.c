#include <stdio.h>

char chg_charater(char c)
{
	return c^0x20;
}

int main(void)
{
	char A = 'A';
	char a = 'a';

	printf("A change %c\n",chg_charater(A));
	printf("a change %c\n",chg_charater(a));
}
