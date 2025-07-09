#include "main.h"

static int count_args(t_token *tokens)
{
	int count = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD)
			count++;
		tokens = tokens->next;
	}
	return count;
}

static char **get_command_args(t_token **tokens)
{
	int args_count = count_args(*tokens);
	char **args = malloc(sizeof(char *) * (args_count + 1));
	if (!args)
		return NULL;

	int i = 0;
	while (*tokens && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == WORD)
		{
			args[i++] = (*tokens)->value;
			*tokens = (*tokens)->next;
		}
		else if ((*tokens)->type == RED_IN || (*tokens)->type == RED_OUT
			|| (*tokens)->type == HEREDOC || (*tokens)->type == APPEND)
		{
			*tokens = (*tokens)->next;
			if (*tokens)
				*tokens = (*tokens)->next;
		}
		else
			*tokens = (*tokens)->next;
	}
	args[i] = NULL;
	return args;
}


t_command *extract_all_commands(t_token *tokens)
{
	t_command *head = NULL;
	t_command *last = NULL;
	while (tokens)
	{
		t_command *new_cmd = malloc(sizeof(t_command));
		if (!new_cmd)
			return NULL;
		new_cmd->command = NULL;
		new_cmd->red = NULL;
		new_cmd->next_command = NULL;
		t_token *scan = tokens;
		new_cmd->command = get_command_args(&tokens);
		new_cmd->red = get_redirections(&scan);
		if (!head)
			head = new_cmd;
		else
			last->next_command = new_cmd;
		last = new_cmd;
		while (tokens && tokens->type != PIPE)
			tokens = tokens->next;
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return head;
}
