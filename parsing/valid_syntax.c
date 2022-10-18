/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:48:55 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/13 05:34:57 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *error_to_print(char *s1, char *s2, char *s3)
{
	char *err;
	
	err = NULL;
	if(!s1)
		return(NULL);
	if(s2 && s3)
		err = ft_strjoin(s1, ft_strjoin(s2, s3));
	else if(!s2)
		err = ft_strjoin(s1, s3);
	return(err);
}

int valid_pipe(t_token *list)
{
    t_token *str;

    str = list;
    if(str->type == PIPE){
        // perror(T_ERROR);
		ft_putstr_fd(error_to_print(T_ERROR, str->content, "\n"), 2);
		return(RETURN_ERROR);
    }
    while(str)
    {
        if(str->type == PIPE)
		{
			str = str->next;
        	if(str)
			{
				while(str->type == WSPACE && str->next != NULL)
					str = str->next;
				if(str->type == PIPE)
				{
        			ft_putstr_fd(error_to_print(T_ERROR, str->content, "\n"), 2);
					return(RETURN_ERROR);
				}
			}
        }
		else
			str = str->next;
    }
	return(check_end_line(str));
}

int valid_redirections(t_token *list)
{
	t_token *str;
	char *buf;
	int buf_type;
	
	str = list;
	while(str)
	{
		buf = str->content;
		buf_type = str->type;
		if(str->next != NULL)
		{
			if(valid_red(str, buf, buf_type) == RETURN_ERROR)
				return(RETURN_ERROR);
		}
		else if((!strcmp("<<", buf) || !strcmp("<", buf) 
    	|| !strcmp(">", buf)|| !strcmp(">>", buf))
		&&(str->type >= 2 && str->type <= 5)){
			ft_putstr_fd(error_to_print(T_ERROR, NULL, "\n"), 2);
            return(RETURN_ERROR);
		}
		str = str->next;
	}
	return(1);
}

int valid_syntax(t_token *list)
{
    if(valid_pipe(list) == RETURN_ERROR)
		return(RETURN_ERROR);
    if(valid_redirections(list) == RETURN_ERROR)
		return(RETURN_ERROR);
	return(1);
}