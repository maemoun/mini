#include "main.h"

char *return_str(t_type type)
{
	if (type == PIPE)
		return (ft_strdup("|"));
	if (type == RED_IN)
		return (ft_strdup("<"));
	if (type == RED_OUT)
		return (ft_strdup(">"));
	if (type == HEREDOC)
		return (ft_strdup("<<"));
	if (type == APPEND)
		return (ft_strdup(">>"));
	return (ft_strdup(""));
}

int syntax_err(const char *msg, t_type type)
{
	write(2, "bash: ", 6);
	write(2, msg, ft_strlen(msg));
	if (type != (t_type)-1)
	{
		char *str = return_str(type);
		if (str)
		{
			write(2, " `", 2);
			write(2, str, ft_strlen(str));
			write(2, "'", 1);
			free(str);
		}
	}
	write(2, "\n", 1);
	return (258);
}

int contains_unclosed_quote(const char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			char quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (!str[i])
				return (1);
			i++;
		}
		else
			i++;
	}
	return (0);
}

int check_syntax(t_token *tokens)
{
	t_token *curr = tokens;

	if (!curr)
		return (0);

	if (curr->type == PIPE)
		return syntax_err("syntax error near unexpected token", curr->type);

	while (curr)
	{
		if (contains_unclosed_quote(curr->value))
			return syntax_err("syntax error: unclosed quote", -1);
		if (curr->type == PIPE)
		{
			if (!curr->next)
				return syntax_err("syntax error near unexpected token `newline'", -1);
			if (curr->next->type == PIPE)
				return syntax_err("syntax error near unexpected token", -1);
		}
		if (curr->type == RED_IN || curr->type == RED_OUT
			|| curr->type == APPEND || curr->type == HEREDOC)
		{
			if (!curr->next)
				return syntax_err("syntax error near unexpected token `newline'", -1);
			if (curr->next->type != WORD)
				return syntax_err("syntax error near unexpected token", curr->next->type);
		}

		curr = curr->next;
	}
	return (0);
}

