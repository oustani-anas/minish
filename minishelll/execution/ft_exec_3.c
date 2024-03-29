/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:23:39 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/20 02:41:50 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_is_pipe(t_token *list)
{
	int	i;

	i = 0;
	while (list)
	{
		if (list->type == PIPE)
			i++;
		list = list->next;
	}
	return (i);
}

void	ft_print_ign_bs(char *cmd, char *buff)
{
	int	i;
	int	cont;

	i = 0;
	cont = 0;
	while (cmd[i])
	{
		if (cmd[i] != '\\')
			buff[cont++] = cmd[i];
		else if (cmd[i++] == '\\')
			buff[cont++] = cmd[i];
		i++;
	}
}

int	check_pid(int pid)
{
	if (pid < 0)
	{
		close(g_all.fd[0]);
		close(g_all.fd[1]);
		close(g_all.fdd);
		while (1)
		{
			if (waitpid(-1, NULL, 0) == -1)
				break ;
		}
		return (ft_putstr_fd("minishell: fork: Resource temporarily \
	unavailable\n", 2), 0);
	}	
	return (1);
}
