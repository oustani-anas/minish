/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:37:31 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/20 18:09:49 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*inside_quots(t_token **list, char *line, char quot, int j)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (j + 1));
	add(&g_all.garbage, str);
	if (!str)
		return (NULL);
	if (j == 0 && *(line + 1) == '\0')
	{
		add_token(list, WORD, str);
		return (" ");
	}
	i = j;
	j = 0;
	while (line[j] && j < i)
	{
		str[j] = line[j];
		j++;
	}
	str[j] = 0;
	check_in_quot(str, list, quot);
	return (NULL);
}

char	*check_double_quot(t_token **list, char *line, char quot)
{
	int	i;

	i = 0;
	if (*line == quot)
	{
		line++;
		if (ft_strchr(line, quot))
		{
			while (line[i] != quot)
				i++;
			inside_quots(list, line, quot, i);
			return (ft_strchr(line, quot));
		}
		else
			return (ft_putstr_fd("minishell: Missing quote\n", 2), NULL);
	}
	return (line);
}

char	*check_single_quot(t_token **list, char *line, char quot)
{
	int	i;

	i = 0;
	if (*line == quot)
	{
		++line;
		if (ft_strchr(line, quot))
		{
			while (line[i] != quot)
				i++;
			inside_s_quots(list, line, quot, i);
			return (ft_strchr(line, quot));
		}
		else
			return (ft_putstr_fd("minishell: Missing quote\n", 2), NULL);
	}
	return (line);
}
