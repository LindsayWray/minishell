NAME := minishell
HEADERFILES :=	includes/minishell.h \
				includes/utils.h
SRCS :=		srcs/main.c \
			srcs/utils/ft_substr.c		srcs/utils/lst_add_back.c	srcs/utils/lst_last.c\
			srcs/utils/lst_new.c		srcs/utils/lst_size.c		srcs/utils/ft_strlen.c\
			srcs/utils/ft_split.c		srcs/utils/ft_strdup.c		srcs/utils/ft_strjoin.c\
			srcs/utils/ft_streql.c		srcs/utils/ft_putstr_fd.c	srcs/utils/ft_cinstr.c\
			srcs/utils/ft_isalnum_str.c	srcs/utils/ft_isdigit_str.c	srcs/utils/ft_isalpha.c\
			srcs/utils/ft_isdigit.c		srcs/utils/ft_itoa.c		srcs/utils/ft_shiftstr_left.c\
			srcs/utils/ft_atoi.c		srcs/utils/ft_free_array.c	srcs/utils/ft_shiftstr_right.c\
			srcs/utils/ft_strcmp.c		srcs/utils/is_whitespace.c\
			srcs/parsing/lexer.c		srcs/parsing/parser.c		srcs/parsing/syntax_error.c\
			srcs/execute/exec.c			srcs/execute/path.c			srcs/execute/redirection.c\
			srcs/execute/wait.c			srcs/execute/heredoc.c\
			srcs/builtins/ft_export.c	srcs/builtins/ft_unset.c	srcs/builtins/ft_env.c\
			srcs/builtins/ft_cd.c		srcs/builtins/ft_pwd.c		srcs/builtins/ft_export_utils_a.c\
			srcs/builtins/ft_echo.c		srcs/builtins/ft_exit.c\
			srcs/expander/expand.c		srcs/expander/complex_cmd.c	srcs/expander/quote_handler.c\
			srcs/environment/getenv.c	srcs/environment/get_env_var.c srcs/environment/envlst_to_array.c\
			srcs/signals/signal.c\
			srcs/cleanup/clean.c srcs/cleanup/error_handler.c

FLAGS := -Wall -Wextra -Werror
OBJFILES := $(SRCS:srcs/%.c=obj/%.o)
LIBS = srcs/utils/dprintf/libftdprintf.a


all: dprintf $(NAME)

$(NAME): $(OBJFILES) 
	gcc -o $@ $^ $(LIBS) -lreadline -L `brew --prefix readline`/lib

obj/%.o: srcs/%.c $(HEADERFILES)
	@mkdir -p $(dir $@)
	gcc -c $(FLAGS) -o $@ $< -I `brew --prefix readline`/include

dprintf:
	@echo "\033[1m\033[32mft_dprintf library generated.\033[39m"
	@$(MAKE) -C srcs/utils/dprintf all

clean:
	rm -f $(OBJFILES)
	@$(MAKE) -C srcs/utils/dprintf clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C srcs/utils/dprintf fclean

re: fclean all

norm:
	norminette $(SRCS) $(HEADERFILES)

.PHONY: all clean fclean re norm 