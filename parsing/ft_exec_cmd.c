/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeskhai <maeskhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:58:57 by maeskhai          #+#    #+#             */
/*   Updated: 2025/07/02 17:22:05 by maeskhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	process_cmd(t_command *cmd_2, t_data *dt, int *pipe_fd, int *prev_fd)
{
	int	its_pipe;

	its_pipe = (cmd_2->next_command != NULL);
	if (its_pipe && setup_pipe(pipe_fd, prev_fd, dt->index_cmd, dt->pids))
		return (1);
	// if (is_builtin_no_pipe(cmd_2, its_pipe))
		//return(exec_builtin_parent(cmd_2, dt, dt->pids));
		return (0);
}

static int	init_exec_data(t_command *cmd, t_data *dt)
{
	int	count_cmd;

	if (ft_check_heredoc(cmd, dt))
		return(1);
	count_cmd = count_cmds(cmd);
	dt->pids = malloc(sizeof(pid_t) * count_cmd);
	if (!dt->pids)
		return(1);
	dt->index_cmd = 0;
	return (0);
}

static void	init_vars_exec_cmd(int *pip_0, int *pip_1, int *prev_fd)
{
	*pip_0 = -1;
	*pip_1 = -1;
	*prev_fd = -1;
}

int ft_exec_cmd(t_command *cmd, t_data *dt)
{
	int			pipe_fd[2];
	t_command	*cmd_2;

	init_vars_exec_cmd(&pipe_fd[0], &pipe_fd[1], &dt->prev_fd);
	if (init_exec_data(cmd, dt))
		return(dt->exit_status = 1);
	cmd_2 = cmd;
	while (cmd_2)
	{
		if (process_cmd(cmd_2, dt, pipe_fd, &dt->prev_fd))
			return (dt->exit_status = 1);
	}
	return(0);
}