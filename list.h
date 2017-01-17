#ifndef __LIST_H
#define __LIST_H

typedef struct list_node {
    struct list_node *prev;
    struct list_node *next;
    void *data;
} list_node_t;

typedef struct list {
    list_node_t *head;
    list_node_t *tail;
    int count;
} list_t;

list_t *list_create();
int list_free(list_t *ls);
int list_push(list_t *ls, void *data);
int list_pop(list_t *ls, void **data);

#endif
