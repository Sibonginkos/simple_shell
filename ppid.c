#include <stdio.h>
#include <unistd.h>

/**
 * main - PPID
 *
 * Return: Always 0.
 */

int main(void)
{
	unsigned int process_id, p_process_id;

	process_id = getpid();
	p_process_id = getppid();
	printf("%d\n", process_id);
	printf("%d\n", p_process_id);
	/* echo $$ print ppid */
	return (0);
}
