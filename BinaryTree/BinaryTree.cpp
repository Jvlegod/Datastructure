nclude <iostream>
#include <queue>
#include <stack>
using namespace std;

typedef int T;

// 二叉树结构体（链式）
typedef struct BiTNode {
	T data;
	struct BiTNode* lchild, * rchild;
} BiTNode_t, * BiTree;

// 建立二叉树
BiTree buildTree(char arr[], int index, int len) {
	BiTree node = nullptr;
	if (index < len) {
		if (arr[index] == '#') {
			return nullptr;
		}

		node = (BiTree)malloc(sizeof(BiTNode_t));
		node->lchild = buildTree(arr, 2 * index + 1, len);
		node->rchild = buildTree(arr, 2 * index + 2, len);
	}
	return node;
}

// 先序建立二叉树
BiTree PrebuildTree(BiTree node) {
	
	char data;
	cin >> data;

	if (data == '#') {
		return nullptr;
	}
	else {
		node = (BiTree)malloc(sizeof(BiTNode_t));
		node->data = data;

		PrebuildTree(node->lchild);
		PrebuildTree(node->rchild);
	}

	return node;
}

// 先序列遍历（递归）
void PreOrderTraverse(BiTree T) {
	if (T == nullptr) {
		return;
	}

	printf("%d", T->data);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
}

// 先序列遍历（非递归）
void PreOrderTraverse(BiTree node) {
	stack<BiTree> s;
	
	while (node != nullptr || !s.empty()) {
		if (node != nullptr) {
			printf("%d", node->data);
			s.push(node);
			node = node->lchild;
		}
		else {
			node = s.top();
			s.pop();
			node = node->rchild;
		}
	}
}

// 中序列遍历（递归）
void InOrderTraverse(BiTree T) {
	if (T == nullptr) {
		return;
	}

	InOrderTraverse(T->lchild);
	printf("%d", T->data);
	InOrderTraverse(T->rchild);
}

// 中序列遍历（非递归）
void InOrderTraverse(BiTree node) {
	if (node == nullptr) {
		return;
	}

	stack<BiTree> s;

	while (node != nullptr || !s.empty()) {
		if (node != nullptr) {
			s.push(node);
			node = node->lchild;
		}
		else {
			node = s.top();
			s.pop();
			printf("%d", node->data);
			node = node->rchild;
		}
	}
}

// 后序列遍历（递归）
void PostOrderTraverse(BiTree T) {
	if (T == nullptr) {
		return;
	}

	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%d", T->data);
}

// 后序列遍历（非递归）
void PostOrderTraverse(BiTree node) {
	stack<BiTree> s;
	BiTree lastVisit = nullptr;

	while (node != nullptr) {
		s.push(node);
		node = node->lchild;
	}

	while (!s.empty()) {
		if (node->rchild == nullptr || node->rchild == lastVisit) {
			printf("%d\n", node->data);
			lastVisit = node;
		}
		else {
			s.push(node);
			node = node->rchild;

			while (node != nullptr) {
				s.push(node);
				node = node->lchild;
			}
		}
	}
}

// 层序遍历（非递归）
void levelOrderTraverse(BiTree T) {
	if (T == nullptr) {
		return;
	}
	
	queue <BiTree> q;

	q.push(T);
	while (!q.empty()) {
		BiTree node = q.front();
		printf("%d\n", node->data);
		
		if (node->lchild != nullptr) {
			q.push(node->lchild);
		}

		if (node->rchild != nullptr) {
			q.push(node->rchild);
		}
	}
}

int main()
{

	return 0;
}
