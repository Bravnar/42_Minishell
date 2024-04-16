# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/08 19:50:57 by smuravyev         #+#    #+#              #
#    Updated: 2024/04/11 18:56:47 by smuravye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 		minishell
HEAD_DIR = 	includes
SRCS_DIR = 	srcs/
OBJS_DIR = 	objs/
LIBFT = 	lib
CC = 		gcc
CFLAGS = 	-Wall -Werror -Wextra -I
#SANITIZE = -g3 -fsanitize=address

# Color Variables
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
MAGENTA=\033[0;35m
CYAN=\033[0;36m
WHITE=\033[0;37m
RESET=\033[0m

SRCS_DOCS=	main \
			lexer \
			lexer_utils \
			lexer_count \
			
			
SRCS= 		$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRCS_DOCS)))
OBJS=		$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS_DOCS)))

OBJS_EXISTS=	.cache_exists

$(NAME): $(OBJS)
					@echo "\n\nCompiling LIBFT: (courtesy of rrouille)\n"
					@make -C $(LIBFT) all
					@$(CC) -o $(NAME) $(OBJS) $(LIBFT)/my_lib.a -lreadline $(SANITIZE)
					@echo "$(YELLOW)\no------------------------------------o$(RESET)"
					@echo "$(GREEN)|           MINISHELL_COMPILED       |$(RESET)"
					@echo "$(YELLOW)o------------------------------------o\n$(RESET)"

all:			$(NAME)

$(OBJS_DIR)%.o:		$(SRCS_DIR)%.c | $(OBJS_EXISTS)
						@$(CC) $(CFLAGS) $(HEAD_DIR) -o $@ -c $< $(SANITIZE)
						@printf	"\033[KCompiling project -----------> $<\r"
					
$(OBJS_EXISTS):
					@mkdir -p $(OBJS_DIR)
	
clean:
					@rm -rf $(OBJS_DIR)
					@make -C $(LIBFT) clean

fclean: 		clean
					@make -C $(LIBFT) fclean
					@rm -f $(NAME)
					@echo "$(YELLOW)\no------------------------------------o$(RESET)"
					@echo "$(RED)|           MINISHELL_CLEARED        |$(RESET)"
					@echo "$(YELLOW)o------------------------------------o\n$(RESET)"

re: 			fclean all

.PHONY: all clean fclean re libft