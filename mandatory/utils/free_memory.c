/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:42:48 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/13 14:30:42 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_array(char **array) {
    int i;

    if (!array)
        return;
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

	clean_tokens(get_first_token());
	clear_export_env();
	data = get_data_env();
	clean_env(&data);
	exit(n_exit);
}
