#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>


#define fals_e 0
#define tru_e 1



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

typedef enum
{
    e_close,
    e_open
} t_status_quote;

typedef enum 
{
    e_nothing,
    e_single_quote,
    e_double_quote

} t_type_quote;

typedef struct
{
    t_status_quote status_quote;
    t_type_quote type_quote;
} t_quote;

typedef enum status
{
    save = 0,
    clean = 1,
}e_status;

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

//this is the structure of save index of the token between single quotes
typedef struct s_list
{
	int			content;
	struct s_list	*next;
}					t_l;

void	ft_add_back(t_l **lst, t_l *new);

//this structure is for the linked list save tokens
typedef struct list
{
	void			*content;
	struct s_list	*next;
}	t_list;

//this function is for garbage collector 
void clean_memory_or_save(void *ptr,e_status status);
void* allocation(size_t nbr_byte);
void  del(void* ptr);

//this function is for the linked list
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));

# endif