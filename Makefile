

NAME = minishell

CFLAGS = -I./
LDFLAGS = -lreadline
CC = cc -g

LIB = ft_isalpha.c ft_isdigit.c ft_isalnum.c \
      ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c \
      ft_memcpy.c ft_memmove.c ft_strlcpy.c \
      ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
      ft_strrchr.c ft_strncmp.c ft_memchr.c ft_strnstr.c \
      ft_atoi.c ft_memcmp.c ft_bzero.c \
      ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
	ft_strtrim.c ft_putchar_fd.c ft_putstr_fd.c \
      ft_putendl_fd.c ft_putnbr_fd.c ft_strmapi.c \
      ft_striteri.c ft_itoa.c ft_split.c mysplit.c \
	ft_lstnew.c ft_lstsize.c ft_lstlast.c \
      ft_lstadd_back.c \
      ft_lstadd_front.c ft_lstiter.c \
      ft_lstdelone.c ft_lstclear.c ft_strpbrk.c\
      ft_lstmap.c ft_strstr.c ft_strcmp.c \
      ft_len_darray.c ft_strrjoin.c \
      ft_strstrjoin.c get_next_line_utils.c \
      get_next_line.c

PARSE = ft_special.c ft_parse_manager.c ft_utils.c\
      ft_parsing_handler.c ft_getenv.c ft_expand.c \
      ft_checkpath.c ft_structs.c ft_init_manager.c \
      ft_print_struct.c ft_parseredir.c ft_check_manager.c \
      ft_caseredir.c ft_signal_manager.c ft_free_manager.c \
      ft_check_struct_manager.c ft_check_directions.c ft_utils_structure.c \
      ft_structs_creation.c ft_free_global_strucure.c ft_free_utils.c

EXEC = ft_execution.c ft_builtings.c\
       ft_free.c ft_route.c ft_close.c\
       ft_path.c ft_childs.c ft_openfd.c\
       ft_erros.c ft_pids.c ft_dups.c\
       ft_pipes.c ft_fail.c

COMANDS = ft_echo.c ft_pwd.c ft_cd.c ft_env.c \
            ft_export.c ft_export2.c ft_unset.c\
            ft_exit.c ft_error.c ft_cd2.c

ENV = ft_create.c

REDIR = ft_heredoc.c ft_append.c

REDIR_SRC = $(addprefix ./src/redirections/, $(REDIR))
EXEC_SRC = $(addprefix ./src/exec/, $(EXEC))
COMANDS_SRC = $(addprefix ./src/scomands/, $(COMANDS))
PARSE_SRC = $(addprefix ./src/parsing/, $(PARSE))
LIB_SRC = $(addprefix ./src/libft/, $(LIB))
ENV_SRC = $(addprefix ./src/env/, $(ENV))

all:
	@${CC} ${CFLAGS} ${LIB_SRC} ${ENV_SRC} ${PARSE_SRC} ${COMANDS_SRC} ${EXEC_SRC} ${REDIR_SRC} main.c -o ${NAME} ${LDFLAGS}
clean: $(NAME)
	rm -rf minishell
re: $(NAME)
	clean all
valgrind:
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --trace-children=yes ./${NAME}
fd:
	@valgrind -q --tool=none --track-fds=yes --trace-children=yes ./${NAME}
      

