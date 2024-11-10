//
// Created by Reinhard Van Astrea  on 2024/11/10.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

/* 链表节点结构 */
typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

/* 队列结构 */
typedef struct {
    ListNode *front, *rear;  // 队首和队尾指针
    int queSize;             // 队列大小
} LinkedListQueue;

/* 创建新节点 */
ListNode *newListNode(int val) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

/* 构造函数 */
LinkedListQueue *newLinkedListQueue() {
    LinkedListQueue *queue = (LinkedListQueue *)malloc(sizeof(LinkedListQueue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->queSize = 0;
    return queue;
}

/* 析构函数 */
void delLinkedListQueue(LinkedListQueue *queue) {
    // 释放所有节点
    while (queue->front != NULL) {
        ListNode *tmp = queue->front; //用指针存储当前首节点的地址以便后续释放节点内存
        queue->front = queue->front->next;
        free(tmp);
    }
    // 释放队列结构体
    free(queue);
}

/* 获取队列的长度 */
int size(LinkedListQueue *queue) {
    return queue->queSize;
}

/* 判断队列是否为空 */
bool empty(LinkedListQueue *queue) {
    return (size(queue) == 0);
}

/* 入队 */
void push(LinkedListQueue *queue, int num) {
    // 在队尾添加一个新节点
    ListNode *node = newListNode(num);
    // 如果队列为空，设置队首和队尾都指向新节点
    if (queue->front == NULL) {
        queue->front = node;
        queue->rear = node;
    }
        // 如果队列不为空，将新节点添加到队尾
    else {
        queue->rear->next = node;
        queue->rear = node;
    }
    queue->queSize++;
}

/* 访问队首元素 */
int peek(LinkedListQueue *queue) {
    assert(queue->queSize > 0 && queue->front != NULL); // 确保队列非空
    return queue->front->val;
}

/* 出队 */
int pop(LinkedListQueue *queue) {
    int num = peek(queue);  // 获取队首元素
    ListNode *tmp = queue->front;  // 临时存储队首节点
    queue->front = queue->front->next;  // 将队首指针移动到下一个节点
    free(tmp);  // 释放原队首节点
    queue->queSize--;  // 队列大小减 1
    if (queue->queSize == 0) {
        queue->rear = NULL;  // 如果队列为空，重置 rear 指针
    }
    return num;
}

/* 打印队列 */
void printLinkedListQueue(LinkedListQueue *queue) {
    ListNode *node = queue->front;
    printf("Queue: ");
    while (node != NULL) {
        printf("%d ", node->val);
        node = node->next;
    }
    printf("\n");
}

/* 测试函数 */
int main() {
    LinkedListQueue *queue = newLinkedListQueue();

    // 测试入队
    push(queue, 10);
    push(queue, 20);
    push(queue, 30);
    printLinkedListQueue(queue); // 应该输出 Queue: 10 20 30

    // 测试访问队首元素
    printf("队首元素: %d\n", peek(queue)); // 应该输出 10

    // 测试出队
    printf("出队元素: %d\n", pop(queue)); // 应该输出 10
    printLinkedListQueue(queue);           // 应该输出 Queue: 20 30

    // 测试队列是否为空
    printf("队列是否为空: %s\n", empty(queue) ? "是" : "否"); // 应该输出 否

    // 清空队列
    pop(queue);
    pop(queue);
    printf("队列是否为空: %s\n", empty(queue) ? "是" : "否"); // 应该输出 是

    // 释放队列
    delLinkedListQueue(queue);
    return 0;
}
