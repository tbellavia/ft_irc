# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/12 19:27:05 by bbellavi          #+#    #+#              #
#    Updated: 2022/05/09 09:47:50 by lperson-         ###   ########.fr        #
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
				srcs/irc/ICmdFactory.cpp		\
				srcs/irc/CmdFactory.cpp			\
				srcs/irc/CmdCtx.cpp				\
				srcs/irc/ACmd.cpp				\
				srcs/irc/Action.cpp				\
				srcs/irc/Actions.cpp			\
				srcs/irc/IRCApi.cpp				\
				srcs/irc/cmd/CmdPONG.cpp		\
				srcs/irc/cmd/CmdPASS.cpp		\
				srcs/irc/cmd/CmdNICK.cpp		\
				srcs/irc/cmd/CmdQUIT.cpp		\
				srcs/irc/ISubscriber.cpp		\
				srcs/irc/User.cpp				\
				srcs/irc/Users.cpp				\
				srcs/irc/Channels.cpp			\
				srcs/irc/Channel.cpp			\
				srcs/irc/MasterUsers.cpp		\
				srcs/irc/Server.cpp

HEADERS		=	include/irc/Server.hpp				\
				include/irc/User.hpp				\
				include/irc/Users.hpp				\
				include/irc/Channel.hpp				\
				include/irc/Channels.hpp			\
				include/irc/MasterUsers.hpp			\
				include/irc/IRCApi.hpp				\
				include/irc/Action.hpp				\
				include/irc/Actions.hpp				\
				include/irc/CmdFactory.hpp			\
				include/irc/CmdCtx.hpp				\
				include/irc/cmd/CmdPASS.hpp			\
				include/irc/cmd/CmdPONG.hpp			\
				include/irc/cmd/CmdNICK.hpp			\
				include/irc/cmd/CmdQUIT.hpp			\
				include/network/Network.hpp			\
				include/network/Selector.hpp		\
				include/network/File.hpp			\
				include/network/Socket.hpp			\
				include/Utils.hpp					\
				include/App.hpp

INC_DIR			= include/
INC_DIRS		= irc network irc/cmd
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