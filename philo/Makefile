# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 12:55:30 by juramos           #+#    #+#              #
#    Updated: 2024/05/20 19:58:25 by juramos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name
NAME 		= 	philo

# Compiler
CC 			= 	gcc
CFLAGS 		= 	-Wall -Werror -Wextra -g3 -fsanitize=address

# Sources
SRC_DIR 	= 	src/
SRC_FILES 	= 	main utils init time launch_threads
				
SRC 		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))

# Objects
OBJ_DIR 	= 	obj/
OBJ_DIRS	=	$(sort $(dir $(OBJ)))
OBJ 		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

# Includes
INC_MS		= -I includes/

# Colors
DEF_COLOR 	= 	\033[0;39m
GRAY 		= 	\033[0;90m
RED 		= 	\033[0;91m
GREEN 		=	\033[0;92m
YELLOW 		=	\033[0;93m
BLUE 		=	\033[0;94m
MAGENTA 	=	\033[0;95m
CYAN 		= 	\033[0;96m
WHITE 		= 	\033[0;97m

# Config
OBJF 		=	.cache_exists
MAKEFLAGS 	+=	--no-print-directory
.SILENT:

###

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	@echo "\033[0;33mCompiling ${notdir $<}			in	$(SRC_DIR)"
	@$(CC) $(CFLAGS) $(INC_MS) -c $< -o $@

$(OBJF):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p  $(OBJ_DIRS)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "$(GREEN)philo compiled!$(DEF_COLOR)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)philo object files cleaned!$(DEF_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(CYAN)philo executable files cleaned!$(DEF_COLOR)"

re: fclean all
	@echo "$(GREEN)Cleaned and rebuilt everything for philo!$(DEF_COLOR)"

norm:
	@norminette | grep -v Norme -B1 || true

.PHONY: all clean fclean re norm