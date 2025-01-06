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
	{
		store_var_element(node_token, parsing);
		return (node_token->errnum);
	}
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
	// if (node_token->token_cmd->operand == VOIDTOKEN && mode_add != 4)
	// 	mode_add = 1;
	if (mode_add == 1 && parsing != NULL)
	{
		node_token->token_cmd->cmd_str = parsing;
		if (node_token->token_cmd->operand != VOIDTOKEN && mode_add != 4)
			mode_add = 2;
	}
	// redirections (4)
	if (mode_add == 4 && node_token->token_flow != NULL && parsing != NULL)
	{
		last_redir = last_flow(node_token->token_flow);
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

void write_heredoc(char *input, int fd_tmp, int expandable)
{
    char *expand;

    expand = NULL;
    while (*input)
    {
        // Si le caractère est '$' et que l'expansion est activée
        if (*input == '$' && expandable)
        {
            // Si c'est suivi par une quote (double ou simple)
            if (*(input + 1) == '"' || *(input + 1) == '\'')
            {
                // Sauter les quotes et les autres caractères avant de continuer
                while (*input && (*input == '"' || *input == '\''))
                {
                    ft_putchar_fd(*input, fd_tmp);
                    input++;
                }
                continue; // Reprendre la boucle sans analyser le '$' de nouveau
            }
            // Expansion de la variable (si nécessaire)
            expand = handle_dollar(&input);
            if (expand != NULL)
            {
                ft_putstr_fd(expand, fd_tmp);
                free(expand);
                continue; // Passer à l'itération suivante
            }
        }

        // Cas général: si ce n'est pas un '$' ou que l'expansion n'est pas activée
        ft_putchar_fd(*input, fd_tmp);
        input++;
    }
}
