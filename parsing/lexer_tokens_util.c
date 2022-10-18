/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:36:23 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/16 09:01:04 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *inside_s_quots(t_token **list, char *line, char quot, int i)
{
    char *str;
    str = malloc(sizeof(char) * (i + 1));
    if(!str)
        return(NULL);
    if(i == 0 && *(line + 1) == '\0')
    {
        add_token(list, WORD, str);
        return(" ");
    }
    i = 0;
    while(line[i] && line[i] != quot)
    {
        str[i] = line[i];
        i++;
    }
    str[i] = '\0';
    add_token(list, WORD, str);
    return(NULL);
}

void *clean_list(t_token **list)
{
    t_token *ptr;
    
    ptr = *list;
	while((*list))
    {
    	ptr = *list;
        *list = (*list)->next;
		free(ptr);
    }
	return(NULL);
}
