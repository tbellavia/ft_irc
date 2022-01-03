/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AddressInfo.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:30:45 by lperson-          #+#    #+#             */
/*   Updated: 2022/01/03 11:55:50 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AddressInfo.hpp"
#include <sys/types.h>
#include <netdb.h>

AddressInfo::AddressInfo()
{}

AddressInfo::AddressInfo(int sockType, int protocol, int flags):
        _sockType(sockType), _protocol(protocol), m_flags(flags)
{}

AddressInfo::AddressInfo(
    std::string const *ipAddress, std::string const *service,
    AddressInfo const &hint = AddressInfo(0, 0, 0)
)
{
    struct addrinfo     cHint;
    cHint.ai_family = hint.getIPFamily();
    cHint.ai_socktype = hint.getSockType();
    cHint.ai_protocol = hint.getProtocol();
    cHint.ai_flags = hint.m_flags;

    struct addrinfo     *results;
    int errcode = getaddrinfo(
        ipAddress->c_str(), service->c_str(), &cHint, &results
    );
    if (errcode != 0)
        throw GetAddressInfoException(errcode);

    for (
        struct addrinfo *iter = results;
        results != NULL;
        results = results->ai_next
    )
    {
        _ipFamily = results->ai_family;
        _sockType = results->ai_socktype;
        _protocol = results->ai_protocol;
        
    }
}
