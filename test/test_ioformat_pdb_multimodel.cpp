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

#include <maral/bootstraps/pdb_multimodel.hpp>

using boost::test_tools::output_test_stream;
namespace butrc = boost::unit_test::runtime_config;

using namespace maral;
using namespace maral::bootstrap::pdb_multimodel;

#define PATTERNS_FOLDER "patterns/"

BOOST_AUTO_TEST_CASE( PDB_1CRN )
{
    std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
    auto rt = make_node<root>();
    in >> rt.get();

    BOOST_CHECK(   1 == boost::distance(rt->range<model>()) );
    BOOST_CHECK(   1 == boost::distance(rt->range<chain>()) );
    BOOST_CHECK(  46 == boost::distance(rt->range<residue>()) );
    BOOST_CHECK( 327 == boost::distance(rt->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( PDB_1CRN_Molecule )
{
    std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
    auto ch = make_node<chain>();
    in >> ch.get();

    BOOST_CHECK(  46 == boost::distance(ch->range<residue>()) );
    BOOST_CHECK( 327 == boost::distance(ch->range<atom>()) );
}

//BOOST_AUTO_TEST_CASE( PDB_2MKK )
//{
//    std::ifstream in(PATTERNS_FOLDER"2MKK.pdb");
//    auto rt = make_node<root>();
//    in >> rt.get();
//
//    BOOST_CHECK(   10 == rt->frames_size() );
//    BOOST_CHECK( 3532 == rt->coords_size() );
//
//    output_test_stream cout(
//        PATTERNS_FOLDER"2MKK_out.pdb",
//        !butrc::save_pattern());
//
//    cout << rt.get();
//    BOOST_CHECK(cout.match_pattern());
//}

//BOOST_AUTO_TEST_CASE( PDB_1CRN_2MKK )
//{
//    std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
//    auto rt = make_node<root>();
//    in >> rt.get();
//    in.close();
//    in.open(PATTERNS_FOLDER"2MKK.pdb");
//    in >> rt.get();
//
//    std::ofstream cout(PATTERNS_FOLDER"1CRN_2MKK_test.pdb");
//    cout<< rt.get();
//}

//BOOST_AUTO_TEST_CASE( PDB_1TOS_1EGT )
//{
//    std::ifstream in(PATTERNS_FOLDER"1TOS.pdb");
//    auto rt = make_node<root>();
//    in >> rt.get();
//    in.close();
//    in.open(PATTERNS_FOLDER"1EGT.pdb");
//    in >> rt.get();
//
//    std::ofstream cout(PATTERNS_FOLDER"1TOS_1EGT_test.pdb");
//    cout << rt.get();
//}

//BOOST_AUTO_TEST_CASE( PDB_2SOC_1TOS )
//{
//    std::ifstream in(PATTERNS_FOLDER"2SOC.pdb");
//    auto rt = make_node<root>();
//    in >> rt.get();
//    in.close();
//    in.open(PATTERNS_FOLDER"1TOS.pdb");
//    in >> rt.get();
//
//    std::ofstream cout(PATTERNS_FOLDER"2SOC_1TOS_out.pdb");
//    cout << rt.get();
//}

//BOOST_AUTO_TEST_CASE( PDB_1TOS_2SOC )
//{
//    std::ifstream in(PATTERNS_FOLDER"1TOS.pdb");
//    auto rt = make_node<root>();
//    in >> rt.get();
//    in.close();
//    in.open(PATTERNS_FOLDER"2SOC.pdb");
//    in >> rt.get();
//
//    std::ofstream cout(PATTERNS_FOLDER"1TOS_2SOC_out.pdb");
//    cout << format(pdb) << rt.get();
//    cout.close();
//    cout.open(PATTERNS_FOLDER"1TOS_out.pdb");
//    cout << *(rt->begin<model>());
//    cout.close();
//    cout.open(PATTERNS_FOLDER"1TOS_out_mol.pdb");
//    cout << *(rt->begin<chain>());
//    cout.close();
//    cout.open(PATTERNS_FOLDER"1TOS_out_res.pdb");
//    cout << *(rt->begin<residue>());
//    cout.close();
//    cout.open(PATTERNS_FOLDER"1TOS_out_atm.pdb");
//    cout << *(rt->begin<atom>()) << std::endl;
//    cout << *(rt->rbegin<atom>()) << std::endl;
//}

BOOST_AUTO_TEST_CASE( OUT_FRAMES_MANIPULATOR )
{
    std::ifstream in(PATTERNS_FOLDER"1S4A.pdb");
    auto rt = make_node<root>();
    in >> rt.get();
    //in >> rt.get();

    std::ofstream cout(PATTERNS_FOLDER"1S4A_default.pdb");
    cout << rt.get();
    //cout.close();
    //cout.open(PATTERNS_FOLDER"1S4A_2_5_3.pdb");
    //cout << frames(2, 5, 3) << rt.get();
    //cout.close();
    //cout.open(PATTERNS_FOLDER"1S4A_1_4.pdb");
    //cout << frames(1, 4) << rt.get();
    //cout.close();
    //cout.open(PATTERNS_FOLDER"1S4A_1_10_2.pdb");
    //cout << frames(1, 10, 2) << rt.get();
    //cout.close();
    //cout.open(PATTERNS_FOLDER"1S4A_5.pdb");
    //cout << frames(5) << rt.get();
    //cout.close();
    //cout.open(PATTERNS_FOLDER"1S4A_res_out.pdb");
    //cout << *(rt->begin<residue>());
    //cout.close();
    //cout.open(PATTERNS_FOLDER"1S4A_atm_out.pdb");
    //for (auto i = 1; i < 6; ++i)
    //{
    //    cout << atomordinal(0) << frames(i, i)
    //         << *(rt->begin<atom>()) << std::endl
    //         << *(rt->rbegin<atom>()) << std::endl;
    //}
}
