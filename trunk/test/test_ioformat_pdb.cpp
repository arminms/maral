// Boost.Maral library (Molecular Architecture Recording & Assembly Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#include <iostream>
#include <fstream>

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/range/distance.hpp>

//#include <boost/iostreams/filtering_streambuf.hpp>
//#include <boost/iostreams/filtering_stream.hpp>
//#include <boost/iostreams/filter/gzip.hpp>
//#include <boost/iostreams/device/file_descriptor.hpp>

#include <maral/bootstraps/basic.hpp>
#include <maral/iomanip.hpp>

using boost::test_tools::output_test_stream;
namespace butrc = boost::unit_test::runtime_config;

using namespace maral;
using namespace maral::bootstrap::basic;

#define PATTERNS_FOLDER "patterns/"

BOOST_AUTO_TEST_CASE(PDB_1CRN)
{
    std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
    auto rt = make_node<root>();
    in >> format(1) >> rt.get();

    BOOST_CHECK(   1 == boost::distance(rt->range<model>()) );
    BOOST_CHECK(   1 == boost::distance(rt->range<molecule>()) );
    BOOST_CHECK(  46 == boost::distance(rt->range<residue>()) );
    BOOST_CHECK( 327 == boost::distance(rt->range<atom>()) );

    output_test_stream cout(
        PATTERNS_FOLDER"1CRN_tree.txt",
        !butrc::save_pattern());
    cout << shallow << delimiters('[', ']') << separator(' ')
         << rt.get() << std::endl;
    BOOST_CHECK(cout.match_pattern());
    for (auto node : *rt)
    {
        cout << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_AUTO_TEST_CASE(PDB_3NY8)
{
    std::ifstream in(PATTERNS_FOLDER"3NY8.pdb");
    auto rt = make_node<root>();
    in >> format(1) >> rt.get();

    BOOST_CHECK(    1 == boost::distance(rt->range<model>()) );
    BOOST_CHECK(    2 == boost::distance(rt->range<molecule>()) );
    BOOST_CHECK(  468 == boost::distance(rt->range<residue>()) );
    BOOST_CHECK( 3698 == boost::distance(rt->range<atom>()) );
    output_test_stream cout(
        PATTERNS_FOLDER"3NY8_tree.txt",
        !butrc::save_pattern());
    cout << shallow << delimiters('[', ']') << separator(' ')
         << rt.get() << std::endl;
    BOOST_CHECK(cout.match_pattern());
    for (auto node : *rt)
    {
        cout << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_AUTO_TEST_CASE(PDB_3SDY)
{
    std::ifstream in(PATTERNS_FOLDER"3SDY.pdb");
    auto rt = make_node<root>();
    in >> format(1) >> rt.get();

    BOOST_CHECK(     1 == boost::distance(rt->range<model>()) );
    BOOST_CHECK(    10 == boost::distance(rt->range<molecule>()) );
    BOOST_CHECK(   947 == boost::distance(rt->range<residue>()) );
    BOOST_CHECK( 14620 == boost::distance(rt->range<atom>()) );

    output_test_stream cout(
        PATTERNS_FOLDER"3SDY_tree.txt",
        !butrc::save_pattern());
    cout << shallow << delimiters('[', ']') << separator(' ')
         << rt.get() << std::endl;
    BOOST_CHECK(cout.match_pattern());
    for (auto node : *rt)
    {
        cout << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_AUTO_TEST_CASE(PDB_NoChain)
{
    std::ifstream in(PATTERNS_FOLDER"no_chain.pdb");
    auto rt = make_node<root>();
    in >> format(1) >> rt.get();

    BOOST_CHECK(  1 == boost::distance(rt->range<model>()) );
    BOOST_CHECK(  0 == boost::distance(rt->range<molecule>()) );
    BOOST_CHECK(  8 == boost::distance(rt->range<residue>()) );
    BOOST_CHECK( 74 == boost::distance(rt->range<atom>()) );

    output_test_stream cout(
        PATTERNS_FOLDER"no_chain_tree.txt",
        !butrc::save_pattern());
    cout << shallow << delimiters('[', ']') << separator(' ')
         << rt.get() << std::endl;
    BOOST_CHECK(cout.match_pattern());
    for (auto node : *rt)
    {
        cout << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_AUTO_TEST_CASE(PDB_NoChain_NoRes)
{
    std::ifstream in(PATTERNS_FOLDER"no_chain_no_res.pdb");
    auto rt = make_node<root>();
    in >> format(1) >> rt.get();

    BOOST_CHECK(  1 == boost::distance(rt->range<model>()) );
    BOOST_CHECK(  0 == boost::distance(rt->range<molecule>()) );
    BOOST_CHECK(  0 == boost::distance(rt->range<residue>()) );
    BOOST_CHECK( 15 == boost::distance(rt->range<atom>()) );

    output_test_stream cout(
        PATTERNS_FOLDER"no_chain_no_res_tree.txt",
        !butrc::save_pattern());
    cout << shallow << delimiters('[', ']') << separator(' ')
         << rt.get() << std::endl;
    BOOST_CHECK(cout.match_pattern());
    for (auto node : *rt)
    {
        cout << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

//BOOST_AUTO_TEST_CASE(PDB_Test_Compress)
//{
//    namespace io = boost::iostreams;
//
//    std::ifstream in("pdb/3NY8.pdb");
//    auto rt = make_node<root>();
//    in >> format(1) >> rt.get();
//
//    io::filtering_ostream out;
//    out.push(io::gzip_compressor());
//    out.push(io::file_descriptor_sink("pdb/3NY8_tree.gz"));
//    out << delimiters('[', ']') << separator(' ') << rt.get();
//
//    std::ofstream file("pdb/3NY8_tree.gz", std::ios_base::out | std::ios_base::binary);
//    io::filtering_streambuf<io::output> out;
//    out.push(io::gzip_compressor(9));
//    out.push(file);
//    file << delimiters('[', ']') << separator(' ') << rt.get();
//}
