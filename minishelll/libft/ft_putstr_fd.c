/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 09:48:50 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/17 13:44:14 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write (fd, s, ft_strlen(s));
}

// int main()
// {
// 	int fd ;
//     char *s = "nba youngboy never broke again";
// 	fd = open("ft_putchar_fd.txt" , O_CREAT | O_RDWR);
//         ft_putstr_fd(s,fd);
// }