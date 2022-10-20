/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_cheker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:23:44 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/20 17:40:23 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_error_fd(void)
{
	ft_putstr_fd(create_err("No such file or directory\n", NULL, NULL), 2);
}

void	open_redout(char *filename, int *status)
{
	g_all.w_out = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (g_all.w_out == -1)
	{
		handle_error_fd();
		return ;
	}
	*status = 0;
	dup2(g_all.w_out, 1);
	close(g_all.w_out);
}

void	open_append(char *filename)
{
	g_all.w_out = open(filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (g_all.w_out == -1)
	{
		dup2(g_all.dup_out, 1);
		close(g_all.w_out);
		handle_error_fd();
		return ;
	}
	dup2(g_all.w_out, 1);
	close(g_all.w_out);
}

int	open_in(char *filename, int *status)
{
	(void) status;
	g_all.r_in = open(filename, O_RDONLY, 0644);
	if (g_all.r_in == -1)
	{
		handle_error_fd();
		return (RETURN_ERROR);
	}
	*status = 0;
	dup2(g_all.r_in, 0);
	close(g_all.r_in);
	return (1);
}

int	open_herdoc_file(char *filename, int *status)
{
	(void) status;
	g_all.r_in = open(filename, O_RDONLY, 0644);
	if (g_all.r_in == -1)
	{
		handle_error_fd();
		return (RETURN_ERROR);
	}
	unlink(filename);
	*status = 0;
	dup2(g_all.r_in, 0);
	close(g_all.r_in);
	return (1);
}
