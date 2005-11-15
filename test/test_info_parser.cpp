// ----------------------------------------------------------------------------
// Copyright (C) 2002-2005 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
// Test data

const char *ok_data_1 = 
    ";Test file for info_parser\n"
    "\n"
    "key1 data1\n"
    "{\n"
    "\tkey data\n"
    "}\n"
    "#include \"testok1_inc.info\"\n"
    "key2 \"data2  \" {\n"
    "\tkey data\n"
    "}\n"
    "#\tinclude \"testok1_inc.info\"\n"
    "key3 \"data\"\n"
    "\t \"3\" {\n"
    "\tkey data\n"
    "}\n"
    "\t#include \"testok1_inc.info\"\n"
    "\n"
    "\"key4\" data4\n"
    "{\n"
    "\tkey data\n"
    "}\n"
    "#include \"testok1_inc.info\"\n"
    "\"key.5\" \"data.5\" { \n"
    "\tkey data \n"
    "}\n"
    "#\tinclude \"testok1_inc.info\"\n"
    "\"key6\" \"data\"\n"
    "\t   \"6\" {\n"
    "\tkey data\n"
    "}\n"
    "\t#include \"testok1_inc.info\"\n"
    "   \n"
    "key1 data1; comment\n"
    "{; comment\n"
    "\tkey data; comment\n"
    "}; comment\n"
    "#include \"testok1_inc.info\"\n"
    "key2 \"data2  \" {; comment\n"
    "\tkey data; comment\n"
    "}; comment\n"
    "#\tinclude \"testok1_inc.info\"\n"
    "key3 \"data\"; comment\n"
    "\t \"3\" {; comment\n"
    "\tkey data; comment\n"
    "}; comment\n"
    "\t#include \"testok1_inc.info\"\n"
    "\n"
    "\"key4\" data4; comment\n"
    "{; comment\n"
    "\tkey data; comment\n"
    "}; comment\n"
    "#include \"testok1_inc.info\"\n"
    "\"key.5\" \"data.5\" {; comment\n"
    "\tkey data; comment\n"
    "}; comment\n"
    "#\tinclude \"testok1_inc.info\"\n"
    "\"key6\" \"data\"; comment\n"
    "\t   \"6\" {; comment\n"
    "\tkey data; comment\n"
    "}; comment\n"
    "\t#include \"testok1_inc.info\"\n"
    "\\\\key\\t7 data7\\n\\\"data7\\\"\n"
    "{\n"
    "\tkey data\n"
    "}\n"
    "\"\\\\key\\t8\" \"data8\\n\\\"data8\\\"\"\n"
    "{\n"
    "\tkey data\n"
    "}\n"
    "\n";

const char *ok_data_1_inc = 
    ";Test file for info_parser\n"
    "\n"
    "inc_key inc_data ;;; comment\\";

const char *ok_data_2 = 
    "";

const char *ok_data_3 = 
    "key1\n"
    "key2\n"
    "key3\n"
    "key4\n";

const char *ok_data_4 = 
    "key1 data data data";

const char *error_data_1 = 
    ";Test file for info_parser\n"
    "#include \"bogus_file\"\n";                // Nonexistent include file

const char *error_data_2 = 
    ";Test file for info_parser\n"
    "key \"data with bad escape: \\q\"\n";      // Bad escape

const char *error_data_3 = 
    ";Test file for info_parser\n"
    "{\n";                                      // Opening brace without key

const char *error_data_4 = 
    ";Test file for info_parser\n"
    "}\n";                                      // Closing brace without opening brace

const char *error_data_5 = 
    ";Test file for info_parser\n"
    "key data\n"
    "{\n"
    "";                                         // No closing brace

#define BOOST_PROPERTY_TREE_DEBUG           // Enable ptree debugging
#include <boost/property_tree/ptree.hpp>

// Do not deprecate insecure CRT calls
#if (defined(BOOST_MSVC) && (BOOST_MSVC >= 1400))
#   define _CRT_SECURE_NO_DEPRECATE
#endif

// Enable ptree debugging
#define BOOST_PROPERTY_TREE_DEBUG           

#include <boost/test/minimal.hpp>
#include <boost/property_tree/info_parser.hpp>
#include "test_utils.hpp"

struct ReadFunc
{
    template<class Ptree>
    void operator()(const std::string &filename, Ptree &pt) const
    {
        boost::property_tree::read_info(filename, pt);
    }
};

struct WriteFunc
{
    template<class Ptree>
    void operator()(const std::string &filename, const Ptree &pt) const
    {
        boost::property_tree::write_info(filename, pt);
    }
};

template<class Ptree>
void test_info_parser()
{

    using namespace boost::property_tree;

    generic_parser_test_ok<Ptree, ReadFunc, WriteFunc>
    (
        ReadFunc(), WriteFunc(), ok_data_1, ok_data_1_inc, 
        "testok1.info", "testok1_inc.info", "testok1out.info", 45, 240, 192
    );
    
    generic_parser_test_ok<Ptree, ReadFunc, WriteFunc>
    (
        ReadFunc(), WriteFunc(), ok_data_2, NULL, 
        "testok2.info", NULL, "testok2out.info", 1, 0, 0
    );

    generic_parser_test_ok<Ptree, ReadFunc, WriteFunc>
    (
        ReadFunc(), WriteFunc(), ok_data_3, NULL, 
        "testok3.info", NULL, "testok3out.info", 5, 0, 16
    );

    generic_parser_test_ok<Ptree, ReadFunc, WriteFunc>
    (
        ReadFunc(), WriteFunc(), ok_data_4, NULL, 
        "testok4.info", NULL, "testok4out.info", 2, 14, 4
    );

    generic_parser_test_error<ptree, ReadFunc, WriteFunc, info_parser_error>
    (
        ReadFunc(), WriteFunc(), error_data_1, NULL,
        "testerr1.info", NULL, "testerr1out.info", 2
    );

    generic_parser_test_error<ptree, ReadFunc, WriteFunc, info_parser_error>
    (
        ReadFunc(), WriteFunc(), error_data_2, NULL,
        "testerr2.info", NULL, "testerr2out.info", 2
    );

    generic_parser_test_error<ptree, ReadFunc, WriteFunc, info_parser_error>
    (
        ReadFunc(), WriteFunc(), error_data_3, NULL,
        "testerr3.info", NULL, "testerr3out.info", 2
    );

    generic_parser_test_error<ptree, ReadFunc, WriteFunc, info_parser_error>
    (
        ReadFunc(), WriteFunc(), error_data_4, NULL,
        "testerr4.info", NULL, "testerr4out.info", 2
    );

    generic_parser_test_error<ptree, ReadFunc, WriteFunc, info_parser_error>
    (
        ReadFunc(), WriteFunc(), error_data_5, NULL,
        "testerr5.info", NULL, "testerr5out.info", 4
    );
    
}

int test_main(int argc, char *argv[])
{
    using namespace boost::property_tree;
    test_info_parser<ptree>();
    test_info_parser<iptree>();
#ifndef BOOST_NO_CWCHAR
    test_info_parser<wptree>();
    test_info_parser<wiptree>();
#endif
    return 0;
}