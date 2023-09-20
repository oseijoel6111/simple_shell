#include "shell.h"

/**
 * interactive - Checks if the shell is running in interactive mode.
 * @info: Pointer to the shell information struct.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int interactive(info_t *info)
{
    return isatty(STDIN_FILENO) && info->readfd <= 2;
}

/**
 * custom_is_delim - Checks if a character is a delimiter.
 * @c: The character to check.
 * @delim: The delimiter characters.
 *
 * Return: 1 if true, 0 if false.
 */
int custom_is_delim(char c, char *delim)
{
    while (*delim) {
        if (*delim++ == c) {
            return 1;
        }
    }
    return 0;
}

/**
 * custom_is_isalpha - Checks if a character is alphabetic.
 * @c: The character to check.
 *
 * Return: 1 if c is alphabetic, 0 otherwise.
 */
int custom_is_isalpha(int c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/**
 * _atoi - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: 0 if no numbers in string, the converted number otherwise.
 */
int _atoi(char *s)
{
    int i = 0;
    int sign = 1;
    int flag = 0;
    unsigned int result = 0;

    while (s[i] != '\0' && flag != 2) {
        if (s[i] == '-') {
            sign *= -1;
        }

        if (s[i] >= '0' && s[i] <= '9') {
            flag = 1;
            result = result * 10 + (s[i] - '0');
        } else if (flag == 1) {
            flag = 2;
        }

        i++;
    }

    return (sign == -1) ? -result : result;
}

