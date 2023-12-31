# 图

## 一、图的相关概念

### 1、无向图和有向图

其中V1, V2为顶点集，E1, E2为边集，无向图用()表示，有向图用<>表示

无向图

![无向图](./graph/image-20220105111136297.png)

有向图

![有向图](./graph/image-20220105111207791.png)



### 2、简单图、完全图和混合图

简单图：不存在重边和环的图

完全图：

无向完全图：

​	图中任意两个顶点之间都存在一条边能互相到达，即有(v~i~, v~j~)

​	特点：

$$
Edge = n(n - 1) / 2
$$

有向完全图：

​	图中任意两个顶点之间都存在<v~i~, v~j~>和<v~j~, v~i~>

​	特点：

$$
Edge = n(n - 1)
$$

混合图：既包含有向边也包含无向边，自研概念，也无需研究，目前没有应用。

### 3、子图

​	子图：设有两个图G = （V， E）和G‘ = （V’， E'），若V‘是V的⼦集并且E‘是E的子集。则称G’是G的⼦图。

​	生成子图：在子图的基础上，若V=V'，则称为G的生成子图

### 4、连通图和连通分量

连通：从顶点i到顶点j有路径，则称顶点i和顶点j连通

连通图：图中任意两个点都连通，则称这个图为连通图

极大连通子图：

​	对于连通图，只有**唯一**一个极大连通子图，那就是它本身

​	对于非连通图，存在多个极大连通子图

连通分量：

​	图中的极大连通子图叫做连通分量，每个连通分量都必定是一个连通图

### 5、强连通图和强连通分量（针对有向图）

​	强连通图：对于**有向图**而言，图中任意两个顶点i和j，都有从i到j和从j到i的路径，则称这个图为强连通图。

​	强连通分量：有向图中的极大连通子图称为图的强连通分量

### 6、连通图的生成树（极小连通子图）

它含有图中全部的n个结点，但是只有构成树的n-1条边  

![连通图的生成树](./graph/image-20231222200948001.png)

### 7、稠密图和稀疏图

​	稠密图：当一个图中的边比较多的时候，称为稠密图

​	稀疏图：当一个图中的边比较少的时候，称为稀疏图

### 8、权和网

​	权：图中每一条边都可以赋予一个对应的数，称这个数为该边的权

​	网：带有权的图称为网

### 9、端点和邻接点

​	端点：图中有两个顶点i和j，i和j用一条边相连，那么i和j称为这条边的端点

​	邻接点：i和j互为邻接点

### 10、度

**注：貌似离散数学当中树的度和图的度是一个意思，但是数据结构中我们常常把树的度视为出度，图的度视为总度（入度+出度）**

​	无向图：

​		度：顶点所具有的边的数目

​	有向图：

​		入度：以顶点为终点的边的数目

​		出度：以顶点为起点的边的数目

​		度：度 = 入度 + 出度

### 11、路径长度

​	从i~1~到i~n~，经过有i~2~, i~3~, i~4~, ... , i~n-1~，那么这个路径途中经过的边的数目为路径长度

### 12、回路（环）

​	有且仅有开始点到最后的点为同一个顶点，那么这条路径叫回路(离散结构的环和数据结构的环好像概念有点不同，这里区分一下)

### 13、简单回路、欧拉回路和哈密顿回路

​	简单回路：开始点和结束点的路径没有重复的部分

​	欧拉回路：在一段路径中刚好经过图中各边一次且恰好一次的回路

​	哈密顿回路：在一段路径中刚好经过图中各顶点一次且恰好一次的回路

## 二、图的存储结构

### 以顶点为目标：

#### 1、邻接矩阵

​	![邻接矩阵](./graph/image-20220105133802949.png)

代码：

```cpp
#include<iostream>
using namespace std;
#define MaxVertices 100
#define MaxWeight 32767


typedef struct {
	int Vertices[MaxVertices];
	int Edge[MaxVertices][MaxVertices];
	int numV;
	int numE;
}AdjMatrix;

void createGraph(AdjMatrix* G);

void createGraph(AdjMatrix* G)
{
	int n, e;
	int vi, vj, w;
	cout << "请输入顶点数和边数" << endl;
	cin >> n, e;
	G->numV = n;
	G->numE = e;
	//初始化顶点集
	for (int i = 0; i < G->numV; i++)
	{
		cout << "请输入第" << i + 1 << "个顶点的信息" << endl;
		cin >> G->Vertices[i];
	}
	cout << endl;
	//初始化图
	for (int i = 0; i < G->numE; i++)
	{
		for (int j = 0; j < G->numE; j++)
		{
			if (i == j)
			{
				G->Edge[i][j] = 0;
			}
			else
			{
				G->Edge[i][j] = MaxWeight;
			}
		}
	}
	for (int i = 0; i < G->numE; i++)
	{
		cout << "请第" << i + 1 << "输入(Vi, Vj)的权值信息" << endl;
		cin >> vi, vj, w;
		G->Edge[vi - 1][vj - 1] = w;
		G->Edge[vj - 1][vi - 1] = w;
	}
}
```



#### 2、邻接表和逆邻接表

![邻接表和逆邻接表](./graph/image-20220105134312873.png)

代码：

```cpp
#include<iostream>
using namespace std;
#define MaxVertices 100
// 若(vi, vj)
typedef struct EdgeNode {
	int adjvex; //vj在数组中的下标
	struct EdgeNode* next;// vi除了vj的下一邻接点
}Edge;

typedef struct VertexNoe {
	int data;// 存放vi的数据
	Edge* next; // 指向vi的邻接点
}Vertex, ArrVertex[MaxVertices];

typedef struct OLGraph {
	ArrVertex Arr;// vi的数组集
	int numV;// 顶点的数量
	int numE;// 边的数量
}Graph;

void createGraph(Graph* G);

int main(void)
{

	system("pause");
	return 0;
}

void createGraph(Graph* G)
{
	int n, e;
	int vi, vj;
	cout << "请输入顶点数和边数" << endl;
	cin >> n, e;
	G->numV = n;
	G->numE = e;
	//初始化顶点数组
	for (int i =0; i < G->numV; i++)
	{
		cout << "请输入第" << i + 1 << "个顶点的数值" << endl;
		cin >> G->Arr[i].data;
		G->Arr[i].next = NULL;
	}
	//初始化边
	for (int i = 0; i < G->numE; i++)
	{
		cout << "请输入第" << i + 1 << "个边的下标(vi, vj)" << endl;
		cin >> vi, vj;
		Edge* new_edge = new Edge;
		new_edge->next = G->Arr[vi].next;
		G->Arr[vi].next = new_edge;
		new_edge->adjvex = vj;

		Edge* new_edge = new Edge;
		new_edge->next = G->Arr[vj].next;
		G->Arr[vj].next = new_edge;
		new_edge->adjvex = vi;
	}
}
```



#### 3、十字链表

![十字链表](./graph/image-20220105150411333.png)

代码：

```cpp
#include<iostream>
using namespace std;
#define MaxVertices 100
// 若(vi, vj)
typedef struct ArcBox {
	int tailvex, headvex; //指向vi和vj的下标 
	struct ArcBox* hlink, * tlink;// 下标为tailvex的点的下一条入度， 出度的点
}EdgeNode;

typedef struct Vertex {
	int data;// 存放vi的数据
	EdgeNode* firstin, * firstout;// 指向vi的入度的点与vi出度的点
}VertexNode, Arr[MaxVertices];

typedef struct OLGraph {
	Arr xlinklist;
	int numV, numE;
}Graph;

void CreateGraph(Graph* G);//创建图
int Locate(Graph* G, int v);//定位

int main(void)
{

	system("pause");
	return 0;
}

void CreateGraph(Graph* G)
{
	int n, e;
	int vi, vj;
	cout << "请输入顶点个数和边的个数" << endl;
	cin >> n, e;
	G->numV = n;
	G->numE = e;
	//初始化顶点
	for (int i = 0; i < G->numV; i++)
	{
		cout << "请输入第" << i + 1 << "个顶点的数据" << endl;
		cin >> G->xlinklist[i].data;
		G->xlinklist[i].firstin = NULL;
		G->xlinklist[i].firstout = NULL;
	}
	//创建十字链表
	for (int i = 0; i < G->numE; i++)
	{
		cout << "请输入(vi, vj)的关系" << endl;
		EdgeNode* new_node = new EdgeNode;
		int m = Locate(G, vi);
		int n = Locate(G, vj);
		if (m == EOF || n == EOF)
		{
			cout << "未查找到相关数据,请重新输入" << endl;
			i--;
			continue;
		}
		else
		{
			new_node->tailvex = vi;
			new_node->headvex = vj;
			new_node->tlink = G->xlinklist[m].firstout;
			new_node->hlink = G->xlinklist[n].firstin;
			G->xlinklist[n].firstin = G->xlinklist[m].firstout = new_node;
		}
	}
}

int Locate(Graph* G, int v) 
{
	for (int i = 0; i < G->numV; i++)
	{
		if (G->xlinklist[i].data == v)
		{
			return i;
		}
	}
	return EOF;
}
```





### 以边为目标：

#### 1、邻接多重表

<u>**注：邻接多重表主要针对无向图**</u>

![邻接多重表](./graph/image-20220105151708393.png)

代码：

```cpp
#include<iostream>
using namespace std;
#define MaxVertices 100

typedef struct EdgeNode {
	int ivex, jvex;//指向vi和vj的下标
	struct EdgeNode* vi, *vj;//指向与vi有直接关系的下一节点和与vj有直接关系的下一节点
}Edge;

typedef struct VertexNode {
	int data;// 存放数据
	Edge* firstEdge;// 指向与接点vi有关联的下一节点
}Vertex;

typedef struct {
	Vertex xlinklist[MaxVertices];
	int numV;
	int numE;
}Graph;

void createGraph(Graph* G);//创建图
int Locate(Graph* G, int v);//定位下标

int main(void)
{

	system("pause");
	return 0;
}

void createGraph(Graph* G)
{
	int n, e;
	int vi, vj;
	cout << "请输入顶点个数和边个数" << endl;
	cin >> n, e;
	G->numV = n;
	G->numE = e;
	//创建顶点集
	for (int i = 0; i < G->numV; i++)
	{
		cout << "请输入第" << i + 1 << "个顶点的数值" << endl;
		cin >> G->xlinklist[i].data;
		G->xlinklist[i].firstEdge = NULL;
	}
	//创建边集
	for (int i = 0; i < G->numE; i++)
	{
		cout << "请输入(vi, vj)的数据" << endl;
		int m = Locate(G, vi);
		int n = Locate(G, vj);
		Edge* new_node = new Edge;
		new_node->ivex = m;
		new_node->jvex = n;
		new_node->vi = G->xlinklist[vi].firstEdge;
		new_node->vj = G->xlinklist[vj].firstEdge;
		G->xlinklist[vi].firstEdge = new_node;
		G->xlinklist[vj].firstEdge = new_node;
	}
}

int Locate(Graph* G, int v)
{
	for (int i = 0; i < G->numV; i++)
	{
		if (G->xlinklist[i].data == v)
		{
			return i;
		}
	}
}
```

#### 2、边集数组

![边集数组](./graph/image-20220105152740127.png)

**注：这里不再写代码，因为太简单了，弄清结构了就可以用**

## 三、图的遍历

​	广度优先搜索和二叉树的层序遍历较为相似，需要借助于队列实现；深度优先搜索和二叉树的前序遍历较为相似，需要借助于栈实现；无论是BFS还是DFS，都适用于有向图和无向图。

### 1、深度优先搜索(DFS)

​		**深度优先搜索算法**（Depth First Search，简称[DFS](https://so.csdn.net/so/search?q=DFS)）：一种用于遍历或搜索树或图的算法。 沿着树的深度遍历树的节点，尽可能深的搜索树的分支。当节点v的所在边都己被探寻过或者在搜寻时结点不满足条件，搜索将回溯到发现节点v的那条边的起始节点。整个进程反复进行直到所有节点都被访问为止。属于盲目搜索,最糟糕的情况算法时间复杂度为O(!n)。

​		优点：1、空间占据小；

​		缺点：2、递归.

​		适用条件：1、要搜索全部的解；2、解在深处

代码:

①邻接矩阵

```cpp
/*
创建无向图并深度优先搜索
*/

#include <stdio.h>
#include <stdlib.h>
#define MAXN 100
typedef struct ArcCell {
    char vexnum[MAXN];         //顶点
    int arcnum[MAXN][MAXN];    //弧
    int n, e;                  //顶点数， 弧数
}Graph;
int Visit[MAXN] = { 0 };         //定义Visit来判断顶点是否被访问，并初始化 



void CreateGraph(Graph *G){        //创建图 ，此处注意&G 
    int s, t;
    scanf("%d %d", &G->n, &G->e);
    getchar();
    for (int i = 0; i < G->n; i++) {
        scanf("%c", &G->vexnum[i]);
    }
    for (int i = 0; i < G->n; i++) {              //初始化数据 
        for (int j = 0; j < G->n; j++) {
            G->arcnum[i][j] = 0;
        }
    }
    for (int i = 0; i < G->e; i++) {              //创建图的邻接矩阵
        scanf("%d %d", &s, &t);
        G->arcnum[s][t] = 1;
        G->arcnum[t][s] = 1;
    }
}

void DFSTraverse(Graph G, int i) {    //对连通分量进行深度搜索 
    printf("%c", G.vexnum[i]);

    for (int j = 0; j < G.n; j++) {
        if (G.arcnum[i][j] != 0 && Visit[j] != false) {
            Visit[j] = 1;
            DFSTraverse(G, j);
        }
    }
}

void DFS(Graph G) {               //对整个图进行深度搜索 
    for (int i = 0; i < G.n; i++) {   //可联想邻接矩阵和无向图来思考遍历过程 
        if (Visit[i] == false) {
            Visit[i] = 1;
            DFSTraverse(G, i);    //连通分量 
        }
    }
}

int main()
{
    Graph G;
    CreateGraph(&G);
    DFS(G);
    return 0;
}


```

②邻接表

```cpp
#include<iostream>
using namespace std;
#define MaxVertices 100

typedef struct EdgeNode {
	int adjvex;
	struct EdgeNode* next;
}Edge;

typedef struct VertexNoe {
	int data;
	Edge* next;
}Vertex, ArrVertex[MaxVertices];

typedef struct OLGraph {
	ArrVertex Arr;
	int numV;
	int numE;
}Graph;

int visited[MaxVertices];//判断是否被查找过

int search(Graph* G, int index);//查找相应数据的下标
void createGraph(Graph* G);
void DFS(Graph* G, int data);//广度优先搜索
void DFStraverse(Graph* G, int data, int index);//开始搜索

int main(void)
{

	system("pause");
	return 0;
}

void createGraph(Graph* G)
{
	int n, e;
	int vi, vj;
	cout << "请输入顶点数和边数" << endl;
	cin >> n, e;
	G->numV = n;
	G->numE = e;
	//初始化顶点数组
	for (int i = 0; i < G->numV; i++)
	{
		cout << "请输入第" << i + 1 << "个顶点的数值" << endl;
		cin >> G->Arr[i].data;
		G->Arr[i].next = NULL;
	}
	//初始化边
	for (int i = 0; i < G->numE; i++)
	{
		cout << "请输入第" << i + 1 << "个边的下标(vi, vj)" << endl;
		cin >> vi, vj;
		Edge* new_edge = new Edge;
		new_edge->next = G->Arr[vi].next;
		G->Arr[vi].next = new_edge;
		new_edge->adjvex = vj;

		Edge* new_edge = new Edge;
		new_edge->next = G->Arr[vj].next;
		G->Arr[vj].next = new_edge;
		new_edge->adjvex = vi;
	}
}

void DFS(Graph* G, int data)
{
	for (int i = 0; i < G->numV; i++)
	{
		visited[i] = false;
	}

	int index = search(G, data);
	if (index == EOF)
	{
		//该数据未在图中
	}
	else
	{
		visited[index] = true;
		BFStraverse(G, data, index);//开始递归查询
	}
}

void DFStraverse(Graph* G, int data, int index)
{
	cout << data << " ";
	Edge* temp = G->Arr[index].next;
	while (temp)
	{
		if (visited[temp->adjvex] == false)
		{
			visited[temp->adjvex] = true;
			BFStraverse(G, G->Arr[temp->adjvex].data, temp->adjvex);
		}
		temp = temp->next;
	}
}

int search(Graph* G, int data)
{
	for (int i = 0; i < G->numV; i++)
	{
		if (G->Arr[i].data == data)
		{
			return i;
		}
	}
	return EOF;
}
```



### 2、广度优先搜索(BFS)

​		**BFS，其英文全称是Breadth First Search**，广度优先搜索算法具有完全性。这意指无论图形的种类如何，只要目标存在，则BFS一定会找到。然而，若目标不存在，且图为无限大，则BFS将不收敛（不会结束）。

​		适用条件：1、求离根最近的解；2、求最优解

代码：

①邻接矩阵

```cpp
#include<iostream>
#include<stack>
using namespace std;
#define MaxVertices 100
#define MaxWeight 32767

typedef struct GraphNode{
	int Vertex[MaxVertices];
	int Edge[MaxVertices][MaxVertices];
	int numV;
	int numE;
}Graph;

void createGraph(Graph* G);//创造图
void BFSTraverse(Graph* G);//邻接矩阵的广度优先搜索
int Locate(Graph* G, int key);//依据元素定位该顶点在数组中的位置
int FirstTraverse(Graph* G, int u);//查找到相关顶点在边集数组中的位置
int NextTraverse(Graph* G, int u, int L);//继上一次查找之后继续遍历

int main(void)
{

	system("pause");
	return 0;
}

void createGraph(Graph* G)
{
	//初始化顶点个数和边的个数
	int n, e;
	cout << "输入顶点个数和边的个数" << endl;
	cin >> n, e;
	G->numV = n;
	G->numE = e;
	//初始化顶点数据
	for (int i = 0; i < G->numV; i++)
	{
		cout << "请输入第" << i + 1 << "个顶点的信息" << endl;
		cin >> G->Vertex[i];
	}
	//初始化边集
	for (int i = 0; i < G->numV; i++)
	{
		for (int j = 0; j < G->numV; j++)
		{
			if (i == j)
			{
				G->Edge[i][j] = 0;
			}
			else
			{
				G->Edge[i][j] = MaxWeight;
			}
		}
	}
	cout << "无权，则1和0表示有无边" << endl;
	//初始化边的信息
	for (int i = 0; i < G->numE; i++)
	{
		int vi, vj, w;
		cout << "请输入第" << i + 1 << "对数据边的信息" << endl;
		cin >> vi, vj, w;
		G->Edge[vi - 1][vj - 1] = w;
		G->Edge[vj - 1][vi - 1] = w;
	}
}

void BFSTraverse(Graph* G)
{
	stack<int> s;//用来广度优先搜素
	int visited[100];//用来判断数据是否遍历过
	//初始化visited
	for (int i = 0; i < G->numE; i++)
	{
		visited[i] = false;
	}
	for (int i = 0; i < G->numV; i++)
	{
		if (visited[i] == false)
		{
			visited[i] = true;
			s.push(G->Vertex[i]);
			cout << "查找到了顶点元素" << G->Vertex[i] << endl;
			while (!s.empty())
			{
				int temp = s.top();
				s.pop();
				temp = Locate(G, temp);
				for (int i = FirstTraverse(G, temp); i >= 0; i = NextTraverse(G, temp, i))
				{
					if (visited[i] == false)
					{
						visited[i] = true;
						cout << G->Vertex[i] << " ";
						s.push(G->Vertex[i]);
					}
				}
				cout << endl;
			}
		}
	}
}

int Locate(Graph* G, int key)
{
	for (int i = 0; i < G->numV; i++)
	{
		if (G->Vertex[i] == key)
		{
			return i;
		}
	}
	cout << "未查找到元素" << endl;
	return EOF;
}

int FirstTraverse(Graph* G, int u)
{
	for (int i = 0; i < G->numV; i++)
	{
		if (G->Edge[u][i] == 1)
		{
			return i;
		}
	}
	return EOF;
}
/*
Graph* G 表示图
int u 表示遍历时的顶点在一维数组中的下标
int L 表示遍历时上一次的位置
*/
int NextTraverse(Graph* G, int u, int L)
{
	for (int i = L + 1; i < G->numV; i++)
	{
		if (G->Edge[u][i] == 1)
		{
			return i;
		}
	}
	return EOF;
}
```

②邻接表

```cpp
#include<iostream>
using namespace std;
#define MaxVertices 100
#include<queue>

typedef struct EdgeNode {
	int adjvex;
	struct EdgeNode* next;
}Edge;

typedef struct VertexNoe {
	int data;
	Edge* next;
}Vertex, ArrVertex[MaxVertices];

typedef struct OLGraph {
	ArrVertex Arr;
	int numV;
	int numE;
}Graph;

int search_subscript(Graph* G, int index);//寻找下标
int visited[MaxVertices];
int exist_index(Graph* G, int index);//检测是否存在
void createGraph(Graph* G);
void initVisited(Graph* G);//初始化判断是否被访问过
void BFS(Graph* G, int index);//广度优先搜索

int main(void)
{

	system("pause");
	return 0;
}

void createGraph(Graph* G)
{
	int n, e;
	int vi, vj;
	cout << "请输入顶点数和边数" << endl;
	cin >> n, e;
	G->numV = n;
	G->numE = e;
	//初始化顶点数组
	for (int i = 0; i < G->numV; i++)
	{
		cout << "请输入第" << i + 1 << "个顶点的数值" << endl;
		cin >> G->Arr[i].data;
		G->Arr[i].next = NULL;
	}
	//初始化边
	for (int i = 0; i < G->numE; i++)
	{
		cout << "请输入第" << i + 1 << "个边的下标(vi, vj)" << endl;
		cin >> vi, vj;
		Edge* new_edge = new Edge;
		new_edge->next = G->Arr[vi].next;
		G->Arr[vi].next = new_edge;
		new_edge->adjvex = vj;

		Edge* new_edge = new Edge;
		new_edge->next = G->Arr[vj].next;
		G->Arr[vj].next = new_edge;
		new_edge->adjvex = vi;
	}
}

void initVisited(Graph* G) 
{
	for (int i = 0; i < G->numV; i++)
	{
		visited[i] = 0;
	}
}

void BFS(Graph* G, int index)
{
	initVisited(G);
	queue<int> q;
	if (exist_index(G, index) == false)
	{
		//提示不存在并退出
	}
	q.push(index);
    visited[search_subscript(G, index)] = 1;
	while (!q.empty())
	{
		int sub = search_subscript(G, index);
		int cur = q.front();
		cout << cur << endl;
		q.pop();
		Edge* temp = G->Arr[sub].next;
		while (temp)
		{
			if (visited[temp->adjvex] == 0)
			{
				cout << G->Arr[temp->adjvex].data << endl;
				visited[temp->adjvex] = 1;
				q.push(G->Arr[temp->adjvex].data);
			}
			temp = temp->next;
		}
	}
}

int exist_index(Graph* G, int index)
{
	for (int i = 0; i < G->numV; i++)
	{
		if (index == G->Arr[i].data)
		{
			return true;
		}
	}
	return false;
}

int search_subscript(Graph* G, int index)
{
	for (int i = 0; i < G->numV; i++)
	{
		if (index == G->Arr[i].data)
		{
			return i;
		}
	}
}
```

## 四、最小生成树
最小生成树这里推荐一个视频，讲解的比较好：
[最小生成树(Kruskal(克鲁斯卡尔)和Prim(普里姆))算法动画演示](https://www.bilibili.com/video/BV1Eb41177d1/?spm_id_from=333.337.search-card.all.click&vd_source=4e0d0cb650fa7f0cb4ae8b51d183d2e2)
### 1、克鲁斯卡尔(Kruskal)
克鲁斯卡尔的算法思想：
1. 将图中所有边按照权值大小排序
2. 依次将边按照不形成环的方式加入到最小生成树的行列当中，若形成环，则将形成环的边丢弃

步骤：
原图

![image](https://github.com/Jvlegod/Datastructure/assets/93458802/05c90e6a-82b4-48bf-bd8b-3db78c4b48ff)

第一步：在图中找出最小的边权，并加入最小生成树行列

![image](https://github.com/Jvlegod/Datastructure/assets/93458802/10be73e4-61ba-4e3b-b1b3-9d7291960bfa)

第二步：寻找下一个最小的边权，继续加入最小生成树行列

![image](https://github.com/Jvlegod/Datastructure/assets/93458802/8a09cc9f-e3e1-4521-8f0e-223d37afbeaa)

继续，到此为止，下一步将加入的边为(6-8)，但是加入之后会形成环，因此我们选择舍弃它，继续加入下一个(2-3)

![image](https://github.com/Jvlegod/Datastructure/assets/93458802/e33914c7-5379-489c-8e1e-6f25fd236883)

![image](https://github.com/Jvlegod/Datastructure/assets/93458802/96ad907b-de9e-47cb-8616-9850d3fe4934)

加入(2-3)则形成如图

![image](https://github.com/Jvlegod/Datastructure/assets/93458802/afb84e8c-54cc-4512-816c-726f1fead28a)

重复以上过程，直到形成最小生成树为止

![image](https://github.com/Jvlegod/Datastructure/assets/93458802/f242b6ac-9780-4d7b-bbaa-ad04572a1377)

红色的路径构成了最小生成树

代码:

```cpp
#include<iostream>
using namespace std;
#define MaxVertices 100
#define MaxWeight 32767


typedef struct {
	int Vertices[MaxVertices];
	int Edge[MaxVertices][MaxVertices];
	int numV;
	int numE;
}AdjMatrix;

typedef struct{
	int weight;
	int Begin;
	int End;
}ArrEdges;

void createGraph(AdjMatrix* G);
void Kruskal(AdjMatrix G);//克鲁斯卡尔

int Find(int parent, int key);//并查集

/* 交换权值 以及头和尾 */
void Swapn(ArrEdges* edges, int i, int j)
{
	int temp;
	temp = edges[i].Begin;
	edges[i].Begin = edges[j].Begin;
	edges[j].Begin = temp;
	temp = edges[i].End;
	edges[i].End = edges[j].End;
	edges[j].End = temp;
	temp = edges[i].weight;
	edges[i].weight = edges[j].weight;
	edges[j].weight = temp;
}

/* 对权值进行排序 */
void sort(ArrEdges edges[], AdjMatrix* G)
{
	int i, j;
	for (i = 0; i < G->numE; i++)
	{
		for (j = i + 1; j < G->numE; j++)
		{
			if (edges[i].weight > edges[j].weight)
			{
				Swapn(edges, i, j);
			}
		}
	}
	printf("权排序之后的为:\n");
	for (i = 0; i < G->numE; i++)
	{
		printf("(%d, %d) %d\n", edges[i].Begin, edges[i].End, edges[i].weight);
	}

}


void createGraph(AdjMatrix* G)
{
	int n, e;
	int vi, vj, w;
	cout << "请输入顶点数和边数" << endl;
	cin >> n, e;
	G->numV = n;
	G->numE = e;
	//初始化顶点集
	for (int i = 0; i < G->numV; i++)
	{
		cout << "请输入第" << i + 1 << "个顶点的信息" << endl;
		cin >> G->Vertices[i];
	}
	cout << endl;
	//初始化图
	for (int i = 0; i < G->numE; i++)
	{
		for (int j = 0; j < G->numE; j++)
		{
			if (i == j)
			{
				G->Edge[i][j] = 0;
			}
			else
			{
				G->Edge[i][j] = MaxWeight;
			}
		}
	}
	for (int i = 0; i < G->numE; i++)
	{
		cout << "请第" << i + 1 << "输入(Vi, Vj)的权值信息" << endl;
		cin >> vi, vj, w;
		G->Edge[vi - 1][vj - 1] = w;
		G->Edge[vj - 1][vi - 1] = w;
	}
}

void Kruskal(AdjMatrix G)
{
	int parent[MaxVertices];
	ArrEdges arredges[MaxVertices];
	int k = 0;
	for (int i = 0; i < G.numV; i++)
	{
		for (int j = i + 1; j < G.numV; j++)
		{
			if (G.Edge[i][j] < MaxWeight)
			{
				arredges[k].Begin = i;
				arredges[k].End = j;
				arredges[k].weight = G.Vertices[k];
			}
		}
	}
	for (int i = 0; i < G.numV; i++)
	{
		parent[i] = -1;
	}
	sort(arredges, &G);

	for (int i = 0; i < G.numV; i++)
	{
		int n = Find(parent[i], arredges[i].Begin);
		int m = Find(parent[i], arredges[i].End);
		if (m != m || n == m == -1)
		{
			parent[n] = m;
		}
	}
}

int Find(int parent[], int key)
{
	if (parent[key] != -1)
	{
		key = parent[key];
	}
	return key;
}
```



### 2、普利姆(Prim)

代码:

```cpp
#include<iostream>
using namespace std;
#define MaxVertices 100
#define MaxWeight 32767


typedef struct {
	int Vertices[MaxVertices];
	int Edge[MaxVertices][MaxVertices];
	int numV;
	int numE;
}AdjMatrix;

void createGraph(AdjMatrix* G);
void Prim(AdjMatrix G);//普利姆

void createGraph(AdjMatrix* G)
{
	int n, e;
	int vi, vj, w;
	cout << "请输入顶点数和边数" << endl;
	cin >> n, e;
	G->numV = n;
	G->numE = e;
	//初始化顶点集
	for (int i = 0; i < G->numV; i++)
	{
		cout << "请输入第" << i + 1 << "个顶点的信息" << endl;
		cin >> G->Vertices[i];
	}
	cout << endl;
	//初始化图
	for (int i = 0; i < G->numE; i++)
	{
		for (int j = 0; j < G->numE; j++)
		{
			if (i == j)
			{
				G->Edge[i][j] = 0;
			}
			else
			{
				G->Edge[i][j] = MaxWeight;
			}
		}
	}
	for (int i = 0; i < G->numE; i++)
	{
		cout << "请第" << i + 1 << "输入(Vi, Vj)的权值信息" << endl;
		cin >> vi, vj, w;
		G->Edge[vi - 1][vj - 1] = w;
		G->Edge[vj - 1][vi - 1] = w;
	}
}

void Prim(AdjMatrix G)
{
	int parent[MaxVertices];//标记父亲
	int visited[MaxVertices];//标记是否被访问过
	int lowcast[MaxVertices];//标记权值
	for (int i = 0; i < G.numV; i++)
	{
		visited[i] = false;
		parent[i] = i;
		lowcast[i] = G.Edge[0][i];
	}
	lowcast[0] = 0;
	parent[0] = 0;
	visited[0] = true;
	for (int i = 0; i < G.numV; i++)
	{
		int min = MaxWeight;
		int index;
		for (int j = 1; j < G.numV; j++)
		{
			if (visited[j] == false && lowcast[j] < min)
			{
				index = j;
				min = lowcast[j];
			}
		}
		visited[index] = true;
		for (int m = 0; m < G.numV; m++)
		{
			if (visited[m] == false && G.Edge[index][m] < lowcast[m])
			{
				lowcast[m] = G.Edge[index][m];
				parent[m] = index;
			}
		}
	}
}
```

## 五、最短路径

### 	1、迪杰斯特拉(Dijkstra)
[最短路径查找—Dijkstra算法](https://www.bilibili.com/video/BV1zz4y1m7Nq/?spm_id_from=333.337.search-card.all.click)

代码:

```cpp
#include<iostream>
using namespace std;
#define MaxVertices 100
#define MaxWeight INT_MAX
typedef int VexType, Edge;

typedef struct AdjacencyMatrix {
	VexType vertex[MaxVertices];
	Edge edge[MaxVertices][MaxVertices];
	int numV;
	int numE;
}Graph;

int dist[MaxVertices];//用于记录最短权值和
int visited[MaxVertices];//用于判断是否查看过
int Prev[MaxVertices];//用于指向前一节点

void createGraph(Graph* G);//创建图
int locate(Graph* G, int v);//定位下标
void Dijkstra(Graph G, int v);//迪杰斯特拉

int main(void)
{
	Graph G;
	createGraph(&G);
	Dijkstra(G, G.vertex[0]);
	cout << G.vertex[0] << "到各顶点的最短路径分别为: " << endl;
	for (int i = 0; i < G.numV; i++)
	{
		cout << "到" << G.vertex[i] << "的最短路径为: " << dist[i];
		cout << endl;
	}

	system("pause");
	return 0;
}

void createGraph(Graph* G)
{
	cout << "请输入顶点个数和边的个数" << endl;
	cin >> G->numV >> G->numE;
	for (int i = 0; i < G->numV; i++)
	{
		cout << "请输入第" << i + 1 << "个顶点的数据" << endl;
		cin >> G->vertex[i];
	}
	for (int i = 0; i < G->numV; i++)
	{
		for (int j = 0; j < G->numV; j++)
		{
			if (i == j)
			{
				G->edge[i][j] = 0;
			}
			else
			{
				G->edge[i][j] = MaxWeight;
			}
		}
	}
	for (int i = 0; i < G->numE; i++)
	{
		int vi, vj, w;
		cout << "请输入第" << i + 1 << "对顶点(vi, vj)的数据以及权值" << endl;
		cin >> vi >> vj >> w;
		vi = locate(G, vi);
		vj = locate(G, vj);
		if (vi == EOF || vj == EOF)
		{
			i--;
			cout << "输入错误,请重新输入" << endl;
			continue;
		}
		G->edge[vi][vj] = w;
		G->edge[vj][vi] = w;
	}
}

int locate(Graph* G, int v)
{
	for (int i = 0; i < G->numV; i++)
	{
		if (G->vertex[i] == v)
		{
			return i;
		}
	}
	return EOF;
}

void Dijkstra(Graph G, int v)
{
	v = locate(&G, v);
	for (int i = 0; i < G.numV; i++)
	{
		Prev[i] = EOF;
		dist[i] = G.edge[v][i];
		visited[i] = false;
	}
	dist[v] = 0;
	visited[v] = true;
	int min;
	int index;//用作标记下标
	for (int i = 0; i < G.numV; i++)
	{
		min = MaxVertices;
		for (int j = 0; j < G.numV; j++)
		{
			if (visited[j] == false && dist[j] < min)
			{
				min = dist[j];
				index = j;
			}
		}
		visited[index] = true;
		for (int m = 0; m < G.numV; m++)
		{
			if (visited[m] == false && (min + G.edge[index][m]) < dist[m])
			{
				dist[m] = min + G.edge[index][m];
				Prev[m] = index;
			}
		}
	}
}
```

### 2、弗洛伊德(Floyd)

代码:

```cpp
#include<iostream>
using namespace std;
#define MaxVertices 100
#define MaxWeight INT_MAX
typedef int VexType, Edge;

typedef struct AdjacencyMatrix {
	VexType vertex[MaxVertices];
	Edge edge[MaxVertices][MaxVertices];
	int numV;
	int numE;
}Graph;

int dist[MaxVertices][MaxVertices];
int path[MaxVertices][MaxVertices];

void createGraph(Graph* G);//创建图
int locate(Graph* G, int v);//定位下标
void Floyd(Graph G);//弗洛伊德

int main(void)
{

	system("pause");
	return 0;
}

void createGraph(Graph* G)
{
	cout << "请输入顶点个数和边的个数" << endl;
	cin >> G->numV >> G->numE;
	for (int i = 0; i < G->numV; i++)
	{
		cout << "请输入第" << i + 1 << "个顶点的数据" << endl;
		cin >> G->vertex[i];
	}
	for (int i = 0; i < G->numV; i++)
	{
		for (int j = 0; j < G->numV; j++)
		{
			if (i == j)
			{
				G->edge[i][j] = 0;
			}
			else
			{
				G->edge[i][j] = MaxWeight;
			}
		}
	}
	for (int i = 0; i < G->numE; i++)
	{
		int vi, vj, w;
		cout << "请输入第" << i + 1 << "对顶点(vi, vj)的数据以及权值" << endl;
		cin >> vi >> vj >> w;
		vi = locate(G, vi);
		vj = locate(G, vj);
		if (vi == EOF || vj == EOF)
		{
			i--;
			cout << "输入错误,请重新输入" << endl;
			continue;
		}
		G->edge[vi][vj] = w;
		G->edge[vj][vi] = w;
	}
}

int locate(Graph* G, int v)
{
	for (int i = 0; i < G->numV; i++)
	{
		if (G->vertex[i] == v)
		{
			return i;
		}
	}
	return EOF;
}

void Floyd(Graph G)
{
	for (int i = 0; i < G.numV; i++)
	{
		for (int j = 0; j < G.numV; j++)
		{
			dist[i][j] = G.edge[i][j];
			path[i][j] = j;
		}
	}

	for (int k = 0; k < G.numV; k++)
	{
		for (int i = 0; i < G.numV; i++)
		{
			for (int j = 0; j < G.numV; j++)
			{
				int temp = (dist[i][k] == MaxWeight || dist[k][j] == MaxWeight) ? MaxWeight : (dist[i][k] + dist[k][j]);
				if (dist[i][j] > temp)
				{
					dist[i][j] = temp;
					path[i][j] = k;
				}
			}
		}
	}
}
```

