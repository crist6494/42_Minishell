# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/21 10:01:41 by anmarque          #+#    #+#              #
#    Updated: 2023/02/09 19:37:10 by cmorales         ###   ########.fr        #
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

# SYMBOLS
INFO = $(CYAN) ℹ️
SUCCESS = $(GREEN)✅
WARNING = $(WHITE)[$(YELLOW)⚠️$(WHITE)] $(YELLOW)
ERROR = $(WHITE)[$(RED)❌$(WHITE)] $(RED)
WARNING = $(WHITE)[$(YELLOW)⚠️$(WHITE)] $(YELLOW)
TRASH = $(RED) 🗑

# Path
OBJ_PATH = ./obj/
INCDIR = includes

# Source
SRC_NAME		=	ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
					ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
					ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
					ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c  ft_strcmp.c\
					ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c \
					ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c  \
					ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c \
					get_next_line.c ft_skip.c ft_memdel.c\
					ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
					ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
					ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c \
					
OBJ_NAME = $(SRC_NAME:.c=.o)

# Files
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

CC			= gcc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -I.

NAME		= libft.a

all:		obj $(NAME)
			
obj:
			@echo "$(INFO) Compiling libft...$(NOC)"	
			@mkdir -p $(OBJ_PATH)		

$(NAME):	$(OBJ)		
			@ar rc $(NAME) $(OBJ)
			@ranlib $(NAME)
			@echo "$(SUCCESS)Libft built successfuly!$(NOC)"

$(OBJ_PATH)%.o:%.c
			@$(CC) $(CFLAGS) -o $@ -c $<

clean:
			@echo "$(TRASH) Deleting libft.o files ..."
			@$(RM) $(OBJ_PATH)
			@echo "$(SUCCESS)Libft.o files deleted successfuly!$(NOC)"
			

fclean:		clean
			@$(RM) $(NAME)

re:	fclean $(NAME)

.PHONY:			all clean fclean re bonus