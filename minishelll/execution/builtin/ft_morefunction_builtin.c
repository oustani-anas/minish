/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_morefunction_builtin.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:23:16 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/20 02:40:34 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_is_in_env(char *arg)
{
	t_envr	*env;

	env = g_all.envir;
	while (env)
	{
		if (!ft_strcmp(env->variable, arg))
			return (0);
		env = env->next;
	}
	return (1);
}

char	*get_var(char *arg)
{
	char	*buff;
	int		i;

	i = 0;
	buff = ft_strdup("");
	if (!arg)
		return (NULL);
	while (arg[i] != '=' && arg[i])
		i++;
	buff = malloc(sizeof(char) * (i + 1));
	if (!buff)
		return (NULL);
	add(&g_all.garbage, buff);
	i = 0;
	while (arg[i] != '=' && arg[i])
	{
		buff[i] = arg[i];
		i++;
	}
	buff[i] = 0;
	return (buff);
}

int	ft_execve(char *path, char **cmd)
{
	execve(path, cmd, export_env(g_all.envir));
	check_status_exit(*cmd);
	if (errno == ENOENT || errno == EFAULT)
		return (127);
	else if (errno == EACCES)
		return (126);
	return (RETURN_ERROR);
}

int	print_cmnd(char **cmd)
{
	char	**splited_path;
	char	*path;

	signal(SIGQUIT, SIG_DFL);
	path = get_path();
	if (!path)
		splited_path = ft_split("", ':');
	else
		splited_path = ft_split(path, ':');
	if (!access(*cmd, X_OK))
		path = *cmd;
	else if (ft_strchr(*cmd, '/'))
		path = *cmd;
	else
	{	
		while (*splited_path)
		{
			path = ft_strjoin(*splited_path, ft_strjoin("/", \
			cmd[0]));
			if (!access(path, X_OK))
				break ;
			splited_path++;
		}
	}
	return (ft_execve(path, cmd));
}

void	handl_signal(int *statuss)
{
	if (WIFEXITED(statuss))
		g_all.status_sign = WEXITSTATUS(statuss);
	else if (WIFSIGNALED(statuss))
		g_all.status_sign = 128 + WTERMSIG(statuss);
}
