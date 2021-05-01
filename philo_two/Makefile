# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/06 17:11:11 by adbenoit          #+#    #+#              #
#    Updated: 2021/05/01 21:45:59 by adbenoit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo_two

INC				=	inc/

HEADER			=	$(INC)philo_two.h

SRC_PATH		=	src/

SRC				=	main.c		init.c			print.c \
					utils.c		simulation.c	philo_action.c

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror

OBJ_PATH		=	obj/

OBJ_NAME		=	$(SRC:.c=.o)

OBJ				=	$(addprefix $(OBJ_PATH),$(OBJ_NAME))

$(NAME) : $(OBJ)
	@printf "\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -pthread
	@echo "Compilation of \033[33;1m$(NAME)\033[0;1m: [\033[1;32mOK\033[0;1m]\033[0m"

all: $(NAME) 

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c $(HEADER)
	@printf "\033[34;1m|\033[0;m"
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_PATH)
	@echo "\033[33;1m$(NAME)\033[0;1m: objects deleted\033[0m"

fclean:	clean
	@rm -rf $(NAME)
	@echo "\033[33;1m$(NAME)\033[0;1m: $(NAME) deleted\033[0m"

re: fclean all

FILE=norme_error.txt
ERROR= `cat $(FILE) | grep -B 1 "Error"`
norme:
	@printf "\033[33mLaunching ...\033[0m"
	@norminette */*/*c */*c */*h > $(FILE)
	@printf "\rNorme of \033[33;1m$(NAME)\033[0;1m: [\033[1;32mOK\033[0;1m]\033[0m"
	@echo "$(ERROR)"
	@rm $(FILE)
	

debug:
	@echo "\033[34;1mOBJ\033[0;m = $(OBJ)"
	@echo "\033[34;1mSRC\033[0;m = $(SRC_PATH)$(SRC)"
	@echo "\033[34;1mHEADER\033[0;m = $(HEADER)\n"

.PHONY: all clean fclean re run
