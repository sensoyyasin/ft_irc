# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
<<<<<<< HEAD
#    By: ysensoy <ysensoy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/23 22:16:26 by yasinsensoy       #+#    #+#              #
#    Updated: 2023/05/02 16:23:28 by ysensoy          ###   ########.fr        #
=======
#    By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 13:07:52 by mtemel            #+#    #+#              #
#    Updated: 2023/05/08 13:20:27 by mtemel           ###   ########.fr        #
>>>>>>> 28184583832779898723191b451770961cc0f9db
#                                                                              #
# **************************************************************************** #

NAME = ircserv
CC = c++
<<<<<<< HEAD
SRCS = $(wildcard headers/*.cpp srcs/*.cpp cmds/*.cpp)
OBJ = $(SRCS:.cpp = .o)
=======
FLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = $(wildcard srcs/*.cpp cmds/*.cpp headers/*.cpp)
OBJS = $(SRCS:.cpp = .o)
>>>>>>> 28184583832779898723191b451770961cc0f9db

$(NAME): $(OBJS)
		@$(CC) $(FLAGS) $(SRCS) -o $(NAME)
		@echo "\033[1;32mCOMPILED SUCCESSFULLY\033[0m"

all: $(NAME)

clean:
		@echo "\033[1;32mCLEAN\033[0m"
		@rm -rf $(NAME)

fclean:
		@echo "\033[1;32mFCLEAN\033[0m"
		@make clean

re:
		@echo "\033[1;32mREMAKE\033[0m"
		@make fclean
		@make all

exe:
		@echo "\033[1;32mSTART EXECUTING\033[0m"
		@./$(NAME)
		@echo "\033[1;32mDONE EXECUTING\033[0m"
