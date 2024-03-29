# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 14:06:14 by sbalk             #+#    #+#              #
#    Updated: 2024/01/12 09:55:59 by sbalk            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIB_DIR		= libs/libft/
LIB_NAME	= libft.a
READLINE_DIR = libs/readline/
READLINE_DIR_SUB = libs/readline/lib/
READLINE_NAME = libreadline.a
READLINE_INSTALL_DIR = libs/readline-install/
CC			= cc
CFLAGS		= -Werror -Wall -Wextra
RM			= rm
SRC_DIR		= src/
OBJ_DIR		= obj/
INCLUDE		= -I include -I libs/libft/include -I libs/readline/include


# Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SRC_FILES	=	main \
				builtins/builtins \
				builtins/cd \
				builtins/echo \
				builtins/env_a \
				builtins/env_b \
				builtins/exit_a \
				builtins/export_a \
				builtins/export_b \
				builtins/pwd \
				builtins/unset_a \
				utils/colors_a \
				utils/colors_b \
				utils/exit_with_code \
				utils/history_a \
				utils/history_b \
				utils/util_lst_a \
				utils/util_lst_b \
				utils/util_lst_c \
				utils/util_strings_a \
				utils/util_strings_b \
				utils/util_strings_c \
				utils/dealloc \
				prompt/prompt \
				init/init_structs \
				error/error_handling \
				error/error_checks \
				free/free_ms \
				free/free_token \
				free/free_expander \
				free/free_parser \
				free/free_cmd_io \
				lexer/lexer \
				lexer/lexer_token_logic \
				lexer/lexer_list_functions \
				expander/checks \
				expander/create_chunks \
				expander/env_checks \
				expander/expand_variable \
				expander/expand_word_chunks \
				expander/expander \
				expander/join_chunks \
				expander/list_functions \
				parser/parser \
				parser/error \
				parser/cmd_list_functions \
				parser/redir_list_functions \
				executer/executer \
				executer/error \
				executer/check_redirections \
				executer/execute \
				executer/utils \
				executer/redirections \
				executer/check_command \
				executer/checks \
				executer/heredoc/heredoc \
				executer/heredoc/heredoc_expand \
				executer/heredoc/heredoc_utils \
				signal_handling/tty \
				signal_handling/signal \


H_FILES		=	include\builtins.h \
				include\executer.h \
				include\exepander.h \
				include\lexer.h \
				include\minishell.h \
				include\parser.h 

SRC				=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ				=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

all:		readline_install $(NAME)

$(NAME):	$(OBJ)
			@make -C $(LIB_DIR)
			@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L $(LIB_DIR) -lft -L $(READLINE_DIR_SUB) -lreadline -lhistory -lncurses -ltermcap
			@echo "$(GREEN)Created $(NAME)!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			@mkdir -p $(OBJ_DIR)
			@mkdir -p $(OBJ_DIR)/utils
			@mkdir -p $(OBJ_DIR)/builtins
			@mkdir -p $(OBJ_DIR)/prompt
			@mkdir -p $(OBJ_DIR)/init
			@mkdir -p $(OBJ_DIR)/lexer
			@mkdir -p $(OBJ_DIR)/expander
			@mkdir -p $(OBJ_DIR)/parser
			@mkdir -p $(OBJ_DIR)/executer
			@mkdir -p $(OBJ_DIR)/error
			@mkdir -p $(OBJ_DIR)/free
			@mkdir -p $(OBJ_DIR)/executer
			@mkdir -p $(OBJ_DIR)/executer/heredoc
			@mkdir -p $(OBJ_DIR)/signal_handling
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
			@$(RM) -rf $(OBJ_DIR)
			@make clean -C $(LIB_DIR)
			@make clean -C $(READLINE_INSTALL_DIR)
			@echo "$(BLUE)$(NAME) Object files cleaned!$(DEF_COLOR)"
			@echo "$(BLUE)$(NAME) Readline install files cleaned!$(DEF_COLOR)"

fclean:		clean
			@make fclean -C $(LIB_DIR)
			@$(RM) -rf $(READLINE_DIR)
			@$(RM) -f $(NAME)
			@echo "$(CYAN)$(NAME) Readline lib cleaned!$(DEF_COLOR)"
			@echo "$(CYAN)$(NAME) Executable files cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for $(NAME)!$(DEF_COLOR)"

norm:
			@norminette $(SRC) include/$(NAME).h| grep -v Norme -B1 || true

git:		fclean
			@git status
			@git add *
			@git status

readline_install:
			@if [ ! -f "$(READLINE_DIR_SUB)$(READLINE_NAME)" ]; then \
				export CURRENT_DIRECTORY="$(shell pwd)" && \
				mkdir -p $(READLINE_DIR) && \
				cd $(READLINE_INSTALL_DIR) && \
				./configure --prefix=$$CURRENT_DIRECTORY/$(READLINE_DIR) && \
				make && \
				make install-static; \
			fi

.PHONY:		all clean fclean re norm git readline_install
