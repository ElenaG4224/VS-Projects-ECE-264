// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h> 

void eliminate(int n, int k)
{
  // allocate an arry of n elements
  int * arr = malloc(sizeof(* arr) * n);
  // check whether memory allocation succeeds.
  // if allocation fails, stop
  if (arr == NULL)
    {
      fprintf(stderr, "malloc fail\n");
      return;
    }
  // initialize all elements
  // You may initialize the elements to a number of your choice (e.g., 0)
  for (int i = 0; i < n; i++)
  {
    arr[i] = 0;
  }

  int check = n;
  int index = 0;
  int counter = 1;

  // counting to k,
  // repeat until only one element is unmarked
  while (check > 1)
  {
    if (!arr[index])
    {
      // mark the eliminated element; you choose the mark (e.g., 1)
      // print the index of the marked element
      if (counter == k)
      {
        arr[index] = 1;
        printf("%d\n", index);
        check--;
      }
      counter = counter % k + 1;
    }
    index = (index + 1) % n;
  }

  // print the last remaining index
  for (int i = 0; i < n && check; i++)
  {
    if (!arr[i])
    {
      check = 0;
      printf("%d\n", i);
    }
  }

  // release the memory of the array
  free (arr);
}

