#include "minishell.h"

int	main(void)
{
	if (unlink("test.tmp"))
	{
		perror("Error removing file!");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}