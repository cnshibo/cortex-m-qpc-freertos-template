#include "bl/bl_list.h"
#include "bl/bl_errno.h"

void list_init(list_t *list)
{
    list->head = list->tail = NULL;

    list->size = 0;
}

uint32_t list_get_size(const list_t *list)
{
    return list->size;
}

bool list_is_empty(const list_t *list)
{
    return (list->size == 0);
}

list_node_t *list_get_front(list_t *list)
{
    if (!list) goto on_error;

    return list->head;
on_error:
    return NULL;
}

list_node_t *list_get_tail(list_t *list)
{
    if (!list) goto on_error;

    return list->tail;
on_error:
    return NULL;
}

list_node_t *list_pop_front(list_t *list)
{
    if (!list) goto on_error;

    list_node_t *node = list->head;

    list_remove_node(list, node);

    return node;

on_error:
    return NULL;
}

list_node_t *list_pop_back(list_t *list)
{
    if (!list) goto on_error;

    list_node_t *node = list->tail;

    list_remove_node(list, node);

    return node;
on_error:
    return NULL;
}

pn_status_t list_push_front(list_t *list, list_node_t *node)
{
    if (!list || !node) goto on_error;

    if (list->head)
    {
        node->prev       = NULL;
        node->next       = list->head;
        list->head->prev = node;
        list->head       = node;
    }
    else
    {
        node->prev = node->next = NULL;
        list->head = list->tail = node;
    }

    return PN_SUCCESS;
on_error:
    return PN_EINVAL;
}

pn_status_t list_push_back(list_t *list, list_node_t *node)
{
    if (!list || !node) goto on_error;

    if (list->tail)
    {
        node->prev       = list->tail;
        node->next       = NULL;
        list->tail->next = node;
        list->tail       = node;
    }
    else
    {
        node->prev = node->next = NULL;
        list->head = list->tail = node;
    }
    return PN_SUCCESS;
on_error:
    return PN_EINVAL;
}

pn_status_t list_insert_before(list_t *list, list_node_t *pos, list_node_t *node)
{
    if (!list || !node) goto on_error;

    return PN_SUCCESS;
on_error:
    return PN_EINVAL;
}

pn_status_t list_insert_after(list_t *list, list_node_t *pos, list_node_t *node)
{
    return PN_SUCCESS;
on_error:
    return PN_EINVAL;
}

list_node_t *list_find_node(list_t *list, list_node_t *node)
{
    return NULL;
}

pn_status_t list_remove_node(list_t *list, list_node_t *node)
{
    if (!list || !node) goto on_error;

    list_node_t *prev = node->prev;
    list_node_t *next = node->next;

    if (prev)
    {
        prev->next = next;
    }

    if (next)
    {
        next->prev = prev;
    }

    node->prev = NULL;
    node->next = NULL;

    list->size--;

    return PN_SUCCESS;
on_error:
    return PN_EINVAL;
}

void list_remove_all(list_t *list)
{
}