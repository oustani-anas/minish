/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:38:27 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/18 09:17:47 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# define RETURN_ERROR 99
# define RETURN_SUCCESS 100
// # define NL_ERROR "minishell: syntax error near unexpected token `newline'"
# define t_ERROR "minishell: syntax error near unexpected token `'"

typedef enum s_token_type
{
	WSPACE,			// ' '
	PIPE,			// 	|
	HERDOC,			// 	<<
	APPEND,			//  >>
	REDIN,			//  <
	REDOUT,			//  >
	QUOTE,			//  '
	DBQUOTE,		//  "		
	WORD,
	DOLLAR_SIGN,	// $
	NEW_line,		// "\n"
	// SEMICOLON,		// ;
	EXIT_STATUS,	// $?
}   t_token_type;

# define MOVE_UP_RIGHRT "\033[1A\033[12C"
# define T_ERROR "minishell: syntax error, near unexpected token `'"
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <termios.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include "./libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_red
{
	int				type;
	char			*filename;
	struct s_red	*next;
}	t_red;

typedef struct s_final
{
	char **cmnd;
	struct s_red *red;
	struct s_final *next;
}				t_final;

typedef struct 	s_token_list
{
	int 		type;
	char 		*content;
	struct s_token_list *next;
}				t_token;

typedef struct s_envr
{
	char 	*variable;
	char 	*value;
	struct s_envr *next;
}				t_envr;

typedef struct s_global
{
	t_envr *envir;
	int shlvl;
	int n_h;
	int status;
}			t_globale;


extern  t_globale g_all; 

t_envr *new_node_envr(char *str, char *value);
void add_new_node_envr(t_envr **list, char *variable, char *value);
void add_token_back(t_token **list, int type, char *value);
void create_envr(char *env[]);
t_final *parse(t_token *list);
char check_lexer(t_token **list, char *line);
void sh_start(t_token **list, t_final **data);
char *check_w_space(t_token **list, char *line);
char *check_pipe(t_token **list, char *line);
char *check_word(t_token **list, char *line, char *wsq);
char *check_redirection(t_token **list, char *line);
char *check_dollar(t_token **list, char *line);
int	check_symboles(t_token **list, char line);
t_token *new_token(int type, char *value);
void add_token(t_token **list, int type, char *value);
char *check_double_quot(t_token **list, char *line, char quot);
void check_in_quot(char *buff, t_token **list, char quot);
char *check_single_quot(t_token **list, char *line, char quot);
char *inside_quots(t_token **list, char *line, char quot, int j);
char *inside_s_quots(t_token **list, char *line, char quot, int i);
void expande_cmd(t_token **cmd);
void expande_dollar(char **value);
void expande_ex_status(char **cmd);
void expande_rest(char *var, char ***content);
int valid_syntax(t_token *list);
int valid_pipe(t_token *list);
int valid_syntax(t_token *list);
char *error_to_print(char *s1, char *s2, char *s3);
int check_end_line(t_token *list);
int valid_red(t_token *str, char *buf, int t);
// int valid_redirections(t_token *list);
void check_is_herdoc(t_token **list);
void *clean_list(t_token **list);
void add_cmd(t_final **list, t_token *tokens);
t_final *new_cmd(char **content, t_red *red);
void add_cmd_back(t_final **list, char **content, t_red *red);
void add_red(t_red **lred, t_token *t);
void add_red_back(t_red **list, int type, char *value);
int begin_herdoc(char **content, int *type);
void start_herdoc(char ***content, int *type);
char	*verify(t_token *list);
char *get_file_name(char *name);
int is_file_exist(char *str);
char *return_del(char *str);

#endif