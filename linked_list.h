#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#define XORSWAP_UNSAFE(a, b)                                                \
    ((a) ^= (b), (b) ^= (a),                                                \
     (a) ^= (b)) /* Doesn't work when a and b are the same object - assigns \
                    zero (0) to the object in that case */
#define XORSWAP(a, b)                                        \
    ((&(a) == &(b)) ? (a) /* Check for distinct addresses */ \
                    : XORSWAP_UNSAFE(a, b))

typedef struct __node {
    int value;
    struct __node *next;
} node_t;

void add_entry(node_t **head, int new_value);
node_t *find_entry(node_t *head, int value);
void remove_entry(node_t **head, node_t *entry);
void delete_list(node_t **head);
void swap_pair(node_t **head);
void swap_pair_by_value(node_t **head);
void reverse(node_t **head);
node_t *rev_recursive(node_t *head, node_t *pre);
void print_list(node_t *head);
node_t *fisher_yates(node_t *head);
#endif
