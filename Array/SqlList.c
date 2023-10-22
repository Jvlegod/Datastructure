#include <stdio.h>
#include <malloc.h>

#define UNDEFINE 0xFFFFFFFF

typedef enum {
	false,
	true
}bool;

typedef struct _SqlList{
	int* data;   // data指向起始位置
	int maxsize; // 最大的存储容量
	int length;  // 顺序表的当前长度
} SqlList_t;

void SqlList_init(SqlList_t* array, int capacity); // 初始化
// 增加操作
bool SqlList_push_back(SqlList_t* array, int data); // 追加操作
// 删除
bool SqlList_pop_back(SqlList_t* array); // 删除末尾元素
// 查看
int SqlList_index(SqlList_t* array, int key); // 查看
// 判断
bool if_full(SqlList_t* array);
bool if_empty(SqlList_t* array);
// 遍历
void traverse(SqlList_t* array);
// 释放
void SqlList_free(SqlList_t* array);


int main()
{
	SqlList_t array;

	// 初始化
	SqlList_init(&array, 10);
	// 增加
	SqlList_push_back(&array, 2);
	SqlList_push_back(&array, 3);
	SqlList_push_back(&array, 100);
	SqlList_pop_back(&array);
	SqlList_pop_back(&array);
	SqlList_push_back(&array, 100);
	traverse(&array);
	// 释放
	SqlList_free(&array);
	return 0;
}

void SqlList_init(SqlList_t* array, int capacity) {
	// 声明一个capacity大小的数组
	array->data = (int*)malloc(sizeof(int) * capacity);
	// 初始化最大存储容量
	array->maxsize = capacity;
	// 初始化当前的长度
	array->length = 0;
}


bool SqlList_push_back(SqlList_t* array, int data) {
	// 顺序表是否存储满了
	if (if_full(array)) {
		// 也可以扩容
		return false;
	}

	// 追加操作
	array->data[array->length] = data;
	array->length++;
}

bool if_full(SqlList_t* array) {
	if (array->maxsize == array->length) {
		return true;
	}
	return false;
}

bool if_empty(SqlList_t* array) {
	if (array->length == 0) {
		return true;
	}
	return false;
}

void traverse(SqlList_t* array) {
	for (int i = 0; i < array->length; i ++) {
		printf("%d ", array->data[i]);
	}
	puts("");
	// printf("\n");
}


bool SqlList_pop_back(SqlList_t* array) {
	// 判断顺序表是否为空
	if (if_empty(array)) {
		return false;
	}

	array->length--;
}

int SqlList_index(SqlList_t* array, int key) {
	
	// 判断key是否超出界限
	if (key >= array->length) {
		return UNDEFINE;
	}

	return array->data[key];
}

void SqlList_free(SqlList_t* array) {
	free(array->data);
	array->length = 0;
	array->maxsize = 0;
}
