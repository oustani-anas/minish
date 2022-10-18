/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:20:42 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/17 21:33:29 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *new_token(int type, char *value)
{
    t_token *new;
    new = (t_token *)malloc(sizeof(t_token));
    if(new != NULL)
    {
        new->type = type;
        new->content = value;
        new->next = NULL;
    }
    return(new);
}

void add_token(t_token **list, int type, char *value)
{
    t_token *begin;
    t_token *new;

    new = new_token(type, value);
    if(!*list)
    {
        *list = new;
    }
    else
    {
        begin = *list;
        while(begin->next)
            begin = begin->next;
        begin->next = new;
    }
}

int is_file_exist(char *str)
{
    
    DIR				*dir;
	struct dirent	*dp;

	if (!str)
		return (0);
	dir = opendir("/tmp");
	if (dir != NULL)
    {
		dp = readdir(dir);
		while (dp)
		{
			if (!ft_strcmp(ft_strchr(str, '.'), dp->d_name))
				return (closedir(dir), 1);
			dp = readdir(dir);
		}
    }
	closedir(dir);
	return (0);
}


char *get_file_name(char *name)
{
    if(is_file_exist(name))
        return(get_file_name(ft_strjoin(name, "_a")));
    return(name);
}