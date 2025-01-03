/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:12:44 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/23 21:11:51 by mrazanad         ###   ########.fr       */
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
void	execute_redirection(t_tokens *token)
{
	t_flow	*flows;
	t_flow	*first_flow;

    if (!token || !token->token_flow)
        return ;
    // first_flow = flows;
    flows = token->token_flow;
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
            printf("bola mitohy apres heredoc\n");
            // recurssive of function execute_redirection avec argument flows->next_flow 
    }
}
