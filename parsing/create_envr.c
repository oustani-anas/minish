/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:46:52 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/17 13:52:58 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_globale	data;

t_envr  *new_node_envr(char *str, char *value)
{
	t_envr  *new;
	new = (t_envr *)malloc(sizeof(t_envr));
	if(new != NULL)
	{
		new->variable = str;
		new->value = value;
		new->next  = NULL;
	}
	return(new);
}

void	add_new_node_envr(t_envr **list, char *variable, char *value)
{
	t_envr	*new;
	t_envr	*begin;

	new = new_node_envr(variable, value);
	if(!new)
		return;
	if(*list == NULL)
		*list = new;
	else
	{
		begin = *list;
		while(begin->next)
			begin = begin->next;
		begin->next = new;
	}    
}   

void	create_envr(char *envr[])
{
	int i = 0;
	char **str;
    
    while(envr[i])
    {
        str = ft_split(envr[i], '=');
        add_new_node_envr(&data.envir, *str, envr[i]);
        // printf("%s=%s\n", *str, *(str + 1));
        i++;
    }
    
}