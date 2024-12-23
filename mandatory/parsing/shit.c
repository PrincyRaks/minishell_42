
static void	handle_var(char **input, char **result, t_tokens *token,
		int mode_add)
{
	char	*expand;

	if (*(*input + 1) == '"' || *(*input + 1) == '\'')
	{
		(*input)++;
		return ;
	}
	expand = handle_dollar(input);
	if (!ft_strlen(*result) && !expand && (**input == ' ' || **input == '\0'
			|| **input == '|'))
	{
		if (mode_add == 1)
			token->token_cmd->operand = VOIDTOKEN;
		else
			last_arg(token->token_arg)->operand = VOIDTOKEN;
	}
	if (!expand)
		expand = ft_calloc(1, sizeof(char));
	*result = concat_str(*result, expand);
}

char	*parse_input(t_tokens *token, char **input, int *mode_add)
{
	char	*result;

	if (!token)
		return (NULL);
	result = ft_calloc(1, sizeof(char));
	while (**input != ' ' && **input != '\0' && **input != '|')
	{
		if (**input == '"' && !handle_doubquotes(input, &result, token))
			return (NULL);
		if (**input == '\'' && !handle_onequotes(input, &result, token))
			return (NULL);
		if (is_char(**input))
		{
			result = concat_str(result, ft_substr(*input, 0, 1));
			(*input)++;
		}
		if (**input == '$')
			handle_var(input, &result, token, *mode_add);
		if ((**input == '>' || **input == '<') && !handle_flow(token, input, mode_add))
			return (NULL);
	}
	if (*mode_add == 1 && token->token_cmd->operand == VOIDTOKEN
		&& ft_strlen(result) > 0)
		token->token_cmd->operand = NOTOP;
	else if (token->token_arg != NULL && *mode_add == 2
		&& last_arg(token->token_arg)->operand == VOIDTOKEN
		&& ft_strlen(result) > 0)
		last_arg(token->token_arg)->operand = NOTOP;
	return (result);
}


static int	store_token(t_tokens *node_token, char **input)
{
	static int	mode_add = 1;
	char		*parsing;

	// commandes (1)
	if (!node_token->token_cmd)
	{
		node_token->token_cmd = new_cmd();
		mode_add = 1;
	}
	parsing = parse_input(node_token, input, &mode_add);
	if (!parsing)
		return (node_token->errnum);
	// arguments (2)
	if (node_token->token_cmd != NULL && mode_add == 2 
		&& node_token->token_cmd->operand == NOTOP && parsing != NULL)
	{
		if (!node_token->token_arg)
			node_token->token_arg = new_arg();
		else if (last_arg(node_token->token_arg)->operand != VOIDTOKEN)
			last_arg(node_token->token_arg)->next_arg = new_arg();
		last_arg(node_token->token_arg)->arg_str = parsing;
		return (node_token->errnum);
	}
	if (node_token->token_cmd->operand == VOIDTOKEN && mode_add != 4)
		mode_add = 1;
	if (mode_add == 1)
	{
		node_token->token_cmd->cmd_str = parsing;
		mode_add = 2;
	}
	// redirections (4)
	if (mode_add == 4 && node_token->token_flow != NULL && parsing != NULL)
	{
		last_flow(node_token->token_flow)->word = parsing;
		if (node_token->token_cmd != NULL && (node_token->token_cmd->cmd_str == NULL 
			|| node_token->token_cmd->operand == VOIDTOKEN))
			mode_add = 1;
		else if (node_token->token_cmd != NULL && node_token->token_cmd->operand == NOTOP)
			mode_add = 2;
		return (node_token->errnum);
	}
	return (node_token->errnum);
}