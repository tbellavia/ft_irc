/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:02:17 by lperson-          #+#    #+#             */
/*   Updated: 2022/01/03 14:40:45 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>
#include "AddressInfo.hpp"

int main(int ac, char const *av[])
{
    if (ac != 2)
        return EXIT_FAILURE;

    AddressInfo infos;

    try
    {
        infos = AddressInfo(av[1], NULL);
        std::cout << infos.getIPAddress()->getRepresentation() << " protocol: "
        << infos.getProtocol() << " socktype: " << infos.getSockType() 
        << std::endl;
    }
    catch (std::exception const &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
