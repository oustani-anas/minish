/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 20:16:15 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/19 11:42:56 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

char	*ft_strdup(const char*s1)
{
	char	*s2;
	int		i;

	s2 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	add(&g_all.garbage, s2);
	i = 0;
	if (s2)
	{
		while (s1[i])
		{
			s2[i] = s1[i];
			i++;
		}
		s2[i] = '\0';
	}
	return (s2);
}
