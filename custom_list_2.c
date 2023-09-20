#include "shell.h"

/**
 * addNode - Adds a node to the start of the list.
 * @head: Address of pointer to head node.
 * @str: str field of node.
 * @num: Node index used by history.
 *
 * Return: Pointer to the new head of the list.
 */
my_list_t *addNode(my_list_t **head, const char *str, int num)
{
    my_list_t *new_head;

    if (!head)
        return NULL;

    new_head = malloc(sizeof(my_list_t));
    if (!new_head)
        return NULL;

    _memset((void *)new_head, 0, sizeof(my_list_t));
    new_head->num = num;

    if (str)
    {
        new_head->str = custom_strdup(str);
        if (!new_head->str)
        {
            free(new_head);
            return NULL;
        }
    }

    new_head->next = *head;
    *head = new_head;
    return new_head;
}

/**
 * addNodeEnd - Adds a node to the end of the list.
 * @head: Address of pointer to head node.
 * @str: str field of node.
 * @num: Node index used by history.
 *
 * Return: Pointer to the new node added at the end.
 */
my_list_t *addNodeEnd(my_list_t **head, const char *str, int num)
{
    my_list_t *new_node, *node;

    if (!head)
        return NULL;

    node = *head;
    new_node = malloc(sizeof(my_list_t));
    if (!new_node)
        return NULL;

    _memset((void *)new_node, 0, sizeof(my_list_t));
    new_node->num = num;

    if (str)
    {
        new_node->str = custom_strdup(str);
        if (!new_node->str)
        {
            free(new_node);
            return NULL;
        }
    }

    if (node)
    {
        while (node->next)
            node = node->next;
        node->next = new_node;
    }
    else
        *head = new_node;

    return new_node;
}

/**
 * printList_str - Prints only the str element of a my_list_t linked list.
 * @h: Pointer to first node.
 *
 * Return: Size of list.
 */
size_t printList_str(const my_list_t *h)
{
    size_t i = 0;

    while (h)
    {
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
        i++;
    }
    return i;
}

/**
 * deleteNodeAtIndex - Deletes a node at the given index.
 * @head: Address of pointer to first node.
 * @index: Index of node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int deleteNodeAtIndex(my_list_t **head, unsigned int index)
{
    my_list_t *node, *prev_node;
    unsigned int i = 0;

    if (!head || !*head)
        return 0;

    if (!index)
    {
        node = *head;
        *head = (*head)->next;
        free(node->str);
        free(node);
        return 1;
    }

    node = *head;
    while (node)
    {
        if (i == index)
        {
            prev_node->next = node->next;
            free(node->str);
            free(node);
            return 1;
        }
        i++;
        prev_node = node;
        node = node->next;
    }
    return 0;
}

/**
 * freeList - Frees all nodes of a list.
 * @head_ptr: Address of pointer to head node.
 *
 * Return: void
 */
void freeList(my_list_t **head_ptr)
{
    my_list_t *node, *next_node, *head;

    if (!head_ptr || !*head_ptr)
        return;

    head = *head_ptr;
    node = head;
    
    while (node)
    {
        next_node = node->next;
        free(node->str);
        free(node);
        node = next_node;
    }
    
    *head_ptr = NULL;
}

