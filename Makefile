NAME		:= cub3D

SRCS_DIR	:= ./src
OBJS_DIR	:= ./obj

SRCS		:=	main.c init.c parse.c check.c \
				utils.c free.c map.c error.c \
				frames.c draw.c utils2.c utils3.c \
				rays.c shapes.c mlx.c door.c \
				draw2.c utils4.c\
				
OBJS		:= $(SRCS:%.c=$(OBJS_DIR)/%.o)

CC			:= gcc -Wall -Werror -Wextra

# FLAGS		:= -fsanitize=address
MFLAGS 		:= -framework OpenGL -framework AppKit

# -L "folder" to looks for library in the folder
# -l(ft) to link library file. l replaces lib
# -I is to look for header file in folder
LIB_FT		:= -L libft -lft
LIB_MLX		:= -L mlx -lmlx $(MFLAGS)
LIBRARY		:= $(LIB_FT) $(LIB_MLX)
INCLUDES	:= -I mlx -I libft -I includes

GETNEXTLINE = get_next_line/*.c

RED		:= \033[0;31m
GREEN	:= \033[0;32m
BLUE	:= \033[0;34m
PURPLE	:= \033[0;35m
YELLOW	:= \033[0;33m
CYAN	:= \033[0;36m
NC		:= \033[0m

# target : prerequisites
# <TAB> recipe
all	: $(NAME)

# "make -C" run make in specific folder
# "-I" is  to look for header file in folder
# "$<" is to match prerequisites
# "$@" is to match target
# '@' before every recipe to silence it in terminal
$(NAME)	: $(OBJS)
	@echo "$(GREEN)Compiling Libft...$(NC)"
	@make -C ./libft
	$(CC) $(FLAGS) $(OBJS) $(LIBRARY) $(GETNEXTLINE) $(INCLUDES) -o $@
	@echo "$(GREEN)Cub3D Compiled Successful.$(NC)"

# "mkdir -p" creates dir if necessary, if dir exist, no error specified
# "gcc -c" is to create .o files or object files
# "gcc -o 'file' " use as a naming feature / place the output result to 'file'
$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

# "echo -e" to allow backslash escapes \ 
clean :
	@rm -rf $(OBJS_DIR)
	@make clean -C ./libft
	@echo "$(YELLOW)Cleaned.$(NC)"

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C ./libft
	@echo "$(RED)Full Cleaned.$(NC)"

re: fclean all

.PHONY: all clean fclean re
