//
// Created by Reinhard Van Astrea  on 2024/11/10.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/* 链表节点 */
typedef struct ListNode {
    int val;             // 数据域
    struct ListNode *next; // 指针域，指向下一个节点
} ListNode;

/* 基于链表实现的栈 */
typedef struct {
    ListNode *top; // 将头节点作为栈顶
    int size;      // 栈的长度
} LinkedListStack;

/* 构造函数 */
LinkedListStack *newLinkedListStack() {
    LinkedListStack *s = malloc(sizeof(LinkedListStack));
    s->top = NULL;
    s->size = 0;
    return s;
}

/* 析构函数 */
void delLinkedListStack(LinkedListStack *s) {
    while (s->top) {
        ListNode *next = s->top->next;
        free(s->top);
        s->top = next;
    }
    free(s);
}

/* 获取栈的长度 */
int size(LinkedListStack *s) {
    return s->size;
}

/* 判断栈是否为空 */
bool isEmpty(LinkedListStack *s) {
    return size(s) == 0;
}

/* 入栈 */
void push(LinkedListStack *s, int num) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    node->next = s->top; // 更新新加节点指针域
    node->val = num;     // 更新新加节点数据域
    s->top = node;       // 更新栈顶
    s->size++;           // 更新栈大小
}

/* 访问栈顶元素 */
int peek(LinkedListStack *s) {
    if (s->size == 0) {
        printf("栈为空\n");
        return INT_MAX;  // 栈空时返回一个特殊值
    }
    return s->top->val;
}

/* 出栈 */
int pop(LinkedListStack *s) {
    if (isEmpty(s)) {
        printf("栈为空，无法执行出栈操作\n");
        return INT_MAX;  // 栈空时返回一个特殊值
    }
    int val = s->top->val;
    ListNode *tmp = s->top; //这里 tmp 的存在非常重要，因为 s->top 已经被更新，我们需要 tmp 来记录原栈顶节点的位置，以便释放内存。
    s->top = s->top->next;
    // 释放内存
    free(tmp); //使用 free(tmp) 释放 tmp 所指向的内存，也就是原来的栈顶节点。
    s->size--;
    return val;
}

/* 测试函数 */
int main() {
    LinkedListStack *stack = newLinkedListStack();

    // 测试入栈操作
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    printf("栈顶元素：%d\n", peek(stack)); // 应该输出 30
    printf("栈的大小：%d\n", size(stack)); // 应该输出 3

    // 测试出栈操作
    printf("出栈元素：%d\n", pop(stack)); // 应该输出 30
    printf("栈顶元素：%d\n", peek(stack)); // 应该输出 20
    printf("栈的大小：%d\n", size(stack)); // 应该输出 2

    // 测试栈是否为空
    printf("栈是否为空：%s\n", isEmpty(stack) ? "是" : "否");

    // 清空栈
    pop(stack);
    pop(stack);
    printf("栈是否为空：%s\n", isEmpty(stack) ? "是" : "否");

    // 销毁栈
    delLinkedListStack(stack);
    return 0;
}
