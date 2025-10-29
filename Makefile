NAME := minirt
INC_DIR := include
BUILD_DIR := obj
SRC_DIR := src
LIBFT_DIR := libft
MLX42_DIR := MLX42
LIBS := $(LIBFT_DIR)/libft.a $(MLX42_DIR)/libmlx42.a
CC := cc
CFLAGS := -Wextra -Werror -Wall -O2 -MMD
CPPFLAGS := -I$(INC_DIR) -I$(LIBFT_DIR)/include -I$(MLX42_DIR)/include
LDFLAGS := -L$(LIBFT_DIR) -L$(MLX42_DIR)
LDLIBS := -lft -lmlx42 -ldl -lglfw -lpthread -lm
DEV_FLAGS := -g -O0 -fno-omit-frame-pointer -fsanitize=address,undefined
SRC_FILES := main.c \
	init_structs.c \
	intersections\color.c \
	intersections\field_of_view.c \
	intersections\color.c \
	math\vec_utils.c \
	parser\parcing.c \
	parser\read_lines.c \
	parser\validate.c

SRC := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
DEP := $(OBJS:$.o=.d)

all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	@$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $<.."
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@echo "Object files created."

$(LIBFT_DIR)/libft.a:
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX42_DIR)/libmlx42.a:
	@$(MAKE) -C $(MLX42_DIR)

-include $(DEP)

clean:
	@rm -rf $(BUILD_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(MLX42_DIR)
	@echo "Object files cleaned."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@$(MAKE) fclean -C $(MLX42_DIR)

re: fclean all

.PHONY: all clean fclean re

#-Ofast for faster compilation or O2