//
// Created by Reinhard Van Astrea  on 2024/11/10.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* 列表类 */
typedef struct {
    int *arr;        // 数组（存储列表元素）
    int capacity;    // 列表容量
    int size;        // 列表大小
    int extendRatio; // 列表每次扩容的倍数
} MyList;

/* 函数声明 */
void extendCapacity(MyList *nums);  // 声明 extendCapacity

/* 构造函数 */
MyList *newMyList() {
    MyList *nums = malloc(sizeof(MyList));
    nums->capacity = 10;
    nums->arr = malloc(sizeof(int) * nums->capacity);
    nums->size = 0;
    nums->extendRatio = 2;
    return nums;
}

/* 析构函数 */
void delMyList(MyList *nums) {
    free(nums->arr);
    free(nums);
}

/* 获取列表长度 */
int size(MyList *nums) {
    return nums->size;
}

/* 获取列表容量 */
int capacity(MyList *nums) {
    return nums->capacity;
}

/* 访问元素 */
int get(MyList *nums, int index) {
    assert(index >= 0 && index < nums->size);
    return nums->arr[index];
}

/* 更新元素 */
void set(MyList *nums, int index, int num) {
    assert(index >= 0 && index < nums->size);
    nums->arr[index] = num;
}

/* 在尾部添加元素 */
void add(MyList *nums, int num) {
    if (size(nums) == capacity(nums)) {
        extendCapacity(nums); // 扩容
    }
    nums->arr[size(nums)] = num;
    nums->size++;
}

/* 在中间插入元素 */
void insert(MyList *nums, int index, int num) {
    assert(index >= 0 && index <= size(nums)); // 插入允许在尾部
    // 元素数量超出容量时，触发扩容机制
    if (size(nums) == capacity(nums)) {
        extendCapacity(nums); // 扩容
    }
    for (int i = size(nums); i > index; --i) {
        nums->arr[i] = nums->arr[i - 1];
    }
    nums->arr[index] = num;
    nums->size++;
}

/* 删除元素 */
// 注意：stdio.h 占用了 remove 关键词
int removeItem(MyList *nums, int index) {
    assert(index >= 0 && index < size(nums));
    int num = nums->arr[index];
    for (int i = index; i < size(nums) - 1; i++) {
        nums->arr[i] = nums->arr[i + 1];
    }
    nums->size--;
    return num;
}

/* 列表扩容 */
void extendCapacity(MyList *nums) {
    // 先分配空间
    int newCapacity = capacity(nums) * nums->extendRatio;
    int *extend = (int *)malloc(sizeof(int) * newCapacity);
    int *temp = nums->arr;

    // 拷贝旧数据到新数据
    for (int i = 0; i < size(nums); i++)
        extend[i] = nums->arr[i];

    // 释放旧数据
    free(temp);

    // 更新新数据
    nums->arr = extend;
    nums->capacity = newCapacity;
}

/* 将列表转换为 Array 用于打印 */
int *toArray(MyList *nums) {
    return nums->arr;
}

/* 打印列表内容 */
void printList(MyList *nums) {
    printf("List (size = %d, capacity = %d): ", size(nums), capacity(nums));
    for (int i = 0; i < size(nums); i++) {
        printf("%d ", nums->arr[i]);
    }
    printf("\n");
}

/* 测试主函数 */
int main() {
    MyList *nums = newMyList();

    // 添加元素
    for (int i = 0; i < 15; i++) {
        add(nums, i + 1);
    }
    printList(nums); // 应该显示列表包含 15 个元素，且容量扩展过

    // 访问元素
    printf("Element at index 5: %d\n", get(nums, 5));

    // 更新元素
    set(nums, 5, 99);
    printf("After setting index 5 to 99: ");
    printList(nums);

    // 插入元素
    insert(nums, 3, 77);
    printf("After inserting 77 at index 3: ");
    printList(nums);

    // 删除元素
    removeItem(nums, 10);
    printf("After removing element at index 10: ");
    printList(nums);

    // 释放内存
    delMyList(nums);
    return 0;
}

