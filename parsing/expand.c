#include "main.h"

char *handle_dollar_quote(const char *str)
{
	if (str[0] == '$' && (str[1] == '\'' || str[1] == '"'))
	{
		char quote = str[1];
		int i = 2;
		int len = 0;
		while (str[i + len] && str[i + len] != quote)
			len++;
		char *res = malloc(len + 1);
		if (!res)
			return NULL;
		int j = 0;
		while (j < len)
		{
			res[j] = str[i + j];
			j++;
		}
		res[len] = '\0';
		return res;
	}
	return NULL;
}

void expand_tokens(t_token **tokens, t_data *dt, t_env *env)
{
	t_token *curr = *tokens;
	t_token *prev = NULL;

	while (curr)
	{
		if (prev && prev->type == HEREDOC)
		{
			prev = curr;
			curr = curr->next;
			continue;
		}
		if (!is_single_quoted(curr->value))
		{
			char *tmp = handle_dollar_quote(curr->value);
			if (tmp)
			{
				free(curr->value);
				curr->value = tmp;
			}
			else
			{
				char *expanded = expand_var(curr->value, dt, env);
				free(curr->value);
				curr->value = expanded;
			}
		}
		prev = curr;
		curr = curr->next;
	}
}
