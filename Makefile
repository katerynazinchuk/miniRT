NAME := minirt
INC_DIR := include
BUILD_DIR := obj
SRC_DIR := src
LIBFT_DIR := libft
MLX42_DIR := MLX42

LIBS := $(LIBFT_DIR)/libft.a $(MLX42_DIR)/build/libmlx42.a

CC := cc
CFLAGS := -Wextra -Werror -Wall -g -O3#-O2 -MMD 

CPPFLAGS := -I$(INC_DIR) -I$(LIBFT_DIR)/include -I$(MLX42_DIR)/include
LDFLAGS := -L$(LIBFT_DIR) -L$(MLX42_DIR)/build
LDLIBS := -lft -lmlx42 -ldl -lglfw -lpthread -lm

VALG_FLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes

DEV_FLAGS := -g -O0 -fno-omit-frame-pointer #-fsanitize=address,undefined

SRC_FILES := main.c \
	utils.c \
	init_structs.c \
	intersections/color.c \
	intersections/color_utils.c \
	intersections/field_of_view.c \
	intersections/hit_cylinder.c \
	intersections/hit_objects.c \
	intersections/hit_sphere_plane.c \
	light/light.c \
	light/specular_reflection.c \
	math/vec_math.c \
	math/vec_utils.c \
	parser/parser.c \
	parser/validate_line.c \
	parser/read_lines.c \
	parser/parse_light.c \
	parser/parse_plane.c \
	parser/parse_sphere.c \
	parser/parse_cylinder.c \
	parser/parser_utils.c \
	parser/validate.c

SRC := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
DEP := $(OBJS:.o=.d)

TEST_NAME := minirt_test
TEST_DIR := tests
TEST_BUILD_DIR := $(BUILD_DIR)/$(TEST_DIR)
TEST_SRC := $(TEST_DIR)/test_parser.c \
			$(TEST_DIR)/main_test.c
TEST_OBJ := $(patsubst $(TEST_DIR)/%.c,$(TEST_BUILD_DIR)/%.o,$(TEST_SRC))
#additional without main.c
MAIN_SRC_FILES := utils.c \
	init_structs.c \
	parser/*.c \
	math/*.c 

# 	parser/parser.c \
# 	parser/read_lines.c \
# 	parser/parse_plane.c \
# 	parser/parse_sphere.c \
# 	parser/parse_cylinder.c \
# 	parser/parser_utils.c \
# 	parser/parse_light.c \
# 	parser/validate.c \
# 	math/vec_utils.c 

# 	intersections/color.c \
# 	intersections/field_of_view.c \
# 	intersections/hit_cylinder.c \
# 	intersections/hit_objects.c \
# 	intersections/hit_sphere_plane.c \
# 	light/light.c \



MAIN_SRCS := $(addprefix $(SRC_DIR)/, $(MAIN_SRC_FILES))
MAIN_OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(MAIN_SRCS))

all: $(NAME)

$(NAME): $(OBJS) $(LIBS) 
	@$(CC) $(OBJS)  $(LDFLAGS) $(LDLIBS) -o $(NAME)


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

test: $(TEST_NAME)
$(TEST_NAME): $(MAIN_OBJS) $(LIBS) $(GNL_OBJS) $(TEST_OBJ)
	@$(CC) $(MAIN_OBJS) $(GNL_OBJS) $(TEST_OBJ) $(LDFLAGS) $(LDLIBS) -o $(TEST_NAME)

$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@echo "Object files for tests created."

test_fclean: fclean
	@rm -rf $(TEST_NAME)

valg:
	@valgrind $(VALGRIND_FLAGS) --suppressions=MLX.supp ./$(NAME) $(FILE)

.PHONY: all clean fclean re test test_fclean valg

#-Ofast for faster compilation or O2