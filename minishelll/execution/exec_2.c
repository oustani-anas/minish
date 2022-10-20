/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:23:28 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/20 02:41:51 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_status_file(int status)
{
	if (status)
	{
		dup2(g_all.dup_out, 1);
		close(g_all.dup_out);
	}
	else
	{
		dup2(g_all.dup_in, 0);
		dup2(g_all.dup_out, 1);
		close(g_all.dup_out);
		close(g_all.dup_in);
	}
}

void	check_status_exit(char *cmd)
{
	if (errno == ENOENT || errno == EFAULT)
		ft_putstr_fd(create_err("minishell : " \
		, cmd, ": command not found \n"), 2);
	else if (errno == EACCES)
		ft_putstr_fd(create_err("minishell : " \
		, cmd, ": : Permission denied \n"), 2);
	else
		ft_putstr_fd("error ...\n", 2);
}

int	cmd_systm_one(t_final *cmd)
{
	int	pid;
	int	status;
	int	statuss;

	pid = fork();
	status = 1;
	if (pid == 0)
	{
		if (check_redirecrt(cmd->red, &status) == RETURN_ERROR)
			exit(0);
		exit(print_cmnd(cmd->cmnd));
	}
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		if (waitpid (-1, &statuss, 0) == -1)
			break ;
	}
	check_status_file(status);
	if (WIFEXITED(statuss))
		g_all.status_sign = WEXITSTATUS(statuss);
	else if (WIFSIGNALED(statuss))
		hendl(statuss);
	return (1);
}

int	check_is_one_cmnd(t_final *cmd, t_token *list, int *status)
{
	if (get_is_pipe(list) == 0)
	{	
		g_all.dup_out = dup(1);
		if (*cmd->cmnd == NULL)
		{
			g_all.dup_in = dup(0);
			if (check_redirecrt(cmd->red, status) == RETURN_ERROR)
				return (check_status_file(*status), 1);
		}
		if (*cmd->cmnd != NULL)
		{
			if (check_builtin(*cmd->cmnd))
			{
				g_all.dup_in = dup(0);
				if (check_redirecrt(cmd->red, status) == RETURN_ERROR)
					return (check_status_file(*status), 1);
				ft_builtin(cmd->cmnd, status);
			}
			else
				cmd_systm_one(cmd);
		}
		return (check_status_file(*status), 1);
	}
	return (0);
}

void	child_process(t_final *cmd, int *status)
{
	close(g_all.fd[0]);
	if (g_all.fdd != 0)
	{
		dup2(g_all.fdd, 0);
		close(g_all.fdd);
	}
	if (cmd->next != NULL)
	{
		close(g_all.fd[0]);
		dup2(g_all.fd[1], 1);
	}
	close(g_all.fd[1]);
	is_red(cmd->red, status);
	if (check_builtin(*(cmd->cmnd)))
	{
		if (g_all.status_sign == 127)
			g_all.status_sign = 1;
		else
			g_all.status_sign = 0;
		ft_builtin(cmd->cmnd, status);
		exit(1);
	}
	else
		exit(print_cmnd(cmd->cmnd));
}
