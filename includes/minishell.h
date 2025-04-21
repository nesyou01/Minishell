/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:37:51 by ylagmah           #+#    #+#             */
/*   Updated: 2025/04/21 22:54:57 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/types.h>
# include <errno.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <string.h>
# include <signal.h>
# include <sys/stat.h>
# include <termios.h>
# include "./defs.h"

int			minishell(t_shell *shell, struct termios *in);
void		execute_tree(t_shell *shell, t_node *node);

void		env_init(t_shell *shell, char **env);

t_env		*ft_parse_env(t_shell *shell, char *str, char *key);
t_env		*ft_last_env(t_env *env);
t_env		*ft_get_env(t_env *env, char *key);
char		*ft_get_env_key(t_shell *shell, char *str);

void		ft_clean_all(t_shell *shell, t_node *node);
void		*ft_malloc(t_shell *shell, size_t size);
char		*ft_strdup(t_shell *shell, const char *s1);
char		*ft_strjoin(t_shell *shell, char const *s1, char const *s2);
char		*ft_substr(t_shell *shell,
				char const *s, unsigned int start, size_t len);
void		ft_add_garbage(t_list **head, t_shell *shell, void *ptr);
void		*ft_malloc_globale(t_shell *shell, size_t size);
char		*ft_strdup_globale(t_shell *shell, const char *s1);
t_list		*ft_split_node(t_shell *shell, t_node *node);
size_t		ft_safe_strlen(char *str);
char		*ft_get_env_value(t_shell *shell, char *key);
t_list		*ft_lstnew(t_shell *shell, void *content);
char		*ft_repeat(t_shell *shell, size_t len, char c);
int			ft_index_of(char *str, char c);
void		ft_add_cmd_garbage(t_shell *shell, void *ptr);
char		**ft_get_all_env(t_shell *shell);
char		**ft_lst_to_array(t_shell *shell, t_list *lst);
void		ft_exit(t_shell *shell, t_node *node, int status);
char		**ft_split(t_shell *shell, char const *s, char c);
int			ft_strcmp2(char *s1, char *s2);
int			ft_isspace(char c);
char		*ft_strnstr2(const char *haystack, const char *needle, size_t len);
void		ft_perror3(char *first, char *middle, char *end);
char		*ft_itoa(t_shell *shell, int n);
int			is_valid_quotes(char *str);
void		malloc_error(t_shell *shell);
int			remove_double_quotes(t_shell *sh, t_node *nd, int start, int expd);
int			ft_match_pattern(char *file, char *pattern, char *filter);
t_list		*read_dir(t_shell *shell, DIR *dir, char *pattern, char *filter);
int			is_valid_start(t_token *token);
void		add_quotes(t_shell *shell, t_node *node);
t_node		*ft_new_node_str(t_shell *shell, char *str);

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
void		ft_clean_cmd(t_shell *shell, t_node *node);
void		ft_tree_builder(t_shell *shell, t_node **node);
t_node		*ft_to_tree(t_node *node);
int			syntax_validator(t_shell *shell, t_token *token);
void		ft_merge_tokens(t_shell *shell, t_token **token);
void		ft_merge_args_with_cmd(t_shell *shell, t_token *token);
t_node		*ft_tokens_to_nodes(t_shell *shell, t_token *token);
t_file		*ft_new_file(t_shell *shell, t_token *token);
int			is_redirection(t_token *token);
t_node		*ft_dup_node(t_shell *shell, t_node *node);
t_command	*ft_parse_command(t_shell *shell, t_node *node);
char		*ft_expand_all_vars(t_shell *shell,	char *str);
int			get_var_end(char *s);
int			ft_wildcard_handler(t_shell *shell, t_node *node);
int			ft_expand_node(t_shell *shell, t_node *node);
char		*ft_join_all(t_shell *shell, t_list *item);
int			ft_isvalid_var(char c);
void		ft_sort(t_list *lst);
t_file		*ft_add_file_last(t_file **lst, t_file *new);
t_file		*ft_last_file(t_file *lst);
void		ft_retokenize(t_node *node, int is_export);
t_token		*ft_last_token(t_token *lst);
int			here_doc_handler(t_shell *shell, t_token *token);
void		ft_remove_quotes(t_shell *shell, t_node *node, int expand);
int			ft_repeat_count(t_token *head, int type);
t_node		*ft_head_node(t_node *node);
int			ft_is_valid_key(char *str);
size_t		set_quotes_filter(t_shell *shell, t_node *node,
				char *str, int is_empty);
int			ft_pipe(int fds[2], const char *path);
size_t		ft_strlcpy_o(char *dst, const char *src, size_t dstsize);
int			is_valid_file(t_token *token);
int			is_valid_operator(t_token *token);
int			is_valid_cmd(t_token *token);

void		ft_error(t_shell *shell, t_node *node, char *msg, int status);
void		ft_perror(char *msg);
void		ft_perror2(char *msg, char *end);
char		*ft_strjoin_globale(t_shell *shell, char const *s1, char const *s2);
int			is_valid_parentheses(t_token *token);
char		*remove_empty(t_shell *shell, t_node *node, int from, int until);

int			ft_any_not_tty(void);
int			ft_is_quote(char c);

void		signals_listener(int action);
int			is_valid_here_doc(t_token *token);

int			is_builtin(t_command *p_cmd);
void		execute_builtin(t_shell *shell, t_node *node, t_command *p_cmd);
void		execute_external(t_shell *shell, t_node *node, t_command *p_cmd);
void		execute_pipe(t_shell *shell, t_node *node);
void		execute_and(t_shell *shell, t_node *node);
void		execute_or(t_shell *shell, t_node *node);
void		execute_subshell(t_shell *shell, t_node *node);
int			handle_redirections(t_shell *shell, t_file *io);
void		execute_logical(t_shell *shell, t_node *node);
void		execute_subshell(t_shell *shell, t_node *node);
int			ft_add_env(t_shell *shell, char *key_value);
void		set_env(t_shell *shell, t_env *env, char *key_value, char *key);
void		ft_trim_node(t_shell *shell, t_node *node);

char		*ft_get_fullpath(t_shell *shell, t_node *node, t_command *p_cmd);
char		*get_cmd_path(t_shell *shell, char **paths, char *cmd);
int			is_directory(char *path);

int			ft_echo(t_command *cmd);
int			ft_export(t_shell *shell, t_command *cmd);
int			ft_unset(t_shell *shell, t_command *cmd);
int			ft_pwd(t_shell *shell, t_command *parse_cmd);
int			ft_cd(t_shell *shell, t_command *parse_cmd);
int			ft_env(t_shell *shell, t_command *cmd);
int			ft_builtin_exit(t_shell *shell, t_node *node,
				t_command *parse_cmd, int *fd);
char		*ft_trim_var(t_shell *shell, char *old);

int			exit_status(int action, int value);
int			is_directory(char *path);

#endif