//
// Created by Reinhard Van Astrea  on 2024/11/15.
//
#include <stdio.h>
#include <stdlib.h>

// 二叉树节点结构体
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 动态数组，用于存储遍历结果
int *arr;
int arr_size = 0;  // 数组的初始大小

// 创建一个新的树节点
TreeNode *newTreeNode(int val) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 扩展数组的大小
void resizeArray(int new_size) {
    arr = (int *)realloc(arr, sizeof(int) * new_size);
    arr_size = new_size;
}

// 前序遍历：根 -> 左 -> 右
void preOrder(TreeNode *root, int *size) {
    if (root == NULL)
        return;

    // 访问根节点
    // 使用对size指针的解引用，每次可以修改size的值而不是副本的值，达到了每次遍历完一个节点后索引自增的效果
    arr[(*size)++] = root->val;

    // 遍历左子树
    preOrder(root->left, size);

    // 遍历右子树
    preOrder(root->right, size);
}

// 中序遍历：左 -> 根 -> 右
void inOrder(TreeNode *root, int *size) {
    if (root == NULL)
        return;

    // 遍历左子树
    inOrder(root->left, size);

    // 访问根节点
    arr[(*size)++] = root->val;

    // 遍历右子树
    inOrder(root->right, size);
}

// 后序遍历：左 -> 右 -> 根
void postOrder(TreeNode *root, int *size) {
    if (root == NULL)
        return;

    // 遍历左子树
    postOrder(root->left, size);

    // 遍历右子树
    postOrder(root->right, size);

    // 访问根节点
    arr[(*size)++] = root->val;
}

// 打印数组的内容
void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 主函数
int main() {
    // 创建树节点
    TreeNode *n1 = newTreeNode(1);
    TreeNode *n2 = newTreeNode(2);
    TreeNode *n3 = newTreeNode(3);
    TreeNode *n4 = newTreeNode(4);
    TreeNode *n5 = newTreeNode(5);
    TreeNode *n6 = newTreeNode(6);

    // 构建树
    n1->left = n2;
    n1->right = n3;
    n2->left = n4;
    n2->right = n5;
    n3->right = n6;

    // 初始化数组
    arr = (int *)malloc(sizeof(int) * 100);  // 假设最多有 100 个节点
    arr_size = 100; // 初始容量

    // 前序遍历
    int size = 0;
    preOrder(n1, &size);
    printf("Preorder: ");
    printArray(arr, size);

    // 清空数组
    size = 0;

    // 中序遍历
    inOrder(n1, &size);
    printf("Inorder: ");
    printArray(arr, size);

    // 清空数组
    size = 0;

    // 后序遍历
    postOrder(n1, &size);
    printf("Postorder: ");
    printArray(arr, size);

    // 释放内存
    free(arr);
    free(n1);
    free(n2);
    free(n3);
    free(n4);
    free(n5);
    free(n6);

    return 0;
}
