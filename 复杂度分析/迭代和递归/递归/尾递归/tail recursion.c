//
// Created by Reinhard Van Astrea  on 2024/11/4.
//
/* 尾递归 */
#include "stdio.h"
int tailRecur(int n, int res) {
    // 终止条件
    if (n == 0)
        return res;
    // 尾递归调用
    return tailRecur(n - 1, res + n);
}
int main(){
    printf("%d", tailRecur(10,0));
}