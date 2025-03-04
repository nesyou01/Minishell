#ifndef DEFS_H
# define DEFS_H
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
# define EMPTY_CMD 21
# define SUB_SHELL 22

typedef struct s_token
{
	int				type;
	int				fd;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_file
{
	int				fd;
	int				type_out_redirect;
	char			*path;
	struct s_file	*next;
}	t_file;

typedef struct s_node
{
	int				type;
	int				taken;
	int				quotes_expanded;
	char			*content;
	char			*filter;
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
}	t_shell;

typedef struct s_command
{
	t_list	*argv;
	char	*cmd;
}	t_command;

typedef struct s_io
{
	t_file	*in;
	t_file	*out;
}	t_io;

#endif