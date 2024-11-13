//
// Created by Reinhard Van Astrea  on 2024/11/13.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100  // 哈希表最大桶数量

/* 键值对 int->string */
typedef struct {
    int key;
    char *val;
} Pair;

/* 基于数组实现的哈希表 */
typedef struct {
    Pair *buckets[MAX_SIZE];
} ArrayHashMap;

/* 存储键或值集合的结构体 */
typedef struct {
    void *set;  // 存储键、值或键值对的集合
    int len;    // 集合的长度
} MapSet;

/* 简单的哈希函数 */
int hashFunc(int key) {
    return key % MAX_SIZE;
}

/* 构造函数 */
ArrayHashMap *newArrayHashMap() {
    ArrayHashMap *hmap = malloc(sizeof(ArrayHashMap));
    for (int i = 0; i < MAX_SIZE; i++) {
        hmap->buckets[i] = NULL;
    }
    return hmap;
}

/* 析构函数 */
void delArrayHashMap(ArrayHashMap *hmap) {
    for (int i = 0; i < MAX_SIZE; i++) {
        if (hmap->buckets[i] != NULL) {
            free(hmap->buckets[i]->val);
            free(hmap->buckets[i]);
        }
    }
    free(hmap);
}

/* 添加操作 */
void put(ArrayHashMap *hmap, const int key, const char *val) {
    int index = hashFunc(key);
    Pair *pair = malloc(sizeof(Pair));
    pair->key = key;
    pair->val = malloc(strlen(val) + 1);
    strcpy(pair->val, val);

    // 若该索引已有元素，先释放再更新
    if (hmap->buckets[index] != NULL) {
        free(hmap->buckets[index]->val);
        free(hmap->buckets[index]);
    }

    hmap->buckets[index] = pair;
}

/* 删除操作 */
void removeItem(ArrayHashMap *hmap, const int key) {
    int index = hashFunc(key);
    if (hmap->buckets[index] != NULL) {
        free(hmap->buckets[index]->val);
        free(hmap->buckets[index]);
        hmap->buckets[index] = NULL;
    }
}

/* 获取所有键值对 */
void pairSet(ArrayHashMap *hmap, MapSet *set) {
    int total = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (hmap->buckets[i] != NULL) {
            total++; //确定哈希表中有多少个有效的键值对（即非空桶的数量），以便为键值对数组分配内存。
        }
    }

    Pair *entries = malloc(sizeof(Pair) * total);
    int index = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (hmap->buckets[i] != NULL) {
            entries[index].key = hmap->buckets[i]->key;
            entries[index].val = malloc(strlen(hmap->buckets[i]->val) + 1);
            strcpy(entries[index].val, hmap->buckets[i]->val);
            index++;
        }
    }
    set->set = entries;
    set->len = total;
}

/* 获取所有键 */
void keySet(ArrayHashMap *hmap, MapSet *set) {
    int total = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (hmap->buckets[i] != NULL) {
            total++;
        }
    }

    int *keys = malloc(total * sizeof(int));
    int index = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (hmap->buckets[i] != NULL) {
            keys[index] = hmap->buckets[i]->key;
            index++;
        }
    }
    set->set = keys;
    set->len = total;
}

/* 获取所有值 */
void valueSet(ArrayHashMap *hmap, MapSet *set) {
    int total = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (hmap->buckets[i] != NULL) {
            total++; //确定哈希表中有多少个有效的键，方便后续分配内存。
        }
    }

    char **vals = malloc(total * sizeof(char *));
    int index = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (hmap->buckets[i] != NULL) {
            vals[index] = malloc(strlen(hmap->buckets[i]->val) + 1);
            strcpy(vals[index], hmap->buckets[i]->val);
            index++;
        }
    }
    set->set = vals;
    set->len = total;
}

/* 打印哈希表 */
void print(ArrayHashMap *hmap) {
    MapSet set;
    pairSet(hmap, &set);
    Pair *entries = (Pair *)set.set;

    for (int i = 0; i < set.len; i++) {
        printf("%d -> %s\n", entries[i].key, entries[i].val);
        free(entries[i].val);  // 释放每个字符串
    }

    free(entries);  // 释放键值对数组
}

int main() {
    ArrayHashMap *hmap = newArrayHashMap();

    put(hmap, 1, "One");
    put(hmap, 2, "Two");
    put(hmap, 3, "Three");

    printf("HashMap Contents:\n");
    print(hmap);

    printf("\nRemoving key 2...\n");
    removeItem(hmap, 2);

    printf("HashMap Contents after removal:\n");
    print(hmap);

    delArrayHashMap(hmap);
    return 0;
}
