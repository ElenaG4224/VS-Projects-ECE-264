#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef __TREE_H__
#define __TREE_H__

typedef struct _Tree {
  int data;
  struct _Tree *left;
  struct _Tree *right;
} Tree;

Tree *invert_tree(Tree *root);

Tree *read_from_file(char *filename);
void preorder_print(Tree *root, char *filename);

void free_tree(Tree *root);

#endif
