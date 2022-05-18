/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:07:03 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/18 16:22:08 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef APP_HPP
# define APP_HPP

# include "Server.hpp"
# include "IRCApi.hpp"
# include "Config.hpp"

struct App {
    App();
    ~App();

    void start(IRC::ConfigServer &config) const;
};

#endif