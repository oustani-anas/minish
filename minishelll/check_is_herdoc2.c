/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_hedoc2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:19:03 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/19 17:22:20 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*verify(t_token *list)
{
	t_token	*token;
	char	*buff;

	token = list;
	buff = ft_strdup("");
	add(&g_all.garbage, buff);
	if (token->type == WSPACE)
		token = token->next;
	while (token)
	{
		if (token->type == WSPACE)
			break ;
		if (token->type == DOLLAR_SIGN)
			buff = ft_strjoin(buff, ft_strjoin("$", token->content));
		else
		{
		buff = ft_strjoin(buff, token->content);
			add(&g_all.garbage, buff);
		}
		token->content = ft_strdup("\0");
		token->type = 1;
		token = token->next;
	}
	return (buff);
}

void	check_is_herdoc(t_token **list)
{
	t_token	*str;

	str = *list;
	while (str)
	{
		if (str->type == HEREDOC && str->next != NULL)
		{
			if (str->next->type == WSPACE && str->next->next != NULL)
			{
				str->next->next->content = verify(str->next);
				begin_herdoc(&str->next->next->content, &str->next->next->type);
			}
			else
			{
				str->next->content = verify(str->next);
				begin_herdoc(&str->next->content, &str->next->type);
			}
		}
		str = str->next;
	}
}
