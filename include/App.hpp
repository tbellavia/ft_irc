/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:07:03 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/09 08:43:40 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef APP_HPP
# define APP_HPP

# include "Server.hpp"
# include "IRCApi.hpp"

struct App {
    App();
    ~App();

    void start(std::string const &port, std::string const &password) const;

private:
    App(App const &app);
    App &operator=(App const &app);
};

#endif