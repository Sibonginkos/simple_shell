#include <stdio.h>

/**
 * main - Prints all arguments
 * @argc: Argument count
 * @av: Argument vector
 * Return: Allways 0
 */

int main(int argc, char *av[])
{
	while (*av)
		printf("%s\n", *av++);
	return (0);
}
