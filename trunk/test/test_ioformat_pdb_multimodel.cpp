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
    in >> format(pdb) >> rt.get();

    BOOST_CHECK(   1 == boost::distance(rt->range<model>()) );
    BOOST_CHECK(   1 == boost::distance(rt->range<chain>()) );
    BOOST_CHECK(  46 == boost::distance(rt->range<residue>()) );
    BOOST_CHECK( 327 == boost::distance(rt->range<atom>()) );
}

BOOST_AUTO_TEST_CASE( PDB_2MKK )
{
    std::ifstream in(PATTERNS_FOLDER"2MKK.pdb");
    auto rt = make_node<root>();
    in >> format(pdb) >> rt.get();

    BOOST_CHECK(   10 == rt->frames_size() );
    BOOST_CHECK( 3532 == rt->coords_size() );

    output_test_stream cout(
        PATTERNS_FOLDER"2MKK_out.pdb",
        !butrc::save_pattern());

    cout << format(pdb) << rt.get();
    BOOST_CHECK(cout.match_pattern());
}
