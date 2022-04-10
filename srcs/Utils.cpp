//
// Created by tony on 29/03/2022.
//

#include "../include/Utils.hpp"

bool ft::ends_with(const std::string &val, const std::string &ending) {
    if ( ending.size() > val.size() )
        return false;
    return std::equal(ending.rbegin(), ending.rend(), val.rbegin());
}

std::vector<std::string> ft::split(const std::string &s, const std::string &delim = " ") {
    std::vector<std::string>    strings;
    std::string                 rest;
    size_t                      pos;

    rest = s;
    while ( (pos = rest.find(delim)) != std::string::npos ){
        strings.push_back(rest.substr(0, pos));
        rest = rest.substr(pos + delim.length(), rest.length());
    }
    strings.push_back(rest);
    return strings;
}
