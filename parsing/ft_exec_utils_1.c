/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeskhai <maeskhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:38:51 by maeskhai          #+#    #+#             */
/*   Updated: 2025/07/02 17:26:47 by maeskhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	count_cmds(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next_command;
	}
	return (count);
}

void	cleanup_pids(pid_t *pids, int count)
{
	int i;
	
	i = 0;
	while (i < count)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	free(pids);
}

int	setup_pipe(int *pipe_fd, int *prev_fd, int i, pid_t *pids)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe: too many open files");
		if (*prev_fd != -1)
		{
			close(*prev_fd);
			*prev_fd = -1;
		}
		cleanup_pids(pids, i);
		return(1);
	}
	return(0);
}