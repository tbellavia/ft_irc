/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AddressInfo.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:30:45 by lperson-          #+#    #+#             */
/*   Updated: 2022/01/03 14:56:16 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AddressInfo.hpp"
#include <sys/types.h>
#include <netdb.h>
#include <cstring>

AddressInfo::AddressInfo():
    _ipAddress(NULL)
{}

AddressInfo::AddressInfo(
    sa_family_t family, int sockType, int protocol, int flags
):
        m_flags(flags), _ipAddress(NULL), _ipFamily(family),
        _sockType(sockType), _protocol(protocol)
{}

AddressInfo::AddressInfo(
    char const *ipAddress, char const *service,
    AddressInfo const &hint
)
{
    struct addrinfo     cHint;

    std::memset(&cHint, 0, sizeof(cHint));
    cHint.ai_family = hint.getIPFamily();
    cHint.ai_socktype = hint.getSockType();
    cHint.ai_protocol = hint.getProtocol();
    cHint.ai_flags = hint.m_flags;

    struct addrinfo     *results;
    int errcode = getaddrinfo(
        ipAddress, service, &cHint, &results
    );
    if (errcode != 0)
        throw GetAddressInfoException(errcode);

    _ipAddress = NULL;
    for (
        struct addrinfo *iter = results;
        iter != NULL;
        iter = iter->ai_next
    )
    {
        _ipFamily = iter->ai_family;
        _sockType = iter->ai_socktype;
        _protocol = iter->ai_protocol;
        if (iter->ai_family == AF_INET)
        {
            _ipAddress = ::getIPAddress(
                reinterpret_cast<struct sockaddr_in *>(iter->ai_addr)
                ->sin_addr
            );
        }
        else if (iter->ai_family == AF_INET6)
        {
            _ipAddress = ::getIPAddress(
                reinterpret_cast<struct sockaddr_in6 *>(iter->ai_addr)
                ->sin6_addr
            );
        }
        if (_ipAddress)
            return ;
    }

    throw NoAddressInfoException();
}

AddressInfo::AddressInfo(AddressInfo const &copy):
        m_flags(copy.m_flags), _ipFamily(copy.getIPFamily()),
        _sockType(copy.getSockType()), _protocol(copy.getProtocol())
{
    if (copy.getIPAddress() != NULL)
        _ipAddress = copy.getIPAddress()->clone();
    else
        _ipAddress = NULL;
}

AddressInfo::~AddressInfo()
{
    delete _ipAddress;
}

int AddressInfo::getSockType() const
{
    return _sockType;
}

int AddressInfo::getProtocol() const
{
    return _protocol;
}

AIPAddress const *AddressInfo::getIPAddress() const
{
    return _ipAddress;
}

sa_family_t AddressInfo::getIPFamily() const
{
    return _ipFamily;
}

AddressInfo &AddressInfo::operator=(AddressInfo const &rhs)
{
    if (this != &rhs)
    {
        m_flags = rhs.m_flags;
        delete _ipAddress;
        if (rhs.getIPAddress() != NULL)
            _ipAddress = rhs.getIPAddress()->clone();
        else
            _ipAddress = NULL;
        _ipFamily = rhs.getIPFamily();
        _sockType = rhs.getSockType();
        _protocol = rhs.getProtocol();
    }
    return *this;
}

AddressInfo::GetAddressInfoException::GetAddressInfoException(int errcode):
        _errcode(errcode)
{}

const char *AddressInfo::GetAddressInfoException::what() const throw()
{
    return gai_strerror(_errcode);
}

const char *AddressInfo::NoAddressInfoException::what() const throw()
{
    return "no address info founds";
}
