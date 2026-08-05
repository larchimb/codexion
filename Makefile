NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -I./include
OBJDIR = .objects
ALGO = srcs/algorithms/
UTILS =srcs/utils/
MOVES = srcs/moves/
PARSING = srcs/parsing/
CHECKER = srcs/checker/
RM = rm -f

VPATH = $(ALGO) $(UTILS) $(MOVES) $(PARSING)
SRCS =	$(ALGO)adaptive.c $(ALGO)complex.c $(ALGO)medium.c $(ALGO)simple.c $(ALGO)medium_utils.c $(ALGO)few_numbers.c \
		$(UTILS)index.c $(UTILS)bench.c $(UTILS)disorder.c $(UTILS)stack.c $(UTILS)utils.c \
		$(UTILS)ft_printf.c $(UTILS)printf_utils.c \
		$(MOVES)push.c $(MOVES)swap.c $(MOVES)rotate.c $(MOVES)rev_rotate.c \
		$(PARSING)parsing.c $(PARSING)parsing_flags.c $(PARSING)parsing_number.c $(PARSING)ft_atoi.c $(PARSING)ft_bzero.c \
		$(PARSING)ft_calloc.c $(PARSING)ft_isdigit.c $(PARSING)ft_itoa.c \
		$(PARSING)ft_split.c $(PARSING)ft_strlcpy.c $(PARSING)ft_strlen.c \
		$(PARSING)ft_strncmp.c $(PARSING)ft_strjoin.c $(PARSING)ft_memcpy.c \
		main.c

OBJS = $(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))
DEPS = $(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.d)))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJDIR)/%.o:%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR) :
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

-include $(DEPS)