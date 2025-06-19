MODULE_SRC = mlx_image.swift mlx_window.swift mlx_init.swift
MODULE_OBJ = $(MODULE_SRC:.swift=.o)
MODULE_MOD = $(MODULE_SRC:.swift=.swiftmodule)

SRC = interface.swift $(MODULE_SRC)
OBJ = $(SRC:.swift=.o)

C_SRC = mlx_xpm.c mlx_png.c mlx_string_put.c
C_OBJ = $(C_SRC:.c=.o)

CFLAGS = -O3
INC = -I.

NAME = libmlx.dylib

all: $(NAME)

$(NAME): $(MODULE_MOD) $(OBJ) $(C_OBJ)
	swiftc $(INC) -o $(NAME) -emit-library $(OBJ) $(C_OBJ) -lz

%.o: %.swift
	swiftc $(INC) -parse-as-library -c $< -o $@

%.swiftmodule: %.swift
	swiftc $(INC) -parse-as-library -emit-module \
		-emit-module-path $@ \
		-module-name $(patsubst %.swift,%,$<) \
		-module-link-name $(patsubst %.swift,%,$<) \
		-c $< -o $(patsubst %.swift,%.o,$<)

clean:
	rm -f $(NAME) $(OBJ) $(MODULE_MOD) $(C_OBJ) *.swiftdoc *~
