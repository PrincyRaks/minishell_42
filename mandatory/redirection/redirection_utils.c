/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:12:44 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/03 16:01:25 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_errflow(t_flow *flow)
{
    if (!flow)
        return (0);
    while (flow != NULL)
    {
        if (flow->operand == NOTOP || flow->operand == VOIDTOKEN)
            return (1);
        if (flow->operand != NOTOP && flow->operand != VOIDTOKEN 
            && !flow->word)
            return (1); 
        flow = flow->next_flow;
    }
    return (0);
}

// pour un flow
// void    execute_typeflow(t_flow  *flows, t_tokens *token)
// {
// 	while (flows != NULL)
// 	{

// 		if (flows->operand == OUTPUT)
// 		{
// 			apply_redirection(token);
// 		}
// 		// else if (flows->operand == APPEND)
// 		//     apply_append_redirection(token);
// 		// else if (flows->operand == INPUT)
// 		//     apply_input_redirection(token);
// 		flows = flows->next_flow;
// 	}
// }

// pour un token
void	execute_redirection(t_flow	*flows)
{
	// t_flow	*first_flow;

    if (!flows)
        return ;
    // first_flow = flows;
    if (check_errflow(flows))
    {
        print_errnum(ERRFLOW);
        return ;
    }
    while (flows != NULL && flows->operand != HEREDOC)
        flows = flows->next_flow;
    if (!flows)
    {
        printf("pas de heredoc\n");
        // execute_typeflow(first_flow);
        return ;
    }
    else if (flows != NULL && flows->operand == HEREDOC)
    {
        // printf("misy heredoc\n");
        open_heredoc(flows);
        if (flows->next_flow != NULL)
            execute_redirection(flows->next_flow);
            // printf("bola mitohy apres heredoc\n");
            // recurssive of function execute_redirection avec argument flows->next_flow 
    }
}
