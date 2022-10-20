/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expande_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 08:42:02 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/20 17:47:53 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_globale	g_all;

void	expande_ex_status(char **cmd)
{
	*cmd = ft_itoa(g_all.status_sign);
}

void	expande_cmd(t_token **list)
{
	t_token	*data;
	int		i;

	data = *list;
	i = 0;
	while (data)
	{
		if (data->type == DOLLAR_SIGN)
			expande_dollar(&data->content);
		else if (data->type == EXIT_STATUS)
			expande_ex_status(&data->content);
		else if (data->type == WORD)
		{
			if (data->content[0] == '~' && data->content[1] == '\0')
				data->content = ft_strdup(getenv("HOME"));
		}
		data = data->next;
	}
}

void	expande_rest(char *var, char ***content)
{
	if (var[0] == '0' && var[1] == '\0')
		**content = ft_strdup("minishell");
	else if (var[0] >= '1' && var[0] <= '9' && var[1] == '\0')
		**content = ft_strdup("\0");
	else if (var[0] >= '1' && var[0] <= '9' && var[1] != '\0')
		**content = ft_strdup("\0");
	else
		**content = ft_strdup("\0");
}

void	expande_dollar(char **content)
{
	t_envr	*env;
	char	*str;
	int		i;

	i = 0;
	str = *content;
	env = g_all.envir;
	while (env)
	{
		if (!ft_strcmp(str, env->variable))
		{
			*content = ft_strstr(env->value, "=") + 1;
			break ;
		}
		else
			expande_rest(str, &content);
		env = env->next;
		i++;
	}
	if (i == 0)
		*str = '\0';
}
