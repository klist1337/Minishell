VPATH= mandatory_objects mandatory mandatory/execution mandatory/parsing
CFLAGS = -Wall -Wextra -Werror -g
CC = cc
NAME = minishell.a
PROG = minishell
MANDATORY_OBJS_PATH=./mandatory_objects/
MANDATORY_OBJS_DIRETORY=mandatory_objects

MANDATORY_SRCS =minishell.c\
				parsing.c\
				lexer_utils.c\
				lexer_utils2.c\
				utils1_parsing.c\
				utils2_parsing.c\
				utils3_parsing.c\
				lst_funct_cmd.c\
				lst_funct_files.c\
				lexer.c\
				token.c\
				parsing_part2.c\
				parsing_part3.c\
				parsing_part4.c\
				parsing_part5.c\
				parsing_part6.c\
				main_parser2.c\
				lst_funct_args.c\
				lst_funct_token.c\
				print.c\
				main_parser2v2.c\
				handle_dollars.c\
				redirection_error.c\
				free_lst.c\
				lexer_utils3.c\
				lexer_utils4.c\
				lexer_utils5.c\
				lexer_utils6.c\
				main_parser3.c\
				main_parser4.c\
				parsing_part7.c\
				parsing_part8.c\
				parsing_part9.c\
				pipe_red_next.c\
				pipe_red_next_utils.c\
				pipe_next_red_utils1.c\
				pipe_red_next_utils2.c\
				pipe_next_red_utils3.c\
				pipe_red_next_case2.c\
				basic1.c\
				basic2.c\
				built_in.c\
				cd.c\
				echo.c\
				env.c\
				env2.c\
				execution.c\
				exit.c\
				export.c\
				file_access.c\
				free.c\
				here_doc.c\
				init.c\
				pwd.c\
				redirection.c\
				signals.c

MANDATORY_OBJS= $(MANDATORY_SRCS:.c=.o)

MANDATORY_HEADER =minishell.h\
					execution.h\
					parsing.h

all:${MANDATORY_OBJS_DIRETORY} ${NAME}

${NAME}: ${MANDATORY_OBJS} ${MANDATORY_SRCS}
	@make -C ./needs/libft
	@make clean -C ./needs/libft
	@mv ./needs/libft/libft.a ./

	@make -C ./needs/gnl
	@make clean -C ./needs/gnl
	@mv ./needs/gnl/get_next_line.a ./

	@ar -rcs ${NAME} $(addprefix ${MANDATORY_OBJS_PATH},${MANDATORY_OBJS})
	@echo "Minishell is ready"
	@$(CC)  ${NAME} -l readline -L $(HOME)/.brew/Cellar/readline/8.1.2/lib  get_next_line.a libft.a  -o ${PROG}

%.o: %.c $(MANDATORY_HEADER)
	@$(CC) -I  $(HOME)/.brew/Cellar/readline/8.1.2/include ${CFLAGS} -c $< -o  ${MANDATORY_OBJS_PATH}$@

${MANDATORY_OBJS_DIRETORY}:
	@mkdir -p $@


re: fclean all

fclean: clean
	@rm -rf *.a ${PROG}
	@make clean -C ./needs/libft
	@make clean -C ./needs/gnl
	@echo "Needed files removed"

clean:
	@rm -rf ${MANDATORY_OBJS_DIRETORY}
	@echo "Object files removed"