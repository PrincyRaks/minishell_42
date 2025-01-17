/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:42:48 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/17 15:15:56 by mrazanad         ###   ########.fr       */
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

void	free_node_tmp(t_data_env *node)
{
	free(node->key);
	free(node);
}

void	clean_up_exit(int n_exit)
{
	t_data_env	*data;

	clean_tokens(get_first_token());
	clear_export_env();
	data = get_data_env();
	clean_env(&data);
	close(0);
	close(1);
	restore_stdio(get_stdin_dup(), get_stdout_dup());
	exit(n_exit);
}
