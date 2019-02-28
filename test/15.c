#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct __qu
{
	int data;
	struct __qu *link;
}qu;

int array_init(int *arr,int len)
{
	int i=0;
	int j=0;

	for(i=0;i<len;i++)
	{
rego:
		arr[i] = rand()%200 +1;

		for(j=(i-1);j>=0;j--)
			if(arr[i]==arr[j])
				goto rego;
	}			
}

qu *get_qu_node(void)
{
	qu *tmp = (qu *)malloc(sizeof(qu));
	tmp->link =NULL;
	return tmp;
}

void enqueue(qu **pHead,int data)
{
	if(!(*pHead))
	{
		*pHead = get_qu_node();
		(*pHead)->data = data;
	}
	else
		enqueue(&(*pHead)->link,data);
}

void dequeue(qu **pHead,int data)
{
	qu *tmp =NULL;
	if((*pHead)->data == data)
	{
		tmp = *pHead;
		*pHead = (*pHead)->link;
		free(tmp);
		return;
	}
	
	if(!(*pHead)->link)
		printf("NO delete data\n");
	else
		dequeue(&(*pHead)->link,data);

	return;
}

void print_queue(qu *pHead)
{
	qu *tmp =pHead;

	while(tmp)
	{
		printf("data = %d\n",tmp->data);
		tmp = tmp->link;
	}
}

int main(void)
{
	int i;
	int array[20] ={0,};
	qu *pHead =NULL;

	srand(time(NULL));
	array_init(array,20);

	for(i=0;i<array[i];i++)
			enqueue(&pHead,array[i]);

	print_queue(pHead);
	return 0;
}
