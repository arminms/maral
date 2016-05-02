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
#include <chrono>

// due to inclusion of <windows.h> by header only boost::test, we need
// the following define to prevent problem with std::numeric_limits
#if defined(_MSC_VER)
#   define NOMINMAX
#endif  //_MSC_VER

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#   if (BOOST_VERSION >= 105900)
#       include <boost/test/unit_test_parameters.hpp>
#   else
#       include <boost/test/detail/unit_test_parameters.hpp>
#   endif  //BOOST_VERSION

#include <boost/range/distance.hpp>

#include <maral/bootstraps/bs_pdb_multimodel.hpp>
#include <maral/algorithms/connect.hpp>

using namespace std::chrono;
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

struct ENT_1TOS_2SOC_INIT
{
    ENT_1TOS_2SOC_INIT()
    {
        std::ifstream in(PATTERNS_FOLDER"1TOS.pdb");
        rt = make<root>();
        in >> rt;
        in.close();
        in.open(PATTERNS_FOLDER"2SOC.pdb");
        in >> rt;
    }

    entity<root> rt;
};

BOOST_AUTO_TEST_CASE( IN_1CRN )
{
    std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
    auto rt = make<root>();
    in >> rt;

    BOOST_CHECK(   1 == boost::distance(rt->range<model>()) );
    BOOST_CHECK(   1 == boost::distance(rt->range<chain>()) );
    BOOST_CHECK(  46 == boost::distance(rt->range<residue>()) );
    BOOST_CHECK( 327 == boost::distance(rt->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( IN_1CRN_Molecule )
{
    std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
    auto ch = make<chain>();
    in >> ch;

    BOOST_CHECK(  46 == boost::distance(ch->range<residue>()) );
    BOOST_CHECK( 327 == boost::distance(ch->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( IO_1TOS )
{
    std::ifstream in(PATTERNS_FOLDER"1TOS.pdb");
    auto rt = make<root>();
    in >> rt;

    BOOST_CHECK(   3 == rt->frames_size() );
    BOOST_CHECK( 468 == rt->coords_size() );
    BOOST_CHECK( 141 == boost::distance(rt->range<atom>()) );

    output_test_stream cout(
        PATTERNS_FOLDER"1TOS_out.pdb",
        !butrc::save_pattern());
    cout << rt;
    BOOST_CHECK(cout.match_pattern());
}

BOOST_AUTO_TEST_CASE( IO_1CRN_1TOS )
{
    std::ifstream in(PATTERNS_FOLDER"1CRN.pdb");
    auto rt = make<root>();
    in >> rt;
    in.close();
    in.open(PATTERNS_FOLDER"1TOS.pdb");
    in >> rt;

    BOOST_CHECK(   3 == rt->frames_size() );
    BOOST_CHECK( 468 == rt->coords_size() );
    BOOST_CHECK( 468 == boost::distance(rt->range<atom>()) );

    output_test_stream cout(
        PATTERNS_FOLDER"1CRN_1TOS_out.pdb",
        !butrc::save_pattern());
    cout << rt;
    BOOST_CHECK(cout.match_pattern());
}

BOOST_AUTO_TEST_CASE( IO_2SOC_1TOS )
{
    std::ifstream in(PATTERNS_FOLDER"2SOC.pdb");
    auto rt = make<root>();
    in >> rt;
    in.close();
    in.open(PATTERNS_FOLDER"1TOS.pdb");
    in >> rt;

    BOOST_CHECK(   3 == rt->frames_size() );
    BOOST_CHECK( 278 == rt->coords_size() );
    BOOST_CHECK( 278 == boost::distance(rt->range<atom>()) );

    output_test_stream cout(
        PATTERNS_FOLDER"2SOC_1TOS_out.pdb",
        !butrc::save_pattern());
    cout << rt;
    BOOST_CHECK(cout.match_pattern());
}

BOOST_FIXTURE_TEST_CASE( IO_1TOS_2SOC_1TOS, ENT_1TOS_2SOC_INIT )
{
    BOOST_CHECK(   3 == rt->frames_size() );
    BOOST_CHECK( 278 == rt->coords_size() );
    BOOST_CHECK( 278 == boost::distance(rt->range<atom>()) );

    output_test_stream cout(
        PATTERNS_FOLDER"1TOS_2SOC_out.pdb",
        !butrc::save_pattern());
    cout << rt;
    BOOST_CHECK(cout.match_pattern());
}

BOOST_FIXTURE_TEST_CASE( IO_1TOSN2SOC_1TOS, ENT_1TOS_2SOC_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"1TOS_out.pdb",
        !butrc::save_pattern());
    cout << *(rt->begin<model>());
    BOOST_CHECK(cout.match_pattern());
}

BOOST_FIXTURE_TEST_CASE( IO_1TOSN2SOC_1TOS_MOL, ENT_1TOS_2SOC_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"1TOS_out_mol.pdb",
        !butrc::save_pattern());
    cout << *(rt->begin<chain>());
    BOOST_CHECK(cout.match_pattern());
}

BOOST_FIXTURE_TEST_CASE( IO_1TOSN2SOC_1TOS_RES, ENT_1TOS_2SOC_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"1TOS_out_res.pdb",
        !butrc::save_pattern());
    cout << *(rt->begin<residue>());
    BOOST_CHECK(cout.match_pattern());
}

BOOST_FIXTURE_TEST_CASE( IO_1TOSN2SOC_1TOS_ATM, ENT_1TOS_2SOC_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"1TOS_out_atm.pdb",
        !butrc::save_pattern());
    cout << *(rt->begin<atom>()) << std::endl;
    cout << *(rt->rbegin<atom>()) << std::endl;
    BOOST_CHECK(cout.match_pattern());
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
        PATTERNS_FOLDER"1S4A_F_5_res.pdb",
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

BOOST_AUTO_TEST_CASE(IN_1FFK)
{
    std::ifstream in(PATTERNS_FOLDER"1FFK.pdb");
    auto rt = make<root>();
    in >> rt;

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    connect<bond>(rt->range<atom>());
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(t2 - t1).count();
    std::cout << duration << " ms" << std::endl;
}
