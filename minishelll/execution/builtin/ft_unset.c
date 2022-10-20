/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:23:21 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/20 02:40:36 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_envr	*remove_to_env(char **cmd, t_envr *list)
{
	t_envr	*tmp;
	t_envr	*prev;

	list = g_all.envir;
	tmp = g_all.envir;
	prev = g_all.envir;
	tmp = tmp->next;
	while (*(cmd))
	{
		tmp = list->next;
		prev = list;
		while (tmp)
		{
			if (!ft_strcmp(tmp->variable, *cmd))
			{
				prev->next = tmp->next;
				break ;
			}
			tmp = tmp->next;
			prev = prev->next;
		}
		cmd++;
	}
	add(&g_all.garbage, tmp);
	return (list);
}

t_envr	*ft_unset(char **cmd)
{
	t_envr	*list;
	t_envr	*prev;

	list = g_all.envir;
	prev = g_all.envir;
	if (!list)
		return (NULL);
	if (!*(cmd + 1))
		return (list);
	else
	{
		if (!ft_strcmp(prev->variable, cmd[1]))
		{
			list = list->next;
			add(&g_all.garbage, prev);
			return (list);
		}
	}
	cmd++;
	if (!*cmd)
		return (list);
	remove_to_env(cmd, list);
	return (list);
}
