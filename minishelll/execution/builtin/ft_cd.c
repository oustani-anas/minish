/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:23:01 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/20 02:40:19 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	push_the_env(int status_pwd, int status_old, char *last_final)
{
	if (status_pwd)
		add_new_node_envr(&g_all.envir, ft_strdup("PWD"), \
				ft_strdup(ft_strjoin("PWD=", ft_getcwd())));
	if (status_old && last_final != NULL)
		add_new_node_envr(&g_all.envir, ft_strdup("OLDPWD"), \
				ft_strdup(ft_strjoin("OLDPWD=", last_final)));
}

void	change_pwd(char *last_final)
{
	t_envr	*env;
	bool	status_old;
	bool	status_pwd;

	status_old = true;
	status_pwd = true;
	env = g_all.envir;
	while (env)
	{
		if (!ft_strcmp(env->variable, "PWD"))
		{
			env->value = ft_strdup(ft_strjoin("PWD=", ft_getcwd()));
			status_pwd = false;
		}
		if (!ft_strcmp(env->variable, "OLDPWD") && last_final != NULL)
		{
			env->value = ft_strdup(ft_strjoin("OLDPWD=", last_final));
			status_old = false;
		}
		env = env->next;
	}
	push_the_env(status_pwd, status_old, last_final);
}

void	ft_cd(char **cmd)
{
	char	*this_path;

	this_path = ft_getcwd();
	if (*(cmd + 1) != NULL )
	{
		if (!ft_strcmp(*(cmd + 1), "."))
		{
			if (chdir(this_path) == -1)
				ft_putstr_fd(MESSAGE_FOLDER, 2);
			return ;
		}
	}
	if (*cmd && (*(cmd + 1) == NULL || !ft_strcmp(*(cmd + 1), "~")))
	{
		chdir(getenv("HOME"));
		change_pwd(this_path);
	}
	else if (*cmd && *(cmd + 1)[0] == '-')
		check_switch_cd();
	else
	{
		more_cd(*(cmd + 1), this_path);
	}
}
