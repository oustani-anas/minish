/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:23:06 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/20 02:40:50 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_is_valid_var(char *arg, int is_egal)
{
	while (*arg)
	{
		if (is_egal)
		{
			if (!ft_isalnum(*arg) && (*arg != '_'))
				return (-2);
		}
		if (!ft_isalnum(*arg) && (*arg != '_' && *arg != '+'))
			return (-1);
		arg++;
	}
	return (1);
}

void	add_new_var_env(char *var, char *val)
{
	char	*temp_var;

	if (!val)
		temp_var = var;
	else
		temp_var = ft_strdup(ft_strjoin(ft_strjoin(var, "="), val));
	add_new_node_envr(&g_all.envir, ft_strdup(var), temp_var);
}

void	update_var_env(char *var, char *val, int is_append)
{
	char	*temp_var;
	t_envr	*env;

	env = g_all.envir;
	if (!val)
		temp_var = var;
	else
		temp_var = ft_strdup(ft_strjoin(ft_strjoin(var, "="), val));
	if (!ft_strstr(temp_var, "="))
		return ;
	while (env)
	{
		if (!ft_strcmp(env->variable, var))
		{
			if (is_append)
				env->value = ft_strjoin(env->value, val);
			else
				env->value = temp_var;
			break ;
		}
		env = env->next;
	}
}

int	checkappend(char *cmd)
{
	int	i;

	i = 0;
	while (*cmd)
	{
		if (*cmd == '+' && *(cmd + 1) == '=')
			return (1);
		cmd++;
	}
	return (0);
}

int	err_arg(char **cmd)
{
	if (!*cmd)
		return (1);
	while (*cmd)
	{
		if ((*cmd[0] < 'a' || *cmd[0] > 'z') && \
		(*cmd[0] < 'A' || *cmd[0] > 'Z'))
			return (1);
		cmd++;
	}
	return (0);
}
