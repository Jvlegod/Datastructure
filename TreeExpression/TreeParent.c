#include <stdio.h>
#include <malloc.h>

#define N 100
typedef int T;

typedef enum {
	false,
	true
}bool;

typedef struct Node{
	T data;
	T parent;
}Node_t;

typedef struct TreeParent {
	int size;
	int maxsize;
	Node_t* data;
}TreeParent_t;

TreeParent_t* TP_init(int maxlen);
bool TP_insert_root(TreeParent_t* tp, T data);
bool TP_insert_child(TreeParent_t* tp, T parent, T data);
int TP_find_parent(TreeParent_t* tp, int index);
void TP_print(TreeParent_t* tp);

int main()
{
	TreeParent_t *tp = TP_init(10);
	TP_insert_root(tp, 2);
	TP_insert_child(tp, 2, 5);
	TP_insert_child(tp, 2, 6);
	TP_insert_child(tp, 5, 1);
	TP_insert_child(tp, 6, 3);
	TP_insert_child(tp, 6, 4);
	TP_print(tp);


	return 0;
}

TreeParent_t* TP_init(int maxlen) {
	if (maxlen <= 0) {
		return NULL;
	}

	TreeParent_t* tp = (TreeParent_t*)malloc(sizeof(TreeParent_t));
	
	if (tp == NULL) {
		return NULL;
	}

	tp->data = (Node_t*)malloc(sizeof(Node_t) * maxlen);
	tp->maxsize = maxlen;
	tp->size = 0;
	return tp;
}

bool TP_insert_root(TreeParent_t* tp, T data) {
	tp->data[tp->size].data = data;
	tp->data[tp->size].parent = -1;
	tp->size++;
	return true;
}

bool TP_insert_child(TreeParent_t* tp, T parent, T data) {
	if (tp->size == tp->maxsize) {
		return false;
	}
	else {
		int parent_index = TP_find_parent(tp, parent);
		if (parent_index == -1) {
			return false;
		}
		tp->data[tp->size].data = data;
		tp->data[tp->size].parent = parent_index;
		tp->size++;
		return true;
	}
}

int TP_find_parent(TreeParent_t* tp, int parent) {
	int len = tp->size;
	for (int i = 0; i < len; i ++) {
		if (parent == tp->data[i].data) {
			return i;
		}
	}
	return -1;
}

void TP_print(TreeParent_t* tp) {
	int len = tp->size;
	for (int i = 0; i < len; i ++) {
		printf("%d %d\n", tp->data[i].data, tp->data[i].parent);
	}

}
