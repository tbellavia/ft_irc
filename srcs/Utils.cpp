//
// Created by tony on 29/03/2022.
//

#include "../include/Utils.hpp"

bool ft::ends_with(const std::string &val, const std::string &ending) {
    if ( ending.size() > val.size() )
        return false;
    return std::equal(ending.rbegin(), ending.rend(), val.rbegin());
}
