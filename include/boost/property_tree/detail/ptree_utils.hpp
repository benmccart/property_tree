// ----------------------------------------------------------------------------
// Copyright (C) 2002-2005 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_PTREE_UTILS_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_PTREE_UTILS_HPP_INCLUDED

#include <boost/property_tree/ptree.hpp>
#include <string>
#include <locale>

namespace boost { namespace property_tree { namespace detail
{

    // Naively convert narrow string to another character type
    template<class Ch>
    std::basic_string<Ch> widen(const char *text)
    {
        std::locale loc;
        std::basic_string<Ch> result;
        while (*text)
        {
            result += Ch(*text);
            ++text;
        }
        return result;
    }

    // Remove trailing and leading spaces
    template<class Ch>
    std::basic_string<Ch> trim(const std::basic_string<Ch> &s, 
                               const std::locale &loc = std::locale())
    {
        typename std::basic_string<Ch>::const_iterator first = s.begin();
        while (first != s.end() && std::isspace(*first, loc)) 
            ++first;
        if (first == s.end())
            return std::basic_string<Ch>();
        typename std::basic_string<Ch>::const_iterator last = s.end();
        do --last; while (std::isspace(*last, loc)); 
        if (first != s.begin() || last + 1 != s.end())
            return std::basic_string<Ch>(first, last + 1);
        else
            return s;
    }

} } }

#endif