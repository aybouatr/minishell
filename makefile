NAME = minishell

INCLUDES = minishell.h

SRCS = main.c parsing/ft_garage_colector_ptr.c  parsing/ft_garage_colector_2ptr.c  parsing/ft_expand.c\
	 parsing/ft_help_funct_for_tokenization.c parsing/ft_tokenization.c  parsing/ft_parsing.c  \
	 parsing/ft_functin_help_for_expand.c parsing/ft_utils.c parsing/ft_garammer_and_deleted_quote.c\
	 wildcards_bns/ft_utils_wildcards.c wildcards_bns/ft_wildcards.c parsing/ft_grbg_env.c parsing/ft_strdup_env.c\
	 builtins/re_cd.c builtins/re_echo.c builtins/re_env.c builtins/re_exit.c builtins/re_export.c \
	 builtins/re_pwd.c builtins/re_unset.c  execution/execution.c execution/utils_exec.c \
	 ft_here_doc/ft_here_doc.c ft_here_doc/ft_here_doc_utils.c parsing/ft_functin_help2_for_expand.c\
	 execution/execution1.c execution/execution2.c execution/execution3.c execution/execution4.c \
     execution/execution5.c execution/execution6.c execution/execution7.c builtins/cd_utils.c \
	 builtins/export_utils.c builtins/export_utils2.c parsing/ft_helpers.c

RESET		=	\033[0m
RESET2		=	'\033[0m'
GREEN		=	'\033[32m'
GRAY		=	'\033[2;37m'
ITALIC		=	'\033[3m'
RED			=	\033[0;31m


OBJECTS = $(SRCS:.c=.o)

CC = cc

LDFLAGS = -lreadline -L/usr/local/opt/readline/lib

CFLAGS = -I/usr/local/opt/readline/include -Wall -Wextra -Werror -g3 

LIBFT_DIR = libft

LIBFT_INCLUDE = $(LIBFT_DIR)

LIBFT_OBJECTS = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT_OBJECTS)
	@echo  "$(RED)"
	@echo  "\t ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓"
	@echo  "\t▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒█ █    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒"
	@echo  "\t▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░"
	@echo  "\t▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░"
	@echo  "\t▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒"
	@echo  "\t░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░"
	@echo  "\t░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░"
	@echo  "\t░      ░    ▒ ░   ░   ░ ░  ▒ ░░ ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░"
	@echo  "\t       ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░"
	@echo  "$(RESET)"	
	@$(CC) $(OBJECTS) $(LIBFT_OBJECTS) $(LDFLAGS) -o $(NAME)  # Link with readline library and libft.a

%.o: %.c $(INCLUDES)
	@$(CC) $(CFLAGS) -c $< -o $@ 

$(LIBFT_OBJECTS):
	@$(MAKE) -s -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJECTS)
	@echo $(ITALIC)$(GRAY) "     - removing the object files ..." $(RESET2)
	@$(MAKE) -s -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@echo $(ITALIC)$(GRAY) "     - removing the object files and the executable $(NAME)..." $(RESET2)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: