NAME	=	miniRT

SRCS	=	./srcs/main.c ./srcs/utils.c ./srcs/__init__.c ./srcs/__fake_globals.c

INC_DIR := ./incs/

OBJS	=	$(SRCS:%.c=%.o)
CC		=/usr/bin/gcc
RM		=rm -f

CFLAGS	=	-Wall -Wextra -Werror -g -std=c89

ifeq ($(DEBUG), 1)
	CFLAGS += -fsanitize=address -g3
endif

BLUE	= \033[0;34m
VIOLET	= \033[0;36m
GREEN	= \033[0;32m
RED		= \033[0;31m
YELLOW	= \033[0;33m
NONE	= \033[0m

all:	$(NAME)

%.o: %.c
	@printf "Compiling %-100s \r" $<
	@$(CC) -I$(INC_DIR) $(CFLAGS) -c $< -o $@

$(NAME)	: $(OBJS)
	@$(CC) $(CFLAGS) -I$(INC_DIR) $(OBJS) -o $(NAME)
	@printf "\n$(GREEN)$(NAME) Ready.\n$(NONE)"

norm:
	@echo "$(VIOLET)[NORM - START]$(NONE)"
	@norminette srcs/*/*.*
	@echo "$(VIOLET)[NORM - END]$(NONE)"

clean:
	@$(RM) $(OBJS)
	@printf "$(GREEN)OBJS removed.\n$(NONE)"

fclean:	clean
	@$(RM) $(NAME)
	@printf "$(GREEN)$(NAME) removed.\n$(NONE)"

re: fclean all

bonus: all

.PHONY:	all clean fclean re bonus
.SILENT: $(NAME) bonus clean fclean re
