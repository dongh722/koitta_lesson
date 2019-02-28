#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 9

typedef struct __tree
{
	int data;
	struct __tree *left_link;
	struct __tree *right_link;
}tree;

tree *get_tree_node(void)
{
	tree *tmp =(tree *)malloc(sizeof(tree));
	tmp->left_link =NULL;
	tmp->right_link =NULL;
	return tmp;
}

#if 0
//del_tree exem code
void chg_node(tree **node)
{
	tree *tmp = *node;
	if(!(*node)->right)
		*node =(*node)->left
	else
		*node = (*node)->right;
	free(tmp);
}

void find_max(tree **node,int *max)
{
	if((*node)->right)
		find_max(&(*node)->right,max);
	else
	{
		*max = (*node)->data;
		chg_node(node);
	}
}

void del_tree(tree **root,int data)
{
	if(!(*root))
	{
		printf("There are no node!\n");
		return;
	}
	else if((*root)->data>data)
		del_tree(&(*root)->left,data);
	else if((*root)->data<data)
		del_tree(&(*root)->right,data);
	else if((*root)->left && (*root)->right)
	{
		int max;
		find_max(&(*root)->left,&max);
		(*root)->data = max;
	}
	else
		cng_node(root);
		
}
#endif


int tree_ins_cnt=0;
void tree_ins(tree **pLink,int data)
{
	tree_ins_cnt++;
	if(!(*pLink))
	{
		printf("data =%d,cnt =%d\n",data,tree_ins_cnt);
		*pLink =get_tree_node();
		(*pLink)->data = data;
		tree_ins_cnt=0;
		return ;
	}
	else if(data > (*pLink)->data)
		tree_ins((&(*pLink)->right_link),data);
	else
		tree_ins((&(*pLink)->left_link),data);
}

int flag =0;
void detree(tree **pLink,int data,tree **key)
{	
	tree *tmp=*pLink;
	if(!(*pLink))
	{
		printf("no match data\n");
		return;
	}
	else if(data > (*pLink)->data)
	{
		if((!(*pLink)->right_link)&&flag)
			*key =*pLink;
		else 
			detree(&((*pLink)->right_link),data,key);
	}
	else if(data < (*pLink)->data)
	{
		if((!(*pLink)->left_link)&&flag) 
			*key =*pLink;
		else 	
			detree(&((*pLink)->left_link),data,key);

	}
	else if(!(*pLink)->left_link)
	{
		*pLink =(*pLink)->right_link;
		free(tmp);
		return;
	}
	else if(!(*pLink)->right_link)
	{
		*pLink = (*pLink)->left_link;
		free(tmp);
		return;
	}
	else
	{
		flag =1;
#if 0
		detree(&((*pLink)->right_link),data,key);
#else
		detree(&((*pLink)->left_link),data,key);
#endif
		if((*pLink)->right_link==*key)
			(*key)->left_link = tmp->left_link;
		else if((*pLink)->left_link==*key)
			(*key)->right_link = tmp->right_link;
		*pLink = *key;
		free(tmp);
		flag =0;
		return;
	}

}

void print_tree(tree *pLink)
{
	if(pLink)
	{
		printf("data = %d, ",pLink->data);

		if(pLink->left_link)
			printf("left =%4d, ",pLink->left_link->data);
		else
			printf("left =NULL, ");

		if(pLink->right_link)
			printf("right =%4d\n",pLink->right_link->data);
		else
			printf("right = NULL\n");

		print_tree(pLink->left_link);
		print_tree(pLink->right_link);
	}
	else
		return;
}

int main(void)
{
	int cnt;
	tree *pLink = NULL;
	int aData[ARRAY_SIZE] ={50,100,25,17,23,15,20,75,80};
	tree *key =NULL;

	for(cnt=0;cnt<sizeof(aData)/sizeof(int);cnt++)
		tree_ins(&pLink,aData[cnt]);
	print_tree(pLink);

	printf("\nafter delete\n");

	detree(&pLink,17,&key);
	print_tree(pLink);
	
	printf("\nsame data redelete\n");
	detree(&pLink,17,&key);
	print_tree(pLink);
	return 0;
}
