//
// Created by Reinhard Van Astrea  on 2024/11/8.
//
#include <stdio.h>
#include <stdlib.h>

/* 在数组的索引 index 处插入元素 num */
void insert(int *nums, int *size, int capacity, int num, int index) {
    // 检查索引是否有效
    if (index < 0 || index > *size) {
        printf("Error: Index out of bounds.\n");
        return;
    }

    // 检查数组是否已满
    if (*size >= capacity) {
        printf("Error: Array is full, cannot insert.\n");
        return;
    }

    // 把索引 index 以及之后的所有元素向后移动一位
    for (int i = *size; i > index; i--) {
        nums[i] = nums[i - 1];
    }

    // 将 num 赋给 index 处的元素
    nums[index] = num;
    (*size)++; // 更新数组大小
}

/* 删除索引 index 处的元素 */
void removeItem(int *nums, int *size, int index) {
    // 检查索引是否有效
    if (index < 0 || index >= *size) {
        printf("Error: Index out of bounds.\n");
        return;
    }

    // 把索引 index 之后的所有元素向前移动一位
    for (int i = index; i < *size - 1; i++) {
        nums[i] = nums[i + 1];
    }

    (*size)--; // 更新数组大小
}

int main() {
    int capacity = 10; // 数组的最大容量
    int nums[capacity]; // 数组定义
    int size = 5; // 当前有效元素的个数
    for (int i = 0; i < size; i++) {
        nums[i] = i * 10; // 初始化数组为 [0, 10, 20, 30, 40]
    }

    // 测试插入操作
    insert(nums, &size, capacity, 25, 2);
    printf("Array after insertion: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    // 测试删除操作
    removeItem(nums, &size, 3);
    printf("Array after deletion: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    return 0;
}
