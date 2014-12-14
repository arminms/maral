// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
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
//#include <boost/iostreams/copy.hpp>
//#include <boost/iostreams/filter/gzip.hpp>
//#include <boost/iostreams/filtering_stream.hpp>
//#include <boost/iostreams/device/file_descriptor.hpp>

#include <maral/bootstraps/pdb.hpp>

using boost::test_tools::output_test_stream;
namespace butrc = boost::unit_test::runtime_config;

using namespace maral;
using namespace maral::bootstrap::pdb;

#define PATTERNS_FOLDER "patterns/"

BOOST_AUTO_TEST_CASE( PDB_1CRN_Root )
{
    std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
    auto rt = make_node<root>();
    in >> format(pdb) >> rt.get();

    BOOST_CHECK(   1 == boost::distance(rt->range<model>()) );
    BOOST_CHECK(   1 == boost::distance(rt->range<chain>()) );
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

BOOST_AUTO_TEST_CASE( PDB_3NY8_Root )
{
    std::ifstream in(PATTERNS_FOLDER"3NY8.pdb");
    auto rt = make_node<root>();
    in >> format(pdb) >> rt.get();

    BOOST_CHECK(    1 == boost::distance(rt->range<model>()) );
    BOOST_CHECK(    2 == boost::distance(rt->range<chain>()) );
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

BOOST_AUTO_TEST_CASE( PDB_3SDY_Root )
{
    std::ifstream in(PATTERNS_FOLDER"3SDY.pdb");
    auto rt = make_node<root>();
    in >> format(pdb) >> rt.get();

    BOOST_CHECK(     1 == boost::distance(rt->range<model>()) );
    BOOST_CHECK(    10 == boost::distance(rt->range<chain>()) );
    BOOST_CHECK(   957 == boost::distance(rt->range<residue>()) );
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

BOOST_AUTO_TEST_CASE( PDB_NoChain_Root )
{
    std::ifstream in(PATTERNS_FOLDER"no_chain.pdb");
    auto rt = make_node<root>();
    in >> format(pdb) >> rt.get();

    BOOST_CHECK(  1 == boost::distance(rt->range<model>()) );
    BOOST_CHECK(  0 == boost::distance(rt->range<chain>()) );
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

BOOST_AUTO_TEST_CASE( PDB_NoChain_NoRes_Root )
{
    std::ifstream in(PATTERNS_FOLDER"no_chain_no_res.pdb");
    auto rt = make_node<root>();
    in >> format(pdb) >> rt.get();

    BOOST_CHECK(  1 == boost::distance(rt->range<model>()) );
    BOOST_CHECK(  0 == boost::distance(rt->range<chain>()) );
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

BOOST_AUTO_TEST_CASE( PDB_1CRN_Model )
{
    std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
    auto md = make_node<model>();
    in >> format(pdb) >> md.get();

    BOOST_CHECK(   1 == boost::distance(md->range<chain>()) );
    BOOST_CHECK(  46 == boost::distance(md->range<residue>()) );
    BOOST_CHECK( 327 == boost::distance(md->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( PDB_NoChain_Model )
{
    std::ifstream in(PATTERNS_FOLDER"no_chain.pdb");
    auto md = make_node<model>();
    in >> format(pdb) >> md.get();

    BOOST_CHECK(  0 == boost::distance(md->range<chain>()) );
    BOOST_CHECK(  8 == boost::distance(md->range<residue>()) );
    BOOST_CHECK( 74 == boost::distance(md->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( PDB_NoChain_NoRes_Model )
{
    std::ifstream in(PATTERNS_FOLDER"no_chain_no_res.pdb");
    auto md = make_node<model>();
    in >> format(pdb) >> md.get();

    BOOST_CHECK(  0 == boost::distance(md->range<chain>()) );
    BOOST_CHECK(  0 == boost::distance(md->range<residue>()) );
    BOOST_CHECK( 15 == boost::distance(md->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( PDB_1CRN_Molecule )
{
    std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
    auto ch = make_node<chain>();
    in >> format(pdb) >> ch.get();

    BOOST_CHECK(  46 == boost::distance(ch->range<residue>()) );
    BOOST_CHECK( 327 == boost::distance(ch->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( PDB_NoChain_Molecule )
{
    std::ifstream in(PATTERNS_FOLDER"no_chain.pdb");
    auto ch = make_node<chain>();
    in >> format(pdb) >> ch.get();

    BOOST_CHECK(  8 == boost::distance(ch->range<residue>()) );
    BOOST_CHECK( 74 == boost::distance(ch->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( PDB_NoChain_NoRes_Molecule )
{
    std::ifstream in(PATTERNS_FOLDER"no_chain_no_res.pdb");
    auto ch = make_node<chain>();
    in >> format(pdb) >> ch.get();

    BOOST_CHECK(  0 == boost::distance(ch->range<residue>()) );
    BOOST_CHECK( 15 == boost::distance(ch->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( PDB_1CRN_Submol )
{
    std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
    auto sm = make_node<residue>();
    in >> format(pdb) >> sm.get();
    BOOST_CHECK( 7 == boost::distance(sm->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( PDB_NoChain_Submol )
{
    std::ifstream in(PATTERNS_FOLDER"no_chain.pdb");
    auto sm = make_node<residue>();
    in >> format(pdb) >> sm.get();
    BOOST_CHECK( 6 == boost::distance(sm->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( PDB_NoChain_NoRes_Submol)
{
    std::ifstream in(PATTERNS_FOLDER"no_chain_no_res.pdb");
    auto sm = make_node<residue>();
    in >> format(pdb) >> sm.get();
    BOOST_CHECK( 0 == boost::distance(sm->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( PDB_1CRN_Atom )
{
    std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
    auto at = make_node<atom>();
    in >> format(pdb) >> at.get();
    std::string name = at->name();
    boost::trim(name);
    BOOST_CHECK( name == "N" );
    //BOOST_CHECK( at->ordinal() == 1 );
    BOOST_CHECK( is_equal(at->center(), mtl::point3f(17.047f, 14.099f, 3.625f), 0.0001f) );
}

BOOST_AUTO_TEST_CASE( PDB_1CRN_Print )
{
    //std::ifstream in(PATTERNS_FOLDER"2MKK.pdb");
    //auto rt = make_node<root>();
    //in >> format(pdb) >> rt.get();
    //std::ofstream cout(PATTERNS_FOLDER"2MKK_out.pdb");
    //cout << format(pdb) << rt.get();

    //std::cout << sizeof(std::string) << std::endl;
    //std::cout << sizeof(data_model::composite_node<hierarchical>) << std::endl;
    //std::cout << sizeof(data_model::leaf_node<hierarchical>) << std::endl;
    //std::cout << sizeof(root) << std::endl;
    //std::cout << sizeof(atom) << std::endl;
    //std::cout << sizeof(chain) << std::endl;
    //std::cout << sizeof(policy::coordinates<mtl::point3f>) << std::endl;
    //std::cout << sizeof(std::size_t) << std::endl;
    //std::cout << sizeof(int) << std::endl;

    //std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
    //auto rt = make_node<root>();
    //in >> format(pdb) >> rt.get();
    //std::cout << format(pdb) << atomordinal(99990) << submolordinal(0xFFF1);
    //for (auto at : rt->range<atom>())
    //    std::cout << at << std::endl;

    //std::ifstream in(PATTERNS_FOLDER"3SDY.pdb");
    //auto rt = make_node<root>();
    //in >> format(pdb) >> rt.get();
    //std::ofstream cout(PATTERNS_FOLDER"3SDY_test.pdb");
    //cout << format(pdb) << rt.get();

    //std::ifstream in(PATTERNS_FOLDER"3SDY.pdb");
    //auto md = make_node<model>();
    //in >> format(pdb) >> md.get();
    //std::ofstream cout(PATTERNS_FOLDER"3SDY_test.pdb");
    //cout << format(pdb) << md.get();

    //std::ifstream in(PATTERNS_FOLDER"3SDY.pdb");
    //auto ch = make_node<chain>();
    //in >> format(pdb) >> ch.get();
    //std::ofstream cout(PATTERNS_FOLDER"3SDY_test.pdb");
    //cout << format(pdb) << ch.get();

    //std::ifstream in(PATTERNS_FOLDER"no_chain.pdb");
    //auto rt = make_node<root>();
    //in >> format(pdb) >> rt.get();
    //std::ofstream cout(PATTERNS_FOLDER"no_chain_test.pdb");
    //cout << format(pdb) << rt.get();

    //std::ifstream in(PATTERNS_FOLDER"no_chain_no_res.pdb");
    //auto rt = make_node<root>();
    //in >> format(pdb) >> rt.get();
    //std::ofstream cout(PATTERNS_FOLDER"no_chain_no_res_test.pdb");
    //cout << format(pdb) << rt.get();
}

//BOOST_AUTO_TEST_CASE( PDB_gzip )
//{
//    namespace io = boost::iostreams;
//    std::ifstream gzfile("pdb/1CRN.pdb.gz", std::ios_base::in | std::ios_base::binary);
//    io::filtering_streambuf<io::input> in;
//    in.push(io::gzip_decompressor());
//    in.push(gzfile);
//    std::stringstream file;
//    boost::iostreams::copy(in, file);
//    auto rt = make_node<root>();
//    file >> format(pdb) >> rt.get();
//
//    BOOST_CHECK(   1 == boost::distance(rt->range<model>()) );
//    BOOST_CHECK(   1 == boost::distance(rt->range<chain>()) );
//    BOOST_CHECK(  46 == boost::distance(rt->range<residue>()) );
//    BOOST_CHECK( 327 == boost::distance(rt->range<atom>()) );
//}
