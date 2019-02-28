#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NON_TYPE 0
#define LR_TYPE 2
#define LL_TYPE 3
#define RL_TYPE 5
#define RR_TYPE 6

typedef struct __avltree
{
	int data;
	int level;
	struct __avltree *Rchild;
	struct __avltree *Lchild;
	struct __avltree *Parent;
}avltree;

avltree *get_tree_node(void)
{
	avltree *tmp = (avltree *)malloc(sizeof(avltree));
	tmp->Rchild = NULL;
	tmp->Lchild = NULL;
	tmp->Parent = NULL;
	tmp->level = 1;
	return tmp;
}

int check_level_def(avltree *pRoot)
{
	int right_level = (pRoot->Rchild) ? pRoot->Rchild->level : 0;
	int left_level = (pRoot->Lchild) ? pRoot->Lchild->level : 0;
	return right_level - left_level;
}

int chg_level(avltree *pRoot)
{
	int left_level = (pRoot->Lchild) ? pRoot->Lchild->level : 0;
	int right_level = (pRoot->Rchild) ? pRoot->Rchild->level : 0;
	
	if(left_level > right_level)
		return left_level+1;
	else
		return right_level+1;
}

int check_rotation(avltree *pRoot)
{
	if(check_level_def(pRoot)<-1)
	{
		if(check_level_def(pRoot->Lchild)<0)
		{	printf("LL\n");
			return LL_TYPE;
		}
		else
		{	printf("LR\n");
			return LR_TYPE;
		}
	}	
	else if(check_level_def(pRoot)>1)
	{
		if(check_level_def(pRoot->Rchild)>0)
		{
			printf("RR\n");
			return RR_TYPE;
		}
		else
		{
			printf("RL\n");
			return RL_TYPE;
		}
	}
	else
		return NON_TYPE;
}

void LL_Rotating(avltree **ppRoot)
{
	avltree *tmp = *ppRoot;

	(*ppRoot) = tmp->Lchild;
	tmp->Lchild = (*ppRoot)->Rchild;
	(*ppRoot)->Rchild  =tmp;

	if(tmp->Lchild)
		tmp->Lchild->Parent =tmp;

	(*ppRoot)->Parent = tmp->Parent;
	tmp->Parent = *ppRoot;

	tmp->level = chg_level(tmp);
	(*ppRoot)->level = chg_level(*ppRoot);
}

void RR_Rotating(avltree **ppRoot)
{	
	avltree *tmp = *ppRoot;
	(*ppRoot) = tmp->Rchild;
	tmp->Rchild = (*ppRoot)->Lchild;
	(*ppRoot)->Lchild  =tmp;

	if(tmp->Rchild)
		tmp->Rchild->Parent =tmp;

	(*ppRoot)->Parent = tmp->Parent;
	tmp->Parent = *ppRoot;

	tmp->level = chg_level(tmp);
	(*ppRoot)->level = chg_level(*ppRoot);

}

void rotation(avltree **ppRoot,int rot_type)
{
	switch(rot_type)
	{
		case LR_TYPE:
			RR_Rotating(&(*ppRoot)->Lchild);
		case LL_TYPE:
			LL_Rotating(ppRoot);
			break;
		case RL_TYPE:
			LL_Rotating(&(*ppRoot)->Rchild);
		case RR_TYPE:
			RR_Rotating(ppRoot);
			break;
		default:
			return;
	}
}

	

void avltree_ins(avltree **ppRoot,int data)
{
	avltree **tmp = ppRoot;
	avltree *tmpParent=NULL;
	avltree *backup =NULL;

	while(*tmp)
	{
		tmpParent = *tmp;
		if((*tmp)->data >data)
			tmp = &(*tmp)->Lchild;
		else
			tmp = &(*tmp)->Rchild;
	}
	
	*tmp = get_tree_node();
	(*tmp) ->data = data;
	(*tmp) ->Parent = tmpParent;	

	while(*tmp)
	{
		(*tmp)->level = chg_level(*tmp);
		rotation(tmp,check_rotation(*tmp));

		if(!(*tmp)->Parent)
			tmp = &(*tmp)->Parent;
		else if(!(*tmp)->Parent->Parent)
			tmp = ppRoot;			
		else if((*tmp)->Parent->Parent->data > (*tmp)->Parent->data)
			tmp = &(*tmp)->Parent->Parent->Lchild;
		else
			tmp = &(*tmp)->Parent->Parent->Rchild;
	}

}


void chg_node(avltree **ppRoot)
{
	avltree *tmp = *ppRoot;

	if(!(*ppRoot)->Rchild)
		*ppRoot = (*ppRoot)->Lchild;
	else
		*ppRoot = (*ppRoot)->Rchild;

	if(*ppRoot)
		(*ppRoot)->Parent = tmp->Parent;

	free(tmp);
}

void find_max(avltree **ppRoot,int *max)
{
	while((*ppRoot)->Rchild)
		ppRoot = &(*ppRoot)->Rchild;
	
	*max = (*ppRoot)->data;
	chg_node(ppRoot);
}

void deavltree(avltree **ppRoot,int data)
{
	avltree **tmp = ppRoot;

	if(!(*ppRoot))
	{
finish:
		printf("There are no delete  data\n");
		return;
	}

	while((*tmp)->data !=data)
	{
		if(!(tmp))
			goto finish;
		else if((*ppRoot)->data >data)
			tmp = &(*tmp)->Lchild;
		else
			tmp = &(*tmp)->Rchild;
	}

	printf("\nNow delet %d\n",data);

	if((*tmp)->Rchild && (*tmp)->Lchild)
		find_max(&(*tmp)->Lchild,&(*tmp)->data);
	else
		chg_node(tmp);

        while(*tmp)
        {
                (*tmp)->level = chg_level(*tmp);
                rotation(tmp,check_rotation(*tmp));

                if(!(*tmp)->Parent)
                        tmp = &(*tmp)->Parent;
                else if(!(*tmp)->Parent->Parent)        
                        tmp = ppRoot;                   
                else if((*tmp)->Parent->Parent->data > (*tmp)->Parent->data)
                        tmp = &(*tmp)->Parent->Parent->Lchild;
                else
                        tmp = &(*tmp)->Parent->Parent->Rchild;
        }

}

void print_now(avltree **ppRoot)
{
	printf("data =%4d, ",(*ppRoot)->data);

	if((*ppRoot)->Lchild)
		printf("left = %4d, ",(*ppRoot)->Lchild->data);
	else
		printf("left= NULL, ");

	if((*ppRoot)->Rchild)
		printf("right = %4d\n",(*ppRoot)->Rchild->data);
	else
		printf("right = NULL\n");

        printf("level=%4d, ",(*ppRoot)->level);

        if((*ppRoot)->Lchild)
                printf("left = %4d, ",(*ppRoot)->Lchild->level);
        else
                printf("left= NULL, ");

        if((*ppRoot)->Rchild)
                printf("right = %4d\n\n",(*ppRoot)->Rchild->level);
        else
                printf("right = NULL\n\n");

}

#if 1
void print_avltree(avltree **ppRoot)
{
	avltree **tmp = ppRoot;
	avltree **backup =tmp;
	int cntL =0;
	int cntR =0;
	
printavl:
	while(*tmp)
	{
		print_now(tmp);

		if((*tmp)->Lchild)
		{
			tmp = &(*tmp)->Lchild;
			cntL++;
		}
		else
		{
			cntL--;
			tmp = &(*tmp)->Parent;

			if((*tmp)->Rchild)
			{
				cntR++;
				tmp = &(*tmp)->Rchild;
			}			
		}
	}
}
#else
void print_avltree(avltree **ppRoot)
{
	if(!(*ppRoot))
		return;
	else
	{
		print_now(ppRoot);
		print_avltree(&(*ppRoot)->Lchild);
		print_avltree(&(*ppRoot)->Rchild);
	}	
}
#endif
int main(void)
{
	int main_cnt;
	avltree *pMain_Root =NULL;
	int aData[9] = {10,20,17,40,50,41,44,30,0};
//	int aData[9] = {10,20,30,40,50,44,41,17,0};
	for(main_cnt = 0;aData[main_cnt];main_cnt++)
		avltree_ins(&pMain_Root,aData[main_cnt]);

	printf("\nafter insert\n");
	print_avltree(&pMain_Root);
	
	deavltree(&pMain_Root,17);
	
	printf("\nafter delet\n");
	print_avltree(&pMain_Root);
	
	return 0;
}
