/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:17:21 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/17 13:09:35 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void add_red(t_red **lred, t_token *t)
{
    while(t)
    {
		if(t->type != REDIN && t->type != REDOUT
			&& t->type != HERDOC && t->type != APPEND)
		{
			if(t->next->type == 1)
			{
				add_red_back(lred, t->next->next->type, ft_strdup(t->next->next->content));
			}
			else
			{
				add_red_back(lred, t->next->type, ft_strdup(t->next->content));
			}
			t = t->next;
		}
		t = t->next;
    }
}

void add_cmd(t_final **list, t_token *tokens)
{
    char *str;
    char **sstr;
    t_red *red;

    str = strdup("");
    red = NULL;
    add_red(&red, tokens);
	while(tokens)
	{
		if(tokens->type == WSPACE && tokens->next == NULL)
			break;
		else if(tokens->type != REDIN && tokens->type != REDOUT
			&& tokens->type != HERDOC && tokens->type != APPEND)
		{
			str = ft_strjoin(str, tokens->content);//str != reds
		}
		else
		{
			if(tokens->next->type == WSPACE)
				tokens = tokens->next;
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	sstr = ft_split(str, ' ');
	add_cmd_back(list, sstr, red);
}

t_final *parse(t_token *list)
{
    t_token *h_cmd;
    t_token *cmd;
    t_final *final;

    h_cmd = list;
    cmd = NULL;
    final = NULL;
    
    while(h_cmd)
    {
        if(h_cmd->type != PIPE && h_cmd->next != NULL)
        {
            add_token(&cmd, cmd->type, cmd->content);
            h_cmd = h_cmd->next;
        }
        add_cmd(&final, cmd);
		clean_list(&h_cmd);
		h_cmd = h_cmd->next;
    }
	clean_list(&h_cmd);
	clean_list(&cmd);
    return(final);
}