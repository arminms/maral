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

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/gzip.hpp>

#include <maral/bootstraps/basic.hpp>
#include <maral/iomanip.hpp>

using boost::test_tools::output_test_stream;
namespace butrc = boost::unit_test::runtime_config;

using namespace maral;
using namespace maral::bootstrap::basic;

#define PATTERNS_FOLDER "patterns/"

BOOST_AUTO_TEST_CASE(PDB_1CRN)
{
    std::ifstream infile("pdb/1CRN.pdb");
    auto rt = make_node<root>();
    infile >> format(1) >> rt.get();
    std::ofstream outfile("pdb/1CRN_tree.txt");
    outfile << delimiters('[', ']') << separator(' ') << rt.get();
    std::cout << "No. of atoms: " << boost::distance(rt->range<atom>()) << std::endl; //327
}

BOOST_AUTO_TEST_CASE(PDB_3NY8)
{
    std::ifstream infile("pdb/3NY8.pdb");
    auto rt = make_node<root>();
    infile >> format(1) >> rt.get();
    std::ofstream outfile("pdb/3NY8_tree.txt");
    outfile << delimiters('[', ']') << separator(' ') << rt.get();
    std::cout << "No. of atoms: " << boost::distance(rt->range<atom>()) << std::endl; //3698
}

BOOST_AUTO_TEST_CASE(PDB_3SDY)
{
    std::ifstream infile("pdb/3SDY.pdb");
    auto rt = make_node<root>();
    infile >> format(1) >> rt.get();
    std::ofstream outfile("pdb/3SDY_tree.txt");
    outfile << delimiters('[', ']') << separator(' ') << rt.get();
    std::cout << "No. of atoms: " << boost::distance(rt->range<atom>()) << std::endl; //14620
}

BOOST_AUTO_TEST_CASE(PDB_NoChain)
{
    std::ifstream infile("pdb/no_chain.pdb");
    auto rt = make_node<root>();
    infile >> format(1) >> rt.get();
    std::ofstream outfile("pdb/no_chain_tree.txt");
    outfile << delimiters('[', ']') << separator(' ') << rt.get();
    std::cout << "No. of atoms: " << boost::distance(rt->range<atom>()) << std::endl; //14620
}

BOOST_AUTO_TEST_CASE(PDB_NoChain_NoRes)
{
    std::ifstream infile("pdb/no_chain_no_res.pdb");
    auto rt = make_node<root>();
    infile >> format(1) >> rt.get();
    std::ofstream outfile("pdb/no_chain_no_res_tree.txt");
    outfile << delimiters('[', ']') << separator(' ') << rt.get();
    std::cout << "No. of atoms: " << boost::distance(rt->range<atom>()) << std::endl; //14620
}

BOOST_AUTO_TEST_CASE(PDB_Test_Compress)
{
    namespace io = boost::iostreams;

    std::ifstream in("pdb/3NY8.pdb");
    auto rt = make_node<root>();
    in >> format(1) >> rt.get();

//    io::filtering_ostream out;
//    out.push(io::gzip_compressor());
//    out.push(io::file_descriptor_sink("pdb/3NY8_tree.gz"));
//    out << delimiters('[', ']') << separator(' ') << rt.get();

    std::ofstream file("pdb/3NY8_tree.gz", std::ios_base::out | std::ios_base::binary);
    io::filtering_streambuf<io::output> out;
    out.push(io::gzip_compressor(9));
    out.push(file);
    file << delimiters('[', ']') << separator(' ') << rt.get();
}
