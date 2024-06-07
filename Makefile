NAME= minishell

INCLUDES = includes

SRCS=	srcs/main/main.c \
		srcs/init/init.c \
		srcs/init/init_prompt.c \
		srcs/lexer/lexer_main.c \
		srcs/errors/errors.c \
		srcs/syntax/check_syntax.c \
		srcs/lexer/lexer_funcs.c \
		srcs/lexer/lexer_info_fill.c \
		srcs/lexer/lexer_llist_utils.c \
		srcs/env/envp.c \
		srcs/env/envp_utils.c \
		srcs/env/envp_get_set.c \
		srcs/cleanup/clean.c \
		srcs/parser/parser_cmds.c \
		srcs/parser/parser_files.c \
		srcs/parser/parser_funcs.c \
		srcs/parser/parser_main.c \
		srcs/parser/parser_free.c \
		srcs/parser/parser_path.c \
		srcs/builtins_stan/cd_new.c \
		srcs/builtins_stan/env.c \
		srcs/builtins_stan/export.c \
		srcs/builtins_stan/echo.c \
		srcs/execution/execute.c \
		srcs/execution/check_files.c \
		srcs/parser/ft_strreplace.c \
		#srcs/builtins/pwd.c \
		#rcs/builtins/cd.c \
		#srcs/builtins/env.c \
		#srcs/builtins/echo.c \

CC= gcc

CFLAGS= -Wall -Wextra -Werror -I$(INCLUDES)

LIBFT = 	lib
LIBFT_LIB = $(LIBFT)/my_lib.a

# SANITIZE= -g3 -fsanitize=address
SANITIZE= -g

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
			@echo "\n\nCompiling LIBFT: (loading bar - courtesy of rrouille)\n"
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
