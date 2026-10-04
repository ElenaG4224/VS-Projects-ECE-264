#include <stdio.h>
#include <stdbool.h>




bool countChar(char * filename, int * counts, int size)
{
  // open a file whose name is filename for reading
  // if fopen fails, return false. Do NOT fclose
  FILE * fptr = fopen(filename, "r");
  if (fptr == NULL)
  {
    return false;
  }

  for (int i = 0; i < size; i++)
  {
    counts[i] = 0;
  }

  int onechar;

  while ((onechar = fgetc(fptr)) != EOF)
  {
    if (onechar >= 0 && onechar <= size - 1)
    {
      counts[onechar]++;
    }

  }

  // if fopen succeeds, read every character from the file
  //
  // if a character (call it onechar) is between
  // 0 and size - 1 (inclusive), increase
  // counts[onechar] by one
  // You should *NOT* assume that size is 256
  // reemember to call fclose
  // you may assume that counts already initialized to zero
  // size is the size of counts
  // you may assume that counts has enough memory space
  //
  // hint: use fgetc
  // Please read the document of fgetc carefully, in particular
  // when reaching the end of the file
  //
  fclose(fptr);
  return true;
}

void printCounts(int * counts, int size)
{

  for (int i = 0; i < size; i++)
  {
    if (counts[i])
    {
      printf("%d, ", i);

      if ((i >= 65 && i <= 90) || (i >= 97 && i <= 122))
      {
        printf("%c, ", i);

      }
      else {
        printf(" , ");
      }
      printf("%d\n", counts[i]);

    }
  }
  // print the values in counts in the following format
  // each line has three items:
  // ind, onechar, counts[ind]
  // ind is between 0 and size - 1 (inclusive)
  // onechar is printed if ind is between 'a' and 'z' or
  // 'A' and 'Z'. Otherwise, print space
  // if counts[ind] is zero, do not print
}


