#include <stdio.h>
#include <malloc.h>

#define UNDEFINE 0xFFFFFFFF
#define ElemType int

typedef enum {
	false,
	true
}bool;

typedef struct _SqlList{
	ElemType* data;   // data指向起始位置
	int maxsize; // 最大的存储容量
	int length;  // 顺序表的当前长度
} SqlList_t;

// 初始化
void SqlList_init(SqlList_t* array, ElemType capacity); // 创建顺序表
void SqlList_MakeEmpty(SqlList_t* array); // 置顺序表为空
// 增加操作
bool SqlList_push_back(SqlList_t* array, ElemType data); // 追加操作
bool SqlList_InsAt(SqlList_t* array, int key, ElemType data); // 插入元素
// 删除
bool SqlList_pop_back(SqlList_t* array); // 删除末尾元素
int SqlList_Length(SqlList_t* array); // 获取顺序表的长度
bool SqlList_DelAt(SqlList_t* array, int key); // 删除下标为key处的元素
int SqlList_DelValue(SqlList_t* array, ElemType data); // 删除顺序表中的第一个data
// 查看
ElemType SqlList_index(SqlList_t* array, int key); // 查看key下标的元素
void SqlList_SetAt(SqlList_t* array, int key); // 设置key下标元素的内容
int SqlList_FindValue(SqlList_t* array, ElemType data); // 查找顺序表中的第一个data
// 判断
bool SqlList_if_full(SqlList_t* array); // 是否为空
bool SqlList_if_empty(SqlList_t* array); // 是否存储满
// 遍历
void SqlList_traverse(SqlList_t* array); // 遍历顺序表的所有元素
// 释放
void SqlList_free(SqlList_t* array); // 释放顺序表


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
	printf("%d", SqlList_FindValue(&array, 100));
	SqlList_push_back(&array, 100);
	SqlList_traverse(&array);
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


bool SqlList_push_back(SqlList_t* array, ElemType data) {
	// 顺序表是否存储满了
	if (SqlList_if_full(array)) {
		// 也可以扩容
		return false;
	}

	// 追加操作
	array->data[array->length] = data;
	array->length++;
}

bool SqlList_if_full(SqlList_t* array) {
	if (array->maxsize == array->length) {
		return true;
	}
	return false;
}

bool SqlList_if_empty(SqlList_t* array) {
	if (array->length == 0) {
		return true;
	}
	return false;
}

void SqlList_traverse(SqlList_t* array) {
	for (int i = 0; i < array->length; i ++) {
		printf("%d ", array->data[i]);
	}
	puts("");
	// printf("\n");
}


bool SqlList_pop_back(SqlList_t* array) {
	// 判断顺序表是否为空
	if (SqlList_if_empty(array)) {
		return false;
	}

	array->length--;
}

ElemType SqlList_index(SqlList_t* array, int key) {
	
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

void SqlList_MakeEmpty(SqlList_t* array) {
	array->length = 0;
}

int SqlList_Length(SqlList_t* array) {
	return array->length;
}

void SqlList_SetAt(SqlList_t* array, int key, ElemType data) {
	if (key > array->length) {
		return;
	}

	if (key < 0) {
		return;
	}

	array->data[key] = data;
}

bool SqlList_InsAt(SqlList_t* array, int key, ElemType data) {
	int len = array->length;

	if (SqlList_if_full(array)) {
		return false;
	}

	for (int i = len - 1; i >= key; i --) {
		array->data[i + 1] = array->data[i];
	}

	array->data[key] = data;
	array->length++;
	return true;
}


bool SqlList_DelAt(SqlList_t* array, int key) {
	int len = array->length;

	if (SqlList_if_empty(array)) {
		return false;
	}
	
	for (int i = key; i < len - 1; i ++) {
		array->data[i] = array->data[i + 1];
	}
	array->length--;
	return true;
}

int SqlList_FindValue(SqlList_t* array, ElemType data) {
	int len = array->length;
	
	for (int i = 0; i < len; i ++) {
		if (array->data[i] == data) {
			return i;
		}
	}

	return UNDEFINE;
}

int SqlList_DelValue(SqlList_t* array, ElemType data) {
	int key = SqlList_FindValue(array, data);
	if (SqlList_DelAt(array, key)) {
		return true;
	}
	return UNDEFINE;
}
