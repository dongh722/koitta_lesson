#include <stdlib.h>
#include <stdio.h>


typedef struct __qu qu;
struct __qu
{
	int data;
	qu *link;
	void  (*q)(qu **,int);
	qu (*(*get_q)(void));
	void (*deq)(qu **,int);
	void (*pq)(qu *);
};


qu *get_node(void);
void enqueue(qu **,int);
void dequeue(qu **,int);
void print_que(qu *);

qu *get_node(void)
{
	qu *tmp = (qu *)malloc(sizeof(qu));
	tmp->link =NULL;
	tmp->data= 0;
	tmp->q = enqueue;
	tmp->deq = dequeue;
	tmp->pq = print_que;
	tmp->get_q = get_node;
	return tmp;
}

void enqueue(qu **ppHead,int data)
{
	qu **tmp =ppHead;
	while((*tmp) && (*tmp)->data)
		 tmp = &(*tmp)->link;
	
	if(!(*tmp))
		*tmp = get_node();
	(*tmp)->data = data;
}

void dequeue(qu **ppHead,int data)
{
	qu **tmp = ppHead;
	qu **backup;

	if(!(*tmp))
	{
finish:
		printf("no data\n");
		return;
	}

	while((*tmp)->data != data)
	{
		if((*tmp)->link)
		{
			backup=&(*tmp)->link;
			tmp = &(*tmp)->link;
		}
		else
			goto finish;
	}
	free(*tmp);
	*backup = (*tmp)->link;
}

void print_que(qu *ppHead)
{
	while(ppHead)
	{
		printf("data = %d\n",ppHead->data);	
		ppHead = ppHead->link;
	}
}

int main(void)
{
	int i;
	int arr[5] = {10,30,20,40};
	
	qu *head = (qu *)malloc(sizeof(qu));
	head->data =0;
	head ->q = enqueue;
	head ->get_q = get_node;
	head ->deq = dequeue;

	for(i =1;i<5;i++)
		head->q(&head,i*10);

	print_que(head);

	printf("\n");
	head->deq(&head,arr[2]);
	print_que(head);
}
