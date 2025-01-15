#include "minishell.h"

int	main(void)
{
	if (unlink("tmp"))
	{
		perror("Error removing file!");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}