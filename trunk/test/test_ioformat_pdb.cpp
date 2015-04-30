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
#include <regex>
#include <chrono>

// due to inclusion of <windows.h> by header only boost::test, we need
// the following define to prevent problem with std::numeric_limits
#if defined(_MSC_VER)
#   define NOMINMAX
#endif  //_MSC_VER

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/range/distance.hpp>

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>

//#include <maral/bootstraps/bs_pdb.hpp>
#include <maral/bootstraps/bs_bond.hpp>
#include <maral/algorithms/connect.hpp>
#include <maral/algorithms/remove.hpp>
#include <maral/algorithms/remove_if.hpp>
#include <maral/algorithms/distance.hpp>
#include <maral/algorithms/rmsd.hpp>

using namespace std::chrono;
using boost::test_tools::output_test_stream;
namespace butrc = boost::unit_test::runtime_config;

using namespace maral;
//using namespace maral::bootstrap::pdb;
using namespace maral::bootstrap::bond;

#define PATTERNS_FOLDER "patterns/"

BOOST_AUTO_TEST_CASE( IN_1CRN_Root )
{
    std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
    auto rt = make<root>();
    in >> rt;

    BOOST_CHECK(   1 == boost::distance(rt->range<model>()) );
    BOOST_CHECK(   1 == boost::distance(rt->range<chain>()) );
    BOOST_CHECK(  46 == boost::distance(rt->range<residue>()) );
    BOOST_CHECK( 327 == boost::distance(rt->range<atom>()) );

    output_test_stream cout(
        PATTERNS_FOLDER"1CRN_tree.txt",
        !butrc::save_pattern());
    cout << shallow << delimiters('[', ']') << separator(' ')
         << format(tree) << rt << std::endl;
    BOOST_CHECK(cout.match_pattern());
    for (auto node : *rt)
    {
        cout << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_AUTO_TEST_CASE( IN_3NY8_Root )
{
    std::ifstream in(PATTERNS_FOLDER"3NY8.pdb");
    auto rt = make<root>();
    in >> rt;

    BOOST_CHECK(    1 == boost::distance(rt->range<model>()) );
    BOOST_CHECK(    2 == boost::distance(rt->range<chain>()) );
    BOOST_CHECK(  468 == boost::distance(rt->range<residue>()) );
    BOOST_CHECK( 3698 == boost::distance(rt->range<atom>()) );
    output_test_stream cout(
        PATTERNS_FOLDER"3NY8_tree.txt",
        !butrc::save_pattern());
    cout << shallow << delimiters('[', ']') << separator(' ')
         << format(tree) << rt << std::endl;
    BOOST_CHECK(cout.match_pattern());
    for (auto node : *rt)
    {
        cout << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_AUTO_TEST_CASE( IN_3SDY_Root )
{
    std::ifstream in(PATTERNS_FOLDER"3SDY.pdb");
    auto rt = make<root>();
    in >> rt;

    BOOST_CHECK(     1 == boost::distance(rt->range<model>()) );
    BOOST_CHECK(    10 == boost::distance(rt->range<chain>()) );
    BOOST_CHECK(   957 == boost::distance(rt->range<residue>()) );
    BOOST_CHECK( 14620 == boost::distance(rt->range<atom>()) );

    output_test_stream cout(
        PATTERNS_FOLDER"3SDY_tree.txt",
        !butrc::save_pattern());
    cout << shallow << delimiters('[', ']') << separator(' ')
         << format(tree) << rt << std::endl;
    BOOST_CHECK(cout.match_pattern());
    for (auto node : *rt)
    {
        cout << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_AUTO_TEST_CASE( IN_2SOC_Root )
{
    std::ifstream in(PATTERNS_FOLDER"2SOC.pdb");
    auto rt = make<root>();
    in >> rt;

    BOOST_CHECK(   1 == boost::distance(rt->range<model>()) );
    BOOST_CHECK(   1 == boost::distance(rt->range<chain>()) );
    BOOST_CHECK(   8 == boost::distance(rt->range<residue>()) );
    BOOST_CHECK( 137 == boost::distance(rt->range<atom>()) );

    output_test_stream cout(
        PATTERNS_FOLDER"2SOC_1st_frame.pdb",
        !butrc::save_pattern());
    cout << rt;
    BOOST_CHECK(cout.match_pattern());
}

BOOST_AUTO_TEST_CASE( IN_NoChain_Root )
{
    std::ifstream in(PATTERNS_FOLDER"no_chain.pdb");
    auto rt = make<root>();
    in >> rt;

    BOOST_CHECK(  1 == boost::distance(rt->range<model>()) );
    BOOST_CHECK(  0 == boost::distance(rt->range<chain>()) );
    BOOST_CHECK(  8 == boost::distance(rt->range<residue>()) );
    BOOST_CHECK( 74 == boost::distance(rt->range<atom>()) );

    output_test_stream cout(
        PATTERNS_FOLDER"no_chain_tree.txt",
        !butrc::save_pattern());
    cout << shallow << delimiters('[', ']') << separator(' ')
         << format(tree) << rt << std::endl;
    BOOST_CHECK(cout.match_pattern());
    for (auto node : *rt)
    {
        cout << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_AUTO_TEST_CASE( IN_NoChain_NoRes_Root )
{
    std::ifstream in(PATTERNS_FOLDER"no_chain_no_res.pdb");
    auto rt = make<root>();
    in >> rt;

    BOOST_CHECK(  1 == boost::distance(rt->range<model>()) );
    BOOST_CHECK(  0 == boost::distance(rt->range<chain>()) );
    BOOST_CHECK(  0 == boost::distance(rt->range<residue>()) );
    BOOST_CHECK( 15 == boost::distance(rt->range<atom>()) );

    output_test_stream cout(
        PATTERNS_FOLDER"no_chain_no_res_tree.txt",
        !butrc::save_pattern());
    cout << shallow << delimiters('[', ']') << separator(' ')
         << format(tree) << rt << std::endl;
    BOOST_CHECK(cout.match_pattern());
    for (auto node : *rt)
    {
        cout << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_AUTO_TEST_CASE( IN_1CRN_Model )
{
    std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
    auto md = make<model>();
    in >> md;

    BOOST_CHECK(   1 == boost::distance(md->range<chain>()) );
    BOOST_CHECK(  46 == boost::distance(md->range<residue>()) );
    BOOST_CHECK( 327 == boost::distance(md->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( IN_NoChain_Model )
{
    std::ifstream in(PATTERNS_FOLDER"no_chain.pdb");
    auto md = make<model>();
    in >> md;

    BOOST_CHECK(  0 == boost::distance(md->range<chain>()) );
    BOOST_CHECK(  8 == boost::distance(md->range<residue>()) );
    BOOST_CHECK( 74 == boost::distance(md->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( IN_NoChain_NoRes_Model )
{
    std::ifstream in(PATTERNS_FOLDER"no_chain_no_res.pdb");
    auto md = make<model>();
    in >> md;

    BOOST_CHECK(  0 == boost::distance(md->range<chain>()) );
    BOOST_CHECK(  0 == boost::distance(md->range<residue>()) );
    BOOST_CHECK( 15 == boost::distance(md->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( IN_1CRN_Molecule )
{
    std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
    auto ch = make<chain>();
    in >> ch;

    BOOST_CHECK(  46 == boost::distance(ch->range<residue>()) );
    BOOST_CHECK( 327 == boost::distance(ch->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( IN_NoChain_Molecule )
{
    std::ifstream in(PATTERNS_FOLDER"no_chain.pdb");
    auto ch = make<chain>();
    in >> ch;

    BOOST_CHECK(  8 == boost::distance(ch->range<residue>()) );
    BOOST_CHECK( 74 == boost::distance(ch->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( IN_NoChain_NoRes_Molecule )
{
    std::ifstream in(PATTERNS_FOLDER"no_chain_no_res.pdb");
    auto ch = make<chain>();
    in >> ch;

    BOOST_CHECK(  0 == boost::distance(ch->range<residue>()) );
    BOOST_CHECK( 15 == boost::distance(ch->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( IN_1CRN_Submol )
{
    std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
    auto sm = make<residue>();
    in >> sm;
    BOOST_CHECK( 7 == boost::distance(sm->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( IN_NoChain_Submol )
{
    std::ifstream in(PATTERNS_FOLDER"no_chain.pdb");
    auto sm = make<residue>();
    in >> sm;
    BOOST_CHECK( 6 == boost::distance(sm->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( IN_NoChain_NoRes_Submol)
{
    std::ifstream in(PATTERNS_FOLDER"no_chain_no_res.pdb");
    auto sm = make<residue>();
    in >> sm;
    BOOST_CHECK( 0 == boost::distance(sm->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( IN_1CRN_Atom )
{
    std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
    auto at = make<atom>();
    in >> at;
    std::string name = at->name();
    boost::trim(name);
    BOOST_CHECK( name == "N" );
    //BOOST_CHECK( at->ordinal() == 1 );
    BOOST_CHECK( is_equal(at->center(), mtl::point3f(17.047f, 14.099f, 3.625f), 0.0001f) );
    BOOST_CHECK( at->chemical_symbol() == "N" );
    BOOST_CHECK_EQUAL( at->covalent_radius().value(), 0.71f );
    //std::cout << at->covalent_radius() << std::endl;
}

BOOST_AUTO_TEST_CASE( PDB_1CRN_Print )
{
    //std::ifstream in(PATTERNS_FOLDER"2MKK.pdb");
    //auto rt = make<root>();
    //in >> rt;
    //std::ofstream cout(PATTERNS_FOLDER"2MKK_out.pdb");
    //cout << rt;

    //std::cout << sizeof(std::string) << std::endl;
    //std::cout << sizeof(datamodel::composite_node<hierarchical>) << std::endl;
    //std::cout << sizeof(datamodel::leaf_node<hierarchical>) << std::endl;
    //std::cout << sizeof(root) << std::endl;
    //std::cout << sizeof(atom) << std::endl;
    //std::cout << sizeof(chain) << std::endl;
    //std::cout << sizeof(component::coordinates<mtl::point3f>) << std::endl;
    //std::cout << sizeof(std::size_t) << std::endl;
    //std::cout << sizeof(int) << std::endl;

    //std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
    //auto rt = make<root>();
    //in >> rt;
    //std::cout << atomordinal(99990) << submolordinal(0xFFF1);
    //for (auto at : rt->range<atom>())
    //    std::cout << at << std::endl;

    //std::ifstream in(PATTERNS_FOLDER"3SDY.pdb");
    //auto rt = make<root>();
    //in >> rt;
    //std::ofstream cout(PATTERNS_FOLDER"3SDY_test.pdb");
    //cout << rt;

    //std::ifstream in(PATTERNS_FOLDER"3SDY.pdb");
    //auto md = make<model>();
    //in >> md;
    //std::ofstream cout(PATTERNS_FOLDER"3SDY_test.pdb");
    //cout << md;

    //std::ifstream in(PATTERNS_FOLDER"3SDY.pdb");
    //auto ch = make<chain>();
    //in >> ch;
    //std::ofstream cout(PATTERNS_FOLDER"3SDY_chain_test_.pdb");
    //cout << ch;

    //std::ifstream in(PATTERNS_FOLDER"no_chain.pdb");
    //auto rt = make<root>();
    //in >> rt;
    //std::ofstream cout(PATTERNS_FOLDER"no_chain_test.pdb");
    //cout << rt;

    //std::ifstream in(PATTERNS_FOLDER"no_chain_no_res.pdb");
    //auto rt = make<root>();
    //in >> rt;
    //std::ofstream cout(PATTERNS_FOLDER"no_chain_no_res_test.pdb");
    //cout << rt;
}

BOOST_AUTO_TEST_CASE( PDB_gzip )
{
    namespace io = boost::iostreams;
    std::ifstream gzfile(PATTERNS_FOLDER"1CRN.pdb.gz"
                        ,   std::ios_base::in | std::ios_base::binary);
    io::filtering_streambuf<io::input> in;
    in.push(io::gzip_decompressor());
    in.push(gzfile);
    std::stringstream file;
    boost::iostreams::copy(in, file);
    auto rt = make<root>();
    file >> rt;

    BOOST_CHECK(   1 == boost::distance(rt->range<model>()) );
    BOOST_CHECK(   1 == boost::distance(rt->range<chain>()) );
    BOOST_CHECK(  46 == boost::distance(rt->range<residue>()) );
    BOOST_CHECK( 327 == boost::distance(rt->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( PDB_1CRN_Bond )
{
    //std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
    //std::ifstream in(PATTERNS_FOLDER"3SDY.pdb");
    std::ifstream in(PATTERNS_FOLDER"1FFK.pdb");
    auto rt = make<root>();
    in >> rt;

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    connect<bond>(rt->range<atom>());
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(t2 - t1).count();
    std::cout << duration << " ms" << std::endl;

    std::cout << "Bonds: " << boost::distance(rt->range<bond>()) << std::endl;
    auto chain_a = rt->begin<chain>();
    //for (auto bnd : chain_a->range<bond>())
    //    std::cout //<< bnd->parent()->name() << ': '
    //              << bnd->first_->name() << '-'
    //              << bnd->second_->name()
    //              << std::endl;
    auto thr = rt->begin<residue>();
    std::advance(thr, 4);
    std::cout << "Before remove:" << std::endl;
    for (auto bnd : thr->range<bond>())
        std::cout << bnd->src()->name() << '-'
                  << bnd->dst()->name()
                  << std::endl;
    auto thr_n = rt->begin<atom>();
    auto thr_ca = rt->begin<atom>();
    ++thr_ca;

    //std::cout << "N-CA Length: " << distance(*thr_n, *thr_ca) << std::endl;
    //std::cout << "N-CA Length: " << distance(thr_n, thr_ca) << std::endl;
    //auto thr2 = thr;
    //++thr2;
    //std::cout << "RMSD: " << rmsd(thr->range<atom>(), thr2->range<atom>()) << std::endl;

    std::cout << "THR:CA bonds:" << std::endl;
    for (auto bnd : thr_ca->bonds<bond>())
        std::cout << bnd->neighbor(bnd->src())->name() << '-'
                  << bnd->neighbor(bnd->dst())->name()
                  << std::endl;

    std::cout << "THR:CA neighbors:" << std::endl;
    for (auto atm : thr_ca->neighbors())
        std::cout << atm->name() << std::endl;

    thr->remove(*thr_ca);
    std::cout << "After CA remove:" << std::endl;
    for (auto bnd : thr->range<bond>())
    std::cout << bnd->src()->name() << '-'
              << bnd->dst()->name()
              << std::endl;
    auto n_ca = rt->begin<bond>();
    thr->remove(*n_ca);
    std::cout << "After N_CA remove:" << std::endl;
    for (auto bnd : thr->range<bond>())
    std::cout << bnd->src()->name() << '-'
              << bnd->dst()->name()
              << std::endl;
    //remove(rt->range<bond>());
    std::cout << "Before removing all CA:" << std::endl;
    std::cout << "Bonds: " << boost::distance(rt->range<bond>()) << std::endl;
    std::cout << "Atoms: " << boost::distance(rt->range<atom>()) << std::endl;

    remove_if(
        rt->range<atom>()
        ,   [=] (const atom* atm)
            { return (std::regex_match(atm->name(), std::regex(".*CA.*"))); } );
            //{ return (std::regex_search(atm->name(), std::regex("CA"))); } );

    std::cout << "After removing all CA:" << std::endl;
    std::cout << "Bonds: " << boost::distance(rt->range<bond>()) << std::endl;
    std::cout << "Atoms: " << boost::distance(rt->range<atom>()) << std::endl;
    //for (auto bnd : chain_a->range<bond>())
    //    std::cout //<< bnd->parent()->name() << ': '
    //              << bnd->src()->name() << '-'
    //              << bnd->dst()->name()
    //              << std::endl;
    //remove(rt->range());
    //std::cout << "Total: " << boost::distance(rt->range()) << std::endl;

    //auto a1 = make<atom>("A1");
    //auto a1p = a1.get();
    //auto a2 = make<atom>("A2");
    //auto a2p = a2.get();
    //make<bond>(a1p, a2p);
}
