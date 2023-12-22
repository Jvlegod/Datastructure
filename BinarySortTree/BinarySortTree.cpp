#include<iostream>
using namespace std;

typedef struct SortTree{
	int data;
	struct SortTree* Left;
	struct SortTree* Right;
}Node;

Node* root;

void initRoot(int key);//初始化根节点
void createChild(int key);//插入孩子节点
void Delete(Node* node, int key);//删除
Node* Find(Node* from_root, Node* node, int key);//定位到待删除节点的前一节点
void visited(Node* node);//中序遍历

int main(void)
{
	initRoot(100);
	createChild(5);
	createChild(123);
	createChild(13);
	createChild(254);
	createChild(99);
	createChild(400);
	cout << "中序遍历结果为: ";
	visited(root);
	Delete(root, 5);
	cout << endl;
	visited(root);
	cout << endl;

	system("pause");
	return 0;
}

void initRoot(int key)
{
	root = new Node;
	root->data = key;
	root->Left = NULL;
	root->Right = NULL;
}

void createChild(int key)
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		Node* temp = root;
		Node* pre = NULL;
		while (temp != NULL)
		{
			if (key < root->data)
			{
				pre = temp;
				temp = temp->Left;
			}
			else
			{
				pre = temp;
				temp = temp->Right;
			}
		}
		if (key < pre->data)
		{
			pre->Left = new Node;
			pre->Left->data = key;
			pre->Left->Left = NULL;
			pre->Left->Right = NULL;
		}
		else
		{
			pre->Right = new Node;
			pre->Right->data = key;
			pre->Right->Left = NULL;
			pre->Right->Right = NULL;
		}

	}
}

void Delete(Node* node, int key)
{
	if (node == NULL)
	{
		return;
	}
	else
	{
		if (key == node->data)
		{
			//删除
			Node* tempNode = Find(root, node, key);
			Node* temp = NULL;
			if (node->Left == NULL)
			{
				temp = node;
				node = node->Right;
				if (tempNode == node)
				{
					delete(tempNode);
					root = node;
					tempNode = NULL;
				}
				if (tempNode->Left == temp)
				{
					Node* free_node = temp;
					tempNode->Left = node;
					delete(free_node);
					free_node = NULL;
				}
				else
				{
					Node* free_node = temp;
					tempNode->Right = node;
					delete(free_node);
					free_node = NULL;
				}
			}
			else if (node->Right == NULL)
			{
				temp = node;
				node = node->Left;
				if (tempNode == node)
				{
					delete(tempNode);
					root = node;
					tempNode = NULL;
				}
				if (tempNode->Left == temp)
				{
					Node* free_node = temp;
					tempNode->Left = node;
					delete(free_node);
					free_node = NULL;
				}
				else
				{
					Node* free_node = temp;
					tempNode->Right = node;
					delete(free_node);
					free_node = NULL;
				}
			}
			else
			{
				Node* pre = node;
				Node* temp = node;
				pre = pre->Left;
				while (pre->Right != NULL)
				{
					temp = pre;
					pre = pre->Right;
				}
				node->data = pre->data;
				if (temp != node)
				{
					Node* free_node = pre;
					temp->Right = pre->Left;
					delete(free_node);
					free_node = NULL;
				}
				else
				{
					Node* free_node = pre;
					temp->Left = pre->Left;
					delete(pre);
					free_node = NULL;
				}
			}
		}
		else if (key < node->data)
		{
			Delete(node->Left, key);
		}
		else
		{
			Delete(node->Right, key);
		}
	}
}

Node* Find(Node* from_root, Node* node, int key)
{
	if (node == from_root)
	{
		return node;
	}
	if (from_root->Left != NULL && from_root->Left->data == key)
	{
		return from_root;
	}
	else if (from_root->Right != NULL && from_root->Right->data == key)
	{
		return from_root;
	}
	else
	{
		if (key < from_root->data)
		{
			Find(from_root->Left, node, key);
		}
		else if (key > from_root->data)
		{
			Find(from_root->Right, node, key);
		}
	}
}

void visited(Node* node)
{
	if (node == NULL)
	{
		return;
	}

	visited(node->Left);
	cout << node->data << " ";
	visited(node->Right);
}
