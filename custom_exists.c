#include "shell.h"

/**
 * custom_strncpy - Copies a string up to 'n' characters.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The number of characters to be copied.
 * Return: The destination string.
 */
char *custom_strncpy(char *dest, char *src, int n)
{
    int i;
    char *s = dest;

    for (i = 0; src[i] != '\0' && i < n - 1; i++)
    {
        dest[i] = src[i];
    }

    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }

    return s;
}

/**
 * custom_strncat - Concatenates two strings up to 'n' characters.
 * @dest: The destination string.
 * @src: The source string.
 * @n: The maximum number of bytes to be used.
 * Return: The destination string.
 */
char *custom_strncat(char *dest, char *src, int n)
{
    int i, j;
    char *s = dest;

    i = 0;
    while (dest[i] != '\0')
    {
        i++;
    }

    j = 0;
    while (src[j] != '\0' && j < n)
    {
        dest[i] = src[j];
        i++;
        j++;
    }

    if (j < n)
    {
        dest[i] = '\0';
    }

    return s;
}

/**
 * custom_strchr - Locates a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 * Return: A pointer to the first occurrence of the character in the string.
 *         If the character is not found, returns NULL.
 */
char *custom_strchr(char *s, char c)
{
    while (*s != '\0')
    {
        if (*s == c)
        {
            return s;
        }
        s++;
    }

    return NULL;
}

