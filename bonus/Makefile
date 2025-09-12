ECHO = @echo
PRINT = @printf
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
INVERT = \033[7m
RESETTXT = \033[0m
BOLD = \033[1m

RM = rm -rf

SRC_DIR := ./srcs
PRS_DIR := $(SRC_DIR)/parsing
TRI_DIR := $(SRC_DIR)/tri_lib
MATH_DIR := $(SRC_DIR)/maths
SRC_DIR_INC := ./incs
TRI_DIR_INC := $(SRC_DIR)/tri_lib
OBJS_DIR := ./objs

SRCS_TRILIB =	tri_auto_draw.c  tri_colors_convert.c  tri_create_window.c  tri_destroy_render.c  tri_draw.c               tri_error.c  tri_get_key.c        tri_init.c        tri_lib.c     tri_loop.c   tri_put_pixel_render.c  tri_put_pixel_window.c tri_colors.c     tri_create_render.c   tri_destroy.c        tri_destroy_window.c  tri_erase_fill_render.c  tri_fps.c    tri_get_key_event.c  tri_init_event.c  tri_lib_gb.c  tri_mouse.c  tri_put_pixel_utils.c   tri_quit.c

SRC := main.c
SRCS_PARSING := __fake_globals.c  free_structs.c  __init__.c  __init_utils.c  nodes.c  object_get_shape.c  object_get_value_utils.c  printing.c  scene_get_value_utils.c  scene_get_light_camera.c  scene_get_shape.c  utils.c  utils_util.c  object_free.c read_file.c check_errors.c rgb_shapes.c __init_objs.c printing_obj.c set_values_objs.c get_values_objs.c scene_get_box.c create_shapes_array.c create_bvh_triangles.c
SRCS_MATHS := utils_maths.c ray.c cal_rays.c lights.c matrice_rotation.c plane.c cylinder.c movements.c fov.c intersect.c on_path.c set_closest.c shadows.c vectors_utils.c vectors_magic.c threads.c boxes.c bvh.c


SRC_FILES := $(addprefix $(SRC_DIR)/, $(SRC))
PRS_FILES := $(addprefix $(PRS_DIR)/, $(SRCS_PARSING))
TRI_FILES := $(addprefix $(TRI_DIR)/, $(SRCS_TRILIB))
MATH_FILES := $(addprefix $(MATH_DIR)/, $(SRCS_MATHS))

OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRC_FILES)) \
		$(patsubst $(PRS_DIR)/%.c, $(OBJS_DIR)/%.o, $(PRS_FILES)) \
		$(patsubst $(TRI_DIR)/%.c, $(OBJS_DIR)/%.o, $(TRI_FILES)) \
		$(patsubst $(MATH_DIR)/%.c, $(OBJS_DIR)/%.o, $(MATH_FILES))

NAME = miniRT_bonus
CC = gcc

CFLAGS = -Wall -Werror -Wextra -I$(SRC_DIR_INC) -I$(TRI_DIR_INC)

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	ifeq ($(METAL), yes)
		MLX_DIR		:= ./libs/mlx_metal
		MLX_NAME	:= $(MLX_DIR)/libmlx.dylib
		CFLAGS		+= -I$(MLX_DIR) -D MACOS
		LDFLAGS		+= -L$(MLX_DIR) -lmlx -framework AppKit
	else
		MLX_DIR		:= ./libs/mlx_macos
		MLX_NAME	:= $(MLX_DIR)/libmlx.a
		CFLAGS		+= -I$(MLX_DIR) -D MACOS
		LDFLAGS		:= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	endif
else ifeq ($(UNAME), Linux)
	MLX_DIR		:= ./libs/mlx
	MLX_NAME	:= $(MLX_DIR)/libmlx.a
	CFLAGS		+= -I$(MLX_DIR) -D LINUX -pthread
	LDFLAGS		:= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
endif

ifeq ($(DEBUG), yes)
	CFLAGS += -pg
endif

ifeq ($(OPTI), yes)
	CFLAGS += -O3
endif

ifeq ($(NOLOOP), yes)
	CFLAGS += -pg -DNOLOOP="1"
endif

ifeq ($(BVH), yes)
	CFLAGS += -DBVH="1"
endif

ifeq ($(THREADS), yes)
	CFLAGS += -DTHREADS="1"
endif

ifeq ($(strip $(SCREEN_X)),)
else
	CFLAGS += -DSCREEN_X=$(SCREEN_X)
endif

ifeq ($(strip $(SCREEN_Y)),)
else
	CFLAGS += -DSCREEN_Y=$(SCREEN_Y)
endif

all: $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)


$(OBJS_DIR)/%.o: $(MATH_DIR)/%.c | $(OBJS_DIR)
	@printf "Compiling %-50s\r" $<
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJS_DIR)
	@printf "Compiling %-50s\r" $<
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: $(PRS_DIR)/%.c | $(OBJS_DIR)
	@printf "Compiling %-50s\r" $<
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: $(TRI_DIR)/%.c | $(OBJS_DIR)
	@printf "Compiling %-50s\r" $<
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@make -C $(MLX_DIR) --no-print-directory
	$(ECHO) "$(YELLOW)Compilation de $(NAME)...$(RESETTXT)"
	@$(CC) -o $(NAME) $(OBJS) $(MLX_NAME) $(LDFLAGS)
	$(ECHO) "$(GREEN)$(BOLD)Compilation Terminée !!!$(RESETTXT)"

bonus: $(NAME)

clean:
	$(ECHO) "$(RED)Suppression des objets...$(RESETTXT)"
	@$(RM) $(OBJS_DIR)
	$(ECHO) "$(GREEN)$(BOLD)Terminé !$(RESETTXT)"

fclean: clean
	$(ECHO) "$(RED)Suppression de $(NAME)...$(RESETTXT)"
	@$(RM) $(NAME)
	$(ECHO) "$(GREEN)$(BOLD)Terminé !$(RESETTXT)"

fclean_all: fclean
	@make clean -C $(MLX_DIR)

re : fclean all

re_all: fclean_all all

.PHONY: all re bonus clean fclean fclean_all re_all