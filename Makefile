NAME = minishell
SRC = src/minishell.c src/utils/utils.c src/built_ins/env.c src/utils/malloc_utils.c \
		src/built_ins/exit.c src/init.c src/utils/env_utils.c src/built_ins/export.c src/built_ins/unset.c \
		src/parsers/parser.c src/parsers/tokens.c src/parsers/tokenization.c src/parsers/node.c \
		src/parsers/token_utils.c src/parsers/node_utils.c src/parsers/tree.c src/parsers/syntax.c \
		src/helpers/clean.c src/utils/ft_strdup.c src/utils/ft_strjoin.c src/utils/ft_substr.c \
		src/parsers/tokens2.c src/parsers/node2.c
SRC_OBJS = ${SRC:.c=.o}
CC = cc
CFLAGS =
#  -Wall -Werror -Wextra
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