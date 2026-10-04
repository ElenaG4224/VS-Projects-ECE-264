#include "hw09.h"
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>

#define INV_SYMBOL 36

// useful static helper functions
static int char_to_int(char c);
const char *skip_whitespace(const char *ptr);

long string_to_long(const char *stringOG, const char **endptr, int base) {
  // checking that the first argument is not null, as specified in hw09.h
  const char * string = stringOG;
  assert(string != NULL);

  // setting errno to zero before function body starts
  errno = 0;

  long ret_value = 0;

  // Check if the base provided is invalid, i.e. it is less than 2 or more than
  // 36. Remember that base 0 is valid, and you need to check the string to see
  // if it is octal or hexadecimal.
  //
  // If the base is invalid, set errno to EINVAL and return

  if (base != 0 && (base < 2 || base > 36))
  {
    errno = EINVAL;
    *endptr = stringOG;
    return 0;
  }
  
  // Skip over any whitespace present

  // Find the sign before the start of the number, if any
  string = skip_whitespace(string);

  int sign = 1;
  if (string[0] == '+')
  {
    string++;
  }
  else if (string[0] == '-')
  {
    sign = -1;
    string++;
  }

  if (char_to_int(string[0]) == INV_SYMBOL || string[0] == '\0')
  {
    *endptr = stringOG;
    return 0;

  }

  // Handle the case where base == 0
  if (base == 16 && string[0] == '0' && (string[1] == 'x' || string[1] == 'X'))
  {
    string += 2;
  }
  else if (base == 0)
  {
    if (string[0] == '0')
    {
      string++;
      if (string[0] == 'x' || string[0] == 'X')
      {
        base = 16;
        string++;
      }
      else
      {
        base = 8;
      }
    }
    else
    {
      base = 10;
    }
  }

  //find lenghth of valid string
  int lenValid = 0;
  int flag = 1;

  while (flag && string[lenValid] != '\0')
  {
    int check = char_to_int(string[lenValid]);
    if (check == INV_SYMBOL || check >= base)
    {
      flag = 0;
    }
    else
    {
      lenValid++;
    }
  }

  //set endptr and convert valid string
  *endptr = string + lenValid;
  for (int i = 0; i < lenValid; i++)
  {
    //check for overflow and underflow
    // asign power of current digit
    int power = 1;
    for (int j = 1; j <= i; j++)
    {
      power *= base;
    }

    long addVal =sign * power * char_to_int(string[lenValid - (i + 1)]);

    if (sign > 0 && addVal >= LONG_MAX - ret_value) // addVal > Longmax - ret_value
    {
      errno = ERANGE;
      return LONG_MAX;
    }
    else if (sign < 0 && addVal <= LONG_MIN - ret_value) // addval < longmin - ret_value
    {
      errno = ERANGE;
      return LONG_MIN;
    }

    ret_value += addVal;
     
  }
  
  // Continue conversion while
  // 1) the string has not ended
  // 2) the current symbol is valid
  // 3) the current symbol is not a numeric value more than the base
  // Remember to deal with overflow! If overflow occurs, set errno to ERANGE

  // Deal with signs

  // If there is no digit conversion, what should endptr be?

  return ret_value;
}

static int char_to_int(char c) {
  // what if c is '0' -- '9'
  if (isdigit(c)) {
    return c - '0';
  }

  // what if c is 'a' -- 'z'
  if (islower(c)) {
    // only deal with one alphabetic case
    c = toupper(c);
  }

  if (isupper(c)) {
    // 'A' becomes 65 - 65 + 10 = 10, 'B' becomes 11 and so on
    return c - 'A' + 10;
  }

  return INV_SYMBOL;
}

const char *skip_whitespace(const char *ptr) {
  while (isspace(*ptr)) {
    ptr++;
  }

  return ptr;
}
