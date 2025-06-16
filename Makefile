NAME	=	miniRT

SRCS_PARSING	=	main.c utils.c __init__.c __fake_globals.c utils_util.c \
			__init_utils.c a_light_camera_light.c nodes.c printing.c \
			free_structs.c

INC_DIR := ./incs/

SRC_DIR := ./srcs
PRS_DIR := $(SRC_DIR)/parsing

FILES := $(addprefix $(PRS_DIR), $(SRCS_PARSING))

MATH_LIB = -lm

OBJS	=	$(FILES:%.c=%.o)
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
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@ $(MATH_LIB)

$(NAME)	: $(OBJS)
	@$(CC) $(CFLAGS) -I$(INC_DIR) $(OBJS) -o $(NAME) $(MATH_LIB)
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
