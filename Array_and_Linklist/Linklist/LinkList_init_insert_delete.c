//
// Created by Reinhard Van Astrea  on 2024/11/8.
//
#include <stdio.h>
#include <stdlib.h>

/* 链表节点结构体 */
typedef struct ListNode {
    int val;               // 节点值
    struct ListNode *next; // 指向下一节点的指针
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
    return node;
}

/* 初始化链表（创建一个带头节点的空链表） */
ListNode *initList() {
    return NULL; // 空链表没有节点
}

/* 在链表头部插入新节点 */
void insertAtHead(ListNode **head, int val) {
    ListNode *new_node = newListNode(val);
    if (new_node == NULL) {
        return;
    }
    new_node->next = *head;
    *head = new_node;
}

/* 在链表尾部插入新节点 */
void insertAtTail(ListNode **head, int val) {
    ListNode *new_node = newListNode(val);
    if (new_node == NULL) {
        return;
    }
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    ListNode *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

/* 在链表中指定元素后插入新节点 */
void insertAfterValue(ListNode **head, int target, int val) {
    // 检查链表是否为空
    if (*head == NULL) {
        printf("Error: List is empty.\n");
        return;
    }

    // 找到目标节点
    ListNode *current = *head;
    while (current != NULL && current->val != target) {
        current = current->next;
    }

    // 如果未找到目标元素
    if (current == NULL) {
        printf("Error: Target value %d not found in the list.\n", target);
        return;
    }

    // 创建新节点并插入
    ListNode *new_node = newListNode(val);
    if (new_node == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    // 将新节点插入到目标节点之后
    new_node->next = current->next;
    current->next = new_node;
}


/* 删除指定值的节点 */
void deleteNode(ListNode **head, int val) {
    if (*head == NULL) {
        printf("Error: List is empty.\n");
        return;
    }

    ListNode *temp = *head;
    ListNode *prev = NULL;

    // 如果待删除节点是头节点
    if (temp != NULL && temp->val == val) {
        *head = temp->next;
        free(temp);
        return;
    }

    // 查找要删除的节点
    while (temp != NULL && temp->val != val) {
        prev = temp;
        temp = temp->next;
    }

    // 如果未找到该值
    if (temp == NULL) {
        printf("Value %d not found in the list.\n", val);
        return;
    }

    // 从链表中删除节点
    prev->next = temp->next;
    free(temp);
}

/* 打印链表 */
void printList(ListNode *head) {
    ListNode *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->val);
        temp = temp->next;
    }
    printf("NULL\n");
}

/* 释放链表的内存 */
void freeList(ListNode *head) {
    ListNode *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    // 初始化链表
    ListNode *head = initList();

    // 插入节点
    insertAtHead(&head, 10);
    insertAtHead(&head, 20);
    insertAtTail(&head, 30);
    insertAtTail(&head, 40);

    // 打印链表
    printf("List after insertion: ");
    printList(head);

    // 删除节点
    deleteNode(&head, 20);
    printf("List after deleting 20: ");
    printList(head);

    deleteNode(&head, 50); // 测试删除不存在的节点

    // 在节点值为 10 之后插入新节点 15
    insertAfterValue(&head, 10, 15);
    printf("List after inserting 15 after 10: ");
    printList(head);

    // 在节点值为 50（不存在）之后插入新节点 55
    insertAfterValue(&head, 50, 55);

    // 释放链表
    freeList(head);

    return 0;
}
