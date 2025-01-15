/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:42:48 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/15 11:11:49 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		if (array[i] != NULL)
			free(array[i]);
		i++;
	}
	free(array);
}

void	clean_up_exit(int n_exit)
{
	t_data_env	*data;

	restore_stdio(get_stdin_dup(), get_stdout_dup());
	clean_tokens(get_first_token());
	clear_export_env();
	data = get_data_env();
	clean_env(&data);
    close(get_stdin_dup());
    close(get_stdout_dup());
    close(0);
    close(1);
	exit(n_exit);
}
