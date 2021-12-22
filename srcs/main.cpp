/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:02:17 by lperson-          #+#    #+#             */
/*   Updated: 2021/12/22 16:23:53 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>
#include "IPAddress.hpp"

int main(int ac, char const *av[])
{
    if (ac != 2)
        return EXIT_FAILURE;

    AIPAddress *ipAddress = getIPAddress(av[1]);
    if (ipAddress == NULL)
        std::cerr << av[1] << " is not a valid ip address" << std::endl;
    else if (ipAddress->getAddressFamily() == AF_INET)
        std::cout << ipAddress->getString() << " is ipv4" << std::endl;
    else
        std::cout << ipAddress->getString() << " is ipv6" << std::endl;

    return EXIT_SUCCESS;
}
