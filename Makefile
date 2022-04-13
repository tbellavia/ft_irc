# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/12 19:27:05 by bbellavi          #+#    #+#              #
#    Updated: 2022/04/13 00:58:50 by bbellavi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX			= c++
CXXFLAGS	= -Wall -Werror -Wextra -std=c++98

SRCS		=	main.cpp \
				srcs/Utils.cpp

HEADERS		=	include/irc/Channel.hpp				\
				include/irc/User.hpp				\
				include/irc/Server.hpp				\
				include/network/Network.hpp			\
				include/network/Selector.hpp		\
				include/network/SelectorValue.hpp	\
				include/network/Socket.hpp			\
				include/Utils.hpp

INCLUDE_DIR	= include/

.PHONY: re clean fclean

NAME = ft_irc

all: $(NAME)

$(NAME): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(SRCS) -I $(INCLUDE_DIR)

re: fclean all

clean: fclean

fclean:
	rm -f $(NAME)