/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagmah <ylagmah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:10:13 by ylagmah           #+#    #+#             */
/*   Updated: 2025/02/17 10:26:15 by ylagmah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/libft.h"

# define SEPECIAL_CHARS "<>|&() "

# define UNKNOWN -1
# define OUT_REDIRECTER 1
# define IN_REDIRECTER 2
# define HERE_DOC 3
# define OUT_APPEND_REDIRECTER 4
# define PIPE 105
# define STATUS_CODE 6
# define FILE 7
# define COMMAND 9
# define ARGUMENT 10
# define HERE_DOC_LIMITER 12
# define PARENTHESES_START 113
# define PARENTHESES_END 114
# define AND 115
# define OR 116

typedef struct s_token
{
	int				type;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_file
{
	int				fd;
	char			*path;
	struct s_file	*next;
}	t_file;

typedef struct s_node
{
	int				type;
	int				taken;
	char			*content;
	t_file			*in;
	t_file			*out;
	struct s_node	*next;
	struct s_node	*prev;
	struct s_node	*r_node;
	struct s_node	*l_node;
}	t_node;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	int		exit;
	t_env	*env;
	t_list	*globale_garbage;
	t_list	*cmd_garbage;
	t_file	*file;
}	t_shell;

typedef struct s_execute
{
	t_file			*in;
	t_file			*out;
	t_node			*node;
}	t_execute;

typedef struct s_command
{
	char	**argv;
	char	*cmd;
}	t_command;

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
char		**ft_split(t_shell *shell, char const *s, char c);
size_t		ft_safe_strlen(char *str);

// PARSING
t_execute		*ft_parser(t_shell *shell, char *str);
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
void		ft_node_parser(t_shell *shell, t_node **node);
t_node		*ft_to_tree(t_node *node);
int			syntax_validator(t_token *token);
void		ft_merge_tokens(t_shell *shell, t_token **token);
void		ft_merge_args_with_cmd(t_shell *shell, t_token *token);
void		ft_tokens_to_nodes(t_shell *shell, t_token *token, t_execute *cmd);
t_file		*get_file_or_add(t_shell *shell, char *path);
int			is_redirection(t_token *token);
t_node		*ft_dup_node(t_shell *shell, t_node *node);
t_command	*ft_parse_command(t_shell *shell, t_node *node);
char		*ft_expand_all_vars(t_shell *shell,	char *str);
int			get_var_end(char *s);
void		ft_expand_node_vars(t_shell *shell, t_node *node);

// EX
void		ft_execute(t_shell *shell, t_node *node);

#endif