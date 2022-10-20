/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:17:21 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/20 18:04:51 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_final	*clear_final(t_final **lst)
{
	t_final	*forfree;
	t_red	*reder;

	while ((*lst))
	{
		while ((*lst)->red)
		{
			reder = (*lst)->red;
			(*lst)->red = (*lst)->red->next;
			free(reder);
		}
		forfree = (*lst);
		(*lst) = (*lst)->next;
		free(forfree);
	}
	return (NULL);
}

void	add_red(t_red **lred, t_token *t)
{
	while (t)
	{
		if (t->type == REDIN || t->type == REDOUT
			|| t->type == HEREDOC || t->type == APPEND)
		{
			if (t->next->type == WSPACE)
			{
				add_red_back(lred, t->type, ft_strdup(t->next->next->content));
			}
			else
			{
				add_red_back(lred, t->type, ft_strdup(t->next->content));
			}
			t = t->next;
		}
		t = t->next;
	}
}

char	*add_cmd_loop(char *str, t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == WSPACE && tokens->next == NULL)
			break ;
		else if (tokens->type != REDIN && tokens->type != REDOUT
			&& tokens->type != HEREDOC && tokens->type != APPEND)
		{
			str = ft_strjoin(str, tokens->content);
			add(&g_all.garbage, str);
		}
		else
		{
			if (tokens->next->type == WSPACE)
				tokens = tokens->next;
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (str);
}

void	add_cmd(t_final **list, t_token *tokens)
{
	char	*str;
	char	**sstr;
	t_red	*red;

	str = ft_strdup("");
	add(&g_all.garbage, str);
	red = NULL;
	add_red(&red, tokens);
	str = add_cmd_loop(str, tokens);
	sstr = ft_split(str, ' ');
	add_cmd_back(list, sstr, red);
}

t_final	*parse(t_token *list)
{
	t_token	*h_cmd;
	t_final	*final;
	t_token	*cmd;

	h_cmd = list;
	cmd = NULL;
	final = NULL;
	while (h_cmd)
	{
		while (h_cmd->type != PIPE && h_cmd->next != NULL)
		{
			add_token(&cmd, h_cmd->type, h_cmd->content);
			h_cmd = h_cmd->next;
		}
		if (h_cmd->next == NULL)
			add_token(&cmd, h_cmd->type, h_cmd->content);
		add_cmd(&final, cmd);
		clean_list(&cmd);
		h_cmd = h_cmd->next;
	}
	clean_list(&h_cmd);
	clean_list(&cmd);
	return (final);
}
