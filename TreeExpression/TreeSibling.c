nclude <stdio.h>
#include <malloc.h>

typedef int T;
typedef enum {
	false,
	true
} bool;

typedef struct Node {
	T data;
	struct Node* child;
	struct Node* sibling;
} Node_t;

Node_t* root;
Node_t* tempNode;
void TCS_init(T data);
bool TCS_insert(int parent, int data);
void TCS_get_node(Node_t *node, T parent);
void TCS_print(Node_t* node);

int main(){
	TCS_init(1);
	TCS_insert(1, 2);
	TCS_insert(1, 3);
	TCS_insert(2, 4);
	TCS_insert(2, 5);
	TCS_insert(2, 6);
	TCS_insert(6, 7);
	TCS_print(root);

	return 0;
}

void TCS_init(T data) {
	root = (Node_t*)malloc(sizeof(Node_t));
	if (root == NULL) {
		exit(1);
	}
	
	root->data = data;
	
	root->child = NULL;
	root->sibling = NULL;
}

bool TCS_insert(int parent, int data) {
	TCS_get_node(root, parent);
	if (tempNode == NULL) {
		return false;
	}
	else {
		if (tempNode->child != NULL) {
			tempNode = tempNode->child;
			Node_t* new_node = (Node_t*)malloc(sizeof(Node_t));
			new_node->data = data;
			new_node->child = NULL;
			new_node->sibling = tempNode->sibling;
			tempNode->sibling = new_node;
		}
		else {
			Node_t* new_node = (Node_t*)malloc(sizeof(Node_t));
			new_node->child = NULL;
			new_node->sibling = NULL;
			new_node->data = data;
			tempNode->child = new_node;
		}
		return true;
	}
}

void TCS_get_node(Node_t* node, T parent) {
	if (node->data == parent) {
		tempNode = node;
	}

	if (node->child != NULL) {
		TCS_get_node(node->child, parent);
	}

	if (node->sibling != NULL) {
		TCS_get_node(node->sibling, parent);
	}
}

void TCS_print(Node_t* node) {
	Node_t* temp = node;
	
	if (temp == NULL) {
		return;
	}
	printf("%d ", node->data);
	TCS_print(node->child);
	TCS_print(node->sibling);
}
