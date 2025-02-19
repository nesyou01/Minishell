NAME = minishell
SRC = src/minishell.c src/utils/utils.c src/built_ins/env.c src/utils/malloc_utils.c \
		src/built_ins/exit.c src/init.c src/utils/env_utils.c src/built_ins/export.c src/built_ins/unset.c \
		src/parser/parser.c src/parser/tokens.c src/parser/tokenization.c src/parser/node.c \
		src/parser/token_utils.c src/parser/node_utils.c src/parser/tree.c src/parser/syntax.c \
		src/helpers/clean.c src/utils/ft_strdup.c src/utils/ft_strjoin.c src/utils/ft_substr.c \
		src/parser/tokens2.c src/parser/node2.c src/parser/file.c src/parser/parse_utils.c \
		src/parser/expander.c src/execution/execute.c src/parser/command.c src/utils/str_utils.c \
		src/utils/ft_split.c src/parser/expand_vars.c src/parser/expand_wildcards.c src/utils/env_utils2.c \
		src/utils/lst_utils.c src/parser/widlcard_utils.c
SRC_OBJS = ${SRC:.c=.o}
CC = cc
CFLAGS =
#  -g -fsanitize=address 
# -Wall -Werror -Wextra
LIBFT = libs/libft/libft.a
HEADERS = includes/minishell.h

${NAME}: ${LIBFT} ${SRC_OBJS}
	${CC} ${CFLAGS} ${SRC_OBJS} ${LIBFT} -l readline -o ${NAME}

${LIBFT}:
	@make -C libs/libft all

src/%.o: src/%.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

clean:
	rm -f ${SRC_OBJS}
	@make -C libs/libft clean

fclean: clean
	rm -f ${NAME}
	@make -C libs/libft fclean

re: fclean all