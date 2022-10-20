/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoustani <aoustani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:38:27 by aoustani          #+#    #+#             */
/*   Updated: 2022/10/19 21:16:15 by aoustani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

# define RETURN_ERROR 99
# define RETURN_SUCCESS 100
// # define NL_ERROR "minishell: syntax error near unexpected token `newline'"
# define T_ERROR "minishell: syntax error near unexpected token `'"
# define MESSAGE_FOLDER "cd: error retrieving current \
 directory: getcwd: cannot access parent directories: \
 No such file or directory\n"
# define ERR_F "minshell: export: `"
# define ERR_L "': not a valid identifier\n"

typedef enum s_token_type
{
	WSPACE,
	PIPE,
	HEREDOC,
	APPEND,
	REDIN,
	REDOUT,
	QUOTE,
	DBQUOTE,		
	WORD,
	DOLLAR_SIGN,
	NEW_line,
	EXIT_STATUS,
}	t_token_type;

# define PATH_STD   "/usr/bin:/bin:/usr/sbin:/sbin:"

// Garbage Collector !!!
typedef struct s_node_free
{
	void				*pointer;
	struct s_node_free	*next;
}	t_node_free;

typedef struct s_red
{
	int				type;
	char			*filename;
	struct s_red	*next;
}	t_red;

typedef struct s_final
{
	char			**cmnd;
	struct s_red	*red;
	struct s_final	*next;
}				t_final;

typedef struct s_token_list
{
	int					type;
	char				*content;
	struct s_token_list	*next;
}				t_token;

typedef struct s_envr
{
	char			*variable;
	char			*value;
	struct s_envr	*next;
}				t_envr;

typedef struct s_global
{
	t_envr		*envir;
	t_node_free	*garbage;
	int			status_sign;
	int			r_in;
	int			w_out;
	int			fdd;
	int			dup_in;
	int			dup_out;
	int			fd[2];
	int			n_h;
}	t_globale;

extern t_globale	g_all;

void	handler(int sig);
t_envr	*new_node_envr(char *str, char *value);
void	add_new_node_envr(t_envr **list, char *variable, char *value);
void	add_token_back(t_token **list, int type, char *value);
void	create_envr(char *env[]);
t_final	*parse(t_token *list);
char	check_lexer(t_token **list, char *line);
void	sh_start(t_token **list, t_final **data);
char	*check_w_space(t_token **list, char *line);
char	*check_pipe(t_token **list, char *line);
char	*check_word(t_token **list, char *line, char *wsq);
char	*check_redirection(t_token **list, char *line);
char	*check_dollar(t_token **list, char *line);
int		check_symboles(t_token **list, char line);
t_token	*new_token(int type, char *value);
void	add_token(t_token **list, int type, char *value);
char	*check_double_quot(t_token **list, char *line, char quot);
void	check_in_quot(char *buff, t_token **list, char quot);
char	*check_single_quot(t_token **list, char *line, char quot);
char	*inside_quots(t_token **list, char *line, char quot, int j);
char	*inside_s_quots(t_token **list, char *line, char quot, int i);
void	expande_cmd(t_token **cmd);
void	expande_dollar(char **value);
void	expande_ex_status(char **cmd);
void	expande_rest(char *var, char ***content);
int		valid_syntax(t_token *list);
int		valid_pipe(t_token *list);
int		valid_syntax(t_token *list);
char	*error_to_print(char *s1, char *s2, char *s3);
int		check_end_line(t_token *list);
int		valid_red(t_token *str, char *buf, int t);
void	check_is_herdoc(t_token **list);
void	*clean_list(t_token **list);
void	add_cmd(t_final **list, t_token *tokens);
t_final	*new_cmd(char **content, t_red *red);
void	add_cmd_back(t_final **list, char **content, t_red *red);
void	add_red(t_red **lred, t_token *t);
void	add_red_back(t_red **list, int type, char *value);
int		begin_herdoc(char **content, int *type);
void	start_herdoc(char ***content, int *type);
char	*verify(t_token *list);
char	*get_file_name(char *name);
int		is_file_exist(char *str);
char	*return_del(char *str);
//execution ...
void	exec_cmd(t_final *cmd, t_token *list);
char	*get_path(void);
char	**export_env(t_envr *env);
char	*setUpper(char *str);
void	ft_builtin(char **cmd, int *status);
int		size_word(char **cmd);
int		check_valid_export(char **cmd);
int		ft_echo(char **cmd);
void	ft_cd(char **cmd);
int		check_folder(char *name);
void	ft_pwd(void);
int		check_redirecrt(t_red *red, int *status);
int		check_builtin(char *cmd);
int		print_cmnd(char **cmd);
//part 2
int		check_is_one_cmnd(t_final *cmd, t_token *list, int *status);
void	child_process(t_final *cmd, int *status);
void	check_switch_cd(void);
// function export and unset cd
char	*get_cmd_export(char ***splited_value, char *cmd);
void	next_export(char **cmd, char **splited_value \
	, int status, t_envr *env);
void	ft_export(char **cmd);
t_envr	*ft_unset(char **cmd);
int		check_cmd_valid(char *cmd);
void	check_exported_append(char ***splited_value, char ***cmd, int *append);
void	is_red(t_red *cmd, int *status);
void	ft_cd(char **cmd);
void	ft_push_to_env(int *status, int *append, \
char *splited_value, char *cmd);

//export
int		err_arg(char **cmd);
int		checkappend(char *cmd);
void	update_var_env(char *var, char *val, int is_append);
void	add_new_var_env(char *var, char *val);
int		check_is_valid_var(char *arg, int is_egal);
char	*get_var(char *arg);
int		check_is_in_env(char *arg);
// red 
void	open_redout(char *filename, int *status);
void	open_append(char *filename);
int		open_in(char *filename, int *status);
int		open_herdoc_file(char *filename, int *status);
char	*create_err(char *firs_s, char *midl_s, char *last_s);
int		checkerr_red(char *buff, int tmp_red, t_token *str);
char	*ft_getcwd(void);
void	check_status_exit(char *cmd);
void	more_cd(char *cmd, char *path);
void	change_pwd(char *last_final);
int		ft_execve(char *path, char **cmd);
int		push_sym_whit_sign(t_token **list, char line);
void	handl_signal(int *statuss);
int		get_is_pipe(t_token *list);
char	*remove_back_slash(char *cmd);
int		is_alpha_cap(char c);
int		check_pid(int pid);
void	handler_herdock(int sig);
void	child_herdoc(int id, char *value);
char	*ft_ignore_sign(char *str);
void	hendl(int c);
void	check_is_herdoc(t_token **list);
int		check__is_exits(char *filename);
char	*check_this(t_token *list);
//size env
int		size_of_env(void);
//garbage
void	add(t_node_free **garbage, void *pointer);
t_final	*clean_final(t_final **lst);
#endif