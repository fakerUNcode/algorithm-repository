//
// Created by Reinhard Van Astrea  on 2024/11/15.
//
#include "stdlib.h"
#include "stdio.h"

/* 二叉树节点结构体 */
typedef struct TreeNode {
    int val;                // 节点值
    int height;             // 节点高度
    struct TreeNode *left;  // 左子节点指针
    struct TreeNode *right; // 右子节点指针
} TreeNode;

/* 构造函数 */
TreeNode *newTreeNode(int val) {
    TreeNode *node;
    node = (TreeNode *)malloc(sizeof(TreeNode));
    node->val = val;
    node->height = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* 先序遍历打印二叉树 */
void preorderTraversal(TreeNode *root) {
    if (root != NULL) {
        // 打印当前节点的值
        printf("%d ", root->val);
        // 递归遍历左子树
        preorderTraversal(root->left);
        // 递归遍历右子树
        preorderTraversal(root->right);
    }
}

/* 主函数 */
int main() {
    /* 初始化二叉树 */
    // 初始化节点
    TreeNode *n1 = newTreeNode(1);
    TreeNode *n2 = newTreeNode(2);
    TreeNode *n3 = newTreeNode(3);
    TreeNode *n4 = newTreeNode(4);
    TreeNode *n5 = newTreeNode(5);

    // 构建节点之间的引用（指针）
    n1->left = n2;
    n1->right = n3;
    n2->left = n4;
    n2->right = n5;

    /* 插入与删除节点 */
    TreeNode *P = newTreeNode(0);
    // 在 n1 -> n2 中间插入节点 P
    n1->left = P;
    P->left = n2;
    // 删除节点 P
    n1->left = n2;

    /* 打印二叉树内容 */
    printf("二叉树先序遍历结果: ");
    preorderTraversal(n1);
    printf("\n");

    return 0;
}
