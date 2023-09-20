#include "shell.h"

/**
 * getHistoryFile - Gets the history file.
 * @info: Parameter struct.
 *
 * Return: Allocated string containing the history file.
 */
char *getHistoryFile(info_t *info)
{
    char *buf, *dir;

    dir = _getenv(info, "HOME=");
    if (!dir)
        return NULL;

    buf = malloc(sizeof(char) * (csutom_strlen(dir) + csutom_strlen(HIST_FILE) + 2));
    if (!buf)
        return NULL;

    buf[0] = 0;
    custom_strcpy(buf, dir);
    custom_strcat(buf, "/");
    custom_strcat(buf, HIST_FILE);

    return buf;
}

int writeHistory(info_t *info)
{
    ssize_t fd;
    char *filename = getHistoryFile(info);
    my_list_t *node = NULL;

    if (!filename)
        return -1;

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);

    if (fd == -1)
        return -1;

    for (node = info->history; node; node = node->next)
    {
        _putsfd(node->str, fd);
        _putfd('\n', fd);
    }

    _putfd(BUF_FLUSH, fd);
    close(fd);

    return 1;
}

/**
 * readHistory - Reads history from a file.
 * @info: The parameter struct.
 *
 * Return: histcount on success, 0 otherwise.
 */
int readHistory(info_t *info)
{
    int i, last = 0, linecount = 0;
    ssize_t fd, rdlen, fsize = 0;
    struct stat st;
    char *buf = NULL, *filename = getHistoryFile(info);

    if (!filename)
        return 0;

    fd = open(filename, O_RDONLY);
    free(filename);

    if (fd == -1)
        return 0;

    if (!fstat(fd, &st))
        fsize = st.st_size;

    if (fsize < 2)
        return 0;

    buf = malloc(sizeof(char) * (fsize + 1));
    if (!buf)
        return 0;

    rdlen = read(fd, buf, fsize);
    buf[fsize] = 0;

    if (rdlen <= 0)
        return free(buf), 0;

    close(fd);

    for (i = 0; i < fsize; i++)
    {
        if (buf[i] == '\n')
        {
            buf[i] = 0;
            buildHistoryList(info, buf + last, linecount++);
            last = i + 1;
        }
    }

    if (last != i)
        buildHistoryList(info, buf + last, linecount++);

    free(buf);
    info->histcount = linecount;

    while (info->histcount-- >= HIST_MAX)
        deleteNodeAtIndex(&(info->history), 0);

    renumberHistory(info);
    return info->histcount;
}

/**
 * buildHistoryList - Adds an entry to a history linked list.
 * @info: Structure containing potential arguments. Used to maintain.
 * @buf: Buffer.
 * @linecount: The history linecount, histcount.
 *
 * Return: Always 0.
 */
int buildHistoryList(info_t *info, char *buf, int linecount)
{
    my_list_t *node = NULL;

    if (info->history)
        node = info->history;

    addNodeEnd(&node, buf, linecount);

    if (!info->history)
        info->history = node;

    return 0;
}

int renumberHistory(info_t *info)
{
    my_list_t *node = info->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }

    return info->histcount = i;
}

