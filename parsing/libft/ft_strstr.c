/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 04:14:27 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/17 13:43:46 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *string, char *find)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (find[k])
		k++;
	if (k == 0)
		return (string);
	while (string[i])
	{
		while (find[j] == string[i + j])
		{
			if (j == k - 1)
				return (string + i);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
