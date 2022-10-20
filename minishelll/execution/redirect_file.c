/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:23:50 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/20 17:43:50 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_n_of_red(t_red *red)
{
	t_red	*tmp;
	int		i;

	i = 0;
	tmp = red;
	while (red)
	{
		i++;
		red = red->next ;
	}
	return (i);
}

int	check_red(int type, char *namefile, int *status)
{
	if (type == REDOUT)
		open_redout(namefile, status);
	else if (type == APPEND)
		open_append(namefile);
	else if (type == REDIN)
	{
		if (open_in(namefile, status) == RETURN_ERROR)
			return (RETURN_ERROR);
	}
	else if (type == HEREDOC)
	{
		if (open_herdoc_file(namefile, status) == RETURN_ERROR)
			return (RETURN_ERROR);
	}
	return (1);
}

int	check_redirecrt(t_red *red, int *status)
{
	int		len;
	t_red	*tmp;

	len = check_n_of_red(red);
	tmp = red;
	if (len > 0)
	{
		while (red)
		{
			if (check_red(red->type, red->filename, \
			status) == RETURN_ERROR)
				return (RETURN_ERROR);
			red = red->next ;
		}
	}
	return (1);
}
