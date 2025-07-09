/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_herdoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeskhai <maeskhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:01:57 by maeskhai          #+#    #+#             */
/*   Updated: 2025/07/02 17:28:57 by maeskhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	ft_write_heredoc_loop(int fd, char *name, t_data *dt)
{
	char	*line;
	char	*tmp;
	
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (ft_strcmp(line, name) == 0)
		{
			free(line);
			break;
		}
		//tmp = expand_heredoc(line, dt);
		if (tmp)
		{
			write(fd, tmp, ft_strlen(tmp));
			write(fd, "\n", 1);
			free(tmp);
		}
		else
			return (free(line), 1);
		free(line);
	}
	return(0);
}

static void	ft_child_process_heredoc(char *file_name, char *name, t_data *dt)
{
	int	fd;
	
	signal(SIGINT, SIG_DFL);
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("heredoc open");
		exit(1);
	}
	if (ft_write_heredoc_loop(fd, name, dt))
		free(file_name);
	close(fd);
	exit(0);
}

static int	ft_parent_process_heredoc(int pid, char *file_name, t_data *dt)
{
	waitpid(pid, &dt->exit_status, 0);
	signal(SIGINT, ctlc_handler);
	if (WIFSIGNALED(dt->exit_status) && WTERMSIG(dt->exit_status) == SIGINT)
	{
		free(file_name);
		return(0);
	}
	return(1);
}

static char	*ft_creat_herdoc_content(char *name, t_data *dt)
{
	char	*file_name;
	int		pid;
	
	ft_change_global(1);
	file_name = ft_strdup("/tmp/.heredoc_tmp.txt");
	if (!file_name)
		return(perror("Herdoc file name"), NULL);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return(free(file_name), NULL);
	}
	if (pid == 0)
		ft_child_process_heredoc(file_name, name, dt);
	if (!ft_parent_process_heredoc(pid, file_name, dt))
		return (NULL);
	return(file_name);
}

int	ft_check_heredoc(t_command *cmd, t_data *dt)
{
	t_command		*cmd_2;
	t_redirection	*redirect;
	char			*file_name;

	cmd_2 = cmd;
	while (cmd_2)
	{
		redirect = cmd_2->red;
		while (redirect)
		{
			if (redirect->type == RED_HEREDOC)
			{
				file_name = ft_creat_herdoc_content(redirect->name, dt);
				ft_change_global(0);
				if (!file_name)
					return(1);
				free(redirect->name);
				redirect->name = file_name;
			}
			redirect = redirect->next_red;
		}
		cmd_2 = cmd_2->next_command;
	}
	return(0);
}