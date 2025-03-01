/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:10:13 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/27 15:06:22 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>//for write, execve, read,
# include <stdlib.h>//malloc
# include <sys/wait.h>//wait
# include <fcntl.h>//for system call open,
# include <sys/types.h>//pid_t
# include <stdio.h>//perror && printf

# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include "./defs.h"

void		env_init(t_shell *shell, char **env);

void		ft_env(t_shell *shell);
void		ft_exit(t_shell *shell);
void		ft_unset(t_shell *shell, char *var);
void		ft_export(t_shell *shell, char *var);

t_env		*ft_parse_env(t_shell *shell, char *str, char *key);
t_env		*ft_last_env(t_env *env);
t_env		*ft_get_env(t_env *env, char *key);
char		*ft_get_env_key(t_shell *shell, char *str);

void		ft_perror(char *str);
void		ft_clean_all(t_shell *shell);
void		*ft_malloc(t_shell *shell, size_t size);
char		*ft_strdup(t_shell *shell, const char *s1);
char		*ft_strjoin(t_shell *shell, char const *s1, char const *s2);
char		*ft_substr(t_shell *shell,
				char const *s, unsigned int start, size_t len);
void		ft_add_garbage(t_list **head, t_shell *shell, void *ptr);
void		*ft_malloc_globale(t_shell *shell, size_t size);
char		*ft_strdup_globale(t_shell *shell, const char *s1);
t_list		*ft_split(t_shell *shell, char *str, char *pattern);
size_t		ft_safe_strlen(char *str);
char		*ft_get_env_value(t_shell *shell, char *key);
t_list		*ft_lstnew(t_shell *shell, void *content);
char		*ft_repeat(t_shell *shell, size_t len, char c);
int			ft_index_of(char *str, char c);

// PARSING
t_node		*ft_parser(t_shell *shell, char *str);
t_token		*ft_split_tokens(t_shell *shell, char *str);
int			ft_tokenize(t_token *lst);
void		ft_add_token_last(t_token **lst, t_token *new);
t_token		*ft_new_token(t_shell *shell, char	*content);
int			ft_strcmp(char *s1, char *s2);
void		ft_add_token_start(t_token **lst, t_token *new);
t_node		*ft_add_node_last(t_node **lst, t_node *new);
t_node		*ft_new_node(t_shell *shell, t_token *token);
void		ft_add_node_start(t_node **lst, t_node *new);
void		ft_clean_cmd(t_shell *shell);
void		ft_tree_builder(t_shell *shell, t_node **node);
t_node		*ft_to_tree(t_node *node);
int			syntax_validator(t_token *token);
void		ft_merge_tokens(t_shell *shell, t_token **token);
void		ft_merge_args_with_cmd(t_shell *shell, t_token *token);
t_node		*ft_tokens_to_nodes(t_shell *shell, t_token *token);
t_file		*ft_new_file(t_shell *shell, char *path);
int			is_redirection(t_token *token);
t_node		*ft_dup_node(t_shell *shell, t_node *node);
t_command	*ft_parse_command(t_shell *shell, t_node *node);
char		*ft_expand_all_vars(t_shell *shell,	char *str);
int			get_var_end(char *s);
int			ft_wildcard_handler(t_shell *shell, t_node *node);
int			ft_expand_node_vars(t_shell *shell, t_node *node);
char		*ft_join_all(t_shell *shell, t_list *item);
int			ft_isvalid_var(char c);
void		ft_sort(t_list *lst);
t_file		*ft_add_file_last(t_file **lst, t_file *new);
t_file		*ft_last_file(t_file *lst);
void		ft_retokenize(t_node *node);

// EX
void		execute_tree(t_shell *shell, t_node *node);
void		execute_builtin(t_shell *shell, t_node *node);
void		execute_external(t_shell *shell, t_node *node);
void		execute_pipe(t_shell *shell, t_node *node);
void		execute_and(t_shell *shell, t_node *node);
void		execute_or(t_shell *shell, t_node *node);
void		execute_subshell(t_shell *shell, t_node *node);
void		handle_here_doc(t_file *heredoc);
void		handle_input_redirections(t_file *in);
void		handle_output_redirections(t_file *out);
void		execute_logical(t_shell *shell, t_node *node);
void		execute_subshell(t_shell *shell, t_node *node);
#endif