//
// Created by Reinhard Van Astrea  on 2024/11/8.
//
#include <stdio.h>
#include <stdlib.h>

/* 环形链表节点结构体 */
typedef struct ListNode {
    int val;               // 节点值
    struct ListNode *next; // 指向后继节点的指针
} ListNode;

/* 创建新节点 */
ListNode *newListNode(int val) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (node == NULL) {
        printf("Error: Memory allocation failed.\n");
        return NULL;
    }
    node->val = val;
    node->next = node; // 初始情况下，新节点的 next 指向自己
    return node;
}

/* 在环形链表的头部插入新节点 */
void insertAtHead(ListNode **head, int val) {
    ListNode *new_node = newListNode(val);
    if (new_node == NULL) {
        return;
    }

    if (*head == NULL) { // 如果链表为空
        *head = new_node;
        return;
    }

    ListNode *temp = *head;
    while (temp->next != *head) { // 找到尾节点
        temp = temp->next;
    }

    new_node->next = *head; // 新节点指向当前头节点
    temp->next = new_node;   // 尾节点指向新节点
    *head = new_node;        // 更新头节点为新节点
}

/* 在环形链表的尾部插入新节点 */
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
    while (temp->next != *head) { // 找到尾节点
        temp = temp->next;
    }

    temp->next = new_node;  // 尾节点指向新节点
    new_node->next = *head; // 新节点指向头节点
}

/* 删除环形链表中的指定节点 */
void deleteNode(ListNode **head, int val) {
    if (*head == NULL) {
        printf("Error: List is empty.\n");
        return;
    }

    ListNode *temp = *head;
    ListNode *prev = NULL;

    // 查找要删除的节点
    do {
        if (temp->val == val) break;
        prev = temp;
        temp = temp->next;
    } while (temp != *head);

    // 如果未找到节点
    if (temp->val != val) {
        printf("Error: Value %d not found in the list.\n", val);
        return;
    }

    if (temp == *head && temp->next == *head) { // 链表中仅有一个节点
        *head = NULL;
    } else {
        if (temp == *head) {
            *head = (*head)->next; // 更新头节点
        }
        if (prev != NULL) {
            prev->next = temp->next; // 跳过删除的节点
        }

        ListNode *tail = *head;
        while (tail->next != temp) { // 找到尾节点
            tail = tail->next;
        }
        tail->next = *head; // 使尾节点的 next 指向新的头节点
    }

    free(temp);
}

/* 遍历并打印环形链表 */
void printList(ListNode *head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    ListNode *temp = head;
    do {
        printf("%d -> ", temp->val);
        temp = temp->next;
    } while (temp != head);
    printf("(head)\n");
}

/* 释放环形链表的内存 */
void freeList(ListNode *head) {
    if (head == NULL) return;

    ListNode *temp = head;
    ListNode *next_node;
    do {
        next_node = temp->next;
        free(temp);
        temp = next_node;
    } while (temp != head);
}

int main() {
    // 初始化环形链表
    ListNode *head = NULL;

    // 插入节点
    insertAtHead(&head, 10);
    insertAtHead(&head, 20);
    insertAtTail(&head, 30);
    insertAtTail(&head, 40);

    // 打印链表
    printf("Circular list: ");
    printList(head);

    // 删除节点
    deleteNode(&head, 20);
    printf("After deleting 20: ");
    printList(head);

    deleteNode(&head, 10);
    printf("After deleting 10: ");
    printList(head);

    // 释放链表
    freeList(head);

    return 0;
}
