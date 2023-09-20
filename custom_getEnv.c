#include "shell.h"

/**
 * get_environ - Returns the string array copy of our environ.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0.
 */
char **get_environ(info_t *info)
{
    if (!info->environ || info->env_changed)
    {
        info->environ = myListToStrings(info->env);
        info->env_changed = 0;
    }

    return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The string env var property.
 * Return: 1 on delete, 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
    my_list_t *node = info->env;
    size_t i = 0;
    char *p;

    if (!node || !var)
        return (0);

    while (node)
    {
        p = starts_with(node->str, var);

        if (p && *p == '=')
        {
            info->env_changed = deleteNodeAtIndex(&(info->env), i);
            i = 0;
            node = info->env;
            continue;
        }

        node = node->next;
        i++;
    }

    return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *           or modify an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The string env var property.
 * @value: The string env var value.
 * Return: Always 0.
 */
int _setenv(info_t *info, char *var, char *value)
{
    char *buf = NULL;
    my_list_t *node;
    char *p;

    if (!var || !value)
        return (0);

    buf = malloc(csutom_strlen(var) + csutom_strlen(value) + 2);

    if (!buf)
        return (1);

    custom_strcpy(buf, var);
    custom_strcat(buf, "=");
    custom_strcat(buf, value);
    node = info->env;

    while (node)
    {
        p = starts_with(node->str, var);

        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info->env_changed = 1;
            return (0);
        }

        node = node->next;
    }

    addNodeEnd(&(info->env), buf, 0);
    free(buf);
    info->env_changed = 1;
    return (0);
}

