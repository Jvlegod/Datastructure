#include <stdio.h>
#include <stdlib.h> 
#define OK 1  
#define ERROR 0
#define MVNum 100
typedef char OtherInfo;
typedef char VerTexType;
int indegree[MVNum] = { 0 };

typedef struct StackNode {
	int data;
	struct StackNode* next;
}StackNode, * StackList;

StackList Pop(StackList S, int* e)
{
	StackList p;
	p = S;
	if (!p)
		return ERROR;
	*e = p->data;
	S = S->next;
	free(p);
	return S;
}

StackList Push(StackList S, int e)
{
	StackList p;
	p = (StackNode*)malloc(sizeof(StackNode));
	p->data = e;
	p->next = S;
	S = p;
	return S;
}

typedef struct ArcNode {
	int adjvex;
	struct ArcNode* nextarc;
	OtherInfo info;
}ArcNode;

typedef struct VNode {
	VerTexType data;
	ArcNode* firstarc;
}VNode,AdjList[MVNum];
typedef struct {
	AdjList vertices;
	int vexnum, arcnum;
}ALGraph;


int LocateVex(ALGraph* G, VerTexType v)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		if (v == G->vertices[i].data) {
			return i;
		}

	}
}

void GreateUDG(ALGraph* G)
{

	VerTexType v1, v2;
	printf("输入总结点数和弧数：");
	scanf_s("%d %d", &G->vexnum, &G->arcnum);
	getchar();
	printf("输入各个结点的值：");
	for (int i = 0; i < G->vexnum; i++)
	{
		scanf_s("%c", &G->vertices[i].data);
		getchar();
		G->vertices[i].firstarc = NULL;
	}
	for (int i = 0; i < G->arcnum; i++)
	{
		printf("弧的两个端点：");
		scanf_s("%c", &v1);
		getchar();
		scanf_s("%c", &v2);
		getchar();
		
		int Locate01 = LocateVex(G, v1);
		int Locate02 = LocateVex(G, v2);
		ArcNode* p1 = (ArcNode*)malloc(sizeof(ArcNode));
		p1->adjvex = Locate02;
		p1->nextarc = G->vertices[Locate01].firstarc;
		G->vertices[Locate01].firstarc = p1;
		indegree[Locate02]++;

	}
}

// TopoSort
int TopoSort(ALGraph G, int* topo) 
{
	int i;
	StackList S;//用队列也行
	ArcNode* p;
	S = NULL;
	//先检查所有节点中入度为0的结点
	for ( i = 0; i < G.vexnum; i++)
	{
		if (!indegree[i])//当数组是0 
		{
			S = Push(S, i);
		}
	}
	int m = 0;
	while (S) {//只要栈不为空 先出栈 取出栈顶元素 并且记录在topo数组中
		S = Pop(S, &i);
		topo[m] = i;
		++m;
		p = G.vertices[i].firstarc;
		while (p!=NULL)
		{
			int k = p->adjvex;
			--indegree[k];
			if (indegree[k] == 0)
			{
				S = Push(S, k);
			}
			p = p->nextarc;
		}
	}
	topo[m] = -1;//拓扑序列结束的标志
	if (m < G.vexnum)
	{
		return ERROR;
	}
	else
	{
		return OK;
	}
}

int main()
{
	ALGraph G;
	int topo[99] = { 0 };
	GreateUDG(&G);
	if (TopoSort(G,topo))
	{
		printf("是有向无环图，序列为");
		for (int i = 0; topo[i] != -1; i++)
		{
			printf("%c ",G.vertices[topo[i]].data);
		}
	}
	else
	{
		printf("有环");
	}
}
