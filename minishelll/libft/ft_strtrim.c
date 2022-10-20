/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 04:08:56 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/19 22:25:46 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

static int	search_set(char c, char const *set)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	i = 0;
	while (s1[start] && search_set(s1[start], set))
		start++;
	while (start < end && search_set(s1[end - 1], set))
		end--;
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	add(&g_all.garbage, str);
	while (end - start)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
