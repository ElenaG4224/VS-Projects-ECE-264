// ***
// *** DO NOT modify this file
// ***

#include "binary_tree.h"

// This program reads a file containing integers
// The first two integers are the low and high values for trimTree function
// The rest of the integers are used to create a binary tree
static bool readFile(const char* filename, int** array, int* size, int* low, int* high)
{
    FILE* fptr = fopen(filename, "r");
    if (fptr == NULL) {
        return false;
    }

    // Count the integers in the file, return if none
    int numint = 0;
    int value;
    while (fscanf(fptr, "%d", &value) == 1) {
        numint++;
    }
    if (numint < 3) {
        fclose (fptr);
        fprintf(stderr, "SOMETHING WRONG\n");
        return false;
    }

    // Go back to the start of the file and read
    fseek (fptr, 0, SEEK_SET);
    // Read the first two integers and store them in low and high
    if (fscanf(fptr, "%d", low) != 1 || fscanf(fptr, "%d", high) != 1 || *low > *high) {
        fclose (fptr);
        fprintf(stderr, "SOMETHING WRONG\n");
        return false;
    }

    numint -= 2; 
    *size = numint;
    int* arr = malloc(sizeof(int) * numint);

    int ind = 0;
    while (ind < numint) {
        if (fscanf(fptr, "%d", &arr[ind]) != 1) {
            fprintf(stderr, "SOMETHING WRONG\n");
            free(arr);
            *size = 0;
            fclose (fptr);
            return false;
        }
        ind++;
    }

    fclose (fptr);
    *array = arr;
    return true;
}

int main(int argc, char** argv)
{
    if (argc < 3) {
        return EXIT_FAILURE;
    }

    // Read in arrays from files
    int* arr = NULL;
    int size, low, high;
    bool rtv;
    rtv = readFile(argv[1], &arr, &size, &low, &high);
    if (rtv == false)
    {
        return EXIT_FAILURE;
    }

    // Construct the binary tree from the array
    TreeNode* root = createTree(arr, size);

    if ( strcmp(argv[2], "trim") == 0 ) {
        root = trimTree(root, low, high);
    }
    else if ( strcmp(argv[2], "bst") == 0 ) {
        root = toBST(root);
    }


    // Print in-order traversal of the tree
    inorderTraversal(root);
    printf("\n");
    // Print pre-order traversal of the tree
    preorderTraversal(root);

    // Free allocated memory
    freeTree(root);
    free(arr);
    return EXIT_SUCCESS;
}

