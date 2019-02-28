#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>	


typedef struct __tree
{
	int data;
	struct __tree *Rchild;
	struct __tree *Lchild;
}tree;

typedef struct __stack
{
	void *p;
	struct __stack *link;
}stack;

tree *get_node(void)
{
	tree *tmp =(tree *)malloc(sizeof(tree));
	tmp->Rchild =NULL;
	tmp->Lchild =NULL;
	return tmp;
}

void tree_ins(tree **ppRoot,int data)
{
	tree **tmp = ppRoot;

	while(*tmp)
	{
		if((*tmp)->data > data)
			tmp = &(*tmp)->Lchild;
		else
			tmp = &(*tmp)->Rchild;
	}

	*tmp = get_node();
	(*tmp) ->data = data;
}

#if 0

tree *chg_node(tree *root)
{
	tree *tmp = root;
	
	if(!root->right)
		root = root->left;
	else if
		root = root->right;
	free(tmp);
	return root;
}
void non_recur_delete_tree(tree **root,int data)
{
	tree **tmp = root;
	int num;
	
	while(*tmp)
	{
		if((*tmp)->data >data)
			tmp = &(*tmp)->left;
		else if((*tmp)->data <data)
			tmp = &(*tmp)->right;
		else if((*tmp)->left &&(*tmp)->right)
		{
			find_max(&(*tmp)->left,&num);
			(*tmp)->data = num;
			return;
		}
		else
		{
			(*tmp) = chg_node(*tmp);
			return;
		}
	}
	printf("not found\n");
}
#else
void chg_node(tree **node)
{
	tree *tmp = *node;
	if(!(*node)->Rchild)
		*node = (*node)->Lchild;
	else
		*node = (*node)->Rchild;
	
	free(tmp);
}

void find_max(tree **node,int *max)
{
	while((*node)->Rchild)
		node = &(*node)->Rchild;
	*max = (*node)->data;
	
	chg_node(node);
}

void detree(tree **pRoot,int data)
{
	tree **tmp = pRoot;

	if(!(*pRoot))
	{
finish:
		printf("Ther are no data\n");
		return;
	}

	while((*tmp)->data != data)
	{
		if(!(*tmp))
			goto finish;
		else if(data > (*pRoot)->data)
			tmp = &(*tmp)->Rchild;
		else
			tmp = &(*tmp)->Lchild;
	}
	
	printf("Now delete %d\n",data);

	if((*tmp)->Rchild && (*tmp)->Lchild)
		find_max(&(*tmp)->Lchild,&(*tmp)->data);
	else
		chg_node(tmp);
}
#endif

stack *get_stack_node(void)
{
	stack *tmp =(stack *)malloc(sizeof(stack));
	tmp->link =NULL;
	return tmp;
}

void push(stack **top,void *p)
{
	if(!p)
		return;
	stack *tmp = *top;
	*top  = get_stack_node();
	(*top)->link = tmp;
	(*top)->p = malloc(sizeof(void *));
	(*top)->p = p;
}

void *pop(stack **top)
{
	stack *tmp =*top;
	void *data =NULL;
	if(!(*top))
	{
		printf("stack is empty!\n");
		return NULL;
	}
	data = (*top)->p;
	*top = (*top)->link;
	free(tmp);
		
	return data;
}

bool stack_is_not_empty(stack *top)
{
	if(top)
		return true;
	else
		return false;
}
void print_now(tree **pRoot)
{
	printf("data =%d, ",(*pRoot)->data);

	if((*pRoot)->Lchild)
		printf("left = %d, ",(*pRoot)->Lchild->data);
	else
		printf("left =NULL, ");

	if((*pRoot)->Rchild)
		printf("right = %4d\n\n",(*pRoot)->Rchild->data);
	else
		printf("right = NULL\n\n");
}

void print_tree(tree **pRoot)
{
	tree **tmp= pRoot;
	stack *top = NULL;

	push(&top,*tmp);

	while(stack_is_not_empty(top))
	{
		tree *t = (tree *) pop(&top);
		tmp = &t;
		print_now(tmp);
		
		push(&top, (*tmp)->Rchild);
		push(&top, (*tmp)->Lchild);
	}
}

int main(void)
{
	int cnt;
	tree *pRoot = NULL;
	int aData[200] = {50,100,25,17,23,15,20,75,80,};
	
	

	for(cnt = 0;aData[cnt];cnt++)
		tree_ins(&pRoot,aData[cnt]);
	
	printf("\nafter insert\n");
	print_tree(&pRoot);
	
	detree(&pRoot,17);
	
	printf("\nafter delete\n");
	print_tree(&pRoot);

	return 0;
}
