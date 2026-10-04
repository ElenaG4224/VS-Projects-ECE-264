#include "hw09.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

// suggested testing function declaration
static void check_string_to_long(const char *string, int base);

int main(int argc, char **argv) {
  errno = 0;

  fprintf(stderr, "Welcome to ECE264, we are working on HW09!\n\n");

  //tests
  const char * string1 = "0xfff3";
  check_string_to_long(string1, 16);//lowest base simple

  const char * string2 = "12Zf";
  check_string_to_long(string2, 36); //highest base simple

  const char * string3 = "   2!";
  check_string_to_long(string3, 10); //whitespace & invalid char--

  const char * string4 = "2!";
  check_string_to_long(string4, 1); //invalid base

  const char * string5 = "0Xff24!";
  check_string_to_long(string5, 0); //base 0, hex, upper and lowercase

  const char * string6 = "  05749!";
  check_string_to_long(string6, 0); //base 0, octal, whitespace

  const char * string7 = "2527!";
  check_string_to_long(string7, 0); //base 0, decimal

  const char * string8 = "zzz";
  check_string_to_long(string8, 20); //invalid number

  const char * string9 = "   +zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz!";
  check_string_to_long(string9, 36); //optional + and overlow

  const char * string10 = "   -zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz!";
  check_string_to_long(string10, 36); //optional - and underflow

  return EXIT_SUCCESS;
}

static void check_string_to_long(const char *string, int base)
{
  const char * stringTest = string;
  char * endptrTol;
  const char * endptrTest;

  long result = strtol(string, &endptrTol, base);
  printf("expected: %ld  at %c\n", result, *endptrTol);
  long resultTest = string_to_long(stringTest, &endptrTest, base);
  printf("actual: %ld  at %c\n\n", resultTest, *endptrTest);

  return;
}