//
// Created by Reinhard Van Astrea  on 2024/11/4.
//
/* 递归 */
#include "stdio.h"
int recur(int n) {
    // 终止条件
    if (n == 1)
        return 1;
    // 递：递归调用
    int res = recur(n - 1);
    // 归：返回结果
    return n + res;
}

int main(){
    printf("%d",recur(10));
}