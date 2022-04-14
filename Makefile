# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/12 19:27:05 by bbellavi          #+#    #+#              #
#    Updated: 2022/04/14 23:47:03 by bbellavi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX			= c++
CXXFLAGS	= -Wall -Werror -Wextra -std=c++98

SRCS		=	main.cpp						\
				srcs/Utils.cpp					\
				srcs/network/Selector.cpp		\
				srcs/network/SelectorValue.cpp	\
				srcs/network/Socket.cpp			\
				srcs/network/Network.cpp		\
				srcs/irc/Server.cpp				\
				srcs/irc/Channel.cpp			\
				srcs/irc/Channels.cpp			\
				srcs/irc/User.cpp				\

HEADERS		=	include/irc/Channel.hpp				\
				include/irc/User.hpp				\
				include/irc/Server.hpp				\
				include/network/Network.hpp			\
				include/network/Selector.hpp		\
				include/network/SelectorValue.hpp	\
				include/network/Socket.hpp			\
				include/Utils.hpp

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