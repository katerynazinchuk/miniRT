NAME := minirt
INC_DIR := include
BUILD_DIR := obj
SRC_DIR := src
LIBFT_DIR := libft
MLX42_DIR := MLX42
GNL_DIR := get_next_line
GNL_BUILD_DIR := $(BUILD_DIR)/$(GNL_DIR)
LIBS := $(LIBFT_DIR)/libft.a $(MLX42_DIR)/build/libmlx42.a
CC := cc
CFLAGS := -Wextra -Werror -Wall -g #-O2 -MMD 
CPPFLAGS := -I$(INC_DIR) -I$(LIBFT_DIR)/include -I$(MLX42_DIR)/include -Iget_next_line
LDFLAGS := -L$(LIBFT_DIR) -L$(MLX42_DIR)/build
LDLIBS := -lft -lmlx42 -ldl -lglfw -lpthread -lm
DEV_FLAGS := -g -O0 -fno-omit-frame-pointer -fsanitize=address,undefined
GNL_SRC := $(GNL_DIR)/get_next_line.c \
	$(GNL_DIR)/get_next_line_utils.c
SRC_FILES := main.c \
	utils.c \
	init_structs.c \
	intersections/color.c \
	intersections/field_of_view.c \
	intersections/plane_intersection.c \
	math/vec_utils.c \
	parser/parser.c \
	parser/read_lines.c \
	parser/validate.c 

SRC := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
GNL_OBJS := $(patsubst $(GNL_DIR)/%.c,$(GNL_BUILD_DIR)/%.o,$(GNL_SRC))
DEP := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS) $(LIBS) $(GNL_OBJS)
	@$(CC) $(OBJS) $(GNL_OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $<.."
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@echo "Object files created."

$(GNL_BUILD_DIR)/%.o: $(GNL_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@echo "Object files created."

$(LIBFT_DIR)/libft.a:
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX42_DIR)/build/libmlx42.a:
	@cmake $(MLX42_DIR) -B $(MLX42_DIR)/build
	@cmake --build $(MLX42_DIR)/build --parallel
	@echo "MLX42 library build successfully"

-include $(DEP)

clean:
	@rm -rf $(BUILD_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(MLX42_DIR)/build
	@echo "Object files cleaned."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re

#-Ofast for faster compilation or O2