#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) 
{ 
  struct list_node * node = malloc(sizeof(struct list_node));
  if (node == NULL)
  {
    return NULL; //OG, only thing in function
  }
  node->value = value;
  node->next = NULL;

  return node;
}

void insert_at_head(struct linked_list *list, size_t value) 
{
  struct list_node * newHead = new_node(value);

  if (list == NULL)
  {
    return;
  }
  if (list->head != NULL)
  {
    newHead->next = list->head;
  }
  list->head = newHead;

  return;
}

void insert_at_tail(struct linked_list *list, size_t value) //enqueue
{
  if (list->head == NULL || list == NULL)
  {
    return;
  }
  struct list_node * newTail = new_node(value);
  if (newTail == NULL)
  {
    return;
  }

  struct list_node * end = list->head;

  while (end != NULL)
  {
    end = end->next;
  }
  end = newTail; // memory issues start here: end->next = newTail;

  return;
}

size_t remove_from_head(struct linked_list *list)  //double check this w/ TA! and double check all -> vs . !!!
{
  if (list->head == NULL || list == NULL)
  {
    printf("remove from head fail\n");
    return 0;
  }
  
  struct list_node * temp = list->head; //no need to tranfer data besides the addresses
  size_t state;
  
  if (list->head->next == NULL)
  {
    
    state = list->head->value;
    list->head = NULL;
    free(temp);
  }
  else
  {
    state = list->head->value;
    list->head = list->head->next;
    free(temp);
  }

  return state; 
}

size_t remove_from_tail(struct linked_list *list) 
{ 
  if (list->head == NULL)
  {
    return 0;
  }
  if (list->head->next == NULL)
  {
    size_t state = list->head->value;
    struct list_node *h = list->head;
    list->head = NULL;
    free(h);
    return state;

  }

  struct list_node * newEnd = list->head;
  struct list_node * end = newEnd->next;
  
  while (end != NULL)
  {
    newEnd = newEnd->next;
    end = end->next;
  }


  free(end);
  size_t state = newEnd->value;
  newEnd->next = NULL;

  return state; 
}

void free_list(struct linked_list list) //is this to free one element or the whole list?
{
  struct list_node * befEnd = list.head;
  struct list_node * end = befEnd->next;

  while (end != NULL)
  {
    free(befEnd);
    befEnd = end->next;
    free(end);
    end = befEnd->next;
  }
  free (befEnd);

  return;
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
