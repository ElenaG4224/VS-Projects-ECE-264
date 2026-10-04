/*
** -----------------------------------------------------------------
** IMPORTANT NOTE: For this assignment, you are not allowed to use
** string.h or any header file other than what is defined below
** -----------------------------------------------------------------
*/
#include "stringm.h"

/*
** strlen_m calculates the length of a string
** const char *string - string to calculate length of
** return the size of the string
**
** note: you can assume string is not NULL
*/
size_t strlen_m(const char *string)
{
    int length = 0;
    while ( *string != '\0')
    {
        length++;
        string++;
    }

    length *= sizeof(char);

    return length;
}

/*
** strncpy_m copies n characters of string and returns it
** const char *string - string to copy
** size_t n - number of characters to copy (not including null character)
** return a copy of first n characters of string
**
** note: you can assume string is not NULL
** hint: you will need to malloc a size n + 1 string to accomodate the null character
*/
char *strncpy_m(const char *string, size_t n)
{
    char* strCopy = malloc(n + 1);
    for (int i = 0; i < n; i++)
    {
        strCopy[i] = string[i];
    }
    strCopy[n] = '\0';
    
    return strCopy;
}

/*
** join_m joins an array of strings separated by a delimiter
** Strings strings - structure that stores an array of strings
** const char *delimiter - delimiter string which joins each string
** return the string created by joining all strings with the delimiter
**
** note: you can assume delimiter is not NULL
** hint: return NULL if strings.num_strings is 0
*/
char *join_m(Strings strings, const char *delimiter)
{
    if (strings.num_strings == 0)
    {
        return NULL;
    }

    size_t joinLen = 1; //to include terminating char
    size_t delimLen = strlen_m(delimiter);

    for (int i = 0; i < strings.num_strings; i++)
    {
        joinLen += strlen_m(strings.strings[i]);
    }

    char* joinString = malloc( joinLen + ((strings.num_strings - 1) * delimLen)); // -1 for missing delimiter,

    int currChar = 0;
    for (int i = 0; i < strings.num_strings; i++)
    {
        for (int j = 0; j < strlen_m(strings.strings[i]); j++)
        {
            joinString[currChar] = strings.strings[i][j];
            currChar++;
        }

        if (i < strings.num_strings - 1)
        {
            for (int k = 0; k < delimLen; k++)
            {
                joinString[currChar] = delimiter[k];
                currChar++;

            }
        }
        else if (i == strings.num_strings - 1)
        {
            joinString[currChar] = '\0';
            currChar++;
        }
    }

    return joinString;
}

/*
** free_strings frees all allocated elements in strings
** String strings - free each string in strings.strings and strings.strings itself
*/
void free_strings(Strings strings)
{
    for (int i = 0; i < strings.num_strings; i++)
    {
        free(strings.strings[i]);
    }
    free(strings.strings);

    return;
}

/*
** split_m splits a string at any occurence of pattern
** const char *string - string that is searched for the pattern
** const char *pattern - pattern which string should be split
** return a String structure which contains an array of each string
**
** note: you may assume string and pattern are not NULL
** hint 1: TA solution uses strlen_m, strstr_m, and strncpy_m
** hint 2: first calculate how many strings are needed, which is: 
**         (the number of times the delimiter appears + 1)
** hint 3: when trying to store a substring, think about how the length of 
**         that substring might be calculated in terms of pointer arithmetic
**         - what is the outcome of adding or subtract pointers?
** hint 3.5: strstr_m will return a pointer to the first character of the next occurence 
**           or NULL if not found
**          
*/
Strings split_m(const char *string, const char *pattern)
{
    Strings result = { .num_strings = 0, .strings = NULL };
    size_t pattLen = strlen_m(pattern);
    const char * stringCpy = string;

    int needString = 1;
    const char * flag = strstr_m(string, pattern);
    while (flag != NULL && pattLen != 0 && strlen_m(string) != 0)//problem
    {
        needString++;
        flag = strstr_m(flag + pattLen, pattern);
    }

    result.num_strings = needString;
    result.strings = malloc(sizeof(char*) * needString);

    if (needString == 1)
    {
        result.strings[0] = strncpy_m(string, strlen_m(string));
        return result;
    }

    const char * ptr1 = strstr_m(stringCpy, pattern);
    result.strings[0] = strncpy_m(stringCpy, ptr1 - stringCpy);

    for (int i = 1; i < needString - 1; i++)
    {
        const char * ptr2 = strstr_m(ptr1 + pattLen, pattern);
        result.strings[i] = strncpy_m(ptr1 + pattLen, ptr2 - (ptr1 + pattLen));

        ptr1 = ptr2;
    }

    result.strings[needString - 1] = strncpy_m(ptr1 + pattLen , strlen_m(ptr1));

    return result;
}

/*
** find_and_replace_all_m finds each occurence of the pattern in the string and replaces it
** const char *string - string to search through
** const char *pattern - pattern to search for in the string
** const char *replacement - replacement string for each occurence of the pattern in the string
** return a string in which every occurence of pattern is replaced replacement
**
** note: you may assume string, pattern, and replacement are all not NULL
** hint: there are two main ways of implementing this function, one involves many lines, one involves four
*/
char *find_and_replace_all_m(const char *string, const char *pattern, const char *replacement)
{
    Strings  strings = split_m(string, pattern);
    char * ptr = join_m(strings,replacement);
    free_strings(strings);
    return ptr;
}

/*
** The strstr function is implemented for you to use -- DO NOT MODIFY
** If you are curious about the algorithm used, look up the Knuth-Morris-Pratt (KMP)
** algorithm that can find a substring inside another string 'blazingly fast'
*/
const char *strstr_m(const char *haystack, const char *needle)
{
    size_t haystack_len = 0, needle_len = 0;
    for (const char *h = haystack; *h; h++)
        haystack_len++;
    for (const char *n = needle; *n; n++)
        needle_len++;

    if (needle_len > haystack_len)
        return NULL;

    char *lps_str = malloc(haystack_len + needle_len + 1);
    size_t i = 0;
    for (const char *n = needle; *n; n++, i++)
        lps_str[i] = *n;
    lps_str[i++] = '\1';
    for (const char *h = haystack; *h; h++, i++)
        lps_str[i] = *h;

    int *lps_arr = calloc((haystack_len + needle_len + 1), sizeof *lps_arr);
    size_t l = 0, r = 1;
    bool success = false;

    while (r < haystack_len + needle_len + 1)
    {
        if (lps_str[l] == lps_str[r])
        {
            l++;
            lps_arr[r] = l;
            r++;
        }
        else if (l)
            l = lps_arr[l - 1];
        else
        {
            lps_arr[r] = 0;
            r++;
        }

        if (l == needle_len)
        {
            success = true;
            break;
        }
    }

    free(lps_arr);
    free(lps_str);
    if (success)
        return haystack + (r - l - needle_len - 1);
    return NULL;
}
