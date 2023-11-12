#include <stdio.h>
#include <malloc.h>

#define N 100
typedef int T;

typedef enum {
	false,
	true
} bool;

typedef struct Node{
	T data;
	struct Node* next;
} Node_t;

typedef struct TreeChild{
	Node_t* data;
	int len;
	int maxsize;
}TreeChild_t;

TreeChild_t* TC_init(int data, int maxlen);
bool TC_create_tree(TreeChild_t* tc, T data);
bool TC_insert(TreeChild_t* tc, T parent, T data);
int TC_find_parent(TreeChild_t* tc, T parent);
void TC_print(TreeChild_t* tc);

int main()
{
	TreeChild_t *tc = TC_init(10, 100);
	TC_create_tree(tc, 1);
	TC_insert(tc, 1, 2);
	TC_insert(tc, 1, 3);
	TC_insert(tc, 2, 5);
	TC_insert(tc, 2, 6);
	TC_insert(tc, 5, 8);
	TC_insert(tc, 5, 9);
	TC_insert(tc, 5, 10);
	TC_print(tc);

	return 0;
}

TreeChild_t* TC_init(int data, int maxlen) {
	if (maxlen <= 0) {
		return NULL;
	}
	
	TreeChild_t* tc = (TreeChild_t*)malloc(sizeof(TreeChild_t));
	if (tc == NULL) {
		return NULL;
	}

	tc->data = (Node_t*)malloc(sizeof(Node_t) * maxlen);
	tc->len = 0;
	tc->maxsize = maxlen;
}

bool TC_create_tree(TreeChild_t* tc, T data) {
	tc->data[tc->len].data = data;
	tc->data[tc->len].next = NULL;
	tc->len++;
}

bool TC_insert(TreeChild_t* tc, T parent, T data) {
	if (tc->len == tc->maxsize) {
		return false;
	}
	else {
		int parent_index = TC_find_parent(tc, parent);
		if (parent_index == -1) {
			return false;
		}

		tc->data[tc->len].data = data;
		tc->data[tc->len].next = NULL;

		Node_t* new_node = (Node_t*)malloc(sizeof(Node_t));
		new_node->data = data;
		new_node->next = tc->data[parent_index].next;
		tc->data[parent_index].next = new_node;
		tc->len++;
	}
	return true;
}

int TC_find_parent(TreeChild_t* tc, T parent) {
	int len = tc->len;

	for (int i = 0; i < len; i ++) {
		if (parent == tc->data[i].data) {
			return i;
		}
	}
	return -1;
}

void TC_print(TreeChild_t* tc) {
	int len = tc->len;

	for (int i = 0; i < len; i ++) {
		printf("%d: ", tc->data[i].data);
		Node_t* temp = tc->data[i].next;
		if (temp == NULL) {
			printf("no children");
		}
		
		while (temp) {
			printf("%d ", temp->data);

			temp = temp->next;
		}
		puts("");
	}
}
