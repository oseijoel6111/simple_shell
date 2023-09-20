#include "shell.h"

char *_memset(char *s, char b, unsigned int n)
{
    unsigned int i = 0;
    
    while (i < n)
    {
        s[i] = b;
        i++;
    }
    
    return s;
}


void ffree(char **pp)
{
    char **a = pp;

    if (!pp)
        return;
    
    while (*pp)
    {
        free(*pp++);
    }
    
    free(a);
}



void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *p;

    if (!ptr)
        return malloc(new_size);
    
    if (!new_size)
    {
        free(ptr);
        return NULL;
    }
    
    if (new_size == old_size)
        return ptr;

    p = malloc(new_size);
    if (!p)
        return NULL;

    old_size = old_size < new_size ? old_size : new_size;
    while (old_size--)
    {
        p[old_size] = ((char *)ptr)[old_size];
    }
    
    free(ptr);
    return p;
}

