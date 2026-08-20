NAME = codexion
CC = cc
INCLUDE = include/
CFLAGS = -Wall -Wextra -Werror -pthread -MMD -MP -I$(INCLUDE)
OBJDIR = .objects
SRC = srcs/
RM = rm -rf

VPATH = $(SRC)
SRCS =	codexion.c initializing.c monitoring.c parser.c \
		parser_utils.c routine.c routine_utils.c routine_utils2.c \
		time_utils.c scheduler.c

OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
DEPS = $(addprefix $(OBJDIR)/,$(SRCS:.c=.d))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJDIR)/%.o:%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)
