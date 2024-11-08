//
// Created by Reinhard Van Astrea  on 2024/11/8.
//
#include <stdio.h>
#include <stdlib.h>

/* 遍历数组并计算总和 */
int traverse(int *nums, int size) {
    int count = 0;
    // 通过索引遍历数组
    for (int i = 0; i < size; i++) {
        count += nums[i];
    }
    printf("Sum of array elements: %d\n", count);
    return count;
}

/* 在数组中查找指定元素 */
int find(int *nums, int size, int target) {
    // 检查数组是否为空
    if (nums == NULL) {
        printf("Error: Array is null.\n");
        return -1;
    }
    for (int i = 0; i < size; i++) {
        if (nums[i] == target)
            return i;
    }
    return -1; // 未找到
}

/* 扩展数组长度 */
int *extend(int *nums, int size, int enlarge) {
    if (nums == NULL || enlarge <= 0) {
        printf("Error: Invalid array or enlarge size.\n");
        return NULL;
    }

    // 初始化一个扩展长度后的数组
    int *res = (int *)malloc(sizeof(int) * (size + enlarge));
    if (res == NULL) {
        printf("Error: Memory allocation failed.\n");
        return NULL;
    }

    // 将原数组中的所有元素复制到新数组
    for (int i = 0; i < size; i++) {
        res[i] = nums[i];
    }

    // 初始化扩展后的空间
    for (int i = size; i < size + enlarge; i++) {
        res[i] = 0;
    }

    // 返回扩展后的新数组
    return res;
}

int main() {
    int size = 5;
    int *nums = (int *)malloc(sizeof(int) * size);
    if (nums == NULL) {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    // 初始化数组
    for (int i = 0; i < size; i++) {
        nums[i] = i * 10;
    }

    // 测试遍历数组
    traverse(nums, size);

    // 测试查找元素
    int target = 20;
    int index = find(nums, size, target);
    if (index != -1) {
        printf("Element %d found at index %d.\n", target, index);
    } else {
        printf("Element %d not found in the array.\n", target);
    }

    // 测试扩展数组
    int enlarge = 3;
    int *newNums = extend(nums, size, enlarge);
    if (newNums != NULL) {
        free(nums); // 释放旧数组
        nums = newNums;
        size += enlarge;

        printf("Array after extension: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", nums[i]);
        }
        printf("\n");
    }

    // 释放扩展后的数组
    free(nums);

    return 0;
}
