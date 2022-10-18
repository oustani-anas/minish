/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_herdoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 02:05:28 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/18 10:11:48 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *return_del(char *str)
{
    char *del;
    int i;

    i = 0;
    while(str[i] && str[i] != ' ')
        i++;
    del = (char *)malloc(sizeof(char) * i + 1);
    if(!del)
        return(NULL);
    i = 0;
    while(str[i])
    {
        del[i] = str[i];
        i++;
    }
    del[i] = '\0';
    return(del);
}

void start_herdoc(char ***content, int *type)
{
    //content delimeter type of delimeter
    char *buff;
    char *file;
    char *h_line;
    int fd;
    
    **content = return_del(ft_strtrim(**content, " "));
    buff = ft_strdup("");
    h_line = NULL;
    while(1)
    {
        h_line = readline("> ");
        if(!h_line || !ft_strcmp(h_line, **content))
            break ;
        else
            buff = ft_strjoin(buff, ft_strjoin(h_line, "\n"));
    }
    file = get_file_name(ft_strjoin("/tmp/.herdooc", ft_itoa(g_all.n_h)));
    **content = file;
    fd = open(**content, O_CREAT | O_RDWR | O_TRUNC, 0644);
    *type = WORD;
    ft_putstr_fd(buff, fd);
    close(fd);
    printf("here\n");
}

int begin_herdoc(char **content, int *type)
{
    static int h = 1;
    h++;
    g_all.n_h = h;
    start_herdoc(&content, type);
    return(1);
}

char	*verify(t_token *list)
{
	t_token	*token;
	char	*buff;

	token = list;
	buff = ft_strdup("");
	if (token->type == 1)
		token = token->next;
	while (token)
	{
		if (token->type == 1)
			break ;
		if (token->type == 9)
			buff = ft_strjoin(buff, ft_strjoin("$", token->content));
		else
			buff = ft_strjoin(buff, token->content);
		token->content = ft_strdup("\0");
		token->type = 1;
		token = token->next;
	}
	return (buff);
}

void check_is_herdoc(t_token **list)
{
    t_token *str;

    str = *list;
    while(str)
    {
        if(str->type == HERDOC && str->next != NULL)
        {
			if(str->next->content == WSPACE && str->next->next != NULL)
            {
                str->next->next->content = ft_strdup(verify(str->next)); 
                begin_herdoc(&str->next->next->content, &str->next->next->type);
            }
            else
            {
                str->next->content = ft_strdup(verify(str->next)); 
                begin_herdoc(&str->next->content, &str->next->type);
            }
        }
        str = str->next;
    }
}
