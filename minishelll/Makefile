NAME = minishell
INCLUDES = minishell.h \
			libft/libft.h

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

SRC =	minishell.c \
		mini_utils.c \
		token_list_utils.c \
		parse.c \
		lexer_utils.c \
		lexer_utils1.c \
		lexer.c \
		create_envr.c \
		lexer_tokens_util.c \
		syntax_utils.c \
		valid_syntax.c \
		add_cmd_back.c	\
		red_list.c	\
		check_is_herdoc.c \
		check_is_herdoc2.c \
		expande_cmd.c \
		execution/utils_2.c \
		execution/exec.c \
		execution/exec_2.c \
		execution/ft_exec_3.c \
		execution/red_cheker.c \
		execution/builtin/ft_builtin.c \
		execution/builtin/ft_builtin2.c \
		execution/builtin/ft_export.c \
		execution/builtin/ft_export_2.c \
		execution/builtin/ft_morefunction_builtin.c \
		execution/builtin/ft_unset.c \
		execution/builtin/ft_cd.c \
		execution/builtin/ft_cd_2.c \
		execution/builtin/size_of_env.c \
		execution/utils_exec.c \
		execution/redirect_file.c \


OBJ = $(SRC:.c=.o)

%.o : %.c minishell.h
	$(CC) $(CFLAGS) -I $(shell brew --prefix readline)/include -c $< -o $@ -g 

all : $(NAME)
$(NAME) : $(OBJ) $(INCLUDES) $(LIBFT_DIR) $(LIBFT_LIB)
	$(CC) $(CFLAGS) -L $(shell brew --prefix readline)/lib -lreadline $(LIBFT_LIB) $(OBJ) -o $(NAME) -g

$(LIBFT_LIB) :
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ)
	$(MAKE) fclean -C $(LIBFT_DIR)

fclean : clean
	rm -rf $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
	
re: fclean all 