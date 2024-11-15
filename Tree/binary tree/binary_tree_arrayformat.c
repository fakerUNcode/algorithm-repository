//
// Created by Reinhard Van Astrea  on 2024/11/15.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* 数组表示下的二叉树结构体 */
typedef struct {
    int *tree;
    int size;
} ArrayBinaryTree;

/* 获取左子节点的索引 */
int left(int i) {
    return 2 * i + 1;
}

/* 获取右子节点的索引 */
int right(int i) {
    return 2 * i + 2;
}

/* 获取父节点的索引 */
int parent(int i) {
    return (i - 1) / 2;
}

/* 构造函数 */
ArrayBinaryTree *newArrayBinaryTree(int *arr, int arrSize) {
    ArrayBinaryTree *abt = (ArrayBinaryTree *)malloc(sizeof(ArrayBinaryTree));
    abt->tree = malloc(sizeof(int) * arrSize);
    memcpy(abt->tree, arr, sizeof(int) * arrSize);
    abt->size = arrSize;
    return abt;
}

/* 析构函数 */
void delArrayBinaryTree(ArrayBinaryTree *abt) {
    free(abt->tree);
    free(abt);
}

/* 列表容量 */
int size(ArrayBinaryTree *abt) {
    return abt->size;
}

/* 获取索引为 i 节点的值 */
int val(ArrayBinaryTree *abt, int i) {
    // 若索引越界，则返回 INT_MAX ，代表空位
    if (i < 0 || i >= size(abt))
        return INT_MAX;
    return abt->tree[i];
}

/* 层序遍历 */
int *levelOrder(ArrayBinaryTree *abt, int *returnSize) {
    int *res = (int *)malloc(sizeof(int) * size(abt));
    int index = 0;
    // 直接遍历数组
    for (int i = 0; i < size(abt); i++) {
        if (val(abt, i) != INT_MAX) {
            res[index++] = val(abt, i);
        }
    }
    *returnSize = index;
    return res;
}

/* 深度优先遍历 */
void dfs(ArrayBinaryTree *abt, int i, char *order, int *res, int *index) {
    // 若为空位，则返回
    if (val(abt, i) == INT_MAX)
        return;
    // 前序遍历
    if (strcmp(order, "pre") == 0)
        res[(*index)++] = val(abt, i);
    dfs(abt, left(i), order, res, index);
    // 中序遍历
    if (strcmp(order, "in") == 0)
        res[(*index)++] = val(abt, i);
    dfs(abt, right(i), order, res, index);
    // 后序遍历
    if (strcmp(order, "post") == 0)
        res[(*index)++] = val(abt, i);
}

/* 前序遍历 */
int *preOrder(ArrayBinaryTree *abt, int *returnSize) {
    int *res = (int *)malloc(sizeof(int) * size(abt));
    int index = 0;
    dfs(abt, 0, "pre", res, &index);
    *returnSize = index;
    return res;
}

/* 中序遍历 */
int *inOrder(ArrayBinaryTree *abt, int *returnSize) {
    int *res = (int *)malloc(sizeof(int) * size(abt));
    int index = 0;
    dfs(abt, 0, "in", res, &index);
    *returnSize = index;
    return res;
}

/* 后序遍历 */
int *postOrder(ArrayBinaryTree *abt, int *returnSize) {
    int *res = (int *)malloc(sizeof(int) * size(abt));
    int index = 0;
    dfs(abt, 0, "post", res, &index);
    *returnSize = index;
    return res;
}

/* 打印二叉树的遍历结果 */
void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    // 测试
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    ArrayBinaryTree *abt = newArrayBinaryTree(arr, arrSize);

    int returnSize;
    int *result;

    // 层序遍历
    result = levelOrder(abt, &returnSize);
    printf("Level Order: ");
    printArray(result, returnSize);
    free(result);

    // 前序遍历
    result = preOrder(abt, &returnSize);
    printf("Pre Order: ");
    printArray(result, returnSize);
    free(result);

    // 中序遍历
    result = inOrder(abt, &returnSize);
    printf("In Order: ");
    printArray(result, returnSize);
    free(result);

    // 后序遍历
    result = postOrder(abt, &returnSize);
    printf("Post Order: ");
    printArray(result, returnSize);
    free(result);

    delArrayBinaryTree(abt);

    return 0;
}
