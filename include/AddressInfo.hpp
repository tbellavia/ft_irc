/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AddressInfo.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:21:25 by lperson-          #+#    #+#             */
/*   Updated: 2021/12/29 11:41:04 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADDRESS_INFO_HPP

# define ADDRESS_INFO_HPP

# include "IPAddress.hpp"

class AddressInfo
{
public:
    int         m_flags;

    AddressInfo();
    AddressInfo(int sockType, int protocol, int flags);
    AddressInfo(
        std::string const *ipAddress, std::string const *service,
        AddressInfo const &hint = AddressInfo(0, 0, 0)
    );
    ~AddressInfo();

    int getSockType() const;
    int getProtocol() const;
    AIPAddress *getIPAddress() const;
    sa_family_t getIPFamily() const;

    class GetAddressInfoException : public std::exception
    {
    public:
        GetAddressInfoException(int errcode);
        const char *what() const throw();

    private:
        int _errcode;
    };

private:
    AIPAddress  *_ipAddress;
    sa_family_t _ipFamily;
    int         _sockType;
    int         _protocol;
};

#endif
