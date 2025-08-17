
//
// Created by 우지범 on 25. 8. 17.
//

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING,
    TYPE_CHAR,
    TYPE_CUSTOM
} DataType;

typedef struct Node {
    void *data;
    DataType type;
    size_t data_size;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
    size_t size;
} LinkedList;

LinkedList* linkedlist_create(void);
void linkedlist_destroy(LinkedList *list);
int linkedlist_insert_front(LinkedList *list, void *data, DataType type, size_t data_size);
int linkedlist_insert_back(LinkedList *list, void *data, DataType type, size_t data_size);
int linkedlist_insert_at(LinkedList *list, size_t index, void *data, DataType type, size_t data_size);
int linkedlist_delete_front(LinkedList *list);
int linkedlist_delete_back(LinkedList *list);
int linkedlist_delete_at(LinkedList *list, size_t index);
void* linkedlist_get(LinkedList *list, size_t index);
DataType linkedlist_get_type(LinkedList *list, size_t index);
size_t linkedlist_size(LinkedList *list);
int linkedlist_is_empty(LinkedList *list);
void linkedlist_print(LinkedList *list);

#define INSERT_INT(list, value) \
    linkedlist_insert_back(list, &(int){value}, TYPE_INT, sizeof(int))

#define INSERT_DOUBLE(list, value) \
    linkedlist_insert_back(list, &(double){value}, TYPE_DOUBLE, sizeof(double))

#define INSERT_STRING(list, value) \
    do { \
        char *str = malloc(strlen(value) + 1); \
        strcpy(str, value); \
        linkedlist_insert_back(list, str, TYPE_STRING, strlen(value) + 1); \
    } while(0)

#define INSERT_CHAR(list, value) \
    linkedlist_insert_back(list, &(char){value}, TYPE_CHAR, sizeof(char))

#define INSERT_CUSTOM(list, value, size) \
    linkedlist_insert_back(list, value, TYPE_CUSTOM, size)

#define GET_INT(list, index) \
    (*(int*)linkedlist_get(list, index))

#define GET_DOUBLE(list, index) \
    (*(double*)linkedlist_get(list, index))

#define GET_STRING(list, index) \
    ((char*)linkedlist_get(list, index))

#define GET_CHAR(list, index) \
    (*(char*)linkedlist_get(list, index))

#define GET_CUSTOM(list, index, type) \
    ((type*)linkedlist_get(list, index))

#endif //LINKED_LIST_H
