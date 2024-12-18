static int	handle_flow(t_tokens *token, char **input, int *mode_add)
{
	int		operand;
    int     is_file;
	t_flow	*node_flow;

	if (!input && !token)
		return (0);
    is_file = 1;
	node_flow = new_flow();
	token->token_flow = node_flow;
	// while (**input != '\0' && **input != '|')
	// {
		// while (**input != ' ')
		// 	(*input)++;
		if (**input == '>' || **input == '<')
		{
			operand = check_operand(input);
			if (operand < 0)
			{
				token->errnum = ERRFLOW;
				return (0);
			}
            store_operator(&token->token_flow, operand);
            *mode_add = 3;
		}
	// }
}