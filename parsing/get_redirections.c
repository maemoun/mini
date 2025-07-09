#include "main.h"

static t_redirection *create_redirection(t_token *red_token, t_token *file_token)
{
	t_redirection *new_red = malloc(sizeof(t_redirection));
	if (!new_red)
		return NULL;

	if (red_token->type == RED_IN)
		new_red->type = INPUT;
	else if (red_token->type == RED_OUT)
		new_red->type = OUTPUT;
	else if (red_token->type == HEREDOC)
		new_red->type = RED_HEREDOC;
	else
		new_red->type = RED_APPEND;

	new_red->name = file_token->value;
	new_red->next_red = NULL;
	if (new_red->type == RED_HEREDOC)
	{
		if (file_token->has_quote)
			new_red->expand_variable = 0;
		else
			new_red->expand_variable = 1;
	}
	return new_red;
}

static void append_redirection(t_redirection **head, t_redirection **last, t_redirection *new_red)
{
	if (!*head)
		*head = new_red;
	else
		(*last)->next_red = new_red;
	*last = new_red;
}

t_redirection *get_redirections(t_token **tokens)
{
	t_redirection *head = NULL;
	t_redirection *last = NULL;
	t_token *tmp = *tokens;

	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == RED_IN || tmp->type == RED_OUT || tmp->type == HEREDOC || tmp->type == APPEND)
		{
			t_token *file_token = tmp->next;
			if (!file_token)
				break;

			t_redirection *new_red = create_redirection(tmp, file_token);
			if (!new_red)
				return NULL;

			append_redirection(&head, &last, new_red);

			tmp = file_token->next;
		}
		else
			tmp = tmp->next;
	}
	return head;
}
