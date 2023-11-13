#include "shell.h"

/**
 * main -  a UNIX command line interpreter
 * Return: int
*/

int main(int argc, char **argv)
{
	char *inputptr = NULL, *copy_inputptr;
	char *token = NULL;
	const char *delim = " \n";
	int num_tok = 0, i;
	bool receive_cmd = true;
	size_t x = 0;
	ssize_t num_charrd;

	(void)argc;
	
	while (receive_cmd)
	{
		print_promt();
		num_charrd = getline(&inputptr, &x, stdin);

		if (num_charrd == -1)
		{
			_printf("Exiting shell...\n");
			exit(EXIT_FAILURE);
		}

		/* copy input before using strtok*/
		copy_inputptr = malloc(sizeof(char) * num_charrd + 1);
		if (!copy_inputptr)
			return (-1);
		_strcpy(copy_inputptr, inputptr);

		/* use strtok function*/
		/* make this a function of its own*/
		token = strtok(inputptr, delim);
		while (token != NULL)
		{
			num_tok++;
			token = strtok(NULL, delim);
		}
		num_tok++;

		/* alocate a memory that point to token pointers*/
		/* make a stand alone funtion*/
		argv = malloc(sizeof(char *) * num_tok);
		if (!argv)
            {
                perror("Error: argv Memory allocation error");
                exit(EXIT_FAILURE);
            }
		token = strtok(copy_inputptr, delim);
		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * _strlen(token));
			if (!argv[i])
            {
                perror("Error: argv[i]Memory allocation error");
                exit(EXIT_FAILURE);
            }
			_strcpy(argv[i], token);
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;

		_execmd(argv);
	}
	free_dylloc(argv, num_tok);
	free(copy_inputptr);
	return (0);
}
