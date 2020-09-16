#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void add_entry(node_t **head, int new_value)
{
    node_t **indirect = head;

    node_t *new_node = malloc(sizeof(node_t));
    assert(new_node);
    new_node->value = new_value;
    new_node->next = NULL;

    while (*indirect)
        indirect = &(*indirect)->next;

    *indirect = new_node;
}

node_t *find_entry(node_t *head, int value)
{
    node_t *current = head;
    for (; current && current->value != value; current = current->next)
        /* interate */;
    return current;
}

void remove_entry(node_t **head, node_t *entry)
{
    node_t **indirect = head;

    while ((*indirect) != entry)
        indirect = &(*indirect)->next;

    *indirect = entry->next;
    free(entry);
}

void delete_list(node_t **head)
{
    while (*head) {
        node_t *next = (*head)->next;
        free(*head);
        *head = next;
    }
}

void swap_pair(node_t **head)
{
    for (node_t **node = head; *node && (*node)->next;
         node = &((*node)->next->next)) {
        node_t *tmp = *node;
        *node = (*node)->next;
        tmp->next = (*node)->next;
        (*node)->next = tmp;
    }
}

void swap_pair_by_value(node_t **head)
{
    for (node_t **node = head; *node && (*node)->next;
         node = &((*node)->next->next)) {
        XORSWAP_UNSAFE((*node)->value, (*node)->next->value);
    }
}

void reverse(node_t **head)
{
    node_t *prev = NULL;
    node_t *next = (*head)->next;

    (*head)->next = prev;
    while (next) {
        prev = (*head);
        *head = next;
        next = next->next;
        (*head)->next = prev;
    }
}

node_t *rev_recursive(node_t *head, node_t *pre)
{
    node_t *tail = head;

    if (head->next)
        head = rev_recursive(head->next, head);

    if (pre) {
        tail->next = pre;
        pre->next = NULL;
    } else
        tail->next = NULL;

    return head;
}

void print_list(node_t *head)
{
    for (node_t *current = head; current; current = current->next)
        printf("%d ", current->value);
    printf("\n");
}

node_t *fisher_yates(node_t *head)
{
    node_t *tmp = head, *output = NULL, *tail = NULL;
    int num = 0;
    while (tmp) {
        tmp = tmp->next;
        num++;
    }

    srand(time(NULL));
    for (; num > 0; num--) {
        int randnum = (rand() % num) + 1;
        node_t *pre = NULL;

        tmp = head;
        if (randnum == 1)
            head = head->next;

        for (; randnum > 1; randnum--) {
            pre = tmp;
            tmp = tmp->next;
        }

        if (pre)
            pre->next = tmp->next;

        if (!output) {
            output = tmp;
            tmp->next = NULL;
            tail = output;
        } else {
            tail->next = tmp;
            tmp->next = NULL;
            tail = tail->next;
        }
    }

    return output;
}
