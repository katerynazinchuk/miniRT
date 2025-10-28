NAME := minirt
INC_DIR := include
BUILD_DIR := obj
SRC_DIR := src
LIBFT_DIR := libft
MLX42_DIR := MLX42
LDLIBS = -lft -lml42
CC := cc
CFLAGS := -Wextra -Werror -Wall -O2
CPPFLAGS := -I$(INC_DIR) -I$(LIBFT_DIR)/include -I$(MLX42_DIR)/include
LDFLAGS := -L$(LIBFT_DIR) -L$(MLX42_DIR)
LDLIBS := -lft -mlx42 -ldl -lglfw -lpthread -lm
DEV_FLAGS := -g -O0 -fno-omit-frame-pointer -fsanitize=address,undefined
SRC := main.c \
	init_structs.c \
	intersections\color.c \
	intersections\field_of_view.c \
	intersections\color.c \
	math\vec_utils.c \
	parser\parcing.c \
	parser\read_lines.c \
	parser\validate.c

OBJ := 

all:
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDFLAGS) $(SRC_DIR)/$(SRC) -o $(NAME)
#-Ofast for faster compilation or O2