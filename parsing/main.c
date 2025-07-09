#include "main.h"

t_command   *parser(char *s, t_data *dt, t_env *env_list)
{
	t_token *tokens = NULL;
	int i = 0;

	while (s[i])
	{
		while (ft_isspace(s[i]))
			i++;
		if (!s[i])
			break;
		int start = i;
		int end = get_token_end(s, i);
		int len = end - start;
		char *val = ft_substr(s, start, len);
		if (!val)
			return NULL;
		i = end;
		int has_space = ft_isspace(s[i]);
		append_token(&tokens, new_token(val, has_space));
	}
    assign_token_types(tokens);
    if(check_syntax(tokens) == 258)
    {
        dt->exit_status = 258;
        return(NULL);
    }
    expand_tokens(&tokens, dt, env_list);
    join_tokens_with_no_space(&tokens);
    t_command *cmds = extract_all_commands(tokens);
	return (cmds);
}

int minishell(t_data *dt, t_env *env_list)
{
    char *input;
    char *line;
    int eror;
    t_command *cmd;

    while (1)
    {
        eror = 0;
        input = readline("minishell$ ");
        if (!input)
        {
            write(1, "exit", 4);
            write(1, "\n", 1);
            eror = 1;
        }
        add_history(input);
        if(eror == 0)
            line = add_spaces_around_symbols(input);
        if (eror == 0)
        {
            cmd = parser(line, dt, env_list);
            if (!cmd)
            {
                // free(); print error
                continue ;
            }
            dt->exit_status = 0;   //kan3awd n setih b 0 ila kan dakchi howa hadak//
            // print_commands(cmd);
            ft_exec_cmd(cmd, dt);
        }
        free(input);
        // ft_free_cmd(dt->cmd);
        //free linked list cmd
    }
    return(0);
}

int main(int ac, char **av, char **envp)
{
    t_data  dt;
    t_env *env_list = init_env(envp);

    (void)ac;
    (void)av;
    dt.exit_status = 0;
    ft_signals();
    minishell(&dt, env_list);
    return 0;
}
