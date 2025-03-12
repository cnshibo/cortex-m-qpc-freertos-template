#ifndef __BL_LIST_H__
#define __BL_LIST_H__

#include "bl/types.h"

PN_BEGIN_DECL

typedef struct list_node_t list_node_t;

struct list_node_t
{
    list_node_t *prev;
    list_node_t *next;
};

typedef struct list_t
{
    list_node_t *head;
    list_node_t *tail;
    uint32_t size;
} list_t;

void list_init(list_t *list);

bool list_is_empty(const list_t *list);
uint32_t list_get_size(const list_t *list);

pn_status_t list_insert_before(list_t *list, list_node_t *pos, list_node_t *node);
pn_status_t list_insert_after(list_t *list, list_node_t *pos, list_node_t *node);

pn_status_t list_push_front(list_t *list, list_node_t *node);
pn_status_t list_push_back(list_t *list, list_node_t *node);

list_node_t *list_find_node(list_t *list, list_node_t *node);

pn_status_t list_remove_front(list_t *list);
pn_status_t list_remove_back(list_t *list);

pn_status_t list_remove_node(list_t *list, list_node_t *node);
void list_remove_all(list_t *list);

PN_END_DECL
#endif /* __PN_LIST_H__ */
