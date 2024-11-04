
char	*trim_doubquotes(char *str)
{
	char	**tab;
	char	*result;
	int		i;

	tab = ft_split(str, '"');
	if (!tab)
		return (NULL);
	i = -1;
	result = ft_calloc(1, sizeof(char));
	if (!result)
		return (NULL);
	while (tab[++i] != NULL)
		result = ft_strjoin(result, tab[i]);
	free_table((void**)tab);
	return (result);
}

char	*trim_simplequotes(char *str)
{
	char	**tab;
	char	*result;
	int		i;

	tab = ft_split(str, '\'');
	if (!tab)
		return (NULL);
	i = -1;
	result = ft_calloc(1, sizeof(char));
	if (!result)
		return (NULL);
	while (tab[++i] != NULL)
		result = ft_strjoin(result, tab[i]);
	free_table((void **)tab);
	return (result);
}

char	*rrrrr(char **start_quotes)
{
	int		is_close;
	char	*result;
	int		len;
	char	*start;

	len = 0;
	is_close = 0;
	start = *start_quotes;
	while (**start_quotes && is_close < 2)
	{
		if (**start_quotes == '\'')
			is_close++;
		if (**start_quotes != '\'')
			len++;
		(*start_quotes)++;
	}
	if (len == 0)
		return (ft_strdup(""));
	result = ft_substr(*start_quotes, 0, len);
	return (result);
}

int	what_quotes(char *str)
{
	while (*str)
	{
		if (*str == '\'')
			return (1);
		if (*str == '"')
			return (2);
		str++;
	}
	return (0);
}
