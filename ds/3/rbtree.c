#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 8

#define RED   1
#define BLACK 0

#define NONE      0
#define RECOLOR    2

#define LR_TYPE  3
#define LL_TYPE  4
#define RL_TYPE  5
#define RR_TYPE  6

typedef struct __rbtree
{
	int data;
	int color;
	struct __rbtree *Parent;
	struct __rbtree *Lchild;
	struct __rbtree *Rchild;
}rbtree;

rbtree *get_rbtree_node(void)
{
	rbtree *tmp = (rbtree *)malloc(sizeof(rbtree));
	tmp->Lchild = NULL;
	tmp->Rchild = NULL;
	tmp->color = RED;
}

int check_color(rbtree *pNode)
{
	if(!pNode)
		return BLACK;
	else
		return pNode->color;
}

void Chg_color(rbtree *pNode)
{
	if(!(pNode))
		return;
	else
		pNode->color ^=RED;
}

int checking_chg(rbtree *pNode)
{
	int Lcolor,Rcolor;
	if(!pNode)
		return NONE;
	
	Lcolor=check_color(pNode->Lchild);
	Rcolor=check_color(pNode->Rchild);

	if(!Lcolor && !Rcolor)
			return NONE;
	else if(((Lcolor-Rcolor)>0))
	{
		if(check_color(pNode->Lchild->Rchild))
			return LR_TYPE;
		else if(check_color(pNode->Lchild->Rchild))
			return LL_TYPE;
	}
	else if((Lcolor-Rcolor)<0)
	{
		if(check_color(pNode->Rchild->Rchild))
			return RR_TYPE;
		else if(check_color(pNode->Rchild->Lchild))
			return RL_TYPE;
	}
	else if(check_color(pNode->Lchild->Rchild)||check_color(pNode->Lchild->Lchild)
		||check_color(pNode->Rchild->Lchild)||check_color(pNode->Rchild->Rchild))
		return RECOLOR;
	else
		return NONE;
}

void recolor(rbtree **ppNode)
{
	if(!(*ppNode))
		return;
	else
	{
		Chg_color(*ppNode);
		Chg_color((*ppNode)->Rchild);
		Chg_color((*ppNode)->Lchild);

	}
	
}

void LL_Rotating(rbtree **ppNode)
{
	rbtree *tmp = *ppNode;
	*ppNode = tmp ->Lchild;

	tmp ->Lchild =(*ppNode)->Rchild;
	(*ppNode)->Rchild = tmp;
}

void RR_Rotating(rbtree **ppNode)
{
	rbtree *tmp =*ppNode;
	*ppNode = tmp->Rchild;
	tmp->Rchild = (*ppNode)->Lchild;
	(*ppNode)->Lchild =tmp;	
}

void rechg(rbtree **ppNode)
{
	switch(checking_chg(*ppNode))
	{
		case RECOLOR:
	                recolor(ppNode);
			return;
		case LR_TYPE:	
			RR_Rotating(&(*ppNode)->Lchild);
		case LL_TYPE:
			LL_Rotating(ppNode);
			Chg_color((*ppNode)->Rchild);
			break;
		case RL_TYPE:
			LL_Rotating(&(*ppNode)->Rchild);
		case RR_TYPE:
			RR_Rotating(ppNode);
			Chg_color((*ppNode)->Lchild);
			break;
		default :
			return;
	}
	
	Chg_color(*ppNode);
	return;		
}


void Rbtree_ins(rbtree **ppNode,rbtree **ppRoot,int data)
{
	if(!(*ppNode))
	{
		*ppNode = get_rbtree_node();
		(*ppNode)->data =data;
		return;
	}

	if(data> (*ppNode)->data)
		Rbtree_ins(&(*ppNode)->Rchild,ppRoot,data);
	else
		Rbtree_ins(&(*ppNode)->Lchild,ppRoot,data);
	

	rechg(ppNode);
	
	if(*ppNode == *ppRoot)
		(*ppNode)->color = BLACK;
}

#if 0
void chg_node(rbtree **ppNode)
{
	rbtree *tmp = *ppNode;
	
	if(!(*ppNode)->Rchild)
		*ppNode = tmp->Lchild;
	else
		*ppNode = tmp->Rchild;
	free(tmp);
}

void find_max(rbtree **ppNode,int *max)
{
	if((*ppNode)->Rchild)
		find_max(&(*ppNode)->Rchild,max,color);
	else
	{
		*max = (*ppNode)->data;
		chg_node(ppNode);
	}
}

void del_tree(rbtree **ppNode)
{
        if((*ppNode)->Lchild && (*ppNode)->Rchild)
                find_max(&(*ppNode)->Lchild,&(*ppNode)->data);          
        else
                chg_node(ppNode);
}

void deRbtree(rbtree **ppNode,rbtree **ppRoot,int data)
{

	if(!(*ppNode))
	{
		printf("no match data\n");
		return;
	}

	if(data> (*ppNode)->data)
		deRbtree(&(*ppNode)->Rchild,ppRoot,data);
	else if(data<(*ppNode)->data)
		deRbtree(&(*ppNode)->Lchild,ppRoot,data);
	else if(check_color(*ppNode))
		del_tree(ppNode);
	else
	{
		del_tree(ppNode);
		if(check_color(ppNode))
			
	}


	
        rechg(ppNode);

        if(*ppNode == *ppRoot)
                (*ppNode)->color = BLACK;
}
#endif

void print_tree(rbtree *pNode)
{
        if(pNode)
        {
                printf("data = %d, ",pNode->data);

                if(pNode->Lchild)
                        printf("left =%4d, ",pNode->Lchild->data);
                else
                        printf("left =NULL, ");

                if(pNode->Rchild)
                        printf("right =%4d\n",pNode->Rchild->data);
                else
                        printf("right = NULL\n");

		if(pNode->color)
			printf("colr = RED, ");
                else
			printf("colr = BLK, ");

                if(check_color(pNode->Lchild))
			printf("left = RED, ");
		else
			printf("left = BLK, ");

		if(check_color(pNode->Rchild))
			printf("right = RED\n\n");
		else
			printf("right = BLK\n\n");
		
                print_tree(pNode->Lchild);
                print_tree(pNode->Rchild);
        }
        else
                return;
}


int main(void)
{
	int main_cnt;
	rbtree *pMain_head =NULL;
	int aData[ARRAY_SIZE] = {10,20,17,40,50,41,44,30};

	for(main_cnt=0;main_cnt<8;main_cnt++)
		Rbtree_ins(&pMain_head,&pMain_head,aData[main_cnt]);

	printf("\nafter insert\n");
	print_tree(pMain_head);

	return 0;
}
