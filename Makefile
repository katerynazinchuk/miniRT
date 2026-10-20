NAME := minirt
INC_DIR := include
BUILD_DIR := obj
SRC_DIR := src
LIBFT_DIR := libft
MLX42_DIR := MLX42

LIBS := $(LIBFT_DIR)/libft.a $(MLX42_DIR)/build/libmlx42.a

CC := cc
CFLAGS := -Wextra -Werror -Wall -g -O3 -MMD

CPPFLAGS := -I$(INC_DIR) -I$(LIBFT_DIR)/include -I$(MLX42_DIR)/include
LDFLAGS := -L$(LIBFT_DIR) -L$(MLX42_DIR)/build
LDLIBS := -lft -lmlx42 -ldl -lglfw -lpthread -lm

VALG_FLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes

COMMON_FILES := main.c \
	utils.c \
	init_structs.c \
	intersections/color.c \
	intersections/color_utils.c \
	intersections/field_of_view.c \
	intersections/hit_cylinder_body.c \
	intersections/hit_cylinder_caps.c \
	intersections/hit_objects.c \
	intersections/hit_sphere_plane.c \
	math/vec_math.c \
	math/vec_utils.c \
	parser/parse_element.c \
	parser/read_lines.c \
	parser/parse_plane.c \
	parser/parse_sphere.c \
	parser/parse_cylinder.c \
	parser/parser_utils.c \
	parser/validate.c

MANDATORY_FILES := 	light/light.c \
	parser/parse_light.c \
	parser/validate_line.c

BONUS_FILES :=	light/light_bonus.c \
	light/specular_reflection.c \
	parser/parse_light_bonus.c \
	parser/validate_line_bonus.c \

ifdef BONUS_FLAG
	SRC_FILES := $(COMMON_FILES) $(BONUS_FILES)
else
	SRC_FILES := $(COMMON_FILES) $(MANDATORY_FILES)
endif

SRC := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
DEP := $(OBJS:.o=.d)

all: $(NAME)

bonus:
	@$(MAKE) BONUS_FLAG=1 all

$(NAME): $(OBJS) $(LIBS) 
	@$(CC) $(OBJS)  $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@echo "Build successful: $(NAME)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $<.."
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

valg:
	@valgrind $(VALGRIND_FLAGS) --suppressions=MLX.supp ./$(NAME) $(FILE)

.PHONY: all clean fclean re valg bonus