    /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:16:49 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/04 21:19:44 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_symboles(t_token **list, char line)
{
    char *symb;
    char *str;
    
    symb = ft_strdup(" \"%'()*+,-./:\\^`|~$");
    str = malloc(2);
    if(!str)
        return(RETURN_ERROR);
    str[0] = line;
    str[1] = 0;
    while(*symb)
    {
        if(line == *symb)
        {
            add_token(list, WORD, ft_strjoin("$", str));
            return(1);   
        }
        symb++;
    }
    return(RETURN_ERROR);
}

char *check_dollar(t_token **list, char *line)
{
    char *str;

    if(*line == '$')
    {
        if(check_symboles(list, line[1]) != RETURN_ERROR)
            return(line + 1);
        if(line[1] == '?'){
            add_token(list, EXIT_STATUS, "$?");
            return(line + 1);
        }
        else if(*line && line[1] >= '0' && line[1] <= '9')
        {
            str = malloc(sizeof(char) * 2);
            if(!str)
                return(NULL);
            str[0] = line[1];
            str[1] = 0;
            add_token(list, DOLLAR_SIGN, str);
            return(line + 1);
        }
        else if(*(line + 1)) {
            line = check_word(list, ++line, " \t\n!\"%'()*+,-./:;<=>?@[\\]^|`~$");
        }
        else
            add_token(list, WORD, "$");
    }
    return(line);
}

char *check_wd_inside_q(t_token **list, char *line, char *str)
{
    char	*s;
	int		i;

	i = 0;
	while (!ft_strchr(str, line[i]))
		i++;
	s = malloc(sizeof(char) * i);
	if (!s)
		return (NULL);
	i = 0;
	while (*line && !ft_strchr(str, *line))
		s[i++] = *line++;
	if (i != 0)
	{
		s[i] = 0;
        add_token(list, WORD, "$");
		return (line - 1);
	}
	return (line);
}

void check_in_quot(char *buff, t_token **list, char quot)
{
    while(*buff != 0)
    {
        buff = check_word(list, buff, "$");
        // printf("\n%s\n", buff);
        if(quot == '"')
            buff = check_dollar(list, buff);
        buff++;
    }
}

char *inside_quots(t_token **list, char *line, char quot, int j)
{
    char *str;
    str = malloc(sizeof(char) * (j + 1));
    if(!str)
        return(NULL);
    if(j == 0 && *(line + 1) == '\0')
    {
        add_token(list, WORD, str);
        return(" ");
    }
    int i = j;
    j = 0;
    while(line[j] && j < i)
    {
        str[j] = line[j];
        j++;
    }
    // printf("str == %s\n", str);
    str[j] = 0;
    check_in_quot(str, list, quot);
    return(NULL);
}

char *check_double_quot(t_token **list, char *line, char quot)
{
    int i;

    i = 0;
    if(*line == quot)
    {
        line++;
        if(strchr(line, quot))
        {
            while(line[i] != quot)
                i++;
            inside_quots(list, line, quot, i);
            return(ft_strchr(line, quot));
        }
        else
            return(ft_putstr_fd("minishell: Missing quote\n", 2), NULL);
    }
    return(line);
}

char *check_single_quot(t_token **list, char *line, char quot)
{
    int i;

    i = 0;
    if(*line == quot)
    {
        ++line;
        if(strchr(line, quot))
        {
            while(line[i] != quot)
                i++;
            inside_s_quots(list, line, quot, i);
            return(ft_strchr(line, quot));
        }
        else
            return(ft_putstr_fd("minishell: Missing quote\n", 2), NULL);
    }
    return(line);
}

char check_lexer(t_token **list, char *line)
{
    // int i = 1;
    while(*line)
    {
        
        line = check_w_space(list, line);
        line = check_word(list, line, " \t\r\n\"'\v\f|<>$");
        // printf("%i is %s\n", i, line);
        // i++;
        line = check_pipe(list, line);
        line = check_redirection(list, line);
        line = check_dollar(list, line);
        line = check_double_quot(list, line, '"');
        if(line == NULL)
            return(RETURN_ERROR);
        // puts("debug");
        // puts(line);
        // puts("debug");
        line = check_single_quot(list, line, '\'');
        if(line == NULL)
            return(RETURN_ERROR);
        // if (!line && line[0] == '"')
        //     continue;
        line++;
    }
    return(1);
}