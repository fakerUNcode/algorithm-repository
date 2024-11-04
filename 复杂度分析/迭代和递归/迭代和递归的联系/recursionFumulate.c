//
// Created by Reinhard Van Astrea  on 2024/11/4.
//
#include <stdio.h>
#include <stdlib.h>

/* 使用迭代模拟递归 */
int forLoopRecur(int n) {
    int stack[1000]; // 借助一个大数组来模拟栈
    int top = -1;    // 栈顶索引
    int res = 0;

    // 递：入栈操作
    for (int i = n; i > 0; i--) {
        stack[++top] = i;  // 入栈
    }

    // 归：出栈操作并计算结果
    while (top >= 0) {
        res += stack[top--]; // 出栈并累加
    }

    // res = 1 + 2 + 3 + ... + n
    return res;
}

int main() {
    int n;

    // 获取用户输入
    printf("请输入一个正整数 n 来计算从 1 到 n 的累加和: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("无效的输入，请输入一个正整数。\n");
        return 1;  // 退出程序，返回错误代码
    }

    // 计算累加和
    int result = forLoopRecur(n);

    // 输出结果
    printf("从 1 到 %d 的累加和是: %d\n", n, result);

    return 0;  // 程序成功结束
}
