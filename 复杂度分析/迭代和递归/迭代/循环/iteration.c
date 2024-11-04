#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* 双层 for 循环 */
char *nestedForLoop(int n) {
    // n * n 为对应点数量，"(i, j), " 对应字符串长最大为 6+10*2，加上最后一个空字符 \0 的额外空间
    int size = n * n * 26 + 1;
    char *res = malloc(size * sizeof(char));
    memset(res, 0, size);  // 初始化 res，确保以空字符开始
    // 循环 i = 1, 2, ..., n-1, n
    for (int i = 1; i <= n; i++) {
        // 循环 j = 1, 2, ..., n-1, n
        for (int j = 1; j <= n; j++) {
            char tmp[26];
            snprintf(tmp, sizeof(tmp), "(%d, %d), ", i, j);
            strncat(res, tmp, size - strlen(res) - 1);
        }
    }
    return res;
}

int main() {
    int n = 5;  // 你可以更改这个值来测试不同的 n
    char *result = nestedForLoop(n);
    printf("%s\n", result);
    free(result);  // 释放分配的内存
    return 0;
}
