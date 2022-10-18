/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:38:40 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/18 10:38:46 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sh_start(t_token **list, t_final **data)
{
    char *line;
    // t_token *test;

    // test = *list;
    (void)data;
    while(1)
    {
        line = readline("minishell> ");
        if (!line)
        {
            printf(MOVE_UP_RIGHRT "exit\n");
            exit(0);
        }
        if(!is_white_space(line))
            continue;
        else if(!strcmp(line, "exit"))
            break;
        if(check_lexer(list, line) == RETURN_ERROR ||
            valid_syntax(*list) == RETURN_ERROR)
        {
            clean_list(list);
            continue;
        }
        check_is_herdoc(list);
        expande_cmd(list);
        // check_is_herdoc();
        clean_list(list);
        add_history(line);
    }
}

int main(int ac, char **av, char **envr)
{
    t_token *list;
    t_final  *cmd;

    (void)av;
    if(ac > 1){
        printf("the prog works without args\n");
        return(0);
    }
    create_envr(envr);
    sh_start(&list, &cmd);
    
    // while(list != NULL)
    //    {
    //       printf("[ type :  %d ]  \n", list->type);
    //       printf("[ Value : %s ]  \n", list->content);
    //       printf("\n");
    //       list = list->next;
    //    }
}
