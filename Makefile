# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/12 19:27:05 by bbellavi          #+#    #+#              #
#    Updated: 2022/05/19 14:34:03 by lperson-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX			= c++
CXXFLAGS	= -Wall -Werror -Wextra -std=c++98

SRC_DIR			= srcs
INC_DIR			= include

SRCS		=	main.cpp								\
				srcs/Utils.cpp							\
				srcs/App.cpp							\
				srcs/network/Selector.cpp				\
				srcs/network/File.cpp					\
				srcs/network/Socket.cpp					\
				srcs/network/Network.cpp				\
				srcs/irc/ICmdFactory.cpp				\
				srcs/irc/CmdFactory.cpp					\
				srcs/irc/CmdCtx.cpp						\
				srcs/irc/ACmd.cpp						\
				srcs/irc/Action.cpp						\
				srcs/irc/Actions.cpp					\
				srcs/irc/Replies.cpp					\
				srcs/irc/IRCApi.cpp						\
				srcs/irc/Config.cpp						\
				srcs/irc/Parse.cpp						\
				srcs/irc/CmdParser.cpp					\
				srcs/irc/Mode.cpp						\
				srcs/irc/cmd/CmdPASS.cpp				\
				srcs/irc/cmd/CmdUSER.cpp				\
				srcs/irc/cmd/CmdNICK.cpp				\
				srcs/irc/cmd/CmdJOIN.cpp				\
				srcs/irc/cmd/CmdWHO.cpp					\
				srcs/irc/cmd/CmdOPER.cpp				\
				srcs/irc/cmd/CmdQUIT.cpp				\
				srcs/irc/cmd/CmdPONG.cpp				\
				srcs/irc/cmd/CmdMODE/CmdMODEParse.cpp	\
				srcs/irc/cmd/CmdMODE.cpp				\
				srcs/irc/ISubscriber.cpp				\
				srcs/irc/User.cpp						\
				srcs/irc/Users.cpp						\
				srcs/irc/Channels.cpp					\
				srcs/irc/Channel.cpp					\
				srcs/irc/MasterUsers.cpp				\
				srcs/irc/Server.cpp

HEADERS		=	include/irc/Server.hpp					\
				include/irc/User.hpp					\
				include/irc/Users.hpp					\
				include/irc/Channel.hpp					\
				include/irc/Channels.hpp				\
				include/irc/MasterUsers.hpp				\
				include/irc/IRCApi.hpp					\
				include/irc/Config.hpp					\
				include/irc/Action.hpp					\
				include/irc/Actions.hpp					\
				include/irc/Replies.hpp					\
				include/irc/Role.hpp					\
				include/irc/Parse.hpp					\
				include/irc/CmdParser.hpp				\
				include/irc/CmdFactory.hpp				\
				include/irc/CmdCtx.hpp					\
				include/irc/cmd/CmdPASS.hpp				\
				include/irc/cmd/CmdNICK.hpp				\
				include/irc/cmd/CmdUSER.hpp				\
				include/irc/cmd/CmdOPER.hpp				\
				include/irc/cmd/CmdJOIN.hpp				\
				include/irc/cmd/CmdWHO.hpp				\
				include/irc/cmd/CmdPONG.hpp				\
				include/irc/cmd/CmdQUIT.hpp				\
				srcs/irc/cmd/CmdMODE/CmdMODEParse.hpp	\
				srcs/irc/cmd/CmdMODE.hpp				\
				include/network/Network.hpp				\
				include/network/Selector.hpp			\
				include/network/File.hpp				\
				include/network/Socket.hpp				\
				include/Utils.hpp						\
				include/App.hpp

SUBDIRS			= ${shell find ${SRC_DIR} -type d}

INCLUDE_DIRS	= $(shell find ${INC_DIR} -type d)
SRCDIRS			= $(SRC_DIR) $(addprefix $(SRC_DIR)/,${SUBDIRS})

BUILD_DIR		= build
OBJS			= $(addprefix $(BUILD_DIR)/,$(notdir $(SRCS:.cpp=.o)))

vpath %.cpp ${foreach dir, ${SUBDIRS}, ${dir}:}

.PHONY: re clean fclean

NAME = ft_irc

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling: $(NAME)"
	@$(CXX) $(CXXFLAGS) $^ -o $@ $(addprefix -I ,$(INCLUDE_DIRS))

$(OBJS): | mkdir_build

mkdir_build:
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cpp
	@printf "Build: %s\n" $<
	@$(CXX) $(CXXFLAGS)  -c $< -o $@ $(addprefix -I ,$(INCLUDE_DIRS))


re: fclean all

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)