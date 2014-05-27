// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_V1_DETAIL_XML_PARSER_ERROR_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_V1_DETAIL_XML_PARSER_ERROR_HPP_INCLUDED

#include <boost/property_tree/version.hpp>
#include <boost/property_tree/v1/detail/file_parser_error.hpp>
#include <string>

BOOST_PROPERTY_TREE_OPENNS(1) namespace xml_parser {

    //! Xml parser error
    class xml_parser_error: public file_parser_error
    {
    public:
        xml_parser_error(const std::string &msg,
                         const std::string &file,
                         unsigned long l):
            file_parser_error(msg, file, l)
        {
        }
    };

} BOOST_PROPERTY_TREE_CLOSENS()

#endif
