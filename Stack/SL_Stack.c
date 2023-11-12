nclude <stdio.h>
#include <malloc.h>

typedef enum {
    false,
    true
} bool;

typedef int T;
typedef struct SeqStack_t {
    T* data; // 数据元素指针
    int top; // 栈顶元素编号
    int max; // 最大节点数
} SeqStack_t;

// 初始化
SeqStack_t* SS_Create(int maxlen);
// 释放
void SS_Free(SeqStack_t* ss);
// 增
bool SS_Push(SeqStack_t* ss, T x); // 压栈
// 删
bool SS_Pop(SeqStack_t* ss, T* item); // 出栈/弹栈
void SS_MakeEmpty(SeqStack_t* ss); // 清空
// 改
// 查
int SS_Length(SeqStack_t* ss);
bool SS_IsFull(SeqStack_t* ss);
bool SS_IsEmpty(SeqStack_t* ss);
bool SS_Top(SeqStack_t* ss, T* item);
void SS_Print(SeqStack_t* ss);


int main()
{
    SeqStack_t* ss = SS_Create(5);
    SS_Push(ss, 5);
    SS_Push(ss, 4);
    SS_Push(ss, 3);
    SS_Push(ss, 2);
    SS_Print(ss);
    SS_Push(ss, 1);
    SS_Print(ss);
    SS_Push(ss, 100);
    SS_Print(ss);
    return 0;
}

SeqStack_t* SS_Create(int maxlen) {
    // 分配空间
    SeqStack_t* ss = (SeqStack_t*)malloc(sizeof(SeqStack_t));

    ss->data = (T*)malloc(sizeof(T) * maxlen);
    ss->max = maxlen;
    ss->top = -1;
}

bool SS_IsFull(SeqStack_t* ss) {
    return ss->top == (ss->max - 1);
}

bool SS_IsEmpty(SeqStack_t* ss) {
    return ss->top == -1;
}

void SS_MakeEmpty(SeqStack_t* ss) {
    ss->top = -1;
}

void SS_Free(SeqStack_t* ss) {
    free(ss->data);
    free(ss);
}

int SS_Length(SeqStack_t* ss) {
    return ss->top + 1;
}

bool SS_Push(SeqStack_t* ss, T x) {
    // 判断是否栈满
    if (SS_IsFull(ss)) {
        return false;
    }

    ss->top++;
    ss->data[ss->top] = x;
}

bool SS_Pop(SeqStack_t* ss, T* item) {
    ss->top--;
}

bool SS_Top(SeqStack_t* ss, T* item) {
    if (SS_IsEmpty(ss)) {
        return false;
    }

    item = ss->data[ss->top];

    return true;
}

void SS_Print(SeqStack_t* ss) {
    for (int i = 0; i <= ss->top; i ++) {
        printf("%d ", ss->data[i]);
    }
    puts("");
}
