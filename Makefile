NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -pedantic
INCLUDES	= -I./includes -I./Libft -I./mlx_linux

SRC_DIR		= srcs
LIBFT_DIR	= Libft
MLX_DIR		= mlx_linux

LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

SRCS		= main.c \
			  $(SRC_DIR)/validate_input.c \
			  $(SRC_DIR)/init_structs.c \
			  $(SRC_DIR)/read_file.c \
			  $(SRC_DIR)/identify_elements.c \
			  $(SRC_DIR)/parse_file.c \
			  $(SRC_DIR)/parse_texture.c \
			  $(SRC_DIR)/parse_color.c \
			  $(SRC_DIR)/extract_map.c \
			  $(SRC_DIR)/validate_map_borders.c \
			  $(SRC_DIR)/validate_map_chars.c \
			  $(SRC_DIR)/validate_map.c \
			  $(SRC_DIR)/cleanup.c \
			  $(SRC_DIR)/utils/parse_utils.c \
			  $(SRC_DIR)/utils/parse_texture_utils.c \
			  $(SRC_DIR)/utils/parse_color_utils.c \
			  $(SRC_DIR)/utils/extract_map_utils.c \
			  $(SRC_DIR)/utils/validate_map_chars_utils.c \
			  $(SRC_DIR)/utils/validate_map_borders_utils.c \
			  $(SRC_DIR)/utils/init_structs_utils.c \
			  $(SRC_DIR)/utils/cleanup_utils.c \
			  $(SRC_DIR)/utils/read_file_utils.c \
			  $(SRC_DIR)/errors/parse_file_errors.c

OBJS		= $(SRCS:.c=.o)

GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
GRAY		= \033[0;90m
RESET		= \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@echo "$(GRAY)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(GRAY)Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory > /dev/null 2>&1

$(MLX):
	@echo "$(GRAY)Compiling MLX...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) --no-print-directory > /dev/null 2>&1

clean:
	@echo "$(GRAY)Cleaning object files...$(RESET)"
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory > /dev/null 2>&1
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory > /dev/null 2>&1

fclean: clean
	@echo "$(GRAY)Cleaning executable and libraries...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory > /dev/null 2>&1
	@echo "$(GREEN)All cleaned!$(RESET)"

re: fclean all

test: $(NAME)
	@echo "$(YELLOW)Running test with maps/test.cub...$(RESET)"
	@./$(NAME) maps/test.cub

debug: CFLAGS += -g -fsanitize=address -DDEBUG
debug: 
	@echo "$(GRAY)Building in debug mode with AddressSanitizer...$(RESET)"
	@$(MAKE) re --no-print-directory
	@echo "$(GRAY)(Debug mode enabled)$(RESET)"

.PHONY: all clean fclean re test debug
.SILENT: