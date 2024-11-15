//
// Created by Reinhard Van Astrea  on 2024/11/15.
//
#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点结构
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 定义二叉搜索树结构
typedef struct {
    TreeNode *root;
} BinarySearchTree;

/* 创建一个新的树节点 */
TreeNode* newTreeNode(int num) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node != NULL) {
        node->val = num;
        node->left = node->right = NULL;
    }
    return node;
}

/* 查找节点 */
TreeNode* search(BinarySearchTree *bst, int num) {
    TreeNode *cur = bst->root;
    while (cur != NULL) {
        if (cur->val < num) {
            cur = cur->right;
        } else if (cur->val > num) {
            cur = cur->left;
        } else {
            break;
        }
    }
    return cur;
}

/* 插入节点 */
void insert(BinarySearchTree *bst, int num) {
    if (bst->root == NULL) {
        bst->root = newTreeNode(num);
        return;
    }

    TreeNode *cur = bst->root, *pre = NULL;
    while (cur != NULL) {
        if (cur->val == num) {
            return;  // 如果节点已存在，直接返回
        }
        pre = cur;
        if (cur->val < num) {
            cur = cur->right;
        } else {
            cur = cur->left;
        }
    }

    // 插入新节点
    TreeNode *node = newTreeNode(num);
    if (pre->val < num) {
        pre->right = node;
    } else {
        pre->left = node;
    }
}

/* 删除节点 */
void removeItem(BinarySearchTree *bst, int num) {
    if (bst->root == NULL) {
        return;
    }

    TreeNode *cur = bst->root, *pre = NULL;
    while (cur != NULL) {
        if (cur->val == num) {
            break;
        }
        pre = cur;
        if (cur->val < num) {
            cur = cur->right;
        } else {
            cur = cur->left;
        }
    }

    if (cur == NULL) {
        return;  // 未找到待删除的节点
    }

    // 处理节点的删除
    if (cur->left == NULL || cur->right == NULL) {
        // 子节点数量为0或1
        TreeNode *child = cur->left != NULL ? cur->left : cur->right;
        if (pre == NULL) {
            // 删除根节点
            bst->root = child;
        } else if (pre->left == cur) {
            pre->left = child;
        } else {
            pre->right = child;
        }
        free(cur);
    } else {
        // 子节点数量为2
        // 找到右子树中的最小节点
        TreeNode *tmp = cur->right;
        while (tmp->left != NULL) {
            tmp = tmp->left;
        }
        int tmpVal = tmp->val;
        removeItem(bst, tmp->val);  // 递归删除中序后继节点
        cur->val = tmpVal;  // 用中序后继节点的值替换当前节点的值
    }
}

/* 创建二叉搜索树 */
BinarySearchTree* newBinarySearchTree() {
    BinarySearchTree *bst = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    bst->root = NULL;
    return bst;
}

/* 销毁树节点 */
void destroyTreeNode(TreeNode *node) {
    if (node != NULL) {
        destroyTreeNode(node->left);
        destroyTreeNode(node->right);
        free(node);
    }
}

/* 销毁二叉搜索树 */
void destroyBinarySearchTree(BinarySearchTree *bst) {
    destroyTreeNode(bst->root);
    free(bst);
}

/* 中序遍历 */
void inorderTraversal(TreeNode *node) {
    if (node != NULL) {
        inorderTraversal(node->left);
        printf("%d ", node->val);
        inorderTraversal(node->right);
    }
}

/* 测试程序 */
int main() {
    BinarySearchTree *bst = newBinarySearchTree();

    insert(bst, 10);
    insert(bst, 5);
    insert(bst, 15);
    insert(bst, 3);
    insert(bst, 7);
    insert(bst, 12);
    insert(bst, 18);

    printf("Inorder Traversal: ");
    inorderTraversal(bst->root);
    printf("\n");

    // 查找节点
    TreeNode *node = search(bst, 7);
    if (node != NULL) {
        printf("Found node with value: %d\n", node->val);
    } else {
        printf("Node not found\n");
    }

    // 删除节点
    printf("Deleting node 7...\n");
    removeItem(bst, 7);
    printf("Inorder Traversal after deletion: ");
    inorderTraversal(bst->root);
    printf("\n");

    // 删除根节点
    printf("Deleting root node 10...\n");
    removeItem(bst, 10);
    printf("Inorder Traversal after deleting root: ");
    inorderTraversal(bst->root);
    printf("\n");

    // 销毁树
    destroyBinarySearchTree(bst);

    return 0;
}
