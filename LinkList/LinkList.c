#include <stdio.h>
#include <malloc.h>

#define T int
typedef enum {
    false,
    true
}bool;

typedef struct _LinkNode {
    T data;
    struct _LinkNode* next;
}LinkNode_t;

typedef struct _LinkList {
    LinkNode_t* front;  // 指向头结点。
    LinkNode_t* rear;   // 指向尾结点。
    LinkNode_t* pre;    // 指向当前位置结点的前一个结点。
    LinkNode_t* curr;   // 指向当前位置结点。
    int position;     // 当前位子结点的编号。
    int len;          // 线性表的大小（链表结点数）。
}LinkList_t;

// 初始化
LinkList_t* LL_Create(); // 创建链表
// 增加
bool LL_InsAfter(LinkList_t* llist, T x); // 在当前位置之后插入元素
// 删除
void LL_MakeEmpty(LinkList_t* llist); // 置为空
bool LL_DelAfter(LinkList_t* llist); // 在当前位置之后删除元素
// 修改
bool LL_SetPosition(LinkList_t* llist, int key); // 修改curr指针的位置
// 查看
bool LL_IsEmpty(LinkList_t* llist);
// 遍历
void LL_Print(LinkList_t* llist);
// 释放

int main()
{
    LinkList_t* llist = LL_Create();
    LL_InsAfter(llist, 10);
    LL_InsAfter(llist, 9);
    LL_InsAfter(llist, 8);
    LL_InsAfter(llist, 7);
    LL_Print(llist);
    LL_MakeEmpty(llist);
    LL_Print(llist);
    LL_InsAfter(llist, 7);
    LL_InsAfter(llist, 8);
    LL_InsAfter(llist, 9);
    LL_InsAfter(llist, 10);
    LL_Print(llist);
    LL_DelAfter(llist);
    LL_Print(llist);
    return 0;
}


LinkList_t* LL_Create() {
    // 创造链表
    LinkList_t* llist = (LinkList_t*)malloc(sizeof(LinkList_t));
    // 初始化失败
    if (llist == NULL) {
        return NULL;
    }

    // 对链表的内部元素进行初始化
    llist->front = NULL;
    llist->rear = NULL;
    llist->pre = NULL;
    llist->curr = NULL;
    llist->position = 0;
    llist->len = 0;
}

bool LL_InsAfter(LinkList_t* llist, T x) {
    // 给新的结点申请空间
    LinkNode_t* node = (LinkNode_t*)malloc(sizeof(LinkNode_t));
    if (node == NULL) {
        return false;
    }

    // 给结点赋值
    node->data = x;
    node->next = NULL;

    // 空表插入
    if (llist->len == 0) {
        llist->front = llist->rear = node;
        llist->pre = NULL;
        llist->curr = node;
        llist->position = 0;
        llist->len++;
        return true;
    }
    // 在尾结点处插入
    if ((llist->position == llist->len - 1) || (llist->position >= llist->len)) {
        llist->rear = node;
        llist->pre = llist->curr;
        llist->curr->next = node;
        llist->curr = node;
        llist->position++;
        llist->len++;
        return true;
    }

    // 在中间插入
    LinkNode_t* old_node = llist->curr->next;
    node->next = old_node;
    llist->curr->next = node;

    llist->pre = llist->curr;
    llist->curr = node;
    llist->len++;
    llist->position++;
    return true;
}

void LL_Print(LinkList_t* llist) {

    LinkNode_t* temp = llist->front;
    
    if (temp == NULL) {
        puts("llist is empty!");
    }

    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    puts("");
}

void LL_MakeEmpty(LinkList_t* llist) {
    LinkNode_t* temp = llist->front;
    while (temp) {
        LinkNode_t* del_node = temp;
        temp = temp->next;
        free(del_node);
    }

    llist->curr = llist->front = llist->pre = llist->rear = NULL;
    llist->len = 0;
    llist->position = 0;
}

bool LL_DelAfter(LinkList_t* llist) {
    
    // 空表删除
    if (LL_IsEmpty(llist)) {
        return true;
    }
    
    // 尾部删除
    if ((llist->position == llist->len - 1) || (llist->position >= llist->len)) {
        return true;
    }

    // 尾部前一个结点删除
    if (llist->position == llist->len - 2) {
        LinkNode_t* del_node = llist->curr->next;
        llist->curr->next = del_node->next;
        llist->rear = llist->curr;
        free(del_node);
        llist->len--;
        return true;
    }

    // 中间删除
    LinkNode_t* del_node = llist->curr->next;
    llist->curr->next = del_node->next;

    free(del_node);
    llist->len--;
    return true;
}

bool LL_IsEmpty(LinkList_t* llist) {
    return llist->len == 0;
}

bool LL_SetPosition(LinkList_t* llist, int key) {
    // 不合理
    if (key < 0 || key >= llist->len) {
        return false;
    }
    
    LinkNode_t* node = llist->front;
    for (int i = 0; i < key - 1; i ++) {
        node = node->next;
    }

    llist->pre = llist->curr;
    llist->curr = node->next;
    llist->position = key;
    return true;
}
