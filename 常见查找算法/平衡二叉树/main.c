#include <stdio.h>
#include <stdlib.h>
#include "AVLtree.h"
#include "queue.h"


int main(void)
{
	AVLtree *t = NULL;

	//createTree(&t);
	t = insert(5, t);
	t = insert(2, t);
	t = insert(1, t);
	t = insert(4, t);
	t = insert(3, t);
	t = insert(8, t);
	t = insert(6, t);
	t = insert(7, t);

	printf("��α���\n");
	levelOrder(t);
	printf("\n�ȸ���\n");
	preOrder(t);
	printf("\n�и���\n");
	inOrder(t);
	printf("\n�����\n");
	postOrder(t);
	printf("\nfind min:%d\n", (findMin(t))->element);
	printf("find max:%d\n", (findMax(t))->element);
	printf("find 6: %d\n", (find(6, t))->element);
	t = erase(6, t);
	printf("ɾ��6����α���\n");
	levelOrder(t);
	t = erase(2, t);
	printf("\nɾ��2����α���\n");
	levelOrder(t);
	system("pause");

	return 0;
}
