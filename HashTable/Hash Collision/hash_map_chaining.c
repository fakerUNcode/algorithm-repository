//
// Created by Reinhard Van Astrea  on 2024/11/13.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 键值对 */
typedef struct {
    int key;
    char *val;
} Pair;

/* 链表节点 */
typedef struct Node {
    Pair *pair;
    struct Node *next;
} Node;

/* 链式地址哈希表 */
typedef struct {
    int size;         // 键值对数量
    int capacity;     // 哈希表容量
    double loadThres; // 触发扩容的负载因子阈值
    int extendRatio;  // 扩容倍数
    Node **buckets;   // 桶数组
} HashMapChaining;

/* Forward declaration of the extend function */
void extend(HashMapChaining *hashMap);

/* 哈希函数 */
int hashFunc(HashMapChaining *hashMap, int key) {
    return key % hashMap->capacity;
}

/* 构造函数 */
HashMapChaining *newHashMapChaining() {
    HashMapChaining *hashMap = (HashMapChaining *)malloc(sizeof(HashMapChaining));
    if (!hashMap) return NULL;

    hashMap->size = 0;
    hashMap->capacity = 4;
    hashMap->loadThres = 2.0 / 3.0;
    hashMap->extendRatio = 2;
    hashMap->buckets = (Node **)malloc(hashMap->capacity * sizeof(Node *));

    if (!hashMap->buckets) {
        free(hashMap);
        return NULL;
    }

    for (int i = 0; i < hashMap->capacity; i++) {
        hashMap->buckets[i] = NULL;
    }
    return hashMap;
}

/* 负载因子 */
double loadFactor(HashMapChaining *hashMap) {
    return (double)hashMap->size / (double)hashMap->capacity;
}

/* 查询操作 */
char *get(HashMapChaining *hashMap, int key) {
    int index = hashFunc(hashMap, key);
    Node *cur = hashMap->buckets[index];
    while (cur) {
        if (cur->pair->key == key) {
            return cur->pair->val;
        }
        cur = cur->next;
    }
    return NULL; // 若未找到 key，返回 NULL
}

/* 添加操作 */
void put(HashMapChaining *hashMap, int key, const char *val) {
    if (loadFactor(hashMap) > hashMap->loadThres) {
        extend(hashMap);
    }

    int index = hashFunc(hashMap, key);
    Node *cur = hashMap->buckets[index];

    while (cur) {
        if (cur->pair->key == key) {
            free(cur->pair->val);
            cur->pair->val = malloc(strlen(val) + 1);
            if (cur->pair->val) {
                strcpy(cur->pair->val, val);
            }
            return;
        }
        cur = cur->next;
    }

    Pair *newPair = (Pair *)malloc(sizeof(Pair));
    if (!newPair) return;
    newPair->key = key;
    newPair->val = malloc(strlen(val) + 1);
    if (!newPair->val) {
        free(newPair);
        return;
    }
    strcpy(newPair->val, val);

    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        free(newPair->val);
        free(newPair);
        return;
    }
    newNode->pair = newPair;
    newNode->next = hashMap->buckets[index];
    hashMap->buckets[index] = newNode;
    hashMap->size++;
}

/* 扩容哈希表 */
void extend(HashMapChaining *hashMap) {
    int oldCapacity = hashMap->capacity;
    Node **oldBuckets = hashMap->buckets;

    hashMap->capacity *= hashMap->extendRatio;
    hashMap->buckets = (Node **)malloc(hashMap->capacity * sizeof(Node *));
    if (!hashMap->buckets) {
        hashMap->buckets = oldBuckets;  // 若分配失败，回滚
        return;
    }

    for (int i = 0; i < hashMap->capacity; i++) {
        hashMap->buckets[i] = NULL;
    }
    hashMap->size = 0;

    for (int i = 0; i < oldCapacity; i++) {
        Node *cur = oldBuckets[i];
        while (cur) {
            Pair *pair = cur->pair;
            put(hashMap, pair->key, pair->val);
            Node *temp = cur;
            cur = cur->next;
            free(temp);
        }
    }
    free(oldBuckets);
}

/* 删除操作 */
int removeItem(HashMapChaining *hashMap, int key) {
    int index = hashFunc(hashMap, key);
    Node *cur = hashMap->buckets[index];
    Node *pre = NULL;

    while (cur) {
        if (cur->pair->key == key) {
            if (pre) {
                pre->next = cur->next;
            } else {
                hashMap->buckets[index] = cur->next;
            }
            free(cur->pair->val);
            free(cur->pair);
            free(cur);
            hashMap->size--;
            return 1;
        }
        pre = cur;
        cur = cur->next;
    }
    return 0;
}

/* 打印哈希表 */
void print(HashMapChaining *hashMap) {
    for (int i = 0; i < hashMap->capacity; i++) {
        Node *cur = hashMap->buckets[i];
        printf("[");
        while (cur) {
            printf("%d -> %s", cur->pair->key, cur->pair->val);
            if (cur->next) {
                printf(", ");
            }
            cur = cur->next;
        }
        printf("]\n");
    }
}

/* 析构函数 */
void delHashMapChaining(HashMapChaining *hashMap) {
    for (int i = 0; i < hashMap->capacity; i++) {
        Node *cur = hashMap->buckets[i];
        while (cur) {
            Node *tmp = cur;
            cur = cur->next;
            free(tmp->pair->val);
            free(tmp->pair);
            free(tmp);
        }
    }
    free(hashMap->buckets);
    free(hashMap);
}


int main() {
    // 创建哈希表
    HashMapChaining *hashMap = newHashMapChaining();
    if (hashMap == NULL) {
        printf("内存分配失败!\n");
        return 1;  // 如果内存分配失败则退出程序
    }

    // 向哈希表中添加一些键值对（包括冲突的键值）
    put(hashMap, 1, "Apple");       // 哈希值为 1 % 4 = 1
    put(hashMap, 5, "Banana");      // 哈希值为 5 % 4 = 1（会与键 1 发生冲突）
    put(hashMap, 9, "Orange");      // 哈希值为 9 % 4 = 1（会与键 1 和 5 发生冲突）
    put(hashMap, 2, "Grapes");      // 哈希值为 2 % 4 = 2
    put(hashMap, 6, "Pineapple");   // 哈希值为 6 % 4 = 2（与键 2 发生冲突）

    // 打印当前哈希表，展示哈希冲突的处理
    printf("当前哈希表内容（哈希冲突处理展示）：\n");
    print(hashMap);

    // 查询一个键的值
    printf("\n查询键 5 对应的值: %s\n", get(hashMap, 5));  // 输出 "Banana"

    // 更新键 9 的值
    printf("\n更新键 9 的值...\n");
    put(hashMap, 9, "Strawberry");
    print(hashMap);

    // 删除键 1
    printf("\n删除键 1...\n");
    if (removeItem(hashMap, 1)) {
        printf("键 1 删除成功!\n");
    } else {
        printf("键 1 删除失败!\n");
    }
    print(hashMap);

    // 尝试删除一个不存在的键
    printf("\n删除不存在的键 10...\n");
    if (removeItem(hashMap, 10)) {
        printf("键 10 删除成功!\n");
    } else {
        printf("键 10 删除失败! 没有找到该键。\n");
    }

    // 打印最终哈希表
    printf("\n最终哈希表内容:\n");
    print(hashMap);

    // 清理哈希表
    delHashMapChaining(hashMap);

    return 0;
}