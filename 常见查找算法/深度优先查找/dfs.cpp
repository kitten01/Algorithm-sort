#include <stdio.h>  
#include <stdlib.h>  
#define  MaxVertices 100
#define MAX_VERTEX_NUM 10
typedef struct node {   //�߱� 
	int adjvex;
	node* next;
}EdgeNode;

typedef struct {     //�����  
	int vertex;
	EdgeNode* edgenext;
}VertexNode;

typedef VertexNode AdjList[MaxVertices];

typedef struct {
	AdjList adjlist;
	int n, e;	//nΪ�������,eΪ����
}AdjMatrix;
int visited[MAX_VERTEX_NUM];
void CreateGraph(AdjMatrix* G)
{
	int i, j, k, w, v;
	EdgeNode *s;
	printf("���붥�����ͱ������м��Կո�ֿ�����");
	scanf_s("%d%d", &G->n, &G->e);

	printf("���������\n");
	for (i = 0; i<G->n; i++)
	{
		//fflush(stdin);  
		//��� stream ָ������������ stdin������ô fflush ��������Ϊ�ǲ�ȷ���ġ�
		//�ʶ�ʹ�� fflush(stdin) �ǲ���ȷ�ġ�
		getchar();
		printf("�������%d���������Ϣ:", i + 1);
		G->adjlist[i].vertex = getchar();
		G->adjlist[i].edgenext = NULL;
	}
	//ǰ�巨 
	printf("�����߱�\n");
	for (k = 0; k<G->e; k++)
	{
		printf("���������ӵĶ�����ţ�");
		scanf_s("%d%d", &i, &j);
		//����ֱ�������Ľ��б���(�������롰0 1��ʱ����0��Ӧ�ı߱��б���1) 
		i -= 1; j -= 1;
		s = (EdgeNode*)malloc(sizeof(EdgeNode));
		s->adjvex = j;//�߱�ֵ 
		s->next = G->adjlist[i].edgenext;
		G->adjlist[i].edgenext = s;
		//���ڼ�������Ľ��б���(�������롰0 1��ʱ����1��Ӧ�ı߱��б���0)
		s = (EdgeNode*)malloc(sizeof(EdgeNode));
		s->adjvex = i;
		s->next = G->adjlist[j].edgenext;
		G->adjlist[j].edgenext = s;
	}
}
void DispGraph(AdjMatrix *G)
{
	int i;
	for (i = 0; i<G->n; i++)
	{
		printf("%d->", i + 1);
		while (1)
		{
			if (G->adjlist[i].edgenext == NULL)
			{
				printf("^");
				break;
			}
			printf("%d->", G->adjlist[i].edgenext->adjvex + 1);
			G->adjlist[i].edgenext = G->adjlist[i].edgenext->next;

		}
		printf("\n");
	}
//}
//void DFS(AdjMatrix *G, int v)
//{
//	EdgeNode *p;
//	printf("->%c", G->adjlist[v].vertex);
//	visited[v] = 1;
//	p = G->adjlist[v].edgenext;
//	while (p)
//	{
//		if (!visited[p->adjvex]) DFS(G, p->adjvex);
//		p = p->next;
//	}
//}   //�ӵ�v���������DFS

void DFS(AdjMatrix *G, int v) {
	EdgeNode *p;
	printf("->c", G->adjlist[v].vertex);
	visited[v] = 1;
	p = G->adjlist[v].edgenext;
	while (p) {
		if (!visited[p->adjvex])DFS(G, p->adjvex);
		p = p->next;
	}
}

void DFSTraverse(AdjMatrix *G)
{
	printf("�����������˳��");
	for (int v = 0; v<G->n; ++v)
		visited[v] = 0;
	for (int v = 0; v<G->n; ++v)
		if (!visited[v]) 
			DFS(G, v);//�ݹ����
	printf("\n\n");
}//DFSTraverse
int main()
{
	//freopen("1.txt", "r", stdin);
	AdjMatrix* G = (AdjMatrix*)malloc(sizeof(AdjMatrix));
	CreateGraph(G);
	DFSTraverse(G);
	DispGraph(G);
	system("pause");
}