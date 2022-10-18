NAME = minishell
INCLUDES = minishell.h \
			libft/libft.h
#READLINE_PATH = $(shell brew --prefix readline)

#INCLUDE_READLINE = $(addprefix $(READLINE_PATH),/include)

#LIB_READLINE = $(addprefix $(READLINE_PATH),/lib)

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

SRC =	minishell.c \
		token_list_utils.c \
		parse.c \
		lexer_utils.c \
		lexer.c \
		create_envr.c \
		lexer_tokens_util.c \
		syntax_utils.c \
		valid_syntax.c \
		add_cmd_back.c	\
		red_list.c	\
		check_is_herdoc.c \
		expande_cmd.c \
		free_all.c \

OBJ = $(SRC:.c=.o)

%.o : %.c
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