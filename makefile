NAME = minishell
INCLUDES = minishell.h  # Corrected the typo "includ" to "INCLUDES"
SRCS = main.c

# Object files: Replace .c with .o
OBJECTS = $(SRCS:.c=.o)  # Corrected "Object" to "OBJECTS" (consistent naming convention)

CC = cc

# Linker flags for readline library
LDFLAGS = -lreadline -L/usr/local/opt/readline/lib  # Add readline library and specify its path if needed
CFLAGS = -I/usr/local/opt/readline/include  # Include path for readline headers (if needed)

# Default target
all: $(NAME)

# Rule to build the final executable
$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(NAME)  # Link with readline library

# Rule to compile .c to .o
%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@  # Compile with readline include path

# Clean up build artifacts
clean:
	rm -f $(OBJECTS)

# Clean up everything, including the executable
fclean: clean
	rm -f $(NAME)

# Rebuild the project
re: fclean all

.PHONY: all clean fclean re