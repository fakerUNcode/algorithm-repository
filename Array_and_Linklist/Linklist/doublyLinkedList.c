//
// Created by Reinhard Van Astrea  on 2024/11/8.
//
#include <stdio.h>
#include <stdlib.h>

/* 双向链表节点结构体 */
typedef struct ListNode {
    int val;               // 节点值
    struct ListNode *next; // 指向后继节点的指针
    struct ListNode *prev; // 指向前驱节点的指针
} ListNode;

/* 创建新节点 */
ListNode *newListNode(int val) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (node == NULL) {
        printf("Error: Memory allocation failed.\n");
        return NULL;
    }
    node->val = val;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

/* 在双向链表的头部插入新节点 */
void insertAtHead(ListNode **head, int val) {
    ListNode *new_node = newListNode(val);
    if (new_node == NULL) {
        return;
    }

    new_node->next = *head; // 新节点的 next 指向当前头节点
    if (*head != NULL) {
        (*head)->prev = new_node; // 当前头节点的 prev 指向新节点
    }
    *head = new_node; // 更新头节点为新节点
}

/* 在双向链表的尾部插入新节点 */
void insertAtTail(ListNode **head, int val) {
    ListNode *new_node = newListNode(val);
    if (new_node == NULL) {
        return;
    }

    if (*head == NULL) { // 如果链表为空
        *head = new_node;
        return;
    }

    ListNode *temp = *head;
    while (temp->next != NULL) { // 找到尾节点
        temp = temp->next;
    }

    temp->next = new_node; // 尾节点的 next 指向新节点
    new_node->prev = temp; // 新节点的 prev 指向尾节点
}

/* 在指定节点后插入新节点 */
void insertAfter(ListNode *node, int val) {
    if (node == NULL) {
        printf("Error: Given node is NULL.\n");
        return;
    }

    ListNode *new_node = newListNode(val);
    if (new_node == NULL) {
        return;
    }

    new_node->next = node->next;
    new_node->prev = node;

    if (node->next != NULL) {
        node->next->prev = new_node;
    }
    node->next = new_node;
}

/* 删除双向链表中的指定节点 */
void deleteNode(ListNode **head, int val) {
    if (*head == NULL) {
        printf("Error: List is empty.\n");
        return;
    }

    ListNode *temp = *head;
    while (temp != NULL && temp->val != val) {
        temp = temp->next;
    }

    if (temp == NULL) { // 未找到目标值
        printf("Error: Value %d not found in the list.\n", val);
        return;
    }

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else { // 删除的是头节点
        *head = temp->next;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    free(temp);
}

/* 正向打印双向链表 */
void printListForward(ListNode *head) {
    ListNode *temp = head;
    printf("Forward: ");
    while (temp != NULL) {
        printf("%d -> ", temp->val);
        temp = temp->next;
    }
    printf("NULL\n");
}

/* 反向打印双向链表 */
void printListBackward(ListNode *head) {
    if (head == NULL) {
        printf("Backward: NULL\n");
        return;
    }

    ListNode *temp = head;
    while (temp->next != NULL) { // 找到尾节点
        temp = temp->next;
    }

    printf("Backward: ");
    while (temp != NULL) {
        printf("%d -> ", temp->val);
        temp = temp->prev;
    }
    printf("NULL\n");
}

/* 释放双向链表的内存 */
void freeList(ListNode *head) {
    ListNode *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    // 初始化双向链表
    ListNode *head = NULL;

    // 插入节点
    insertAtHead(&head, 10);
    insertAtHead(&head, 20);
    insertAtTail(&head, 30);
    insertAtTail(&head, 40);

    // 打印链表（正向和反向）
    printListForward(head);
    printListBackward(head);

    // 在节点值为 20 后插入 25
    ListNode *temp = head->next; // 假设我们知道要插入的位置
    insertAfter(temp, 25);
    printListForward(head);

    // 删除节点
    deleteNode(&head, 25);
    printListForward(head);

    // 释放链表
    freeList(head);

    return 0;
}
