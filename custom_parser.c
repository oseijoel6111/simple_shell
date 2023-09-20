#include "shell.h"

/**
 * isCMD - Determines if a file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Return: 1 if true, 0 otherwise.
 */
int isCMD(info_t *info, char *path)
{
    struct stat st;

    (void)info;
    if (!path || stat(path, &st))
        return 0;

    if (st.st_mode & S_IFREG)
    {
        return 1;
    }
    return 0;
}

/**
 * dupChars - Duplicates characters from a string.
 * @pathstr: The PATH string.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * Return: Pointer to a new buffer.
 */
char *dupChars(char *pathstr, int start, int stop)
{
    static char buf[1024];
    int i = start, k = 0;

    while (i < stop)
    {
        if (pathstr[i] != ':')
            buf[k++] = pathstr[i];
        i++;
    }
    buf[k] = '\0';
    return buf;
}

/**
 * findPath - Finds the cmd in the PATH string.
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The cmd to find.
 *
 * Return: Full path of cmd if found or NULL.
 */
char *findPath(info_t *info, char *pathstr, char *cmd)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!pathstr)
        return NULL;
    if ((csutom_strlen(cmd) > 2) && starts_with(cmd, "./"))
    {
        if (isCMD(info, cmd))
            return cmd;
    }
    while (1)
    {
        if (!pathstr[i] || pathstr[i] == ':')
        {
            path = dupChars(pathstr, curr_pos, i);
            if (!*path)
                custom_strcat(path, cmd);
            else
            {
                custom_strcat(path, "/");
                custom_strcat(path, cmd);
            }
            if (isCMD(info, path))
                return path;
            if (!pathstr[i])
                break;
            curr_pos = i;
        }
        i++;
    }
    return NULL;
}

