/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_herdoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 02:05:28 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/20 18:07:09 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*return_del(char *str)
{
	char	*del;
	int		i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	del = (char *)malloc(sizeof(char) * i + 1);
	if (!del)
		return (NULL);
	add(&g_all.garbage, del);
	i = 0;
	while (str[i])
	{
		del[i] = str[i];
		i++;
	}
	del[i] = '\0';
	add(&g_all.garbage, str);
	return (del);
}

char	*loop_herdoc(char *buff, char *content, char *h_line)
{
	while (1)
	{
		h_line = readline("> ");
		add(&g_all.garbage, h_line);
		if (!h_line || !ft_strcmp(h_line, content))
			break ;
		else
		{
			buff = ft_strjoin(buff, ft_strjoin(h_line, "\n"));
			add(&g_all.garbage, buff);
		}
	}
	return (buff);
}

void	start_herdoc(char ***content, int *type)
{
	char	*buff;
	char	*file;
	char	*h_line;
	int		fd;

	**content = return_del(ft_strtrim(**content, " "));
	buff = ft_strdup("");
	add(&g_all.garbage, buff);
	h_line = NULL;
	buff = loop_herdoc(buff, **content, h_line);
	file = get_file_name(ft_strjoin("/tmp/.herdooc", ft_itoa(g_all.n_h)));
	add(&g_all.garbage, file);
	**content = file;
	fd = open(**content, O_CREAT | O_RDWR | O_TRUNC, 0644);
	*type = WORD;
	ft_putstr_fd(buff, fd);
	close(fd);
}

int	begin_herdoc(char **content, int *type)
{
	static int	h;

	h = 1;
	h++;
	g_all.n_h = h;
	start_herdoc(&content, type);
	return (1);
}
