# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: logan  <logan@42.us.org>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/13 10:03:24 by logan             #+#    #+#              #
#    Updated: 2018/10/20 18:59:13 by lkaser           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIST = main \
line_edit \
parse_command \
update_path \
expand util \
b_cd \
b_echo \
b_env \
b_exit \
b_path \
b_setenv \
b_unsetenv

OBJ_DIR = obj
VPATH = src:src/builtin

SRC = $(addsuffix .c, $(LIST))
OBJ = $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(LIST)))
DEP = $(OBJ:%.o=%.d)
CC = clang
SUB = libft

INCLUDES = -I libft/includes -I src

CPPFLAGS = -Wall -Wextra -Werror -g -O2 -march=native \
$(INCLUDES) \
#-fsanitize=address -fsanitize=undefined

LDFLAGS = -L libft -lft \
-flto=thin
#-fsanitize=address -fsanitize=undefined

all: $(NAME)

$(NAME): $(OBJ)
	@for s in $(SUB);\
	do\
		make -sC $$s;\
	done
	@printf "\e[32;1mLinking.. \e[0m\n"
	$(CC) $(LDFLAGS) -o $@ $^
	@printf "\e[32;1mCreated:\e[0m %s\n" $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

-include $(DEP)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@printf "\e[34;1mCompiling: \e[0m%s\n" $<
	$(CC) $(CPPFLAGS) -MMD -c $< -o $@

clean:
	@for s in $(SUB);\
	do\
		make -sC $$s clean;\
	done
	@printf "\e[31;1mCleaning..\e[0m\n"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@for s in $(SUB);\
	do\
		make -sC $$s fclean;\
	done
	@printf "\e[31;1mFull Cleaning..\e[0m\n"
	@rm -f $(NAME)
	@rm -rf $(NAME).dSYM

re:	fclean all

.PHONY: clean fclean all re
