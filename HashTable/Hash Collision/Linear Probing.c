//
// Created by Reinhard Van Astrea  on 2024/11/13.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 键值对结构
typedef struct {
    int key;
    char *val;
} Pair;

/* 开放寻址哈希表 */
typedef struct {
    int size;         // 键值对数量
    int capacity;     // 哈希表容量
    double loadThres; // 触发扩容的负载因子阈值
    int extendRatio;  // 扩容倍数
    Pair **buckets;   // 桶数组
    Pair *TOMBSTONE;  // 删除标记
} HashMapOpenAddressing;

// 函数声明
void extend(HashMapOpenAddressing *hashMap); // 添加函数声明

/* 构造函数 */
HashMapOpenAddressing *newHashMapOpenAddressing() {
    HashMapOpenAddressing *hashMap = (HashMapOpenAddressing *)malloc(sizeof(HashMapOpenAddressing));
    if (hashMap == NULL) {
        return NULL; // 如果内存分配失败，返回 NULL
    }
    hashMap->size = 0;
    hashMap->capacity = 4;
    hashMap->loadThres = 2.0 / 3.0;
    hashMap->extendRatio = 2;
    hashMap->buckets = (Pair **)calloc(hashMap->capacity, sizeof(Pair *));
    if (hashMap->buckets == NULL) {
        free(hashMap);  // 如果内存分配失败，释放已经分配的内存
        return NULL;
    }
    hashMap->TOMBSTONE = (Pair *)malloc(sizeof(Pair));
    if (hashMap->TOMBSTONE == NULL) {
        free(hashMap->buckets); // 释放内存
        free(hashMap);
        return NULL;
    }
    hashMap->TOMBSTONE->key = -1;
    hashMap->TOMBSTONE->val = "-1";

    return hashMap;
}

/* 析构函数 */
void delHashMapOpenAddressing(HashMapOpenAddressing *hashMap) {
    if (hashMap == NULL) return;
    for (int i = 0; i < hashMap->capacity; i++) {
        Pair *pair = hashMap->buckets[i];
        if (pair != NULL && pair != hashMap->TOMBSTONE) {
            free(pair->val);
            free(pair);
        }
    }
    free(hashMap->buckets);
    free(hashMap->TOMBSTONE);
    free(hashMap);
}

/* 哈希函数 */
int hashFunc(HashMapOpenAddressing *hashMap, int key) {
    return key % hashMap->capacity;
}

/* 负载因子 */
double loadFactor(HashMapOpenAddressing *hashMap) {
    return (double)hashMap->size / (double)hashMap->capacity;
}

/* 搜索 key 对应的桶索引 */
int findBucket(HashMapOpenAddressing *hashMap, int key) {
    int index = hashFunc(hashMap, key);
    int firstTombstone = -1;
    // 线性探测，当遇到空桶时跳出
    while (hashMap->buckets[index] != NULL) {
        // 若遇到 key ，返回对应的桶索引
        if (hashMap->buckets[index]->key == key) {
            // 若之前遇到了删除标记，则将键值对移动至该索引处
            if (firstTombstone != -1) {
                hashMap->buckets[firstTombstone] = hashMap->buckets[index];
                hashMap->buckets[index] = hashMap->TOMBSTONE;
                return firstTombstone; // 返回移动后的桶索引
            }
            return index; // 返回桶索引
        }
        // 记录遇到的首个删除标记
        if (firstTombstone == -1 && hashMap->buckets[index] == hashMap->TOMBSTONE) {
            firstTombstone = index;
        }
        // 计算桶索引，越过尾部则返回头部
        index = (index + 1) % hashMap->capacity;
    }
    // 若 key 不存在，则返回添加点的索引
    return firstTombstone == -1 ? index : firstTombstone;
}

/* 查询操作 */
char *get(HashMapOpenAddressing *hashMap, int key) {
    // 搜索 key 对应的桶索引
    int index = findBucket(hashMap, key);
    // 若找到键值对，则返回对应 val
    if (hashMap->buckets[index] != NULL && hashMap->buckets[index] != hashMap->TOMBSTONE) {
        return hashMap->buckets[index]->val;
    }
    // 若键值对不存在，则返回空字符串
    return "";
}

/* 添加操作 */
void put(HashMapOpenAddressing *hashMap, int key, char *val) {
    // 当负载因子超过阈值时，执行扩容
    if (loadFactor(hashMap) > hashMap->loadThres) {
        extend(hashMap); // 调用扩容函数
    }
    // 搜索 key 对应的桶索引
    int index = findBucket(hashMap, key);
    // 若找到键值对，则覆盖 val 并返回
    if (hashMap->buckets[index] != NULL && hashMap->buckets[index] != hashMap->TOMBSTONE) {
        free(hashMap->buckets[index]->val);
        hashMap->buckets[index]->val = (char *)malloc(strlen(val) + 1);
        if (hashMap->buckets[index]->val == NULL) {
            return; // 如果内存分配失败，则返回
        }
        strcpy(hashMap->buckets[index]->val, val);
        return;
    }
    // 若键值对不存在，则添加该键值对
    Pair *pair = (Pair *)malloc(sizeof(Pair));
    if (pair == NULL) {
        return; // 内存分配失败，退出
    }
    pair->key = key;
    pair->val = (char *)malloc(strlen(val) + 1);
    if (pair->val == NULL) {
        free(pair);
        return; // 内存分配失败，退出
    }
    strcpy(pair->val, val);

    hashMap->buckets[index] = pair;
    hashMap->size++;
}

/* 删除操作 */
void removeItem(HashMapOpenAddressing *hashMap, int key) {
    // 搜索 key 对应的桶索引
    int index = findBucket(hashMap, key);
    // 若找到键值对，则用删除标记覆盖它
    if (hashMap->buckets[index] != NULL && hashMap->buckets[index] != hashMap->TOMBSTONE) {
        Pair *pair = hashMap->buckets[index];
        free(pair->val);
        free(pair);
        hashMap->buckets[index] = hashMap->TOMBSTONE;
        hashMap->size--;
    }
}

/* 扩容哈希表 */
void extend(HashMapOpenAddressing *hashMap) {
    // 暂存原哈希表
    Pair **bucketsTmp = hashMap->buckets;
    int oldCapacity = hashMap->capacity;
    // 初始化扩容后的新哈希表
    hashMap->capacity *= hashMap->extendRatio;
    hashMap->buckets = (Pair **)calloc(hashMap->capacity, sizeof(Pair *));
    if (hashMap->buckets == NULL) {
        hashMap->buckets = bucketsTmp; // 如果扩容失败，则恢复原哈希表
        return;
    }
    hashMap->size = 0;
    // 将键值对从原哈希表搬运至新哈希表
    for (int i = 0; i < oldCapacity; i++) {
        Pair *pair = bucketsTmp[i];
        if (pair != NULL && pair != hashMap->TOMBSTONE) {
            put(hashMap, pair->key, pair->val);
            free(pair->val);
            free(pair);
        }
    }
    free(bucketsTmp);
}

/* 打印哈希表 */
void print(HashMapOpenAddressing *hashMap) {
    for (int i = 0; i < hashMap->capacity; i++) {
        Pair *pair = hashMap->buckets[i];
        if (pair == NULL) {
            printf("NULL\n");
        } else if (pair == hashMap->TOMBSTONE) {
            printf("TOMBSTONE\n");
        } else {
            printf("%d -> %s\n", pair->key, pair->val);
        }
    }
}

int main() {
    // 测试代码
    HashMapOpenAddressing *hashMap = newHashMapOpenAddressing();
    put(hashMap, 1, "one");
    put(hashMap, 2, "two");
    put(hashMap, 3, "three");
    put(hashMap, 4, "four");
    print(hashMap);

    printf("Value for key 2: %s\n", get(hashMap, 2));

    removeItem(hashMap, 2);
    printf("After removing key 2:\n");
    print(hashMap);

    delHashMapOpenAddressing(hashMap);
    return 0;
}
