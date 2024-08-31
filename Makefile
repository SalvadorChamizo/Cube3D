MAKEFLAGS += --no-print-directory

NAME = cub3D
NAME_BNS = cub3D_bonus
CC = clang
RM = rm -f

FLAGS = -g -Wall -Werror -Wextra -Iinclude #-fsanitize=address
MLX_FLAGS = -ldl -lglfw -pthread -lm

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a
MLX_PATH = ./MLX42
MLX = $(MLX_PATH)/libmlx42.a

FILES =	main \
		check_map_borders \
		check_textures \
		check_utils \
		errors \
		get_map_utils \
		get_map \
		get_texture \
		parser \
		textures \
		game \

BNS_FILES = main_bonus \

$(shell mkdir -p ./src/obj)
$(shell mkdir -p ./src/obj/charge_flag_makefile)
$(shell mkdir -p ./bonus/src_bonus/obj)

SRCS_DIR = ./src/

OBJS_DIR = ./src/obj/

SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

BNS_SRC_DIR = ./bonus/src_bonus/
BNS_OBJ_DIR = ./bonus/src_bonus/obj/
BNS_SRCS = $(addprefix $(BNS_SRC_DIR), $(addsuffix .c, $(BNS_FILES)))
BNS_OBJS = $(addprefix $(BNS_OBJ_DIR), $(addsuffix .o, $(BNS_FILES)))

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(CC) $(FLAGS) -c $< -o $@

$(BNS_OBJ_DIR)%.o: $(BNS_SRC_DIR)%.c
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJS) $(OBJS_DIR)/charge_flag_makefile/charge.flag
	@$(CC) $(OBJS) $(MLX) $(LIBFT) $(FLAGS) $(MLX_FLAGS) -o $(NAME)
	@echo
	@echo "$(MAGENTA)Cub3D compiled!$(RESET)"
	@echo

bonus: $(NAME_BNS)

$(NAME_BNS): $(BNS_OBJS) $(OBJS_DIR)/charge_flag_makefile/bonus.flag
	@$(CC) $(BNS_OBJS) $(MLX) $(FLAGS) -lpthread -o $(NAME_BNS)
	@echo
	@echo "$(BLUE)Cub3D bonus compiled!$(RESET)"
	@echo

$(LIBFT):
	@make -C $(LIBFT_PATH) all

$(MLX):
	@make -C $(MLX_PATH) all

clean: 
	@$(RM) $(OBJS) $(BNS_OBJS) $(OBJS_DIR)/charge_flag_makefile/charge.flag
	@make -C $(LIBFT_PATH) clean
	@make -C $(MLX_PATH) clean
	@$(RM) $(OBJS_DIR)/charge_flag_makefile/bonus.flag:
	@echo
	@echo "$(RED)Cleaning Cub3D objects. $(RESET)"
	$(shell rm -rf ./src/obj)
	$(shell rm -rf ./bonus/src_bonus/obj)

fclean: clean
	@$(RM) $(NAME) $(NAME_BNS) $(MLX)
	@make -C $(LIBFT_PATH) fclean
	@echo "$(RED)Cleaning Cub3D executables.$(RESET)"
	@echo

re: fclean setup $(NAME)

setup:
	$(shell mkdir -p ./src/obj)
	$(shell mkdir -p ./src/obj/charge_flag_makefile)
	$(shell mkdir -p ./bonus/src_bonus/obj)

.PHONY: clean fclean re all bonus setup

# Colors
MAGENTA = \033[35;1m
YELLOW  = \033[33;1m
GREEN   = \033[32;1m
WHITE   = \033[37;1m
RESET   = \033[0m
GRAY    = \033[0;90m
BLUE    = \033[34;1m
CYAN    = \033[37;1m
BOLD    = \033[1m
RED     = \033[31;1m

# Rule for the charging bar
$(OBJS_DIR)/charge_flag_makefile/charge.flag:
	@echo
	@echo -n "$(GREEN)Compiling: $(RESET)["
	@for i in $$(seq 1 2); do \
		echo -n "##"; \
		sleep 0.20; \
	done
	@for i in $$(seq 1 6); do \
		echo -n "####"; \
		sleep 0.10; \
	done
	@echo "] $(GREEN)Done!$(RESET)"
	@touch $(OBJS_DIR)/charge_flag_makefile/charge.flag

# Rule for the bonus charging bar
$(OBJS_DIR)/charge_flag_makefile/bonus.flag:
	@echo
	@echo -n "$(YELLOW)Compiling bonus: $(RESET)["
	@for i in $$(seq 1 2); do \
		echo -n "##"; \
		sleep 0.20; \
	done
	@for i in $$(seq 1 6); do \
		echo -n "####"; \
		sleep 0.10; \
	done
	@echo "] $(YELLOW)Done!$(RESET)"
	@touch $(OBJS_DIR)/charge_flag_makefile/bonus.flag
