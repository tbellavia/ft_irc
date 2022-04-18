/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:07:03 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/18 14:37:16 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef APP_HPP
# define APP_HPP

# include "Server.hpp"
# include "IRCApi.hpp"

struct App {
    App();

    void start(std::string const &port, std::string const &password) const;
};

#endif