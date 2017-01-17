#include <stdlib.h>
#include "list.h"

list_t *list_create()
{
    list_t *retval;

    retval = malloc(sizeof(list_t));
    if (retval) {
        retval->head = NULL;
        retval->tail = NULL;
        retval->count = 0;
    }

    return retval;
}

int list_free(list_t *ls)
{
    if (ls) {
        if (ls->count != 0) {
            return -1;
        }
        free(ls);
    }

    return 0;
}

int list_push(list_t *ls, void *data)
{
    list_node_t *node;

    node = malloc(sizeof(list_node_t));
    if (!node) {
        return -1;
    }

    node->data = data;
    node->prev = NULL;
    node->next = ls->head;

    if (ls->head) { /* reset head's prev pointer */
        ls->head->prev = node;
    }

    ls->head = node;

    if (!ls->count) { /* is the first list node, reset tail pointer */
        ls->tail = node;
    }

    ls->count++;

    return 0;
}

int list_pop(list_t *ls, void **data)
{
    list_node_t *node;

    if (!ls->count) {
        return -1;
    }

    node = ls->tail;

    ls->tail = node->prev;
    if (ls->tail) { /* not empty update next pointer */
        ls->tail->next = NULL;
    }

    if (--ls->count == 0) { /* if list nodes was empty, reset head pointer */
        ls->head = NULL;
    }

    *data = node->data;

    free(node);

    return 0;
}

int list_count(list_t *ls)
{
    return ls->count;
}
