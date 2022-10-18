/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:14:31 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/12 01:24:35 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *check_w_space(t_token **list, char *line)
{
    int j = 0;
    while(*line && ft_strchr(" \t\v\f\r\n", *line))
    {
        line++;
        j++;
    }
    if(j != 0)
        add_token(list, WSPACE, " ");
    return(line);
}

char *check_pipe(t_token **list, char *line)
{
    if(*line == '|')
        add_token(list, PIPE, "|");
    return(line);
}

char *check_redirection(t_token **list, char *line)
{
    if(*line == '<' && line[1] == '<')
    {
        add_token(list, HERDOC, "<<");
        line++;
    }
    else if (*line == '<')
        add_token(list, REDIN, "<");
    else if (*line == '>' && line[1] == '>')
    {
        add_token(list, APPEND, ">>");
        line++;
    }
    else if(*line == '>')
        add_token(list, REDOUT, ">");
    return(line);
}

char *check_word(t_token **list, char *line, char *chars)
{
    char *str;
    int i;
    //echo "$PWD"    " \t\r\n\"'\v\f|<>$"
    i = 0;
    while(!strchr(chars, line[i]))
        i++;
    str = malloc(sizeof(char) * i);
    if(!str)
        return(NULL);
    i = 0;
    while(*line && !strchr(chars, *line))
        str[i++] = *line++;
    if(i != 0)
    {
        str[i] = 0;
        if(ft_strlen(chars) == 12 || ft_strlen(chars) == 1){
            add_token(list, WORD, str);
            // printf("inside %s\n", str);
        }
        else
            add_token(list, DOLLAR_SIGN, str);
        return(line - 1);
    }
    return(line);
}
