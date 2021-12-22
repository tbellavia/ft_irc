/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IPAddress.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:03:39 by lperson-          #+#    #+#             */
/*   Updated: 2021/12/22 16:22:58 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IP_ADDRESS_HPP

# include <string>
# include <stdexcept>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netinet/ip.h>

/*
 * A module for handling differents ip address (IPv4 or IPv6)
*/

/*
 * A base class for all ip address
 * can not be instantiated
*/

class AIPAddress
{
public:
    AIPAddress();
    AIPAddress(std::string const &_string, int _addressFamily);
    AIPAddress(AIPAddress const &copy);

    virtual AIPAddress *clone() const = 0;

    std::string getString() const;
    int         getAddressFamily() const;
    void const  *getCStyleAddress() const;

    virtual ~AIPAddress();

protected:
    AIPAddress &operator=(AIPAddress const &rhs);

    std::string const   _string;
    int const           _addressFamily;
    void const          *_cStyleAddress;

};

/*
 * Concrete IPv4 class
*/

class IPv4Address : public AIPAddress
{
public:
    IPv4Address(std::string const &ipAddress);
    IPv4Address(IPv4Address const &copy);

    AIPAddress *clone() const;

    ~IPv4Address();

    class AddressValueException : public std::exception
    {
    public:
        const char *what() const throw();
    };

private:
    struct in_addr  _sin_addr; // C-style representation

    IPv4Address();
    IPv4Address &operator=(IPv4Address const &rhs);
};

/*
 * Concrete IPv6Address
*/

class IPv6Address : public AIPAddress
{
public:
    IPv6Address(std::string const &ipAddress);
    IPv6Address(IPv6Address const &copy);

    AIPAddress *clone() const;

    ~IPv6Address();

    class AddressValueException : public std::exception
    {
    public:
        const char *what() const throw();
    };

private:
    struct in6_addr _sin6_addr; // C-style representation

    IPv6Address();
    IPv6Address &operator=(IPv6Address const &rhs);
};

/*
 * Producer of ip address
 * guess if ipv4 or ipv6 or none and then return NULL
*/

AIPAddress *getIPAddress(std::string const &ipAddress);

#endif
