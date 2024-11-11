//
// Created by Reinhard Van Astrea  on 2024/11/11.
//
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

/*双向列表的节点定义*/
typedef struct double_ended_queue_node{
    int data;
    struct double_ended_queue *prev;
    struct double_ended_queue *next;
}double_ended_queue_node;
/*节点构造函数*/
 double_ended_queue_node *new_double_ended_queue_node(int num){
    double_ended_queue_node *new_node = (double_ended_queue_node*)malloc(sizeof (double_ended_queue_node));
    new_node->data = num;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}
/*删除节点*/
void delete_double_ended_queue_node(double_ended_queue_node* node){
    free(node);
 }
/*双向列表结构体定义*/
 typedef struct double_ended_queue{
     double_ended_queue_node *front , *rear;
     int queue_size;
 }double_ended_queue;
/*双向列表构造函数*/
 double_ended_queue *new_double_ended_queue(){
     double_ended_queue *new_queue =  (double_ended_queue*)(malloc(sizeof (double_ended_queue)));
     new_queue->front = NULL;
     new_queue->rear = NULL;
     new_queue->queue_size = 0;
     return new_queue;
 }
/*删除双向列表*/
 void del_double_ended_queue(double_ended_queue *queue_to_del){
     for(int i = 0; i<queue_to_del->queue_size && queue_to_del->front != NULL; i++){
         double_ended_queue_node *temp = queue_to_del->front;
         queue_to_del->front = queue_to_del->front->next;
         free(temp);
     }
     free(queue_to_del);
 }

 int size_of_queue(double_ended_queue *queue){
     return queue->queue_size;
 }

 bool isEmpty(double_ended_queue *queue){
     return (queue->front==NULL && queue->rear==NULL);
 }

 /*入队插入函数*/
 void push (double_ended_queue *queue,int num,bool isFront){
     double_ended_queue_node *new_node = new_double_ended_queue_node(num);
     if(isEmpty(queue)){
         queue->front = queue->rear = new_node;
     }
     else if(isFront){
         queue->front->prev = new_node;
         new_node->next = queue->front;
         queue->front = new_node;
     }
     else{
         queue->rear->next = new_node;
         new_node->prev = queue->rear;
         queue->rear = new_node;
     }
     queue->queue_size++;
 }

 /*首部入队*/
 void pushFront(double_ended_queue *queue, int num){
     push(queue,num,true);
 }
/*尾部入队*/
void pushRear(double_ended_queue *queue, int num){
    push(queue,num,false);
}

/* 访问队首元素 */
int peekFirst(double_ended_queue *queue) {
    if(size_of_queue(queue) && queue->front)
        return queue->front->data;
    return INT32_MAX;
}

/* 访问队尾元素 */
int peekLast(double_ended_queue *queue) {
    if(size_of_queue(queue) && queue->rear)
        return queue->rear->data;
    return INT32_MAX;
}

/*出队函数*/
int pop(double_ended_queue *queue,bool isFront){
    int val;
    if(isEmpty(queue))
        return -1;
    else if(isFront){
        val = queue->front->data;
        double_ended_queue_node *temp = queue->front;
        queue->front = queue->front->next;
        free(temp);
    }else{
        val = queue->rear->data;
        double_ended_queue_node *temp = queue->rear;
        queue->rear = queue->rear->prev;
        free(temp);
    }
    queue->queue_size--;
    return val;
}

/*首部出队*/
int popFront(double_ended_queue *queue){
    return pop(queue,true);
}
/*尾部出队*/
int popRear(double_ended_queue *queue){
    return pop(queue,false);
}

void printArray(int arr[], int size) {  // Function definition
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/*打印队列*/
void printQueue(double_ended_queue *queue){
    int *arr = malloc(sizeof(int) * queue->queue_size);
    double_ended_queue_node *temp_node = queue->front;
    for (int i = 0; i<queue->queue_size; i++){
        arr[i] = temp_node->data;
        temp_node = temp_node->next;
    }
    printArray(arr,queue->queue_size);
    free(arr);
}

int main(){
    double_ended_queue *queue = new_double_ended_queue();
    for(int i = 0; i<5; i++){
        pushFront(queue,i);
    }
    printQueue(queue);

    popFront(queue);
    popRear(queue);
    printQueue(queue);
}