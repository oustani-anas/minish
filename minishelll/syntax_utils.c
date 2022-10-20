/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:59:42 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/20 02:33:27 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_end_line(t_token *list)
{
	char	*val;
	int		type;
	t_token	*str;

	str = list;
	while (str)
	{
		val = str->content;
		type = str->type;
		str = str->next;
	}
	if (*val == '|' && type == 1)
	{
		ft_putstr_fd(error_to_print(T_ERROR, val, "\n"), 2);
		return (RETURN_ERROR);
	}
	return (1);
}

int	valid_red(t_token *str, char *buf, int t)
{
	if ((!ft_strcmp("<<", buf) || !ft_strcmp("<", buf)
			|| !ft_strcmp(">", buf) || !ft_strcmp(">>", buf))
		&& (t >= 2 && t <= 5))
	{
		if (str->next->type == WSPACE && str->next->next != NULL)
			str = str->next;
		else if (str->next->type != WORD && str->next->type != DOLLAR_SIGN)
		{
			ft_putstr_fd(error_to_print(T_ERROR, NULL, "\n"), 2);
			return (RETURN_ERROR);
		}
	}
	return (1);
}
