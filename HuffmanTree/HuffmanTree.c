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
