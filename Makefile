NAME= minishell

INCLUDES = includes

SRCS= 	srcs/main/main.c \
		srcs/init/init.c \
		srcs/lexer/lexer_main.c \
		srcs/errors/errors.c \
		srcs/syntax/check_syntax.c \
		srcs/lexer/lexer_funcs.c \
		srcs/lexer/lexer_info_fill.c \
		srcs/lexer/lexer_llist_utils.c \
#		srcs/parser/parser.c \
		srcs/parser/parser_linked_utils.c \
		
		

CC= gcc

CFLAGS= -Wall -Wextra -Werror -I$(INCLUDES)

LIBFT = 	lib
LIBFT_LIB = $(LIBFT)/my_lib.a

SANITIZE= -g3 -fsanitize=address

# Color Variables
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
MAGENTA=\033[0;35m
CYAN=\033[0;36m
WHITE=\033[0;37m
RESET=\033[0m

.PHONY: all clean fclean re libft header

all: $(NAME)

header:
		@echo "$(CYAN) _______  __    __   __         .______        ___      .__   __.   _______  _______ .______          _______.";
		@echo "$(RED)|   ____||  |  |  | |  |        |   _  \      /   \     |  \ |  |  /  _____||   ____||   _  \        /       |";
		@echo "$(CYAN)|  |__   |  |__|  | |  |        |  |_)  |    /  ^  \    |   \|  | |  |  __  |  |__   |  |_)  |      |   (----\`";
		@echo "$(RED)|   __|  |   __   | |  |        |   _  <    /  /_\  \   |  . \`  | |  | |_ | |   __|  |      /        \   \    ";
		@echo "$(CYAN)|  |____ |  |  |  | |  \`----.   |  |_)  |  /  _____  \  |  |\   | |  |__| | |  |____ |  |\  \----.----)   |   ";
		@echo "$(RED)|_______||__|  |__| |_______|   |______/  /__/     \__\ |__| \__|  \______| |_______|| _| \`._____|_______/    $(RESET)";


$(NAME) : $(SRCS)
			@$(MAKE) header
			@echo "\n\nCompiling LIBFT: (courtesy of rrouille)\n"
			@make -C $(LIBFT) all
			@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_LIB) -lreadline $(SANITIZE)
			@echo "$(YELLOW)\no------------------------------------o$(RESET)"
			@echo "$(GREEN)|           MINISHELL_COMPILED       |$(RESET)"
			@echo "$(YELLOW)o------------------------------------o\n$(RESET)"

clean:
	@$(MAKE) header
	@echo "${RED}\nCleaning up...${RESET}"
	@rm -f $(NAME)
	@echo "${GREEN}Cleanup done.${RESET}"

fclean: 	clean
		@make -C $(LIBFT) fclean
		@rm -f $(NAME)
		@rm -rf objs
		@echo "$(YELLOW)\no------------------------------------o$(RESET)"
		@echo "$(RED)|           MINISHELL_CLEARED        |$(RESET)"
		@echo "$(YELLOW)o------------------------------------o\n$(RESET)"

re: 			fclean all
