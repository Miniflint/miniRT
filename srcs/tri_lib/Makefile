ECHO = @echo
PRINT = @printf
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
INVERT = \033[7m
RESETTXT = \033[0m
BOLD = \033[1m

RM = rm -rf

SRC =	tri_colors.c              tri_destroy_render.c      tri_lib.c                 tri_put_pixel_utils.c \
tri_create_render.c       tri_destroy_window.c      tri_lib_gb.c \
tri_create_window.c       tri_error.c               tri_loop.c \
tri_destroy.c             tri_init.c \

OBJ = $(SRC:.c=.o)

NAME = libtri.a
CC = gcc
AR = ar -rcs

CFLAGS = -Wall -Werror -Wextra -g3

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	ifeq ($(METAL), yes)
		MLX_DIR		:= ../mlx_metal
		MLX_NAME	:= $(MLX_DIR)/libmlx.dylib
		CFLAGS		+= -I$(MLX_DIR) -D MACOS
		LDFLAGS		+= -L$(MLX_DIR) -lmlx -framework AppKit
	else
		MLX_DIR		:= ../mlx_macos
		MLX_NAME	:= $(MLX_DIR)/libmlx.a
		CFLAGS		+= -I$(MLX_DIR) -D MACOS
		LDFLAGS		:= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	endif
else ifeq ($(UNAME), Linux)
	MLX_DIR		:= ../mlx
	MLX_NAME	:= $(MLX_DIR)/libmlx.a
	CFLAGS		+= -I$(MLX_DIR) -D LINUX
	LDFLAGS		:= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
endif

ifeq ($(DEBUG), debug)
	CFLAGS += -fsanitize=address -g3
endif

ifeq ($(OPTI), yes)
	CFLAGS += -O3
endif

ifeq ($(strip $(SCREEN_X)),)
else
	CFLAGS += -DSCREEN_X=$(SCREEN_X)
endif

ifeq ($(strip $(SCREEN_Y)),)
else
	CFLAGS += -DSCREEN_Y=$(SCREEN_Y)
endif

$(NAME) : $(OBJ)
	@make -C $(MLX_DIR) --no-print-directory
	$(ECHO) "$(YELLOW)Compilation de $(NAME)...$(RESETTXT)"
	@$(AR) $(NAME) $(OBJ) -I$(MLX_DIR)
	$(ECHO) "$(GREEN)$(BOLD)Compilation Terminée !!!$(RESETTXT)"

%.o : %.c
	$(PRINT) "$(YELLOW)Generation des objets...$(RESETTXT)\r"
	@$(CC) $(CFLAGS) -I$(MLX_DIR) -o $@ -c $<

bonus : $(NAME)

all : $(NAME)

clean :
	$(ECHO) "$(RED)Suppression des objets...$(RESETTXT)"
	@$(RM) $(OBJ)
	$(ECHO) "$(GREEN)$(BOLD)Terminé !$(RESETTXT)"

fclean : clean
	$(ECHO) "$(RED)Suppression de $(NAME)...$(RESETTXT)"
	@$(RM) $(NAME)
	$(ECHO) "$(GREEN)$(BOLD)Terminé !$(RESETTXT)"

fclean_all : fclean
	@make clean -C $(MLX_DIR)

re : fclean all

re_all : fclean_all all

.PHONY: all re bonus clean fclean