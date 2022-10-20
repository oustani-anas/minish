/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:23:57 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/20 02:42:00 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*set_upper(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			printf("%c", str[i]);
		i++;
	}
	return (str);
}

char	**export_env(t_envr *env)
{
	t_envr	*tmp;
	int		len;
	char	**exported_env;
	int		i;
	char	**forfree;

	i = 0;
	len = 0;
	tmp = env;
	exported_env = NULL;
	while (tmp && ++len)
		tmp = tmp->next;
	exported_env = malloc(sizeof(char *) * len++);
	if (!exported_env)
		return (NULL);
	add(&g_all.garbage, exported_env);
	while (env)
	{
		exported_env[i++] = env->value;
		env = env->next;
	}
	exported_env[i] = NULL;
	forfree = exported_env;
	return (forfree);
}

char	*get_path(void)
{
	t_envr	*env;

	env = g_all.envir;
	while (env)
	{
		if (ft_strstr(env->variable, "PATH"))
			return (ft_strstr(env->value, "=") + 1);
		env = env->next;
	}
	return (NULL);
}

int	size_word(char **cmd)
{
	int	i;

	i = 0;
	if (!*cmd)
		return (RETURN_ERROR);
	while (cmd[i])
		i++;
	return (i);
}
