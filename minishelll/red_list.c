/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:27:52 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/19 20:08:15 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_red	*new_node_red(char *value, int type)
{
	t_red	*newnode;

	newnode = (t_red *)malloc(sizeof(t_red));
	add(&g_all.garbage, newnode);
	if (newnode != NULL)
	{
		newnode->type = type;
		newnode->filename = value;
		newnode->next = NULL;
	}
	return (newnode);
}

void	add_red_back(t_red **list, int type, char *value)
{
	t_red	*head;
	t_red	*new;

	new = new_node_red(value, type);
	if (!*list)
		*list = new;
	else
	{
		head = *list;
		while (head->next)
			head = head->next;
		head->next = new;
	}
}
