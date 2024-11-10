//
// Created by Reinhard Van Astrea  on 2024/11/10.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

/* 环形数组实现的队列结构 */
typedef struct {
    int *nums;       // 用于存储队列元素的数组
    int front;       // 队首指针，指向队首元素
    int queSize;     // 队列的当前大小
    int queCapacity; // 队列容量
} ArrayQueue;

/* 构造函数 */
ArrayQueue *newArrayQueue(int capacity) {
    ArrayQueue *queue = (ArrayQueue *)malloc(sizeof(ArrayQueue));
    // 初始化数组
    queue->queCapacity = capacity;
    queue->nums = (int *)malloc(sizeof(int) * queue->queCapacity);
    queue->front = 0;
    queue->queSize = 0;
    return queue;
}

/* 析构函数 */
void delArrayQueue(ArrayQueue *queue) {
    free(queue->nums);
    free(queue);
}

/* 获取队列的容量 */
int capacity(ArrayQueue *queue) {
    return queue->queCapacity;
}

/* 获取队列的长度 */
int size(ArrayQueue *queue) {
    return queue->queSize;
}

/* 判断队列是否为空 */
bool empty(ArrayQueue *queue) {
    return queue->queSize == 0;
}

/* 判断队列是否已满 */
bool full(ArrayQueue *queue) {
    return queue->queSize == queue->queCapacity;
}

/* 访问队首元素 */
int peek(ArrayQueue *queue) {
    assert(!empty(queue));  // 检查队列非空
    return queue->nums[queue->front];
}

/* 入队 */
void push(ArrayQueue *queue, int num) {
    if (full(queue)) {
        printf("队列已满，无法入队\n");
        return;
    }
    // 计算队尾指针的位置（队尾索引 + 1），取余以实现循环
    int rear = (queue->front + queue->queSize) % queue->queCapacity;
    // 将 num 添加至队尾
    queue->nums[rear] = num;
    queue->queSize++;
    printf("入队元素: %d\n", num);
}

/* 出队 */
int pop(ArrayQueue *queue) {
    if (empty(queue)) {
        printf("队列为空，无法出队\n");
        return INT_MAX; // 返回一个特殊值表示队列为空
    }
    int num = peek(queue);  // 获取队首元素
    // 队首指针向后移动一位，若越过尾部，则回到数组头部
    queue->front = (queue->front + 1) % queue->queCapacity;
    queue->queSize--;
    printf("出队元素: %d\n", num);
    return num;
}

/* 打印队列内容 */
void printArrayQueue(ArrayQueue *queue) {
    printf("Queue: ");
    for (int i = 0; i < queue->queSize; i++) {
        int index = (queue->front + i) % queue->queCapacity;
        printf("%d ", queue->nums[index]);
    }
    printf("\n");
}

/* 测试函数 */
int main() {
    int capacity = 5;
    ArrayQueue *queue = newArrayQueue(capacity);

    // 测试入队
    push(queue, 10);
    push(queue, 20);
    push(queue, 30);
    push(queue, 40);
    push(queue, 50);
    printArrayQueue(queue); // 应该输出 Queue: 10 20 30 40 50

    // 尝试入队已满的队列
    push(queue, 60); // 队列已满

    // 测试出队
    pop(queue);
    pop(queue);
    printArrayQueue(queue); // 应该输出 Queue: 30 40 50

    // 测试队列循环
    push(queue, 60);
    push(queue, 70);
    printArrayQueue(queue); // 应该输出 Queue: 30 40 50 60 70

    // 检查队列是否已满
    push(queue, 80); // 队列已满，无法入队

    // 测试访问队首元素
    printf("队首元素: %d\n", peek(queue)); // 应该输出 30

    // 清空队列
    pop(queue);
    pop(queue);
    pop(queue);
    pop(queue);
    pop(queue);
    printf("队列是否为空: %s\n", empty(queue) ? "是" : "否"); // 应该输出 是

    // 释放队列
    delArrayQueue(queue);
    return 0;
}
