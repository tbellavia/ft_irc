# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/12 19:27:05 by bbellavi          #+#    #+#              #
#    Updated: 2022/04/19 15:20:40 by bbellavi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX			= c++
CXXFLAGS	= -Wall -Werror -Wextra -std=c++98

SRCS		=	main.cpp						\
				srcs/Utils.cpp					\
				srcs/App.cpp					\
				srcs/network/Selector.cpp		\
				srcs/network/File.cpp			\
				srcs/network/Socket.cpp			\
				srcs/network/Network.cpp		\
				srcs/irc/User.cpp				\
				srcs/irc/Server.cpp

HEADERS		=	include/irc/Server.hpp				\
				include/irc/User.hpp				\
				include/network/Network.hpp			\
				include/network/Selector.hpp		\
				include/network/File.hpp			\
				include/network/Socket.hpp			\
				include/Utils.hpp					\
				include/App.hpp

INC_DIR			= include/
INC_DIRS		= irc network
INCLUDE_DIRS	= $(addprefix $(INC_DIR),${INC_DIRS})
INCLUDE_DIRS	+= include/

.PHONY: re clean fclean

NAME = ft_irc

all: $(NAME)

$(NAME): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(SRCS) $(addprefix -I ,$(INCLUDE_DIRS))

re: fclean all

clean: fclean

fclean:
	rm -f $(NAME)