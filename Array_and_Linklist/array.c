//
// Created by Reinhard Van Astrea  on 2024/11/8.
//
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/* 随机访问元素 */
int randomAccess(int *nums, int size) {
    // 检查数组是否为空或大小是否为0
    if (nums == NULL || size <= 0) {
        printf("Error: Invalid array or size.\n");
        return -1; // 返回错误码
    }

    // 设置随机数种子
    srand(time(NULL));

    // 在区间 [0, size) 中随机抽取一个数字
    int randomIndex = rand() % size;

    // 获取并返回随机元素
    int randomNum = nums[randomIndex];
    return randomNum;
}

int main() {
    int nums[] = {10, 20, 30, 40, 50};
    int size = sizeof(nums) / sizeof(nums[0]);

    // 随机访问并打印一个元素
    int randomNum = randomAccess(nums, size);
    if (randomNum != -1) { // 检查返回值是否有效
        printf("Random element: %d\n", randomNum);
    }

    return 0;
}

