//
// Created by Reinhard Van Astrea  on 2024/11/15.
//
#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点结构体
typedef struct TreeNode {
    int val;                // 节点值
    struct TreeNode *left;  // 左子节点指针
    struct TreeNode *right; // 右子节点指针
} TreeNode;

/* 层序遍历 */
int *levelOrder(TreeNode *root, int *size) {
    if (root == NULL) {
        *size = 0;
        return NULL;
    }

    /* 动态队列，初始大小可以较大，之后根据需求扩展 */
    int front = 0, rear = 0, index = 0;
    int *arr = (int *)malloc(sizeof(int) * 100); // 初始分配 100 个空间
    TreeNode **queue = (TreeNode **)malloc(sizeof(TreeNode *) * 100); // 初始队列容量为 100

    TreeNode *node;
    queue[rear++] = root;  // 加入根节点

    while (front < rear) {
        node = queue[front++];  // 队列出队
        arr[index++] = node->val;  // 保存节点值

        if (node->left != NULL) {
            queue[rear++] = node->left;  // 左子节点入队
        }
        if (node->right != NULL) {
            queue[rear++] = node->right;  // 右子节点入队
        }

        // 如果队列满了，扩展队列
        if (rear >= 100) {
            queue = (TreeNode **)realloc(queue, sizeof(TreeNode *) * (rear + 100));
        }

        // 如果数组满了，扩展数组
        if (index >= 100) {
            arr = (int *)realloc(arr, sizeof(int) * (index + 100));
        }
    }

    // 更新数组长度
    *size = index;

    // 释放队列空间
    free(queue);

    // 返回重新分配后的数组
    arr = (int *)realloc(arr, sizeof(int) * (*size));

    return arr;
}

/* 测试代码 */
int main() {
    // 示例二叉树：
    //        1
    //       / \
    //      2   3
    //     / \   \
    //    4   5   6
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->val = 1;
    root->left = (TreeNode *)malloc(sizeof(TreeNode));
    root->left->val = 2;
    root->right = (TreeNode *)malloc(sizeof(TreeNode));
    root->right->val = 3;
    root->left->left = (TreeNode *)malloc(sizeof(TreeNode));
    root->left->left->val = 4;
    root->left->right = (TreeNode *)malloc(sizeof(TreeNode));
    root->left->right->val = 5;
    root->right->right = (TreeNode *)malloc(sizeof(TreeNode));
    root->right->right->val = 6;

    int size;
    int *result = levelOrder(root, &size);

    // 输出层序遍历的结果
    for (int i = 0; i < size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    // 释放内存
    free(result);
    free(root->right->right);
    free(root->left->right);
    free(root->left->left);
    free(root->left);
    free(root);

    return 0;
}
