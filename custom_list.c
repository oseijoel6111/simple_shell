#include "shell.h"

/**
 * list_len - Determines the length of a linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t list_len(const my_list_t *h)
{
    size_t i = 0;

    for (; h; h = h->next)
    {
        i++;
    }
    return i;
}

/**
 * myListToStrings - Returns an array of strings from the list->str.
 * @head: Pointer to the first node.
 *
 * Return: Array of strings.
 */
char **myListToStrings(my_list_t *head)
{
    my_list_t *node = head;
    size_t i = list_len(head), j;
    char **strs;
    char *str;

    if (!head || !i)
        return NULL;

    strs = malloc(sizeof(char *) * (i + 1));
    if (!strs)
        return NULL;

    for (i = 0; node; node = node->next, i++)
    {
        str = malloc(csutom_strlen(node->str) + 1);
        if (!str)
        {
            for (j = 0; j < i; j++)
                free(strs[j]);
            free(strs);
            return NULL;
        }

        str = custom_strcpy(str, node->str);
        strs[i] = str;
    }
    strs[i] = NULL;
    return strs;
}

/**
 * printList - Prints all elements of a my_list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t printList(const my_list_t *h)
{
    size_t i = 0;

    for (; h; h = h->next)
    {
        _puts(convert_number(h->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        i++;
    }
    return i;
}

/**
 * nodeStartsWith - Returns the node whose string starts with a prefix.
 * @node: Pointer to list head.
 * @prefix: String to match.
 * @c: The next character after the prefix to match.
 *
 * Return: Matching node or NULL.
 */
my_list_t *nodeStartsWith(my_list_t *node, char *prefix, char c)
{
    char *p = NULL;

    while (node)
    {
        p = starts_with(node->str, prefix);
        if (p && ((c == -1) || (*p == c)))
            return node;
        node = node->next;
    }
    return NULL;
}

/**
 * getNodeIndex - Gets the index of a node.
 * @head: Pointer to list head.
 * @node: Pointer to the node.
 *
 * Return: Index of the node or -1.
 */
ssize_t getNodeIndex(my_list_t *head, my_list_t *node)
{
    size_t i = 0;

    while (head)
    {
        if (head == node)
            return i;
        head = head->next;
        i++;
    }
    return -1;
}

