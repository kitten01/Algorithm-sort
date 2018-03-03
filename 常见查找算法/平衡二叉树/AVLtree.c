#include <stdio.h>
#include <stdlib.h>
#include "AVLtree.h"
#include "queue.h"      //水平遍历时需要队列数据结构

AVLtree *find(myType data, AVLtree *T) {
	if (T == NULL)
		return NULL;
	else if (data < T->element)
		return find(data, T->lchild);
	else if (data > T->element)
		return find(data, T->rchild);
	else return T;
}

AVLtree *findMin(AVLtree *T) {
	if (T == NULL)
		return NULL;
	else if (T->lchild != NULL)
		return findMin(T->lchild);
	else return  T;
}

AVLtree *findMax(AVLtree *T)
{
	if (T != NULL)
		while (T->rchild != NULL)
			T = T->rchild;
	return T;

}

static int getHight(AVLtree *T) {
	return GET_HEIGHT(T);
}

//LL型
static AVLtree *singleRotateWithLeft(AVLtree *A) {
	AVLtree *B = A->lchild;
	A->lchild = B->rchild;
	B->rchild = A;
	A->height = MAX(GET_HEIGHT(B->lchild), GET_HEIGHT(A->rchild)) + 1;
	B->height = MAX(GET_HEIGHT(B->lchild), A->height) + 1;
	return B;

}

//RR型
static AVLtree *singleRotateWithRight(AVLtree *A) {
	AVLtree *B = A->rchild;
	A->rchild = B->lchild;
	B->lchild = A;
	A->height = MAX(GET_HEIGHT(B->lchild), GET_HEIGHT(A->rchild)) + 1;
	B->height = MAX(GET_HEIGHT(B->lchild), A->height) + 1;
	return B;
}

//LR型
static AVLtree *doubleRotateWithLeft(AVLtree *A) {
	A->lchild = singleRotateWithRight(A->lchild);
	return singleRotateWithLeft(A);
}

//RL型
static AVLtree *doubleRotateWithRight(AVLtree *A) {
	A->rchild = singleRotateWithLeft(A->rchild);
	return singleRotateWithRight(A);
}

AVLtree *insert(myType data, AVLtree *T){
	if (T == NULL) {
		T = (AVLtree *)malloc(sizeof(struct treeNode));
		T->element = data;
		T->lchild = NULL;
		T->rchild = NULL;
		T->height = 0;
	}
	else if (data < T->element) {
		T->lchild = insert(data, T->lchild);
		if (GET_HEIGHT(T->lchild) - GET_HEIGHT(T->rchild) == 2) {
			if(data < T->lchild->element)
			T = singleRotateWithLeft(T);
			else T = doubleRotateWithLeft(T);
		}
	}
	else if (data > T->element) {
		T->rchild = insert(data, T->rchild);
		if (GET_HEIGHT(T->rchild) - GET_HEIGHT(T->lchild) == 2) {
			if (data > T->rchild->element)
				T = singleRotateWithRight(T);
			else T = doubleRotateWithRight(T);
		}
	}
	T->height = MAX(getHight(T->lchild),getHight(T->rchild)) + 1;
	return  T;
}

AVLtree *erase(myType data, AVLtree *T) {
	AVLtree *temp,*temp1,*tmpNode;
	if (T == NULL) {
		printf("there has no tree data");
	}
	//找到删除后的平衡函数
	else if (data < T->element) {
		T->lchild = erase(data, T->lchild);
		if (getHight(T->rchild) - getHight(T->lchild) == 2) {
			temp = T->rchild;
			if (getHight(temp->lchild) < getHight(temp->rchild))
				T = singleRotateWithRight(T);
			else T = doubleRotateWithRight(T);
		}
	}
	else if (data > T->element) {
		T->rchild = erase(data, T->rchild);
		if (getHight(T->lchild) - getHight(T->rchild) == 2) {
			temp = T->lchild;
			if (getHight(temp->lchild) < getHight(temp->rchild))

				T = doubleRotateWithLeft(T);
			else T = singleRotateWithLeft(T);
		}
	}
	//删除有两个子结点的
	else if (T->lchild && T->rchild) {
		if (getHight(T->lchild) < getHight(T->rchild)) {
			temp1 = findMin(T->rchild);
			T->element = temp1->element;
			T->rchild = erase(T->element, T->rchild);
		}
		else {
			temp1 = findMax(T->lchild);
			T->element = temp1->element;
			T->rchild = erase(T->element, T->lchild);
		}
	}
	//删除有一个或零个子结点的
	//先赋值给第三空间后，指针后移，释放结点
	else {
		//	one or zero children
		tmpNode = T;
		T = (T->lchild == NULL ? T->rchild : T->lchild);
		free(tmpNode);
	}
	return T;
}
void levelOrder(AVLtree *T)
{
	QUEUE *q = createQueue(100);

	while (T != NULL) {
		printf("%d ", T->element);
		if (T->lchild != NULL)
			enQueue(T->lchild, q);
		if (T->rchild != NULL)
			enQueue(T->rchild, q);

		if (!isEmpty(q))
			T = frontAndDequeue(q);
		else
			T = NULL;
	}

	disposeQueue(q);
}

void preOrder(AVLtree *T)
{
	if (T != NULL) {
		printf("%d ", T->element);
		preOrder(T->lchild);
		preOrder(T->rchild);
	}
}

void inOrder(AVLtree *T)
{
	if (T != NULL) {
		inOrder(T->lchild);
		printf("%d ", T->element);
		inOrder(T->rchild);
	}
}
void postOrder(AVLtree *T)
{
	if (T != NULL) {
		postOrder(T->lchild);
		postOrder(T->rchild);
		printf("%d ", T->element);
	}
}