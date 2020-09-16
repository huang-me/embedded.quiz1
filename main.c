#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linked_list.h"

int main()
{
    node_t *head = NULL;
    srand(time(NULL));

    for (int i = 0; i < 10000; i++) {
        add_entry(&head, (rand() % 1000));
    }

    printf("Prev: \n");
    print_list(head);

    // swap_pair(&head);
    // printf("After swap: \n");
    // print_list(head);

    // head = rev_recursive(head, NULL);
    // printf("After reverse: \n");
    // print_list(head);

    head = fisher_yates(head);
    printf("after Fisher-Yates shuffle:\n");
    print_list(head);

    delete_list(&head);

    return 0;
}
