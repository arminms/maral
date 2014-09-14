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

#include <maral/bootstraps/basic.hpp>
#include <maral/iomanip.hpp>

using boost::test_tools::output_test_stream;
namespace butrc = boost::unit_test::runtime_config;

using namespace maral;
using namespace maral::bootstrap::basic;

#define PATTERNS_FOLDER "patterns/"

struct CRN_INIT
{
    CRN_INIT()
    {
        using mtl::point3f;
        rt = make_node<root>();
        auto crambin = make_node<model>("1CRN");
        auto chain = make_node<molecule>("A");

        auto res = make_node<residue>("PRO", 5);
        res->add(std::move(make_node<atom>
            ( "N", 27, point3f(9.561f, 9.108f, 13.563f))));
        res->add(std::move(make_node<atom>
            ("CA", 28, point3f(9.448f, 9.034f, 15.012f))));
        res->add(std::move(make_node<atom>
            ( "C", 29, point3f(9.288f, 7.670f, 15.606f))));
        res->add(std::move(make_node<atom>
            ( "O", 30, point3f(9.490f, 7.519f, 16.819f))));
        res->add(std::move(make_node<atom>
            ("CB", 31, point3f(8.230f, 9.957f, 15.345f))));
        res->add(std::move(make_node<atom>
            ("CG", 32, point3f(7.338f, 9.786f, 14.114f))));
        res->add(std::move(make_node<atom>
            ("CD", 33, point3f(8.366f, 9.804f, 12.958f))));
        chain->add(std::move(res));

        res = make_node<residue>("SER", 6);
        res->add(std::move(make_node<atom>
            ( "N", 34, point3f(8.875f, 6.686f, 14.796f))));
        res->add(std::move(make_node<atom>
            ("CA", 35, point3f(8.673f, 5.314f, 15.279f))));
        res->add(std::move(make_node<atom>
            ( "C", 36, point3f(8.753f, 4.376f, 14.083f))));
        res->add(std::move(make_node<atom>
            ( "O", 37, point3f(8.726f, 4.858f, 12.923f))));
        res->add(std::move(make_node<atom>
            ("CB", 38, point3f(7.340f, 5.121f, 15.996f))));
        res->add(std::move(make_node<atom>
            ("OG", 39, point3f(6.274f, 5.220f, 15.031f))));
        chain->add(std::move(res));

        crambin->add(std::move(chain));
        rt->add(std::move(crambin));
    }

    node<root> rt;
};

BOOST_FIXTURE_TEST_CASE( Root_Tree_Shallow, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"root_tree.txt",
        !butrc::save_pattern());

    cout << delimiters('[', ']') << separator(' ')
         << shallow << rt.get() << std::endl;
    BOOST_CHECK(cout.match_pattern());
    for (auto node : *rt)
    {
        cout << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_FIXTURE_TEST_CASE( Root_Tree_Deep, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"root_tree.txt",
        !butrc::save_pattern());

    cout << delimiters('[', ']') << separator(' ') << rt.get();
    BOOST_CHECK(cout.match_pattern());
}

BOOST_FIXTURE_TEST_CASE( Model_Tree_Shallow, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"model_tree.txt",
        !butrc::save_pattern());

    auto crambin = *(rt->begin<model>());
    cout << shallow << delimiters('[', ']') << separator(' ')
         << crambin << std::endl;
    BOOST_CHECK(cout.match_pattern());
    for (auto node : *crambin)
    {
        cout << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_FIXTURE_TEST_CASE( Model_Tree_Deep, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"model_tree.txt",
        !butrc::save_pattern());

    auto crambin = *(rt->begin<model>());
    cout << delimiters('[', ']') << separator(' ') << crambin;
    BOOST_CHECK(cout.match_pattern());
}

BOOST_FIXTURE_TEST_CASE( Molecule_Tree_Shallow, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"molecule_tree.txt",
        !butrc::save_pattern());

    auto chain_a = *(rt->begin<molecule>());
    cout << shallow << delimiters('[', ']') << separator(' ')
         << chain_a << std::endl;
    BOOST_CHECK(cout.match_pattern());
    for (auto node : *chain_a)
    {
        cout << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_FIXTURE_TEST_CASE( Molecule_Tree_Deep, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"molecule_tree.txt",
        !butrc::save_pattern());

    auto chain_a = *(rt->begin<molecule>());
    cout << delimiters('[', ']') << separator(' ') << chain_a;
    BOOST_CHECK(cout.match_pattern());
}

BOOST_FIXTURE_TEST_CASE( Submolecule_Tree_Shallow, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"submolecule_tree.txt",
        !butrc::save_pattern());

    auto pos = rt->begin<residue>();
    auto res = *pos;
    cout << shallow << delimiters('[', ']') << separator(' ')
         << res << std::endl;
    BOOST_CHECK(cout.match_pattern());
    for (auto node : *res)
    {
        cout << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }

    res = *(++pos);
    cout << res << std::endl;
    BOOST_CHECK(cout.match_pattern());
    for (auto node : *res)
    {
        cout << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_FIXTURE_TEST_CASE( Submolecule_Tree_Deep, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"submolecule_tree.txt",
        !butrc::save_pattern());

    auto pos = rt->begin<residue>();
    auto res = *pos;
    cout << delimiters('[', ']') << separator(' ') << res;
    BOOST_CHECK(cout.match_pattern());

    res = *(++pos);
    cout << res;
    BOOST_CHECK(cout.match_pattern());
}

BOOST_FIXTURE_TEST_CASE( Atom_Tree, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"atom_tree.txt",
        !butrc::save_pattern());

    auto atm = *(rt->begin<atom>());
    cout << delimiters('[', ']') << separator(' ')
         << shallow << atm << std::endl;
    BOOST_CHECK(cout.match_pattern());
    cout << deep << atm << std::endl;
    BOOST_CHECK(cout.match_pattern());
}
