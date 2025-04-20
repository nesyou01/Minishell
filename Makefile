NAME = minishell
SRC = src/main.c src/minishell.c src/utils/utils.c src/builtins/env.c src/utils/malloc_utils.c \
		src/init.c src/utils/env_utils.c src/builtins/export.c src/builtins/unset.c \
		src/parser/parser.c src/parser/tokens.c src/parser/tokenization.c src/parser/node.c \
		src/parser/token_utils.c src/parser/node_utils.c src/parser/tree.c src/parser/syntax.c \
		src/helpers/clean.c src/utils/ft_strdup.c src/utils/ft_strjoin.c src/utils/ft_substr.c \
		src/parser/tokens2.c src/parser/node2.c src/parser/file.c src/parser/parse_utils.c \
		src/parser/expander.c src/parser/command.c src/utils/str_utils.c \
		src/parser/split_node.c src/parser/expand_vars.c src/parser/expand_wildcards.c src/utils/env_utils2.c \
		src/utils/lst_utils.c src/parser/wildcard_utils.c src/parser/here_doc.c src/parser/env_utils.c \
		src/execution/handle_pipe.c src/execution/logical_operator.c src/execution/exit_status.c src/builtins/exit.c \
		src/execution/execute_cmd.c src/execution/handle_subshell.c src/execution/redirections.c src/execution/cmd_utils.c \
		src/signals.c src/utils/ft_split.c src/builtins/echo.c src/builtins/cd.c src/builtins/pwd.c src/utils/ft_strnstr2.c \
		src/utils/ft_itoa.c src/parser/trim_var.c src/utils/malloc_g_utils.c src/parser/syntax2.c src/parser/node3.c src/parser/expander2.c \
		src/parser/filter.c src/parser/var_utils.c src/execution/execute_builtin.c

SRC_OBJS = ${SRC:.c=.o}
CC = cc
CFLAGS = -Wall -Werror -Wextra 
LIBFT = libs/libft/libft.a
HEADERS = includes/minishell.h includes/defs.h
READLINE = /mnt/homes/ael-gady/.brew/opt/readline


${NAME}: ${LIBFT} ${SRC_OBJS}
	${CC} ${CFLAGS} ${SRC_OBJS} ${LIBFT} -o ${NAME} -l readline -L ${READLINE}/lib

all: ${NAME}

bonus: all

${LIBFT}: libs/libft/libft.h
	@make -C libs/libft all

src/%.o: src/%.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -I ${READLINE}/include  -o $@ 


clean:
	rm -f ${SRC_OBJS}
	@make -C libs/libft clean

fclean: clean
	rm -f ${NAME}
	@make -C libs/libft fclean

re: fclean all