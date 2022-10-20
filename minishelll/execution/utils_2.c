/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:58:42 by akadi             #+#    #+#             */
/*   Updated: 2022/10/18 12:04:38 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_folder(char *name)
{
	DIR	*dirs;

	errno = 0;
	dirs = opendir(name);
	if (!name)
		return (RETURN_ERROR);
	if ((dirs) == NULL)
	{
		g_all.status_sign = 1;
		if (errno == 13)
			printf("permission denied\n");
		if (errno == ENOENT)
			printf("Directory does not exist\n");
		if (errno == ENOTDIR)
			printf("is not a directory\n");
		return (RETURN_ERROR);
	}
	return (1);
}

char	*create_err(char *firs_s, char *midl_s, char *last_s)
{
	char	*str;

	str = NULL;
	g_all.status_sign = 1;
	if (!firs_s)
		return (NULL);
	if (midl_s && last_s)
		str = ft_strjoin(firs_s, ft_strjoin(midl_s, last_s));
	else if (!midl_s && last_s)
		str = ft_strjoin(firs_s, last_s);
	else
		str = firs_s;
	return (str);
}

char	*ft_getcwd(void)
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	return (ft_strdup(path));
}

void	ft_pwd(void)
{
	printf("%s\n", ft_getcwd());
}

void	more_cd(char *cmd, char *path)
{
	if (chdir(cmd) == -1)
		check_folder (cmd);
	else
		change_pwd(path);
}
