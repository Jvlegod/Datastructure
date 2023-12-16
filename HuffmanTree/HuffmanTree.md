# 哈夫曼编码树

一、定长编码和变长编码

①定长编码：A-0001, B-0010, C-0011 

例：<u>0001</u>0010<u>0001</u>0011  表示  ABAC

②变长编码：A-0, B-1, C-01

那么0101 表示什么？(ABC/CC/ABAB/CAB)

为此我们规定变长编码必须是前缀码，因此A-111, B-10, C-0是可以的

二、什么是节点的路径长度

从**根节点开始到目标节点的连线长度**（或者说个数）

三、什么是树的路径长度

每个**节点**的**路径长度之和**，记作TL（书上讲的是结点而不是叶子结点，这里和带权路径长度要区分开来）

四、什么是节点的带权路径长度

节点的路径长度和节点的权值的乘积

五、什么是树的带权路径长度

所有**叶子节点**的带权路径长度之和，记作WPL

六、哈夫曼编码树的生成

每次在节点堆中取得两个最小权值的元素A和B，将其中相对较小权值的元素作为新节点C的左子树，另外一个作为C右子树，构成一个二叉树，其中C的权值为A和B的权值之和，将A和B从待取节点堆中删除，将节点C加入节点堆，重复上述操作直到节点堆中没有元素为止。

七、哈夫曼编码树的特点

①哈夫曼编码树是WPL最小的树

②生成哈夫曼编码树之后，树中的结点个数必为2n - 1个，（其中n为待编码的元素个数）

③哈夫曼树实质上是一个特殊的二叉树

八、哈夫曼树的作用：数据压缩

C代码:

```cpp
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define T int
#define NO_PARENT 0
#define NO_CHILD 0

typedef struct _Huffman_Tree{
	int weight; // 权重
	T parent;   // 父结点
	T lchild;   // 左孩子
	T rchild;   // 右孩子
}HuffmanNode, * HuffmanTree;

typedef char* HuffmanCode;

void HT_createHuffmanTree(HuffmanTree* HT, int n, int w[]);
void HT_createHuffmanCode(HuffmanCode* HC, HuffmanTree *HT, int n);
void HT_selectMin(HuffmanTree *HT, int *s1, int *s2, int n);

int main()
{
	HuffmanTree HT;
	HuffmanCode HC;
	int w[11] = { 0, 1, 2, 4, 6, 9, 123, 456, 367, 42, 66};
	HT_createHuffmanTree(&HT, 10, w);
	HT_createHuffmanCode(&HC, &HT, 10);

	return 0;
}

void HT_createHuffmanTree(HuffmanTree *HT, int n, int w[]) {
	int s1, s2;
	int m = 2 * n - 1;
	(*HT) = (HuffmanTree)malloc(sizeof(HuffmanNode) * (m + 1));

	for (int i = 1; i <= n; i ++) {
		(*HT)[i].weight = w[i];
		(*HT)[i].lchild = NO_CHILD;
		(*HT)[i].rchild = NO_CHILD;
		(*HT)[i].parent = NO_PARENT;
	}

	for (int i = n + 1; i <= m; i ++) {
		(*HT)[i].weight = 0;
		(*HT)[i].lchild = NO_CHILD;
		(*HT)[i].rchild = NO_CHILD;
		(*HT)[i].parent = NO_PARENT;
	}

	for (int i = n + 1; i <= m; i ++) {
		HT_selectMin(HT, &s1, &s2, i - 1);
		(*HT)[s1].parent = i;
		(*HT)[s2].parent = i;
		(*HT)[i].lchild = s1;
		(*HT)[i].rchild = s2;
		(*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
	}
}

void HT_createHuffmanCode(HuffmanCode* HC, HuffmanTree* HT, int n){
	char* cd;

	cd = (char*)malloc(sizeof(char) * n);
	cd[n - 1] = '\0';
	HC = (HuffmanCode*)malloc(sizeof(char *) * (n + 1));

	for (int i = 1; i <= n; i ++) {
		int start = n - 1;
		for (int cur = i, p = (*HT)[i].parent; p != 0; cur = p, p = (*HT)[p].parent) {
			if (cur == (*HT)[p].lchild) {
				cd[--start] = '0';
			}
			else {
				cd[--start] = '1';
			}
		}

		HC[i] = (char *)malloc(sizeof(char) * (n - start));
		strcpy(HC[i], &cd[start]);
	}

	free(cd);

	for (int i = 1; i <= n; i ++) {
		printf("%d %s\n", (*HT)[i].weight, HC[i]);
	}
}

void HT_selectMin(HuffmanTree* HT, int* s1, int* s2, int n){
	int min = 0;
	
	for (int i = 1; i <= n; i ++) {
		if ((*HT)[i].parent == NO_PARENT) {
			min = i;
			break;
		}
	}

	for (int i = 1; i <= n; i ++) {
		if (((*HT)[i].parent == NO_PARENT) && (*HT)[i].weight < (*HT)[min].weight) {
			min = i;
		}
	}

	*s1 = min;

	for (int i = 1; i <= n; i++) {
		if ((*HT)[i].parent == NO_PARENT && i != *s1) {
			min = i;
			break;
		}
	}

	for (int i = 1; i <= n; i++) {
		if (((*HT)[i].parent == NO_PARENT) && (*HT)[i].weight < (*HT)[min].weight && i != *s1) {
			min = i;
		}
	}

	*s2 = min;
}
```

C++版本：

```cpp
#include <iostream>
using namespace std;

class Node {
public:
	Node() :left(0), right(0), parent(0) {}

	int weight;
	int parent;
	int left;
	int right;
};

class HuffmanTree {
public:
	Node* HT;
	HuffmanTree(int n, int *w) 
	{
		int s1, s2;
		int m = 2 * n - 1;
		HT = new Node[m];
		//叶子节点的初始化
		for (int i = 1; i <= n; i ++)
		{
			HT[i].weight = w[i];
		}
		//非叶子节点的初始化
		for (int i = n + 1; i <= m; i ++)
		{
			HT[i].weight = 0;
		}

		HT[0].weight = 0;

		for (int i = n + 1; i <= m; i ++)
		{
			select(s1, s2, i - 1);
			this->HT[s1].parent = i;
			this->HT[s2].parent = i;
			this->HT[i].left = s1;
			this->HT[i].right = s2;
			this->HT[i].weight = this->HT[s1].weight + this->HT[s2].weight;
		}
	}

	void HuffmanCode(int n);

private:
	using HC = char*;
	HC cd;
	HC* hc;
	void select(int &s1, int &s2, int n);
};

int main()
{
	int w[5] = {0,1,2,4,6};
	HuffmanTree tree(5, w);
	tree.HuffmanCode(5);
	return 0;
}

void HuffmanTree::select(int& s1, int& s2, int n)
{
	int mini;
	for (int i = 1; i <= n; i++)
	{
		if (this->HT[i].parent == 0)
		{
			mini = i;
			break;
		}
	}

	for (int i = 1; i <= n; i ++)
	{
		if (this->HT[i].parent == 0)
		{
			if (this->HT[i].weight < this->HT[mini].weight)
			{
				mini = i;
			}
		}
	}

	s1 = mini;

	for (int i = 1; i <= n; i++)
	{
		if (this->HT[i].parent == 0 && i != s1)
		{
			mini = i;
			break;
		}
	}

	for (int i = 1; i <= n; i++)
	{
		if (this->HT[i].parent == 0 && i != s1)
		{
			if (this->HT[i].weight < this->HT[mini].weight)
			{
				mini = i;
			}
		}
	}
	s2 = mini;
}

void HuffmanTree::HuffmanCode(int n)
{
	int p;
	cd = new char[n];
	cd[n - 1] = '\0';
	this->hc = new char*[n + 1];
	for (int i = 1; i <= n; i ++)
	{
		int start = n - 1;
		for (int j = i, p = this->HT[j].parent; p != 0; j = p, p = this->HT[p].parent)
		{
			if (this->HT[p].left == j)
			{
				cd[--start] = '0';
			}
			else
			{
				cd[--start] = '1';
			}
		}
		hc[i] = new char[n - start];
		strcpy_s(hc[i], strlen(hc[i]), &cd[start]);
		cout << "该节点的Huffman编码为: " << hc[i] << endl;
	}
	delete[] cd;
}
```

