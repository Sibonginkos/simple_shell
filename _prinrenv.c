#include "shell.h"

/**
 * _printenv - print enviroment
 * Return: Nothing
 */

void _printenv(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		write(1, environ[i], _strlen(environ[i]));
		write(1, "\n", 1);
		i++;
	}
}
