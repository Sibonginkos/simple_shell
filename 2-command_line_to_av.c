#include <stdio.h>
#include <string.h>

/**
 * main - Entry point
 * Return: Always 0
 */

int main(void)
{
	char string[50] = "Hello! We are learning about strtok";

	/* Extract the first token */
	char *token = strtok(string, " ");
	/* loop through the string to extract all other tokens */
	while (token != NULL)
	{
		printf(" %s\n", token); /* printing each token */
		token = strtok(NULL, " ");
	}
	return (0);
}
