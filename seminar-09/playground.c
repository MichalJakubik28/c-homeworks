#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "stack.h"
#include "tree.h"

#define UNUSED(x) (void) (x)

/**********
 * Task 1 *
 ******** */

int tree_sum(const struct node *node)
{
    UNUSED(node);
    /* TODO */
    return -1;
}

int tree_size(const struct node *node)
{
    UNUSED(node);
    /* TODO */
    return -1;
}

int tree_max_value(const struct node *node)
{
    UNUSED(node);
    /* TODO */
    return -1;
}

void usage_task_1(const struct tree *tree)
{
    puts("Task 1");
    if (tree == NULL || tree->root == NULL) {
        fprintf(stderr, "\tthe tree is empty");
        return;
    }

    printf("\tsum: %d\n", tree_sum(tree->root));
    printf("\tsize: %d\n", tree_size(tree->root));
    printf("\tmax number: %d\n", tree_max_value(tree->root));
}

/* small main */

int main(void)
{
    srand(time(NULL)); // initialize pseudo-random generator
    struct tree *tree = tree_create(11);
    if (tree == NULL)
        return EXIT_FAILURE;

    if (!tree_print(tree, stdout)) {
        tree_destroy(tree);
        return EXIT_FAILURE;
    }

    int exit_status = EXIT_SUCCESS;
    // HERE YOU CAN USE THE GENERATED TREE
    usage_task_1(tree);

    tree_destroy(tree);

    return exit_status;
}
