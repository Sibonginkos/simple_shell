#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>


#if !(defined _POSIX_C_SOURCE)
typedef long int ssize_t;
#endif

/* Only include our version of getline() if the POSIX version isn't availabl */

#if !(defined _POSIX_C_SOURCE) || _POSIX_C_SOURCE < 200809L

#if !(defined SSIZE_MAX)
#define SSIZE_MAX (SIZE_MAX >> 1)
#endif

/**
 * getline - Gets line
 * @pline_buf: Line buffer
 * @pn: PN
 * @fin: Fin
 * Return: ssize_t
 */

ssize_t getline(char **pline_buf, size_t *pn, FILE *fin)
{
	const size_t INITALLOC = 16;
	const size_t ALLOCSTEP = 16;
	size_t num_read = 0;

	/* First check that none of our input pointers are NULL. */
	if ((pline_buf == NULL) || (pn == NULL) || (fin == NULL))
	{
		errno = EINVAL;
		return (-1);
	}

	/* If output buffer is NULL, then allocate a buffer. */
	if (*pline_buf == NULL)
	{
		*pline_buf = malloc(INITALLOC);
		if (*pline_buf == NULL)
		{
		/* Can't allocate memory. */
		return (-1);
		}
	else
	{
		/* Note how big the buffer is at this time. */
		*pn = INITALLOC;
	}
	}

	/* Step through the file, pulling characters until either a newline or EOF. */

	{
	int c;

	while (EOF != (c = getc(fin)))
	{
		/* Note we read a character. */
		num_read++;

		/* Reallocate the buffer if we need more room */
		if (num_read >= *pn)
		{
			size_t n_realloc = *pn + ALLOCSTEP;
			char *tmp = realloc(*pline_buf, n_realloc + 1);

			if (tmp != NULL)
			{
				/* Use the new buffer and note the new buffer size. */
				*pline_buf = tmp;
				*pn = n_realloc;
			}
			else
			{
				/* Exit with error and let the caller free the buffer. */
				return (-1);
			}

			/* Test for overflow. */
			if (*pn > SSIZE_MAX)
			{
				errno = ERANGE;
				return (-1);
			}
		}

		/* Add the character to the buffer. */
		(*pline_buf)[num_read - 1] = (char) c;

		/* Break from the loop if we hit the ending character. */
		if (c == '\n')
		{
			break;
		}
	}

	/* Note if we hit EOF. */
	if (c == EOF)
	{
		errno = 0;
		return (-1);
	}
	}

	/* Terminate the string by suffixing NUL. */
	(*pline_buf)[num_read] = '\0';

	return (ssize_t);
}

#endif
