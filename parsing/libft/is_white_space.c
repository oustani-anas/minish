/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_white_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:09:45 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/17 13:42:23 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_white_space(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '\f'
			||str[i] == '\v' || str[i] == '\r' || str[i] == '\t')
			j++;
	}
	if (i == j)
		return (0);
	return (1);
}
