//
// Created by Reinhard Van Astrea  on 2024/11/4.
//
#include <stdio.h>

/* 斐波那契数列：递归 */
int fib(int n) {
    // 终止条件 f(1) = 0, f(2) = 1
    if (n == 1 || n == 2) {
        return n - 1;
    }
    // 递归调用 f(n) = f(n-1) + f(n-2)
    return fib(n - 1) + fib(n - 2);
}

int main() {
    int n;

    // 获取用户输入
    printf("请输入一个正整数 n 来计算斐波那契数列的第 n 项: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("无效的输入，请输入一个正整数。\n");
        return 1;  // 退出程序，返回错误代码
    }

    // 计算斐波那契数列的第 n 项
    int result = fib(n);

    // 输出结果
    printf("斐波那契数列的第 %d 项是: %d\n", n, result);

    return 0;  // 程序成功结束
}
