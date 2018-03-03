#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "hashlist.h"

/*初始化一个哈希表*/
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
/*初始化一个哈希链表头*/
pHash_Header init_hash_header(void)
{
	Hash_Header *phead;

	phead = (Hash_Header *)malloc(sizeof(Hash_Header));
	phead->next = NULL;

	return phead;
}

/*初始化一个链表节点头*/
pNode init_node_header(void)
{
	Node *phead;

	phead = (Node *)malloc(sizeof(Node));
	phead->next = NULL;

	return phead;
}

/*初始化所有节点链表头*/
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

/*根据id插入一个节点数据*/
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

		printf("链表插入点id=%d\n", ptail->id);

		return ptail;
	}
	pre = plist->list[temp]->next;
	while (pre)
	{
		p = pre;
		pre = pre->next;
	}
	p->next = ptail;
	printf("链表插入点id=%d\n", ptail->id);

	return ptail;
}

/*根据id删除一个节点数据*/
int delete_node_to_hash(pHash_List plist, u32 id)
{
	u32 temp = id % 100;
	Node *psea;

	psea = plist->list[temp]->next;
	if (NULL == psea)
	{
		printf("搜索的链表内容为空\n");
		return -1;
	}
#if 1  
	if (id == psea->id)
	{
		plist->list[temp]->next = psea->next;
		free(psea);
		//printf("该链表唯一元素被删除\n"); 
		printf("正确删除数据\n");
		return 0;
	}
#endif  
	if (NULL == psea->next)
	{
		printf("搜索的id不存在\n");
		return -2;
	}

	while (id != psea->next->id)
	{
		psea = psea->next;
		if (NULL == psea->next)
		{
			printf("搜索的id不存在\n");
			return -2;
		}
	}
	psea->next = psea->next->next;
	free(psea->next);

	printf("正确删除数据\n");
	return 0;
}

/*遍历打印哈希表信息*/
void print_hash(pHash_List plist)
{
	u32 i;
	pNode p;

	printf("打印整个哈希表信息:\n");

	for (i = 0; i < 100; i++)
	{
		p = plist->list[i]->next;
		if (NULL != p)
		{
			printf("第%d排: \n", i);
		}

		while (NULL != p)
		{
			printf("节点id=%d，节点信息data=%d\n", p->id, p->data);

			p = p->next;
		}
	}
}

/*释放整个哈希表数据*/
int free_all_hash(pHash_List plist)
{
	u32 i;
	pNode p, pn;

	printf("\n释放哈希表内存空间:\n");

	for (i = 0; i < 100; i++)
	{
		p = plist->list[i]->next;;
		pn = p;
		if (NULL == p)
		{
			continue;
		}
		printf("释放第%d排: \n", i);
		while (NULL != pn)
		{
			p = pn;
			pn = p->next;

			printf("节点id=%d，节点信息data=%d\n", p->id, p->data);
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
