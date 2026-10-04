#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * TODO: Implement all the functions in tree.h here.
 *
 * Use as many helper functions as you need, just declare them to be static.
 *
 */
static Tree * buildTreeHelp(FILE * fptr);
static void printHelp(Tree * root, FILE * fptr);

static Tree *alloc_node(int data) {
  Tree *ret = calloc(1, sizeof(Tree));
  if (ret == NULL) {
    return NULL;
  }

  ret->data = data;

  return ret;
}

Tree *read_from_file(char *filename)
{
  printf("\nreading from file: ");

  if(filename == NULL)
  {
    printf("no file. ");
    return NULL;
  }
  FILE *fptr = fopen(filename, "rb");
  if (fptr == NULL)
  {
    printf("file open failed. ");
    return NULL;
  }

  Tree * binary_tree = buildTreeHelp(fptr);

  fclose(fptr);

  if (binary_tree == NULL)
  {
    printf("build tree failed. ");
  }
  return binary_tree;

}

static Tree * buildTreeHelp(FILE * fptr) //possible problem
{
  int data = 0;
  char structure = 0;

  if (!fread(&data, 4, 1, fptr) || !fread(&structure, 1, 1, fptr))
  {
    return NULL; //possible issue?
  }
  Tree * root = alloc_node(data);
  if (root == NULL)
  {
    printf("not allocating. ");
    return NULL;
  }

  printf("\nnode info:  %d, children: %c", data, structure);

  if (structure & 2) //check left
  {
    root->left = buildTreeHelp(fptr);

  }
  if (structure & 1) //check right
  {
    root->right = buildTreeHelp(fptr);

  }

  return root;
}

Tree * invert_tree(Tree * root)
{
  if (root == NULL)
  {
    return NULL;
  }
  Tree* temp = root->left;
  root->left = invert_tree(root->right);
  root->right = invert_tree(temp);

  return root;

}

void preorder_print(Tree * root, char * filename)
{
  printf("\nprinting tree: ");
  if(root == NULL) 
  {
    printf("no root. ");
  }
  if (filename == NULL)
  {
    printf(" no file. ");
    return;
  }
  FILE *fptr = fopen(filename, "wb");
  if (fptr == NULL)
  {
    printf("file open failed. ");
    return;
  }
  printHelp(root, fptr);
  fclose(fptr);

  return;
}

static void printHelp(Tree * root, FILE * fptr)
{
  if (root == NULL)
  {
    return;
  }

  char count = 0;
  if (root->left != NULL)
  {
    count += 2;
  }
  if (root->right != NULL)
  {
    count++;
  }

  fwrite(&root->data, sizeof(int), 1, fptr);
  fwrite(&count, 1, 1, fptr);
  printHelp(root->left, fptr);
  printHelp(root->right, fptr);

  return;
}

void free_tree(Tree * root)
{
  if (root == NULL)
  {
    return;
  }
  free_tree(root->left);
  free_tree(root->right);
  free(root);
  return;
}


