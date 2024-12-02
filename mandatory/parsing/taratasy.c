t_tokens	**store_instruction(char *input)
{
	int			is_cmd;
	t_tokens	*node_token;
	t_tokens	**first_node;
	t_cmd		*node_cmd;

	is_cmd = 0;
	first_node = malloc(sizeof(t_tokens *));
	if (!first_node)
		return (NULL);
	node_token = new_token();
	*first_node = node_token;
	if (!node_token)
		return (NULL);
	while (*input)
	{
		while (*input == ' ')
			input++;
		if (*input != ' ' && *input != '\0')
		{
			if (!is_cmd)
			{
				node_cmd = new_cmd();
				node_cmd->cmd_str = parse_input(&input);
				if (!node_cmd->cmd_str)
					node_cmd->errnum = UNQUOTES;
				node_token->token_cmd = node_cmd;
				is_cmd = 1;
			}
			else
				addback_arg(&node_token->token_arg, parse_input(&input));
		}
		if (*input == '|')
		{
			node_token = new_token();
			if (!node_token)
				return (NULL);
			addback_token(first_node, node_token);
			is_cmd = 0;
			input++;
		}
	}
	printf("cmd: %s\n", (*first_node)->token_cmd->cmd_str);
	// printf("number of node: %d\n", count_token(*first_node));
	// printf("arg: %s\n", (*first_node)->token_arg->arg_str);
	// printf("arg2: %s\n", (*first_node)->token_arg->next_arg->arg_str);
	return (first_node);
}