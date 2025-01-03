/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:42:48 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/03 09:36:37 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_array(char **array) {
    int i;

    if (!array)
        return;
    i = 0;
    while (array[i]) 
	{
        // free(array[i]);
        i++;
    }
    free(array);
}

// clean_minishell(t_tokens *token)
// {
// 	clean_tokens(token);
// 	// tokens
// 	// env
// 	// valuer de retour
// }