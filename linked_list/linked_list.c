//
// Created by 우지범 on 25. 8. 17.
//

#include "linked_list.h"

LinkedList* linkedlist_create(void) {
    LinkedList *list = malloc(sizeof(LinkedList));
    if (!list) return NULL;
    
    list->head = NULL;
    list->size = 0;
    return list;
}

void linkedlist_destroy(LinkedList *list) {
    if (!list) return;
    
    Node *current = list->head;
    while (current) {
        Node *next = current->next;
        if (current->type == TYPE_STRING) {
            free(current->data);
        } else if (current->type == TYPE_CUSTOM) {
            free(current->data);
        } else {
            free(current->data);
        }
        free(current);
        current = next;
    }
    free(list);
}

int linkedlist_insert_front(LinkedList *list, void *data, DataType type, size_t data_size) {
    if (!list || !data) return -1;
    
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) return -1;
    
    new_node->data = malloc(data_size);
    if (!new_node->data) {
        free(new_node);
        return -1;
    }
    
    memcpy(new_node->data, data, data_size);
    new_node->type = type;
    new_node->data_size = data_size;
    new_node->next = list->head;
    
    list->head = new_node;
    list->size++;
    return 0;
}

int linkedlist_insert_back(LinkedList *list, void *data, DataType type, size_t data_size) {
    if (!list || !data) return -1;
    
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) return -1;
    
    new_node->data = malloc(data_size);
    if (!new_node->data) {
        free(new_node);
        return -1;
    }
    
    memcpy(new_node->data, data, data_size);
    new_node->type = type;
    new_node->data_size = data_size;
    new_node->next = NULL;
    
    if (!list->head) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
    
    list->size++;
    return 0;
}

int linkedlist_insert_at(LinkedList *list, size_t index, void *data, DataType type, size_t data_size) {
    if (!list || !data || index > list->size) return -1;
    
    if (index == 0) {
        return linkedlist_insert_front(list, data, type, data_size);
    }
    
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) return -1;
    
    new_node->data = malloc(data_size);
    if (!new_node->data) {
        free(new_node);
        return -1;
    }
    
    memcpy(new_node->data, data, data_size);
    new_node->type = type;
    new_node->data_size = data_size;
    
    Node *current = list->head;
    for (size_t i = 0; i < index - 1; i++) {
        current = current->next;
    }
    
    new_node->next = current->next;
    current->next = new_node;
    list->size++;
    return 0;
}

int linkedlist_delete_front(LinkedList *list) {
    if (!list || !list->head) return -1;
    
    Node *to_delete = list->head;
    list->head = list->head->next;
    
    free(to_delete->data);
    free(to_delete);
    list->size--;
    return 0;
}

int linkedlist_delete_back(LinkedList *list) {
    if (!list || !list->head) return -1;
    
    if (!list->head->next) {
        return linkedlist_delete_front(list);
    }
    
    Node *current = list->head;
    while (current->next->next) {
        current = current->next;
    }
    
    free(current->next->data);
    free(current->next);
    current->next = NULL;
    list->size--;
    return 0;
}

int linkedlist_delete_at(LinkedList *list, size_t index) {
    if (!list || !list->head || index >= list->size) return -1;
    
    if (index == 0) {
        return linkedlist_delete_front(list);
    }
    
    Node *current = list->head;
    for (size_t i = 0; i < index - 1; i++) {
        current = current->next;
    }
    
    Node *to_delete = current->next;
    current->next = to_delete->next;
    
    free(to_delete->data);
    free(to_delete);
    list->size--;
    return 0;
}

void* linkedlist_get(LinkedList *list, size_t index) {
    if (!list || !list->head || index >= list->size) return NULL;
    
    Node *current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    return current->data;
}

DataType linkedlist_get_type(LinkedList *list, size_t index) {
    if (!list || !list->head || index >= list->size) return -1;
    
    Node *current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    return current->type;
}

size_t linkedlist_size(LinkedList *list) {
    return list ? list->size : 0;
}

int linkedlist_is_empty(LinkedList *list) {
    return list ? (list->size == 0) : 1;
}

void linkedlist_print(LinkedList *list) {
    if (!list) return;
    
    Node *current = list->head;
    printf("[");
    while (current) {
        switch (current->type) {
            case TYPE_INT:
                printf("%d", *(int*)current->data);
                break;
            case TYPE_DOUBLE:
                printf("%.2f", *(double*)current->data);
                break;
            case TYPE_STRING:
                printf("\"%s\"", (char*)current->data);
                break;
            case TYPE_CHAR:
                printf("'%c'", *(char*)current->data);
                break;
            case TYPE_CUSTOM:
                printf("(custom data)");
                break;
        }
        if (current->next) printf(", ");
        current = current->next;
    }
    printf("]\n");
}