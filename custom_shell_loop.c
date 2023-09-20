#include "shell.h"

int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = getInput(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = findBuiltIn(info);
			if (builtin_ret == -1)
				findCMD(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	writeHistory(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}


int findBuiltIn(info_t *info)
{
    int i = 0;
    int built_in_ret = -1;
    
    builtin_table builtintbl[] = {
        {"exit", _myexit},
        {"env", _myenv},
        {"help", custom_myhelp},
        {"history", _myhistory},
        {"setenv", _mysetenv},
        {"unsetenv", custom_myunsetenv},
        {"cd", _mycd},
        {"alias", _myalias},
        {NULL, NULL}
    };

    while (builtintbl[i].type)
    {
        if (custom_strcmp(info->argv[0], builtintbl[i].type) == 0)
        {
            info->line_count++;
            built_in_ret = builtintbl[i].func(info);
            break;
        }
        i++;
    }

    return built_in_ret;
}



void findCMD(info_t *info)
{
    char *path = NULL;
    int i = 0;
    int k = 0;

    info->path = info->argv[0];

    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }

    while (info->arg[i])
    {
        if (!custom_is_delim(info->arg[i], " \t\n"))
        {
            k++;
        }
        i++;
    }

    if (!k)
    {
        return;
    }

    path = findPath(info, _getenv(info, "PATH="), info->argv[0]);
    if (path)
    {
        info->path = path;
        forkCMD(info);
    }
    else
    {
        if ((interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && isCMD(info, info->argv[0]))
        {
            forkCMD(info);
        }
        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            print_error(info, "not found\n");
        }
    }
}


void forkCMD(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

