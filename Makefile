# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 20:40:36 by anmarque          #+#    #+#              #
#    Updated: 2023/02/13 18:32:25 by cmorales         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLORS
NOC         = \033[0m
BOLD        = \033[1m
UNDERLINE   = \033[4m
BLACK       = \033[1;30m
RED         = \033[31m
GREEN       = \033[32m 
YELLOW      = \033[1;33m
BLUE        = \033[1;34m
VIOLET      = \033[1;35m
CYAN        = \033[36m
WHITE       = \033[1;37m

INFO = $(CYAN) ℹ️
SUCCESS = $(GREEN)✅
WARNING = $(WHITE)[$(YELLOW)⚠️$(WHITE)] $(YELLOW)
ERROR = $(WHITE)[$(RED)❌$(WHITE)] $(RED)
WARNING = $(WHITE)[$(YELLOW)⚠️$(WHITE)] $(YELLOW)
TRASH = $(RED) 🗑


NAME = minishell

SRC_DIR = ./src/
OBJ_DIR = ./obj/

CC = gcc

CFLAGS = -Wall -Wextra -Werror -MD -g3  -I /Users/cmorales/.brew/opt/readline/include

LIBFT = -L libft -lft

READLINE = -lreadline -L /Users/cmorales/.brew/opt/readline/lib

HEADER = minishell.h

PARSING = line tokens

ENV = env1 env2 env3

TOOLS = fd parser token type free

BUILTINS = echo pwd env exit

EXEC = exec builtins

SRCS = 	$(addsuffix .c, $(addprefix env/, $(ENV))) \
		$(addsuffix .c, $(addprefix parser/, $(PARSING))) \
		$(addsuffix .c, $(addprefix utils/, $(TOOLS))) \
		$(addsuffix .c, $(addprefix builtins/, $(BUILTINS))) \
		$(addsuffix .c, $(addprefix exec/, $(EXEC))) \
		main.c \
		redir.c \
		signal.c \

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))


all: lib  obj $(NAME)

obj:
	@echo "$(INFO) Creating objects folder... $(NOC)"
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parser
	@mkdir -p $(OBJ_DIR)/utils
	@mkdir -p $(OBJ_DIR)/env
	@mkdir -p $(OBJ_DIR)/builtins
	@mkdir -p $(OBJ_DIR)/exec

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -I ./includes/ -I ./libft/ -o $@ -c $<
-include $(OBJ_DIR)*.d

$(NAME): $(OBJS)
	@echo "$(INFO) Building $(NAME)...$(NOC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(READLINE)
	@echo "$(SUCCESS)$(NAME) built successfully!$(NOC)"

%.o: %.c
	@printf "$(WARNING)Generando objetos ... %-33.33s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@
	
lib:
	@make -C ./libft
	@echo "$(NOC)"


clean:
	@make clean -C libft/
	@echo "$(NOC)"
	@echo "$(TRASH) Deleting .o files...$(NOC)"
	@rm -rf obj $(OBJS) 
	@echo "$(SUCCESS).o files deleted successfully!$(NOC)"
	
fclean: clean
	@echo "$(TRASH) Deleting $(NAME)...$(NOC)"
	@rm -rf obj $(NAME) 
	@echo "$(SUCCESS)$(NAME) deleted successfully!$(NOC)"

re: fclean all

test: all
	./minishell

norm:
	norminette $(SRCS) includes/$(HEADER)


.PHONY:	all clean fclean re

