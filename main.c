#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>


void	ft_add_back(t_l **lst, t_l *new)
{
	t_l	*temp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_l	*ft_new(int content)
{
	t_l	*node;

	node = (t_l *)malloc(sizeof(t_l));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

int is_spaces(char c) 
{
    return (c == ' ' || c == '\t');
}

void check_quote(t_quote *ifo_quote, char c)
{
    if (c != '\'' && c != '"')
        return;
    if (ifo_quote->status_quote == e_close)
    {
        if (c == '\'') {
            ifo_quote->type_quote = e_single_quote;
            ifo_quote->status_quote = e_open;
        } else if (c == '"') {
            ifo_quote->type_quote = e_double_quote;
            ifo_quote->status_quote = e_open;
        }
    } 
    else if (ifo_quote->status_quote == e_open)
    {
        if ((ifo_quote->type_quote == e_single_quote && c == '\'') || (ifo_quote->type_quote == e_double_quote && c == '"'))
        {
            ifo_quote->type_quote = e_nothing;
            ifo_quote->status_quote = e_close;
        }
    }
}

void insilize_quote(t_quote *quote)
{
    quote->status_quote = e_close;
    quote->type_quote = e_nothing;
}

size_t	ft_strlen(const char *str)
{
	size_t	e;

	e = 0;
	while (str[e])
		e++;
	return (e);
}

char	*ft_strdup(const char *s1)
{
	char	*new_s;
	int		i;

	i = 0;
	new_s = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	while (s1[i])
	{
		new_s[i] = s1[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

short count_nbr_token(char *str,t_l **head)
{
    short counter;
    short check;
    t_quote quote;

    insilize_quote(&quote);
    counter = 0;
    while (str && *str)
    {
        check = 0;
        while (str && *str && is_spaces(*str))
            str++;
        counter++;
        while (*str && (!is_spaces(*str) && quote.status_quote == e_close)) 
        {
            check_quote(&quote, *str);
            str++;
        }
        while (*str && quote.status_quote == e_open)
        {
            check_quote(&quote, *str);
            if (quote.status_quote == e_open && quote.type_quote == e_single_quote)
                check = 1;
            str++;
        }
        if (check == 1)
           ft_add_back(head,ft_new((counter - 1)));
    }
    if (quote.status_quote == e_open)
        clean_memory_or_save(NULL,clean);
    return counter;
}


// char** split_to_token(char *input_line)
// {
//     t_l *Head;
//     char **arr;
//     char word[1000];
//     int i;
//     t_quote quote;

//     Head = NULL;
//     insilize_quote(&quote);
//     arr = malloc(sizeof(char *) * (count_nbr_token(input_line,&Head) + 1));
//     if (!arr)
//         clean_memory_or_save(NULL,clean);
//     while (input_line && *input_line)
//     {
//         i = 0;
//         while (is_spaces(*input_line))
//             input_line++;

//         check_quote(&quote, *input_line);
        
        
//     }


// }

// void get_tokens(char *str)
// {
    

//     split_to_token(str);
    
// }

char** split_to_token(char *input_line)
{
    t_l *Head;
    char **arr;
    char word[1000];
    int i, token_count;
    t_quote quote;

    Head = NULL;
    insilize_quote(&quote);
    token_count = count_nbr_token(input_line, &Head);
    arr = malloc(sizeof(char *) * (token_count + 1));
    if (!arr)
        clean_memory_or_save(NULL, clean);

    int token_index = 0;
    while (input_line && *input_line)
    {
        i = 0;
        while (is_spaces(*input_line))
            input_line++;

        while (*input_line && (!is_spaces(*input_line) || quote.status_quote == e_open))
        {
            check_quote(&quote, *input_line);
            word[i++] = *input_line++;
        }
        word[i] = '\0';
        if (i > 0)
        {
            arr[token_index++] = ft_strdup(word);
        }
    }
    arr[token_index] = NULL;

    return arr;
}

void get_tokens(char *str)
{
    char **tokens = split_to_token(str);
    for (int i = 0; tokens[i] != NULL; i++)
    {
        printf("Token %d: %s\n", i, tokens[i]);
        free(tokens[i]);
    }
    free(tokens);
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