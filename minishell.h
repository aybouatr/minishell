/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:46:31 by aybouatr          #+#    #+#             */
/*   Updated: 2025/05/11 19:44:15 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <wait.h>

# define YES 1
# define NO 0

typedef enum s_status_quote
{
	e_close,
	e_open
}					t_status_quote;

typedef enum s_type_quote
{
	e_nothing,
	e_single_quote,
	e_double_quote
}					t_type_quote;

typedef struct s_quote
{
	t_status_quote	status_quote;
	t_type_quote	type_quote;
}					t_quote;

typedef enum status
{
	save = 0,
	clean = 1,
}					t_status;

typedef enum type_token
{
	e_pipe,
	e_redir_in,
	e_redir_ou,
	e_redir_app,
	e_here_doc,
	e_name_file,
	e_delimeter_here_doc,
	e_arg,
	e_cmd,
	e_nothin,
	e_builtins,
}					t_type_token;

typedef struct _list
{
	void			*content;
	t_type_token	type_token;
	struct _list	*next;
}					t_token;

typedef struct list
{
	int				content;
	struct list		*next;
}					t_l;
typedef struct s_lis
{
	void			**content;
	t_type_token	type_token;
	int				here_doc;
	struct s_lis	*next;
}					t_2d_list;

typedef struct s_data
{
	char			**env;
	t_list			*save_head_gc;
	char			*cwd;
	char			*oldpwd;
	int				or_stdout;
	int				with_wildcards;
	int				or_stdin;
	int				exit_status;
	int				pipe;
	int				sig_here_doc;
	t_2d_list		*files;
}					t_data;

extern t_data	g_data;

void				setup_signals(void);
void				ft_tokenadd_back(t_token **lst, t_token *new);
t_token				*ft_tokennew(void *content);
void				clean_memory_or_save(void *ptr, t_status status);
void				clean_memory(const char *meesage, int nb_exit);
void				*allocation(size_t nbr_byte);
t_2d_list			*ft_2d_lstnew(void **content);
void				**allocation_2d(size_t nbr_byte);
void				ft_lstadd_2d_back(t_2d_list **lst, t_2d_list *new);
void				del(void *ptr);
void				clean_memory_or_save_2d(void **ptr, t_status status);
char				**get_values_the_keys(char **arr);
char				*remplace_keys_to_values(char *str, char **arr);
char				*get_arg_expand(char *str);
char				*get_value_from_env(char *key);
int					ft_expand(t_token **lst_to, t_l *head);
int					len_arr(char **arr, char *str);
int					count_wrd_expand(char *str);
int					len_key_expand(char *str);
int					is_shoold_expand(t_quote quote, char c);
void				clean_all(char *str, int i);
int					count_nbr_token(char *str, int *counter, t_l **head);
char				*ft_operator_token(char **str);
char				*get_token(t_quote *quot, char **input_line);
char				**split_to_token(char *input_line, t_l **head);
t_type_token		get_type_token(t_type_token prev, char *content);
char				*sstrdup(const char *s);
void				check_quote(t_quote *ifo_quote, char c);
void				insilize_quote(t_quote *quote);
void				skip_token(char **str);
void				assign_name_to_token(char **tokens, t_token **list);
void				hand_quote(t_token **list);
char				*delete_quote(char *str);
char				*get_name(t_type_token type);
int					is_not_opertor(char c, t_quote quote);
int					is_spaces(char c);
t_l					*ft_new(int content);
void				ft_add_back(t_l **lst, t_l *new);
int					is_opertor_or_redire(t_token *token);
int					len_not_oper_redir(t_token *pos);
void				split_token_to_opertor(t_token *Head,
						t_2d_list **lst_token);
t_2d_list			*rename_tokents(t_2d_list *lst_t, t_token *list);
int					ft_parsing(char *str, t_2d_list **lst_tok);
size_t				ft_sizetoken(t_token *head);
int					is_builts(char *str);
void				hand_quote(t_token **list);
int					ft_grammer(t_token *lst);
t_token				*match_files(const char *pattern);
int					is_found_wildcards(void **arr);
char				**copy_lst_into_arr(t_token *lst);
void				**processing_wildcards(char **arr);
int					handl_wildcards(t_2d_list **lst_token);
char				*grbc_strdup(const char *s);
int					ft_fnmatch(const char *pattern, char *name_file);

char				*ft_itoa_grbg(int n);
void				print_content_tokens_for_testing(t_2d_list *lst_token);
char				*get_name(t_type_token type);
char				*process_token_with_quote(char *str, t_quote *quote,
						int *counter, short *check);
t_2d_list			*ft_2d_lstnew_env(void **conten);
void				clean_env_or_save(char *ptr, t_status status);
void				clean_env_or_save_2d(char **ptr, t_status status);
void				clean_env(void);
char				**allocation_env_2d(size_t nbr_ptr);
int					tab_counter(char **env);
void				start_env(void);
char				*ft_strdup_env(char *s);
void				*allocation_env(size_t nbr_byt);
char				*ft_itoa_grbg(int n);
char				*remplace_keys_to_values_here_doc(char *str, char **arr);

int					gc_free_one(void *ptr);
int					exit_status(int status);
void				setup_signals(void);
void				handle_sigint(int sig);
int					check_ifquoted(char *str);
void				for_norm(int check, char **line, char **new);
int					cold_arms(char *line, char *limiter);
char				*del_nl(char *str);
char				*add_nl(char *str);
char				*read_from_here_doc(char *limiter);
int					ft_here_doc(t_2d_list **lst_token);
void				ft_child_in_here_doc(int fd, char *limiter);

int					is_redir(t_2d_list *lst);
int					is_next_redir_and_next_next_arg(t_2d_list *lst);
char				**str_joine_2d(char **arr1, char **arr2);
t_2d_list			*deplacement_arg_near_cmd(t_2d_list *lst_token);
char				*remplace_keys_to_values_here_doc(char *str, char **arr);
char				*get_arg_expand_for_here_doc(char *str);
int					skip_all_word(char *str, int i);
int					condition_exp(char *str, int i, t_quote quote);
/*------execution---------*/

int					dup_to_heredoc(t_2d_list *tokens);
int					apply_redirection(t_2d_list *tokens);
int					append_redirection(t_2d_list *tokens);
int					count_nbr_her_doc(t_2d_list *lst);
t_2d_list			*for_multiple_rediapp(t_2d_list **tokens);
void				skip_no_cmd(t_2d_list **tokens);
char				*ft_check(char *str, char *path);
char				*ft_checkfirst(char *str);
char				*get_path(char **env);
void				start_execution(t_2d_list *tokens);
void				execute_command(t_2d_list *tokens);
void				error(int i);
void				dup_intializer(void);
int					work_with_pipe(int *status, t_2d_list **tokens);
int					output_redirection(t_2d_list *tokens);
int					input_redirection(t_2d_list *tokens);
void				waitforchild(pid_t pid, int *status);
int					execution_machine(t_2d_list **tokens);
char				*ft_strjoin_gc(char const *s1, char const *s2);
char				*add_nl(char *str);
void				skip_pipe(t_2d_list **tokens);
void				error(int i);
void				continue_builtins(t_2d_list *tokens);
void				apply_builtin_forked(t_2d_list *tokens);
int					apply_builtin(t_2d_list *tokens);
int					input_redi(t_2d_list **tokens);
t_2d_list			*for_multiple_rediou(t_2d_list *tokens);
int					update_global_pipe(t_2d_list *tokens);
int					no_pipe(t_2d_list *tokens);
int					for_builtin(t_2d_list *tokens);
int					open_skip(t_2d_list *files);
void				next_one(t_2d_list **tokens);
void				clean_all(char *str, int i);
int					f(t_2d_list *current);
int					ft_next_check(t_2d_list *tokens);
int					pipe_founder(t_2d_list *copy);
int					open_get_fd(t_2d_list *h_d);
void				clean_all_exit(char *str, int nb);
void				set_child_signals(int sig);
t_token				*check_names_token(t_token *temp);

/*--------builtins-----------*/
void				ft_get_envdata(void);
int					search_the_env(char *search);
char				**del_tab_2d_arr(int del);
void				re_cd(char *str);
void				re_echo(char **str);
void				re_env(void);
void				re_exit(char **str);
void				re_export(char **str);
void				re_pwd(void);
void				re_unset(char **str);
char				*get_oldpwd(char **env);
void				edit_var(int i, char *str);
void				sort_env(void);
void				error_custom(char *str, int exit);
char				*get_home(char **env);
void				update_pwd(char *cwd);
void				update_oldpwd(char *cwd);
int					cd_home(void);
void				replace_oldpwd(char *oldpwd);
void				print_export(void);
int					search_for_export(char *search);
char				*del_fplus(char *str);
int					ft_equal_len(char *str);
void				quote_value(int i);
int					check_the_special(char *s);
void				join_the_value(char *str, char *new);
void				export_value(char *str);
void				edit_var(int i, char *str);
char				**add_new(char *str);

#endif
