//
// Created by Reinhard Van Astrea  on 2024/11/14.
//
#include <stdio.h>
#include <string.h>

// 加法哈希
int addHash(char *key) {
    long long hash = 0;
    const int MODULUS = 1000000007;
    for (int i = 0; i < strlen(key); i++) {
        hash = (hash + (unsigned char)key[i]) % MODULUS;
    }
    return (int)hash;
}

// 乘法哈希
int mulHash(char *key) {
    long long hash = 0;
    const int MODULUS = 1000000007;
    for (int i = 0; i < strlen(key); i++) {
        hash = (31 * hash + (unsigned char)key[i]) % MODULUS;
    }
    return (int)hash;
}

// 异或哈希
int xorHash(char *key) {
    int hash = 0;
    const int MODULUS = 1000000007;

    for (int i = 0; i < strlen(key); i++) {
        hash ^= (unsigned char)key[i];
    }
    return hash & MODULUS;
}

// 旋转哈希
int rotHash(char *key) {
    long long hash = 0;
    const int MODULUS = 1000000007;
    for (int i = 0; i < strlen(key); i++) {
        hash = ((hash << 4) ^ (hash >> 28) ^ (unsigned char)key[i]) % MODULUS;
    }

    return (int)hash;
}

int main() {
    char key[100];

    // 提示用户输入一个字符串
    printf("请输入一个字符串：");
    fgets(key, sizeof(key), stdin);

    // 去除换行符
    key[strcspn(key, "\n")] = '\0';

    // 计算并打印哈希值
    printf("加法哈希值: %d\n", addHash(key));
    printf("乘法哈希值: %d\n", mulHash(key));
    printf("异或哈希值: %d\n", xorHash(key));
    printf("旋转哈希值: %d\n", rotHash(key));

    return 0;
}
