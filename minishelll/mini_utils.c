/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:49:22 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/19 19:54:43 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_final	*clean_final(t_final **lst)
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

void	free_all(t_node_free *garbage)
{
	void	*tmp;

	tmp = NULL;
	while (garbage)
	{
		free(garbage->pointer);
		tmp = garbage;
		free(tmp);
		garbage = garbage->next;
	}
}

void	add(t_node_free **garbage, void *pointer)
{
	t_node_free	*node;

	node = malloc(sizeof(t_node_free));
	if (!node)
		return ;
	node->pointer = pointer;
	node->next = *garbage;
	*garbage = node;
}

void	handler(int sig)
{
	(void) sig;
	rl_catch_signals = 0;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}
