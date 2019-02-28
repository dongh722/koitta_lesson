/*자료구조 학습의 의의:
SW 개발자에게 있어서 머리속 생각을 프로그램 코드로 바꾸는 것이 무엇보다 중요하다.
이것이 불가능하다면 단순한 코더가 되고
이것이 가능해진다면 비로소 그 때 SW개발자가 될 수 있다.

자료구조를 학습하는 이유는 머리속에서
생각한 내용을 코드로 변환하는 훈련을 하는 일련의 절차라고 보면 된다.

익숙해지면 이후에는
생각한 대부분의 모든 것들을 프로그램 코드로 바꿀 수 있다.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct __que
{
	int data;
	struct __que*link;
}que;

que *get_que_node(void)
{
	que *tmp = (que*)malloc(sizeof(que));
	tmp->link =NULL;
	return tmp;
}
	
void push(que**top, int data)
{
	if(*top == NULL)
	{
		*top =get_que_node();
		(*top)->data = data;
	}
	else
		push(&((*top)->link),data);
}

void  pop(que **top,int data)
{
	que *tmp =NULL;
	if(((*top)->data)==data)
	{
		tmp = *top;
		*top = (*top)->link;
		free(tmp);
		return;
	}
	else
	{
		if(!((*top)->link))
			printf("No match data\n");
		else
			pop(&((*top)->link),data);
		return;
	}
}

void print_que(que *top)
{
	que *tmp = top;
	
	while(tmp)
	{
		printf("tmp->data = %d\n", tmp->data);
		tmp = tmp->link;
	}	
}

int main(void)
{
	int i;
	int data;
	que *top = NULL;
	for(i = 1; i<=4; i++)
		push(&top,i*10);
	print_que(top);
	pop(&top,30);
	print_que(top);
	return 0;
}
