#ifndef _H_HASHLIST_
#define _H_HASHLIST_

#define HASH_NUM_MAX 100

#define u32 unsigned int

//typedef struct _Node * pNode;
//typedef struct _Hash_Header * pHash_Header;

typedef struct _Node
{
	u32 id;
	u32 data;
	struct _Node *next;
}Node, *pNode;

typedef struct _Hash_Header
{
	struct _Node *next;
}Hash_Header, *pHash_Header;

typedef struct _Hash_List
{
	struct  _Hash_Header* list[100];
}Hash_List, *pHash_List;

pHash_List init_hash_list(void);
//pHash_Header init_hash_header(void);
//pNode init_node_header(void);
//void init_all_node_header(void);
pNode insert_node_to_hash(pHash_List plist, u32 id, u32 data);
int delete_node_to_hash(pHash_List plist, u32 id);
void print_hash(pHash_List plist);
int free_all_hash(pHash_List plist);


#endif
