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

void tree_sum_rec(const struct node *node, int *sum)
{
    if (node == NULL) {
        return;
    }
    *sum += node->value;
    tree_sum_rec(node->left, sum);
    tree_sum_rec(node->right, sum);
}

int tree_sum(const struct node *node)
{
    int total = 0;
    tree_sum_rec(node, &total);
    return total;
}

void tree_size_rec(const struct node *node, int *sum)
{
    if (node == NULL) {
        return;
    }
    *sum++;
    tree_size_rec(node->left, sum);
    tree_size_rec(node->right, sum);
}

int tree_size(const struct node *node)
{
    int total = 0;
    tree_size_rec(node, &total);
    return total;
}

void tree_max_value_rec(const struct node *node, int *sum)
{
    if (node == NULL) {
        return;
    }
    if (node->value > *sum) {
        *sum = node->value;
    }
    tree_max_value_rec(node->left, sum);
    tree_max_value_rec(node->right, sum);
}

int tree_max_value(const struct node *node)
{
    int max = 0;
    tree_max_value_rec(node, &max);
    return max;
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

void tree_aggregate_rec(const struct node *node, int (*projector)(int), int *result) {
    if (node == NULL) {
        return;
    }
    result += projector(node->value);
    tree_aggregate_rec(node->left, projector, result);
    tree_aggregate_rec(node->right, projector, result);
}

int tree_aggregate(const struct node *node, int (*projector)(int)) {
    int result = 0;
    tree_aggregate_rec(node, projector, &result);
    return result;
}

void tree_for_each(const struct node *node, void (*operation)(int, void *), void *data_pack) {
    if (node == NULL) {
        return;
    }
    operation(node->value, data_pack);
    tree_for_each(node->left, operation, data_pack);
    tree_for_each(node->right, operation, data_pack);
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
