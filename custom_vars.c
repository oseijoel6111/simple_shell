#include "shell.h"

int is_custom_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') 
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

void checkChain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}


int replace_alias(info_t *info)
{
	int i;
	my_list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = nodeStartsWith(info->alias, info->argv[0], '=');
		if (!node) {
			return (0);
		}
		free(info->argv[0]);
		p = custom_strchr(node->str, '=');
		if (!p)
			return (0);
		p = custom_strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}


int replaceVars(info_t *info)
{
	int i = 0;
	my_list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1]){
			continue;
		}

		if (!custom_strcmp(info->argv[i], "$?"))
		{
			replaceString(&(info->argv[i]),
				custom_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!custom_strcmp(info->argv[i], "$$"))
		{
			replaceString(&(info->argv[i]),
				custom_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = nodeStartsWith(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replaceString(&(info->argv[i]),
				custom_strdup(custom_strchr(node->str, '=') + 1));
			continue;
		}
		replaceString(&info->argv[i], custom_strdup(""));

	}
	return 0;
}


int replaceString(char **older, char *new)
{
	free(*older);
	*older = new;
	return 1;
}

