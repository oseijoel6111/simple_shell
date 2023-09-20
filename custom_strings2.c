#include "shell.h"


char *custom_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0){
		return dest;
	}
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return dest;
}


char *custom_strdup(const char *string)
{
	int length = 0;
	char *ret;

	if (string == NULL)
		return NULL;
	while (*string++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return NULL;
	for (length++; length--;){
		ret[length] = *--string;
	}
	return ret;
}


void _puts(char *string)
{
	int i = 0;

	if (!string)
		return;
	while (string[i] != '\0')
	{
		_putchar(string[i]);
		i++;
	}
}


int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH){
		buf[i++] = c;
	}
	return 1;
}

