/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 23:00:39 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/19 11:38:58 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (0);
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	add(&g_all.garbage, str);
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		if (i <= ft_strlen(s1))
			str[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
	{
		if (i <= ft_strlen(s2))
			str[j++] = s2[i++];
	}
	str[j] = '\0';
	return (str);
}
