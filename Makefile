NAME := miniRT

SRC_DIR := ./srcs
PRS_DIR := $(SRC_DIR)/parsing
INC_DIR := ./incs
OBJS_DIR := ./objs

SRC := main.c
SRCS_PARSING := utils.c __init__.c __fake_globals.c utils_util.c \
                __init_utils.c a_light_camera_light.c nodes.c printing.c \
                free_structs.c

SRC_FILES := $(addprefix $(SRC_DIR)/, $(SRC))
PRS_FILES := $(addprefix $(PRS_DIR)/, $(SRCS_PARSING))
ALL_SRC := $(SRC_FILES) $(PRS_FILES)

OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRC_FILES)) \
        $(patsubst $(PRS_DIR)/%.c, $(OBJS_DIR)/%.o, $(PRS_FILES))

CC := /usr/bin/gcc
CFLAGS := -Wall -Wextra -Werror -g -std=c89 -I$(INC_DIR)
LDFLAGS := -lm

ifeq ($(DEBUG), 1)
	CFLAGS += -fsanitize=address -g3
endif

GREEN := \033[0;32m
RED := \033[0;31m
VIOLET := \033[0;36m
NONE := \033[0m

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJS_DIR)
	@printf "Compiling %-50s\r" $<
	@$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(OBJS_DIR)/%.o: $(PRS_DIR)/%.c | $(OBJS_DIR)
	@printf "Compiling %-50s\r" $<
	@$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	@printf "\n$(GREEN)[OK]$(NONE) Executable $(NAME) built.\n"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

norm:
	@echo "$(VIOLET)[NORM - START]$(NONE)"
	@norminette srcs/ incs/
	@echo "$(VIOLET)[NORM - END]$(NONE)"

clean:
	@rm -rf $(OBJS)
	@printf "$(GREEN)[CLEAN]$(NONE) Object files removed.\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)[FCLEAN]$(NONE) Executable removed.\n"

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus norm
.SILENT: $(NAME) clean fclean re bonus
