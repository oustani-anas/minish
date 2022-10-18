/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 19:00:09 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/17 13:50:04 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_final	*new_cmd(char **content, t_red *red)
{
	t_final	*new;

	new = (t_final *)malloc(sizeof(t_final));
	if (new != NULL)
	{
		new->red = red;
		new->cmnd = content;
		new->next = NULL;
	}
	return (new);
}

void	add_cmd_back(t_final **list, char **content, t_red *red)
{
	t_final	*begin;
	t_final	*new;

	new = new_cmd(content, red);
	if (!*list)
	{
		*list = new;
	}
	else
	{
		begin = *list;
		while (begin->next)
			begin = begin->next;
		begin->next = new;
	}
}
