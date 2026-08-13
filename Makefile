NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -I./include
OBJDIR = .objects
SRC = srcs/
INCLUDE = include/
RM = rm -f

VPATH = $(INCLUDE) $(SRC)
SRCS =	$(SRC)codexion.c $(SRC)initializing.c $(SRC)monitoring.c $(SRC)parser.c \
		$(SRC)parser_utils.c $(SRC)routine.c $(SRC)routine_utils.c $(SRC)time_utils.c

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