#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "hashlist.h"

/*��ʼ��һ����ϣ��*/
pHash_List init_hash_list(void)
{
	u32 i;
	pHash_List plist;
	//pHash_Header phead;

	plist = (Hash_List *)malloc(sizeof(Hash_List));

	for (i = 0; i < 100; i++)
	{
		plist->list[i] = (Hash_Header *)malloc(sizeof(Hash_Header));
		plist->list[i]->next = NULL;
	}

	return plist;
}

#if 0
/*��ʼ��һ����ϣ����ͷ*/
pHash_Header init_hash_header(void)
{
	Hash_Header *phead;

	phead = (Hash_Header *)malloc(sizeof(Hash_Header));
	phead->next = NULL;

	return phead;
}

/*��ʼ��һ������ڵ�ͷ*/
pNode init_node_header(void)
{
	Node *phead;

	phead = (Node *)malloc(sizeof(Node));
	phead->next = NULL;

	return phead;
}

/*��ʼ�����нڵ�����ͷ*/
void init_all_node_header(void)
{
	u32 i;
	Hash_Header *plist;

	for (i = 0; i < HASH_NUM_MAX; i++)
	{
		hash_list[i] = init_hash_header();
	}
}
#endif

/*����id����һ���ڵ�����*/
pNode insert_node_to_hash(pHash_List plist, u32 id, u32 data)
{
	Node *ptail, *pre, *p = NULL;
	u32 temp = id % 100;

	ptail = (Node *)malloc(sizeof(Node));
	ptail->next = NULL;
	ptail->data = data;
	ptail->id = id;

	if (NULL == plist->list[temp]->next)
	{
		plist->list[temp]->next = ptail;

		printf("��������id=%d\n", ptail->id);

		return ptail;
	}
	pre = plist->list[temp]->next;
	while (pre)
	{
		p = pre;
		pre = pre->next;
	}
	p->next = ptail;
	printf("��������id=%d\n", ptail->id);

	return ptail;
}

/*����idɾ��һ���ڵ�����*/
int delete_node_to_hash(pHash_List plist, u32 id)
{
	u32 temp = id % 100;
	Node *psea;

	psea = plist->list[temp]->next;
	if (NULL == psea)
	{
		printf("��������������Ϊ��\n");
		return -1;
	}
#if 1  
	if (id == psea->id)
	{
		plist->list[temp]->next = psea->next;
		free(psea);
		//printf("������ΨһԪ�ر�ɾ��\n"); 
		printf("��ȷɾ������\n");
		return 0;
	}
#endif  
	if (NULL == psea->next)
	{
		printf("������id������\n");
		return -2;
	}

	while (id != psea->next->id)
	{
		psea = psea->next;
		if (NULL == psea->next)
		{
			printf("������id������\n");
			return -2;
		}
	}
	psea->next = psea->next->next;
	free(psea->next);

	printf("��ȷɾ������\n");
	return 0;
}

/*������ӡ��ϣ����Ϣ*/
void print_hash(pHash_List plist)
{
	u32 i;
	pNode p;

	printf("��ӡ������ϣ����Ϣ:\n");

	for (i = 0; i < 100; i++)
	{
		p = plist->list[i]->next;
		if (NULL != p)
		{
			printf("��%d��: \n", i);
		}

		while (NULL != p)
		{
			printf("�ڵ�id=%d���ڵ���Ϣdata=%d\n", p->id, p->data);

			p = p->next;
		}
	}
}

/*�ͷ�������ϣ������*/
int free_all_hash(pHash_List plist)
{
	u32 i;
	pNode p, pn;

	printf("\n�ͷŹ�ϣ���ڴ�ռ�:\n");

	for (i = 0; i < 100; i++)
	{
		p = plist->list[i]->next;;
		pn = p;
		if (NULL == p)
		{
			continue;
		}
		printf("�ͷŵ�%d��: \n", i);
		while (NULL != pn)
		{
			p = pn;
			pn = p->next;

			printf("�ڵ�id=%d���ڵ���Ϣdata=%d\n", p->id, p->data);
			free(p);
			//p = p->next;
		}
		free(plist->list[i]);
	}

}

int main()
{
	pNode p;
	pHash_List plist;

	plist = init_hash_list();
	insert_node_to_hash(plist, 301, 138);
	insert_node_to_hash(plist, 32, 1334);
	insert_node_to_hash(plist, 201, 137);
	insert_node_to_hash(plist, 132, 1442);

	print_hash(plist);

	delete_node_to_hash(plist, 132);
	//delete_node_to_hash(plist,201);
	//delete_node_to_hash(plist,301);

	print_hash(plist);

	free_all_hash(plist);

	getch();
}
