/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:53:33 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/17 17:03:47 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_operand(char *str, int nb_operator, int iter, int *expand)
{
	if (*str == '\0' || nb_operator >= 3 || nb_operator <= 0)
		return (-1);
	if (nb_operator == 1)
	{
		if (*(str - iter) == '>')
			return (OUTPUT);
		return (INPUT);
	}
	if (*(str - iter) == '<' && *(str - (iter - 1)) == '<')
	{
		*expand = 0;
		return (HEREDOC);
	}
	if (*(str - iter) == '>' && *(str - (iter - 1)) == '>')
		return (APPEND);
	return (-1);
}

static int	check_operand(char **str, int *is_expand)
{
	int	i;
	int	nb_op;

	if (!str && !*str)
		return (-1);
	i = 0;
	nb_op = 0;
	while (ft_isspace(**str) || **str == '<' || **str == '>')
	{
		if (**str == '<' || **str == '>')
			nb_op++;
		(*str)++;
		i++;
	}
	if (**str == '|')
		return (-1);
	return (valid_operand(*str, nb_op, i, is_expand));
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

int	handle_flow(t_tokens *token, char **input, int *mode_add, int *is_expand)
{
	int	operand;

	if (!input && !token)
		return (0);
	if (**input == '>' || **input == '<')
	{
		operand = check_operand(input, is_expand);
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
