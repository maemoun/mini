/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeskhai <maeskhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:39:00 by maeskhai          #+#    #+#             */
/*   Updated: 2025/07/02 17:27:44 by maeskhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_is_builtin(char **command)
{
	return((!ft_strcmp(command[0], "cd") || !ft_strcmp(command[0], "echo") 
					|| !ft_strcmp(command[0], "pwd") || !ft_strcmp(command[0], "export") 
					|| !ft_strcmp(command[0], "unset")
					|| (!ft_strcmp(command[0], "env") && command[1] == NULL)));
}

int	is_builtin_bo_pipe(t_command *cmd_2, int its_pipe)
{
	if (cmd_2->command && cmd_2->command[0] && ft_is_builtin(cmd_2->command) && !its_pipe)
		return(1);
	return(0);
}

int	save_stdio(int *saved_stdout, int *saved_stdin)
{
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout == -1)
		return (1);
	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin == 1)
	{
		close(*saved_stdout);
		return (1);
	}
	return (0);
}

int	exec_builtin_parent(t_command *cmd_2, t_data *dt, pid_t *pids)
{
	int saved_stdout;
	int saved_stdin;

	if (save_stdio(&saved_stdout, &saved_stdin))
		return(free(pids), perror("dup"), 1);
	// if (ft_handle_redirct(cmd_2->red))
	// {
	// 	close(saved_stdout);
	// 	close(saved_stdin);
	// 	free(pids);
	// 	return (dt->exit_status = 1);
	// }
	//not complete
	return 0;
}