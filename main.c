#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

t_data g_data;

//this functions just for testing ,when finsh test i will deleted

char	*get_name(e_type_token type)
{
	if (type == e_redir_app)
		return ("redir_append");
	if (type == e_pipe)
		return ("pipe");
	if (type == e_cmd)
		return ("cmd");
	if (type == e_redir_in)
		return ("redi_in");
	if (type == e_redir_ou)
		return ("redir_ou");
	if (type == e_name_file)
		return ("Name file");
	if (type == e_delimeter_here_doc)
		return ("delemiter here doc");
	if (type == e_here_doc)
		return ("here_doc");
	if (type == e_builtins)
		return ("builtns");
	return ("nothing");
}

void	print_content_tokens_for_testing(t_2d_list *lst_token)
{
	int	i;
	int	j;

	i = 0;
	while (lst_token)
	{
		j = 0;
		printf("Token  %d : %s\n", i, get_name(lst_token->type_token));
		while (lst_token->content[j])
		{
			printf("index %d = %s\n", j, (char *)lst_token->content[j]);
			j++;
		}
		i++;
		lst_token = lst_token->next;
	}
}

//-------------------------------------start function  signals ---------------------------

void handle_eof()
{
	clean_env();
	clean_memory("finx",0);
	exit(0);
}

// void sigint_handler(int sig) {
//     //(void)sig;
//    write(1,"\n\033[1;31m-> \033[0m minishell ",27);
// }

// void sigquit_handler(int sig) {
//     (void)sig;
//     write(STDOUT_FILENO, "\nCaught Ctrl+\\! Ignoring.\n", 27);
// }

void handle_sigint(int sig) {
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);                    // move to new line
    rl_replace_line("", 0);                          // clear current input line
    rl_on_new_line();                                // tell readline we're on a new line
    rl_redisplay();                                  // redisplay prompt
}

// --- Setup signal handling ---
void setup_signals(void) {
    signal(SIGINT, handle_sigint);   // Ctrl+C → custom prompt
    signal(SIGQUIT, SIG_IGN);        // Ctrl+\ → ignored
}

//-------------------------------------------_  end function signals _-__-__-__-__-__-__-__-___-___-__-



int	main(int ac, char **av, char **env)
{
	char *line_input ;
	char *line_tokens;
	t_2d_list *lst_token = NULL;

	start_env();
	g_data.exit_status = 0;

	setup_signals();

	//signal(SIGINT, sigint_handler);
	//signal(SIGINT, sigint_handler);   // Ctrl+C
   // signal(SIGQUIT, sigquit_handler); // Restore default Ctrl+\ behavior
	while (1337)
	{
		//// fix all leaks but readline it have a leak reachble memory
		if (g_data.exit_status == 0)
			line_input = readline("\033[1;32m-> \033[0m minishell ");
		else 
			line_input = readline("\033[1;31m-> \033[0m minishell ");
		if (!line_input)
			handle_eof();
		else
			add_history(line_input);
		// printf("%s\n\n", line_input);
		if (1 == ft_parsing(line_input, &lst_token)	)
			continue ;
		if( 1 == handl_wildcards(&lst_token))
			continue ;
		//exuctions()
		print_content_tokens_for_testing(lst_token);
		clean_memory("",0);
		//start_execution(lst_token);
		free(line_input);
	}


	//testing for leaks and  gdb 


// 	char *line_input = "ls | grep * >> hh | echo $??$USER";
// 	char *line_tokens;
// 	t_2d_list *lst_token = NULL;

// 	start_env();


// 	ft_parsing(line_input, &lst_token);
// 	handl_wildcards(&lst_token);
// 	print_content_tokens_for_testing(lst_token);
// 	clean_memory("finish",1);
// 	clean_env();
 }
