/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_of_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:03:12 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/19 23:04:54 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	size_of_env(void)
{
	int		i;
	t_envr	*env;

	env = g_all.envir;
	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}
