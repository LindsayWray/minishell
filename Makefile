NAME := minishell
HEADERFILES :=	includes/minishell.h \
				includes/utils.h
SRCS :=		srcs/main.c \
			srcs/lexer.c \
			srcs/utils/ft_substr.c \
			srcs/utils/lst_add_back.c \
			srcs/utils/lst_last.c \
			srcs/utils/lst_new.c \
			srcs/utils/ft_strlen.c \
			srcs/parser.c

FLAGS := -Wall -Wextra -Werror
OBJFILES := $(SRCS:srcs/%.c=obj/%.o)

all: $(NAME)

$(NAME): $(OBJFILES) 
	gcc -o $@ $^ -lreadline

obj/%.o: srcs/%.c $(HEADERFILES)
	@mkdir -p $(dir $@)
	gcc -c $(FLAGS) -o $@ $<

clean:
	rm -f $(OBJFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette $(SRCS) $(HEADERFILES)

.PHONY: all clean fclean re norm 