#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 8

#define NO_TYPE 0
#define LL_TYPE 2
#define LR_TYPE 3
#define RR_TYPE 4
#define RL_TYPE 5

typedef struct __tree
{
	int data;
	int level;
	struct __tree *Lchild;
	struct __tree *Rchild;
}tree;

tree *get_tree_node(void)
{
	tree *tmp = (tree *)malloc(sizeof(tree));
	tmp->Lchild = NULL;
	tmp->Rchild = NULL;
	tmp->level = 1;
	return tmp;
}
#if 0
int check_lev(avl *root)
{
	int right = root->right > 0 ? root->right->lev : 0;
	int left = root->left >0 ? root->left->lev :0;
	return right-left;
}
int chg_lev(avl *root)
{
	int left,right;
	left = root->left >0 ? root->left_lev : 0;
	right = root->right >0 ? root->right->lev : 0;
	
	if(left>right)
		return left +1;
	else
		return right+1;
}

int check_rotation(avl *root,int data)
{
	if(check_lev(root) <0)
	{
		if(check_lev(root->left) > -1 && root->left->data < data)
			return LR;
		else
			return LL;
	}
	else
	{
		if(check_lev(root->right) <1 && root->right->data >data)
			return RL;
		else
			return RR;
	}
	return 0;
}

avl *rotation(avl *root, int ret)
{
	switch(ret)
	{
		case LL:
			return ll_rot(root,root->left);
			break;
		case LR:
			return lr_rot(rot, root->left);
			break;
		case RR:
			return rr_rot(root,root->right);
			break;
		case RL
			return rl_rot(root,root->right);
			break;
	}
}

avl *ll_rot(abl *p,avl *c)
{
	p->left = c->right;
	c->right =p;
	p->lev =chg_lev(p);
	c->lev =chg_lev(c);
	return c;
}

avl *rr_rgt(avl *p,avl *c)
{
	p->right = c->left;
	c->left =p;
	p->lev = chg_lev(p);
	c->lev = chg_lev(c);
}

avl *lr_rgt(avl *p,avl *c)
{
	c =rr_rgt(c,c->right);
	return ll_root(p,c);
}

avl *rl_rgt(avl *p,avl *c)
{
	c = ll_rgt(c,c->left);
	return rr_rot(p,c);
}

void avl_ins(avl **root,int data)
{
	if(!(*root))
	{
		*root = get_avl_node();
		(*root)->data = data;
		return;
	}
	
	if((*root)->data>data)
		avl_ins(&(*root)->left,data);
	else
		avl_ins(&(*root)->right,data);
	(*root)->lev = chg_lev(*root);
	
	if((ABS(check_lev(*root)))>1)
		*root = rotation(*root,check_rotation(*root,data));
}
#endif


void searching_level(tree *pHead,int *max_level)
{
	if(pHead)
	{
		searching_level(pHead->Lchild,max_level);
		searching_level(pHead->Rchild,max_level);

		if(*max_level < pHead->level)
			*max_level = pHead->level;
		return;	
	}
	else
		return;
}

int Balance_check(tree *pHead)
{
	int R_max_level = pHead->level;
	int L_max_level = pHead->level;
	
	searching_level(pHead->Rchild,&R_max_level);
	searching_level(pHead->Lchild,&L_max_level);

	return R_max_level-L_max_level;
}

int Rotation_type(tree *pHead)
{		
	int balance_fact = Balance_check(pHead);

	if(balance_fact>1)
	{
		balance_fact = Balance_check(pHead->Rchild);
		if(balance_fact>0)
			return RR_TYPE;
		else
			return RL_TYPE;
	}
	else if(balance_fact<-1)
	{
		balance_fact= Balance_check(pHead->Lchild);
		if(balance_fact>0)
			return LR_TYPE;
		else
			return LL_TYPE;
	}
	else
		return NO_TYPE;
}

void chg_level(tree **pHead,int now_level)
{
	if(!(*pHead))
		return;
	else
	{
		(*pHead) ->level =now_level; 
		chg_level(&((*pHead)->Rchild),now_level+1);
		chg_level(&((*pHead)->Lchild),now_level+1);
		return;
	}
}

void LL_Rotating(tree **pHead)
{
	tree *tmp = *pHead;
	*pHead =tmp->Lchild;

	tmp->Lchild =(*pHead)->Rchild;
	(*pHead)->Rchild = tmp;	
	(*pHead)->level =tmp->level;
	chg_level(pHead,(*pHead)->level);
}

void RR_Rotating(tree **pHead)
{
	tree *tmp =*pHead;
	*pHead = tmp->Rchild;
	
	tmp->Rchild =(*pHead)->Lchild;
	(*pHead)->Lchild = tmp;
	(*pHead)->level =tmp->level;
	chg_level(pHead,(*pHead)->level);
}

void RL_Rotating(tree **pHead)
{
	tree *tmp =(*pHead)->Rchild->Lchild;
	(*pHead)->Rchild->Lchild =tmp->Rchild;
	tmp->Rchild =(*pHead)->Rchild;
	(*pHead)->Rchild =tmp;
	RR_Rotating(pHead);	
}

void LR_Rotating(tree **pHead)
{
	tree *tmp = (*pHead)->Lchild->Rchild;

	(*pHead)->Lchild->Rchild =tmp->Lchild;
	tmp->Lchild =(*pHead)->Lchild;
	(*pHead)->Lchild =tmp;
	LL_Rotating(pHead);
}

void Rotating_tree(tree **pHead)
{
	int rot_type; 
	if(!(*pHead))
		return;
	else
	{
		rot_type= Rotation_type(*pHead);

		if(!rot_type)
			return;
		else if(rot_type==LL_TYPE) 
			LL_Rotating(pHead);
		else if(rot_type==RR_TYPE)
			RR_Rotating(pHead);
		else if(rot_type==LR_TYPE)
			LR_Rotating(pHead);
		else
			RL_Rotating(pHead);
	}
}

void Avltree_ins(tree **ppHead,int data)
{
	if(!(*ppHead))
	{
		*ppHead = get_tree_node();
		(*ppHead)->data  = data;
		return;
	}
	
	if(data > (*ppHead)->data)
		Avltree_ins(&((*ppHead)->Rchild),data);
	else
		Avltree_ins(&((*ppHead)->Lchild),data);

	chg_level(ppHead,(*ppHead)->level);
	Rotating_tree(ppHead);
}

void chg_node(tree **ppHead)
{
	tree *tmp =*ppHead;
	if(!(*ppHead)->Rchild)
		*ppHead = tmp->Lchild;
	else
		*ppHead = tmp->Rchild;

	if(*ppHead) (*ppHead)->level = tmp->level;
	free(tmp);
}

void find_max(tree **ppHead,int *max)
{
	if((*ppHead)->Rchild)
		find_max(&(*ppHead)->Rchild,max);
	else
	{
		*max = (*ppHead)->data;
		chg_node(ppHead);
	}
}

void deAvltree(tree **ppHead,int data)
{
	if(!(*ppHead))
	{
		printf("no match data\n");
		return;
	}
	if(data > (*ppHead)->data)
		deAvltree(&((*ppHead)->Rchild),data);
	else if(data < (*ppHead)->data)
		deAvltree(&((*ppHead)->Lchild),data);
	else if((*ppHead)->Lchild && (*ppHead)->Rchild)
	{
		int max;
		find_max(&(*ppHead)->Lchild,&max);
		(*ppHead)->data = max;
	}
	else
		chg_node(ppHead);	
	
	if(*ppHead) chg_level(ppHead,(*ppHead)->level);
	Rotating_tree(ppHead);
}

void print_tree(tree *pHead)
{
	if(pHead)
	{
                printf("data = %d, ",pHead->data);

                if(pHead->Lchild)
                        printf("left =%4d, ",pHead->Lchild->data);
                else
                        printf("left =NULL, ");

                if(pHead->Rchild)
                        printf("right =%4d\n",pHead->Rchild->data);
                else
                        printf("right = NULL\n");

                printf("level = %d, ",pHead->level);

                if(pHead->Lchild)
                        printf("left =%4d, ",pHead->Lchild->level);
                else
                        printf("left =NULL, ");

                if(pHead->Rchild)
                        printf("right =%4d\n\n",pHead->Rchild->level);
                else
                        printf("right = NULL\n\n");
                print_tree(pHead->Lchild);
                print_tree(pHead->Rchild);
        }
        else
                return;
}

int main(void)
{
	int main_cnt;
	tree *pMain_head =NULL;
	int aData[ARRAY_SIZE]= {10,20,30,40,50,44,41,17};
//	int aData[ARRAY_SIZE]= {10,20,17,40,50,41,44,30};	
	for(main_cnt=0;main_cnt<sizeof(aData)/sizeof(int);main_cnt++)
		Avltree_ins(&pMain_head,aData[main_cnt]);

	printf("\nafter insert\n");
	print_tree(pMain_head);
	
	deAvltree(&pMain_head,30);

	printf("\nafter delet\n");
	print_tree(pMain_head);

	return 0;
}
