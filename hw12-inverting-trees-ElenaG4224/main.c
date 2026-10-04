#include "tree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) 
{ 
    if (argc < 3)
    {
        return EXIT_FAILURE;
    }

    Tree * binary_tree = read_from_file(argv[1]); //filename 1
    invert_tree(binary_tree);
    preorder_print(binary_tree, argv[2]); //filename 2
    free_tree(binary_tree);

    return EXIT_SUCCESS; 
}
