/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:38:40 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/20 17:46:34 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_and_free(t_token **list, t_final **cmd, char *line)
{
	(void)cmd;
	unlink("/tmp/.herdooc");
	if (!list || !line)
		return ;
	clean_list(list);
	clean_final(cmd);
	free(line);
}

char	*read_line(char *line)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	line = readline("minishell> ");
	add(&g_all.garbage, line);
	if (!line)
	{
		printf("exit\n");
		exit(0);
	}
	return (line);
}

void	sh_start(t_token **list, t_final **data)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = read_line(line);
		if (!is_white_space(line))
			continue ;
		else if (!ft_strcmp(line, "exit"))
			break ;
		if (check_lexer(list, line) == RETURN_ERROR
			|| valid_syntax(*list) == RETURN_ERROR)
		{
			clean_list(list);
			continue ;
		}
		check_is_herdoc(list);
		expande_cmd(list);
		*data = parse(*list);
		exec_cmd(*data, *list);
		add_history(line);
		clear_and_free(list, data, line);
	}
	rl_clear_history();
}

int	main(int ac, char **av, char **envr)
{
	t_token	*list;
	t_final	*cmd;

	(void)av;
	if (ac > 1)
	{
		printf("the prog works without args\n");
		return (0);
	}
	create_envr(envr);
	sh_start(&list, &cmd);
}
