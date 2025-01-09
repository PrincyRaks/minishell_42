#include "minishell.h"

static int	store_token(t_tokens *node_token, char **input)
{
	static int	mode_add = 1;
	char		*parsing;
	t_flow		*last_redir;

	// commandes (1)
	if (!node_token->token_cmd)
	{
		node_token->token_cmd = new_cmd();
		mode_add = 1;
	}
	parsing = parse_input(node_token, input, &mode_add);
	if (!parsing)
		return (node_token->errnum);
	// commande in variable (3)
	if (mode_add == 3)
		return (store_var_element(node_token, parsing, &mode_add));
	// arguments (2)
	if (valid_arguments(node_token, mode_add, parsing))
		return (store_parse_argument(node_token, parsing));
	if (mode_add == 1 && parsing != NULL)
		return (store_parse_cmd(node_token, parsing, &mode_add));
	// redirections (4)
	if (mode_add == 4 && node_token->token_flow != NULL && parsing != NULL)
	{
		last_redir = last_flow(node_token->token_flow);
		// veririfier si heredoc peut faire un parsing du $variable ou non
		set_expandable_var_heredoc(node_token, last_redir);
		last_redir->word = parsing;
		if (node_token->token_cmd != NULL && (node_token->token_cmd->cmd_str == NULL 
			|| node_token->token_cmd->operand == VOIDTOKEN))
			mode_add = 1;
		else if (node_token->token_cmd != NULL && node_token->token_cmd->operand == NOTOP)
			mode_add = 2;
		return (node_token->errnum);
	}
	return (node_token->errnum);
}


t_tokens	**store_instruction(char *input)
{
	t_tokens	*node_token;
	t_tokens	**first_node;
	char		*new_input;

	first_node = malloc(sizeof(t_tokens *));
	if (!first_node)
		return (NULL);
	node_token = new_token();
	*first_node = node_token;
	if (!node_token)
		return (NULL);
	while (*input && node_token->errnum == DEFAULT)
	{
		while (*input == ' ')
			input++;
		if (*input != ' ' && *input != '\0' && *input != '|' 
			&& store_token(node_token, &input) != DEFAULT)
		{
			print_errnum(node_token->errnum);
			break ;
		}
		if (*input == '|')
		{
			input++;
			while (*input == ' ')
				input++;
			if (*input == '\0')
			{
				new_input = readline("> ");
				while (new_input && *new_input == '\0')
					new_input = readline("pipe▷ ");
				if (!new_input)
				{
					clean_tokens(first_node);
					return (NULL);
				}
				input = new_input;
			}
			if (!create_new_token(first_node, &node_token))
				break ;
		}
	}
	parse_heredoc(*first_node);
	return (first_node);
}
