//
// Created by Reinhard Van Astrea  on 2024/11/10.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 100  // 定义栈的最大容量

/* 基于数组实现的栈 */
typedef struct {
    int *data;  // 用于存储栈的元素
    int size;   // 当前栈的大小
} ArrayStack;

/* 构造函数 */
ArrayStack *newArrayStack() {
    ArrayStack *stack = malloc(sizeof(ArrayStack));
    stack->data = malloc(sizeof(int) * MAX_SIZE);  // 初始化大容量数组
    stack->size = 0;  // 初始栈为空
    return stack;
}

/* 析构函数 */
void delArrayStack(ArrayStack *stack) {
    free(stack->data);  // 释放数据数组
    free(stack);        // 释放栈结构
}

/* 获取栈的长度 */
int size(ArrayStack *stack) {
    return stack->size;
}

/* 判断栈是否为空 */
bool isEmpty(ArrayStack *stack) {
    return stack->size == 0;
}

/* 入栈 */
void push(ArrayStack *stack, int num) {
    if (stack->size == MAX_SIZE) {  // 检查是否达到最大容量
        printf("栈已满，无法入栈\n");
        return;
    }
    stack->data[stack->size] = num;  // 将元素放入数组的当前空位
    stack->size++;  // 栈大小加 1
}

/* 访问栈顶元素 */
int peek(ArrayStack *stack) {
    if (isEmpty(stack)) {  // 检查栈是否为空
        printf("栈为空，无法访问栈顶元素\n");
        return INT_MAX;  // 栈空时返回特殊值
    }
    return stack->data[stack->size - 1];  // 返回栈顶元素
}

/* 出栈 */
int pop(ArrayStack *stack) {
    if (isEmpty(stack)) {  // 检查栈是否为空
        printf("栈为空，无法执行出栈操作\n");
        return INT_MAX;  // 栈空时返回特殊值
    }
    int val = stack->data[stack->size - 1];  // 保存栈顶元素
    stack->size--;  // 栈大小减 1
    return val;  // 返回出栈的元素
}

/* 测试函数 */
int main() {
    ArrayStack *stack = newArrayStack();

    // 测试入栈
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    printf("栈顶元素：%d\n", peek(stack)); // 应该输出 30
    printf("栈的大小：%d\n", size(stack)); // 应该输出 3

    // 测试出栈
    printf("出栈元素：%d\n", pop(stack)); // 应该输出 30
    printf("栈顶元素：%d\n", peek(stack)); // 应该输出 20
    printf("栈的大小：%d\n", size(stack)); // 应该输出 2

    // 测试栈是否为空
    printf("栈是否为空：%s\n", isEmpty(stack) ? "是" : "否");

    // 清空栈
    pop(stack);
    pop(stack);
    printf("栈是否为空：%s\n", isEmpty(stack) ? "是" : "否");

    // 尝试访问空栈的栈顶元素
    printf("访问空栈的栈顶元素：%d\n", peek(stack));

    // 销毁栈
    delArrayStack(stack);
    return 0;
}
