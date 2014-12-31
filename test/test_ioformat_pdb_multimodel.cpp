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

#include <maral/bootstraps/bs_pdb_multimodel.hpp>

using boost::test_tools::output_test_stream;
namespace butrc = boost::unit_test::runtime_config;

using namespace maral;
using namespace maral::bootstrap::pdb_multimodel;

#define PATTERNS_FOLDER "patterns/"

struct ENT_1S4A_INIT
{
    ENT_1S4A_INIT()
    {
        std::ifstream in(PATTERNS_FOLDER"1S4A.pdb");
        rt = make<root>();
        in >> rt;
    }

    entity<root> rt;
};

BOOST_AUTO_TEST_CASE( PDB_1CRN )
{
    std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
    auto rt = make<root>();
    in >> rt;

    BOOST_CHECK(   1 == boost::distance(rt->range<model>()) );
    BOOST_CHECK(   1 == boost::distance(rt->range<chain>()) );
    BOOST_CHECK(  46 == boost::distance(rt->range<residue>()) );
    BOOST_CHECK( 327 == boost::distance(rt->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( PDB_1CRN_Molecule )
{
    std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
    auto ch = make<chain>();
    in >> ch;

    BOOST_CHECK(  46 == boost::distance(ch->range<residue>()) );
    BOOST_CHECK( 327 == boost::distance(ch->range<atom>()) );
}

//BOOST_AUTO_TEST_CASE( PDB_2MKK )
//{
//    std::ifstream in(PATTERNS_FOLDER"2MKK.pdb");
//    auto rt = make<root>();
//    in >> rt;
//
//    BOOST_CHECK(   10 == rt->frames_size() );
//    BOOST_CHECK( 3532 == rt->coords_size() );
//
//    output_test_stream cout(
//        PATTERNS_FOLDER"2MKK_out.pdb",
//        !butrc::save_pattern());
//
//    cout << rt;
//    BOOST_CHECK(cout.match_pattern());
//}

//BOOST_AUTO_TEST_CASE( PDB_1CRN_2MKK )
//{
//    std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
//    auto rt = make<root>();
//    in >> rt;
//    in.close();
//    in.open(PATTERNS_FOLDER"2MKK.pdb");
//    in >> rt;
//
//    std::ofstream cout(PATTERNS_FOLDER"1CRN_2MKK_test.pdb");
//    cout<< rt;
//}

//BOOST_AUTO_TEST_CASE( PDB_1TOS_1EGT )
//{
//    std::ifstream in(PATTERNS_FOLDER"1TOS.pdb");
//    auto rt = make<root>();
//    in >> rt;
//    in.close();
//    in.open(PATTERNS_FOLDER"1EGT.pdb");
//    in >> rt;
//
//    std::ofstream cout(PATTERNS_FOLDER"1TOS_1EGT_test.pdb");
//    cout << rt;
//}

BOOST_AUTO_TEST_CASE( PDB_2SOC_1TOS )
{
    std::ifstream in(PATTERNS_FOLDER"2SOC.pdb");
    auto rt = make<root>();
    in >> rt;
    in.close();
    in.open(PATTERNS_FOLDER"1TOS.pdb");
    in >> rt;

    //std::ofstream cout(PATTERNS_FOLDER"2SOC_1TOS_out.pdb");
    //cout << rt;
}

BOOST_AUTO_TEST_CASE( PDB_1TOS_2SOC )
{
    std::ifstream in(PATTERNS_FOLDER"1TOS.pdb");
    auto rt = make<root>();
    in >> rt;
    in.close();
    in.open(PATTERNS_FOLDER"2SOC.pdb");
    in >> rt;

    //std::ofstream cout(PATTERNS_FOLDER"1TOS_2SOC_out.pdb");
    //cout << rt;
    //cout.close();
    //cout.open(PATTERNS_FOLDER"1TOS_out.pdb");
    //cout << *(rt->begin<model>());
    //cout.close();
    //cout.open(PATTERNS_FOLDER"1TOS_out_mol.pdb");
    //cout << *(rt->begin<chain>());
    //cout.close();
    //cout.open(PATTERNS_FOLDER"1TOS_out_res.pdb");
    //cout << *(rt->begin<residue>());
    //cout.close();
    //cout.open(PATTERNS_FOLDER"1TOS_out_atm.pdb");
    //cout << *(rt->begin<atom>()) << std::endl;
    //cout << *(rt->rbegin<atom>()) << std::endl;
}

BOOST_FIXTURE_TEST_CASE( OUT_FRAMES_0_0_0, ENT_1S4A_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"1S4A_F_0_0_0.pdb",
        !butrc::save_pattern());
    cout << rt;
    BOOST_CHECK(cout.match_pattern());
}

BOOST_FIXTURE_TEST_CASE( OUT_FRAMES_2_5_3, ENT_1S4A_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"1S4A_F_2_5_3.pdb",
        !butrc::save_pattern());
    cout << frames(2, 5, 3) << rt;
    BOOST_CHECK(cout.match_pattern());
}

BOOST_FIXTURE_TEST_CASE( OUT_FRAMES_1_4, ENT_1S4A_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"1S4A_F_1_4.pdb",
        !butrc::save_pattern());
    cout << frames(1, 4) << rt;
    BOOST_CHECK(cout.match_pattern());
}

BOOST_FIXTURE_TEST_CASE( OUT_FRAMES_1_10_2, ENT_1S4A_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"1S4A_F_1_10_2.pdb",
        !butrc::save_pattern());
    cout << frames(1, 10, 2) << rt;
    BOOST_CHECK(cout.match_pattern());
}

BOOST_FIXTURE_TEST_CASE( OUT_FRAMES_5, ENT_1S4A_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"1S4A_F_5.pdb",
        !butrc::save_pattern());
    cout << frames(5) << rt;
    BOOST_CHECK(cout.match_pattern());
}

BOOST_FIXTURE_TEST_CASE( OUT_FRAMES_5_RES, ENT_1S4A_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"1S4A_F_5_RES.pdb",
        !butrc::save_pattern());
    cout << frames(5) << *(rt->begin<residue>());
    BOOST_CHECK(cout.match_pattern());
}

BOOST_FIXTURE_TEST_CASE( OUT_FRAMES_LOOP_ATM, ENT_1S4A_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"1S4A_F_loop_atm.pdb",
        !butrc::save_pattern());
    for (auto i = 1; i < 6; ++i)
        cout << atomordinal(0) << frames(i, i)
             << *(rt->begin<atom>()) << std::endl
             << *(rt->rbegin<atom>()) << std::endl;
    BOOST_CHECK(cout.match_pattern());
}

BOOST_AUTO_TEST_CASE( IN_FRAMES_2_5_3 )
{
    std::ifstream in(PATTERNS_FOLDER"1S4A.pdb");
    auto rt = make<root>();
    in >> frames(2, 5, 3) >> rt;
    output_test_stream cout(
        PATTERNS_FOLDER"1S4A_F_2_5_3.pdb",
        !butrc::save_pattern());
    cout << rt;
    BOOST_CHECK(cout.match_pattern());
}

BOOST_AUTO_TEST_CASE( IN_FRAMES_1_4 )
{
    std::ifstream in(PATTERNS_FOLDER"1S4A.pdb");
    auto rt = make<root>();
    in >> frames(1, 4) >> rt;
    output_test_stream cout(
        PATTERNS_FOLDER"1S4A_F_1_4.pdb",
        !butrc::save_pattern());
    cout << rt;
    BOOST_CHECK(cout.match_pattern());
}

BOOST_AUTO_TEST_CASE( IN_FRAMES_1_10_2 )
{
    std::ifstream in(PATTERNS_FOLDER"1S4A.pdb");
    auto rt = make<root>();
    in >> frames(1, 10, 2) >> rt;
    output_test_stream cout(
        PATTERNS_FOLDER"1S4A_F_1_10_2.pdb",
        !butrc::save_pattern());
    cout << rt;
    BOOST_CHECK(cout.match_pattern());
}

BOOST_AUTO_TEST_CASE( IN_FRAMES_5 )
{
    std::ifstream in(PATTERNS_FOLDER"1S4A.pdb");
    auto rt = make<root>();
    in >> frames(5) >> rt;
    output_test_stream cout(
        PATTERNS_FOLDER"1S4A_F_5.pdb",
        !butrc::save_pattern());
    cout << rt;
    BOOST_CHECK(cout.match_pattern());
}
