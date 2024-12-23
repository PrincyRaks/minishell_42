/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:53:33 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/23 16:25:07 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_operand(char **str)
{
	int	nb_op;
    int i;

	if (!str && !*str)
		return (-1);
	nb_op = 0;
    i = 0;
	while (**str == ' ' || **str == '<' || **str == '>')
	{
		if (**str == '<' || **str == '>')
			nb_op++;
        (*str)++;
        i++;
	}
	if (nb_op >= 3 || nb_op <= 0)
		return (-1);
	if (nb_op == 1)
	{
		if (*(*str - i) == '>')
			return (OUTPUT);
		return (INPUT);
	}
	if (*(*str - i) == '<' && *(*str - (i - 1)) == '<')
		return (HEREDOC);
	if (*(*str - i) == '>' && *(*str - (i - 1)) == '>')
		return (APPEND);
	return (-1);
}

static void	store_operator(t_flow **node_flow, int operator)
{
	t_flow	*new;

	if (!*node_flow)
		return ;
	if ((*node_flow)->operand == NOTOP)
	{
		(*node_flow)->operand = operator;
		return ;
	}
	new = new_flow();
	new->operand = operator;
	addback_flow(node_flow, new);
}

int	handle_flow(t_tokens *token, char **input, int *mode_add)
{
	int	operand;

	if (!input && !token)
		return (0);
	if (**input == '>' || **input == '<')
	{
		operand = check_operand(input);
		if (operand < 0)
		{
			token->errnum = ERRFLOW;
			return (0);
		}
		if (!token->token_flow)
			token->token_flow = new_flow();
		store_operator(&token->token_flow, operand);
		*mode_add = 4;
	}
	return (1);
}
