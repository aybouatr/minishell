#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>


// void	ft_lstadd_back(t_list **lst, t_list *new)
// {
// 	t_list	*temp;

// 	if (!new)
// 		return ;
// 	if (!*lst)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	temp = *lst;
// 	while (temp->next)
// 		temp = temp->next;
// 	temp->next = new;
// }

// void	ft_lstclear(t_list **lst, void (*del)(void *))
// {
// 	t_list	*temp;
// 	t_list	*help;

// 	if ((!lst) || (!del))
// 		return ;
// 	help = *lst;
// 	while (help)
// 	{
// 		temp = help;
// 		help = help->next;
// 		del(temp->content);
// 		free(temp);
// 	}
// 	*lst = NULL;
// }

// t_list	*ft_lstnew(void *content)
// {
// 	t_list	*node;

// 	node = (t_list *)malloc(sizeof(t_list));
// 	if (!node)
// 		return (NULL);
// 	node->content = content;
// 	node->next = NULL;
// 	return (node);
// }

int is_spaces(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
    return (0);
}

int is_valid_token(char c, int quote, int doubl_quote)
{
    if (!is_spaces(c) && ((quote % 2 == 0) || (doubl_quote % 2 == 0)))
        return (1);
    return (0);
}

void count_quotes(char c, int *quote, int *double_quote)
{
    if (c == '\'')
        *quote += 1;
    if (c == '"' )
        *double_quote += 1;
}

short count_nbr_token(char* str)
{
    int	    (quote) ,(double_quote);
	short	counter;
    int i;

	counter = 0;
    quote = 0;
    double_quote = 0;
    while (str && *str)
    {
        while (*str && is_spaces(*str) && (quote % 2 == 0) && (double_quote % 2 == 0))
        { 
            
            count_quotes(*str, &quote, &double_quote);
            str++;
        }
        if (*str && is_valid_token(*str, quote, double_quote))
            counter++;
        while (*str && !is_spaces(*str) && (quote % 2 == 0) && (double_quote % 2 == 0))
        {
            count_quotes(*str, &quote, &double_quote);
            str++;
        }
        while (*str && ((quote % 2 == 1) || (double_quote % 2 == 1)))
        {
            count_quotes(*str, &quote, &double_quote);
            str++;
        }
    }
    return counter;
}

void get_tokens(char *str)
{
    short nb = count_nbr_token(str);
    printf("%d\n\n",nb);
}


int main()
{
    char* line_input;
    char *line_tokens;
    while (1)
    {
       line_input = readline("\033[1;32m->\033[0m \033[1;31mminishell \033[0m");
       //add_history(line_input);
       printf("%s\n\n",line_input);
       get_tokens(line_input);
       free(line_input);
    }
    
}