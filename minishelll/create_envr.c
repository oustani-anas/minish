/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:46:52 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/19 21:36:54 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envr	*new_node_envr(char *str, char *value)
{
	t_envr	*new;

	new = (t_envr *)malloc(sizeof(t_envr));
	add(&g_all.garbage, new);
	if (new != NULL)
	{
		new->variable = str;
		new->value = value;
		new->next = NULL;
	}
	return (new);
}

void	add_new_node_envr(t_envr **list, char *variable, char *value)
{
	t_envr	*new;
	t_envr	*begin;

	new = new_node_envr(variable, value);
	if (!new)
		return ;
	if (*list == NULL)
		*list = new;
	else
	{
		begin = *list;
		while (begin->next)
			begin = begin->next;
		begin->next = new;
	}
}

void	get_3_variables(void)
{
	char	path[1024];

	getcwd(path, 1024);
	add_new_node_envr(&g_all.envir, "PATH", ft_strjoin("PATH=", PATH_STD));
	add_new_node_envr(&g_all.envir, "SHLVL", "SHLVL=1" );
	add_new_node_envr(&g_all.envir, "PWD", ft_strjoin("PWD=", path));
}

void	create_envr(char *envr[])
{
	int		i;
	char	**str;

	i = 0;
	if (!*envr)
	{
		get_3_variables();
		return ;
	}
	while (envr[i])
	{
		str = ft_split(envr[i], '=');
		add(&g_all.garbage, str);
		add_new_node_envr(&g_all.envir, *str, envr[i]);
		i++;
	}
}
