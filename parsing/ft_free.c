/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeskhai <maeskhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:44:53 by maeskhai          #+#    #+#             */
/*   Updated: 2025/07/02 13:16:44 by maeskhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_free_red(t_redirection *red)
{
	t_redirection	*tmp;

	while (red)
	{
		tmp = red->next_red;
		free(red->name);
		free(red);
		red = tmp;
	}
}

void	ft_free_cmd(t_command *cmd)
{
	t_command	*tmp;
	int			i;
	
	while (cmd)
	{
		tmp = cmd->next_command;
		if (cmd->command)
		{
			i = 0;
			while (cmd->command[i])
				free(cmd->command[i++]);
			free(cmd->command);
		}
		ft_free_red(cmd->red);
		free(cmd);
		cmd = tmp;
	}
}