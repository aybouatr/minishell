NAME = minishell

# Include files
INCLUDES = minishell.h  # Corrected the typo "includ" to "INCLUDES"

# Source files
SRCS = main.c parsing/ft_garage_colector_ptr.c  parsing/ft_garage_colector_2ptr.c  parsing/ft_expand.c\
	 parsing/ft_help_funct_for_tokenization.c parsing/ft_tokenization.c  parsing/ft_parsing.c  \
	 parsing/ft_functin_help_for_expand.c parsing/ft_utils.c parsing/ft_garammer_and_deleted_quote.c\
	 wildcards_bns/ft_utils_wildcards.c wildcards_bns/ft_wildcards.c parsing/ft_grbg_env.c parsing/ft_strdup_env.c\
	 builtins/re_cd.c builtins/re_echo.c builtins/re_env.c builtins/re_exit.c builtins/re_export.c \
	 builtins/re_pwd.c builtins/re_unset.c  execution/execution.c execution/utils_exec.c 


# Object files: Replace .c with .o
OBJECTS = $(SRCS:.c=.o)  # Corrected "Object" to "OBJECTS" (consistent naming convention)

# Compiler and flags
CC = cc

# Linker flags for readline library
LDFLAGS = -lreadline -L/usr/local/opt/readline/lib  # Add readline library and specify its path if needed

# Debugging flags: -g (to include debug information), -Og (optimize for debugging), -g3 (maximum debug info)
CFLAGS = -I/usr/local/opt/readline/include -g3 -Og

# Path to libft directory
LIBFT_DIR = libft

# Include libft headers
LIBFT_INCLUDE = $(LIBFT_DIR)

# Object files for libft
LIBFT_OBJECTS = $(LIBFT_DIR)/libft.a

# Default target
all: $(NAME)

# Rule to build the final executable
$(NAME): $(OBJECTS) $(LIBFT_OBJECTS)
	$(CC) $(OBJECTS) $(LIBFT_OBJECTS) $(LDFLAGS) -o $(NAME)  # Link with readline library and libft.a

# Rule to compile .c to .o
%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@  # Compile with readline include path

# Build libft library
$(LIBFT_OBJECTS):
	$(MAKE) -C $(LIBFT_DIR)

# Clean up build artifacts
clean:
	rm -f $(OBJECTS)

	# Clean up libft object files
	$(MAKE) -C $(LIBFT_DIR) clean

# Clean up everything, including the executable and libft
fclean: clean
	rm -f $(NAME)

	# Clean up libft library
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild the project
re: fclean all

.PHONY: all clean fclean re $(LIBFT_OBJECTS)
