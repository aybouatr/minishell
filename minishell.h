#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>


#define fals_e 0
#define tru_e 1

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef enum e_operators
{
    pipeline,
    and_if,
    or_if,
    dollar,
}e_operator;

// typedef enum e_redirection
// {
//     redir_input,
//     redir_output,
//     redir_append,

// }e_redirection;

typedef enum type_token
{
    e_operators,
    e_redirections,
    e_arg,
    e_command,

}e_type_token;

typedef struct s_token
{
    e_type_token type;
    char*        value;
}t_token;


void print_token(t_token token);

# endif