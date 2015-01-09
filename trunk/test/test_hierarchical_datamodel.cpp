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
#include <list>

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/uniqued.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/count_if.hpp>
#include <boost/range/algorithm/for_each.hpp>

#include <maral/bootstraps/bs_basic.hpp>
#include <maral/iomanip.hpp>
#include <maral/units.hpp>

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
        rt = make<root>();
        auto crambin = make<model>("1CRN");
        auto chain = make<molecule>("A");

        auto res = make<residue>("PRO", 5);
        res->add(std::move(make<atom>
            ( "N", 27, point3f(9.561f, 9.108f, 13.563f))));
        res->add(std::move(make<atom>
            ("CA", 28, point3f(9.448f, 9.034f, 15.012f))));
        res->add(std::move(make<atom>
            ( "C", 29, point3f(9.288f, 7.670f, 15.606f))));
        res->add(std::move(make<atom>
            ( "O", 30, point3f(9.490f, 7.519f, 16.819f))));
        res->add(std::move(make<atom>
            ("CB", 31, point3f(8.230f, 9.957f, 15.345f))));
        res->add(std::move(make<atom>
            ("CG", 32, point3f(7.338f, 9.786f, 14.114f))));
        res->add(std::move(make<atom>
            ("CD", 33, point3f(8.366f, 9.804f, 12.958f))));
        chain->add(std::move(res));

        res = make<residue>("SER", 6);
        res->add(std::move(make<atom>
            ( "N", 34, point3f(8.875f, 6.686f, 14.796f))));
        res->add(std::move(make<atom>
            ("CA", 35, point3f(8.673f, 5.314f, 15.279f))));
        res->add(std::move(make<atom>
            ( "C", 36, point3f(8.753f, 4.376f, 14.083f))));
        res->add(std::move(make<atom>
            ( "O", 37, point3f(8.726f, 4.858f, 12.923f))));
        res->add(std::move(make<atom>
            ("CB", 38, point3f(7.340f, 5.121f, 15.996f))));
        res->add(std::move(make<atom>
            ("OG", 39, point3f(6.274f, 5.220f, 15.031f))));
        chain->add(std::move(res));

        crambin->add(std::move(chain));
        rt->add(std::move(crambin));
    }

    entity<root> rt;
};

BOOST_AUTO_TEST_CASE( Size_Test )
{
    entity<atom> atm(new atom("atom1"));
    BOOST_CHECK(sizeof(hierarchical::node_type) == sizeof(atm));
//    BOOST_CHECK(sizeof(hierarchical::hierarchy_type) == (2 * sizeof(atm)));
    BOOST_CHECK(sizeof(hierarchical) == sizeof atm);
//    BOOST_CHECK(sizeof(data_model::composite_node<hierarchical>) == (4 * sizeof(atm)));
    BOOST_CHECK(sizeof(data_model::leaf_node<hierarchical>) == (2 * sizeof(atm)));
//    BOOST_CHECK(sizeof(data_model::root_host<hierarchical>) == (4 * sizeof(atm)));
    //BOOST_CHECK(sizeof(component::name<std::string>) == sizeof(std::string));
    BOOST_CHECK(sizeof(component::order<unsigned>) == sizeof(unsigned));

    //BOOST_CHECK(sizeof(atom) == (4 * sizeof(atm)));
    //BOOST_CHECK(sizeof(molecule) == (6 * sizeof(atm)));
}

BOOST_AUTO_TEST_CASE( Dynamic_Casts )
{
    entity<molecule> mol = make<molecule>("Test");
    BOOST_CHECK(dynamic_cast<hierarchical*>(mol.get()));
    BOOST_CHECK(dynamic_cast<data_model::composite_node<hierarchical>*>(mol.get()));
    //BOOST_CHECK(dynamic_cast<component::name<std::string>*>(mol.get()));
    BOOST_CHECK(dynamic_cast<data_model::leaf_node<hierarchical>*>(mol.get()) == nullptr);
    BOOST_CHECK(dynamic_cast<data_model::root_node<hierarchical>*>(mol.get()) == nullptr);
    BOOST_CHECK(dynamic_cast<atom*>(mol.get()) == nullptr);
}

BOOST_FIXTURE_TEST_CASE( Find_Root, CRN_INIT )
{
    auto atm = rt->begin<atom>();
    BOOST_CHECK( atm->root() == rt.get() );
    auto pro = rt->begin<residue>();
    BOOST_CHECK( pro->root() == rt.get() );
    auto mol = rt->begin<molecule>();
    BOOST_CHECK( mol->root() == rt.get() );
    auto crn = rt->begin<model>();
    BOOST_CHECK( crn->root() == rt.get() );
}

BOOST_FIXTURE_TEST_CASE( Has_Ancestor, CRN_INIT )
{
    auto atm = rt->begin<atom>();
    BOOST_CHECK( atm->has_ancestor(rt.get()) );
    auto pro = rt->begin<residue>();
    BOOST_CHECK( pro->has_ancestor(rt.get()) );
    BOOST_CHECK( atm->has_ancestor(*pro) );
    auto mol = rt->begin<molecule>();
    BOOST_CHECK( mol->has_ancestor(rt.get()) );
    BOOST_CHECK( pro->has_ancestor(*mol) );
    BOOST_CHECK( atm->has_ancestor(*mol) );
    auto crn = rt->begin<model>();
    BOOST_CHECK( crn->has_ancestor(rt.get()) );
    BOOST_CHECK( mol->has_ancestor(*crn) );
    BOOST_CHECK( pro->has_ancestor(*crn) );
    BOOST_CHECK( atm->has_ancestor(*crn) );
    auto ser = rt->rbegin<residue>();
    BOOST_CHECK( atm->has_ancestor(*ser) == false );
    BOOST_CHECK( rt->has_ancestor(*atm) == false );
    BOOST_CHECK( rt->has_ancestor(rt.get()) == false );
    BOOST_CHECK( atm->has_ancestor(*atm) == false );
}

BOOST_AUTO_TEST_CASE( Composite_Add )
{
    auto rt = make<root>();
    //rt->name() = "new root";
    //rt->center() = { 1.0f, 1.0f, 1.0f };
    //std::cout << rt << std::endl;

    entity<atom> atom1(new atom("atom1"));
    rt->add(std::move(atom1));
    BOOST_CHECK(!atom1);

    entity<atom> atom2 = make<atom>("atom2", 2);
    rt->add(std::move(atom2));
    BOOST_CHECK(!atom2);

    auto atom3 = make<atom>("atom3", 3);
    rt->add(std::move(atom3));
    BOOST_CHECK(!atom3);

    rt->add(std::move(make<atom>("atom4", 4)));

    BOOST_CHECK(4 == rt->children()->size());

    for (auto atm : *rt)
    {
        BOOST_CHECK(atm->parent() == rt.get());
    }

    //auto atoms = make<atom[]>(5);
    //rt->add(std::move(atoms), 5);

    //for (auto atm : *rt)
    //    std::cout << delimiters('[', ']') << separator(' ')
    //         << atm << std::endl;
}

BOOST_FIXTURE_TEST_CASE( Composite_Insert, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"composite_insert.txt",
        !butrc::save_pattern());

    {
        auto pos = rt->begin<atom>();
        auto parent = (*pos)->parent();
        parent->insert(pos, std::move(make<atom>("B27")));
        pos += 3;
        parent->insert(pos, std::move(make<atom>("B30")));
        std::advance(pos, 4);
        parent = (*pos)->parent();
        parent->insert(pos, std::move(make<atom>("B34")));
    }
    {
        auto pos = rt->begin();
        ++pos;
        auto parent = (*pos)->parent();
        parent->insert(pos, std::move(make<molecule>("B4 A")));
        ++pos;
        parent = (*pos)->parent();
        parent->insert(pos, std::move(make<residue>("B4 PRO")));
        std::advance(pos, 10);
        parent = (*pos)->parent();
        parent->insert(pos, std::move(make<residue>("B4 SER")));
    }
    cout << shallow << delimiters('[', ']') << separator(' ');
    for (auto node : *rt)
    {
        cout << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_FIXTURE_TEST_CASE( Composite_Remove, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"composite_remove.txt",
        !butrc::save_pattern());

    auto pos = rt->begin<residue>();
    auto proline = *pos;
    std::list<atom*> to_be_removed;
    boost::copy(
        rt->range<atom>()
        |   boost::adaptors::filtered(
        [=] (const atom* atm)
            { return (atm->parent() == proline); }),
        back_inserter(to_be_removed) );

    cout << shallow << delimiters('[', ']') << separator(' ');
    for (auto atm : to_be_removed)
    {
        cout << atm << std::endl;
        BOOST_CHECK(cout.match_pattern());
        auto removed = proline->remove(atm);
        BOOST_CHECK(nullptr == removed->parent());
    }

    for (auto node : *rt)
    {
        cout << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_FIXTURE_TEST_CASE(Composite_Remove_Boost, CRN_INIT )
{
    //boost::remove(
    //    rt->range<atom>()
    //    |   boost::adaptors::filtered(
    //    [=] (const atom* atm)
    //        { return (atm->parent() == rt.get()); } ) );

    //boost::remove_if(
    //    rt->range<atom>(), true);
    //    [=] (const atom* atm)
    //        { return (atm->parent() == rt.get()); } );
}

BOOST_FIXTURE_TEST_CASE( Composite_Erase, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"composite_erase.txt",
        !butrc::save_pattern());

    // erasing all atoms in the proline
    auto proline = *(rt->begin<residue>());

    auto pos = proline->begin<atom>();
    while (pos != proline->end<atom>())
    {
        auto atom = *pos;
        if (proline == atom->parent())
        {
            //rt->erase(pos++);
            pos = proline->erase(pos);
            delete atom;
        }
        else
            ++pos;
    }

    cout << shallow << delimiters('[', ']') << separator(' ');
    for (auto node : *rt)
    {
        cout << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }

    // erasing all nodes in the root node
    auto itr = rt->begin();
    while (itr != rt->end())
    {
        auto node = *itr;
        if (rt.get() == node->parent())
        {
            itr = rt->erase(itr);
            delete node;
        }
        else
            ++itr;
    }

    BOOST_CHECK(0 == rt->children()->size());
}

BOOST_FIXTURE_TEST_CASE( Node_Iterator, CRN_INIT )
{
    auto itr = rt->begin();

    auto carmbin = dynamic_cast<model*>(*itr);
    BOOST_CHECK(carmbin->name() == "1CRN");

    auto chain = dynamic_cast<molecule*>(*(++itr));
    BOOST_CHECK(chain->name() == "A");

    auto res = dynamic_cast<residue*>(*(++itr));
    BOOST_CHECK(res->name() == "PRO");
    BOOST_CHECK(res->ordinal() == 5);

    atom* atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "N");
    BOOST_CHECK(atm->ordinal() == 27);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "CA");
    BOOST_CHECK(atm->ordinal() == 28);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "C");
    BOOST_CHECK(atm->ordinal() == 29);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "O");
    BOOST_CHECK(atm->ordinal() == 30);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "CB");
    BOOST_CHECK(atm->ordinal() == 31);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "CG");
    BOOST_CHECK(atm->ordinal() == 32);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "CD");
    BOOST_CHECK(atm->ordinal() == 33);

    res = dynamic_cast<residue*>(*(++itr));
    BOOST_CHECK(res->name() == "SER");
    BOOST_CHECK(res->ordinal() == 6);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "N");
    BOOST_CHECK(atm->ordinal() == 34);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "CA");
    BOOST_CHECK(atm->ordinal() == 35);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "C");
    BOOST_CHECK(atm->ordinal() == 36);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "O");
    BOOST_CHECK(atm->ordinal() == 37);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "CB");
    BOOST_CHECK(atm->ordinal() == 38);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "OG");
    BOOST_CHECK(atm->ordinal() == 39);
}

BOOST_FIXTURE_TEST_CASE( Reverse_Node_Iterator, CRN_INIT )
{
    auto itr = rt->rbegin();

    auto carmbin = dynamic_cast<model*>(*itr);
    BOOST_CHECK(carmbin->name() == "1CRN");

    auto chain = dynamic_cast<molecule*>(*(++itr));
    BOOST_CHECK(chain->name() == "A");

    auto res = dynamic_cast<residue*>(*(++itr));
    BOOST_CHECK(res->name() == "SER");
    BOOST_CHECK(res->ordinal() == 6);

    atom* atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "OG");
    BOOST_CHECK(atm->ordinal() == 39);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "CB");
    BOOST_CHECK(atm->ordinal() == 38);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "O");
    BOOST_CHECK(atm->ordinal() == 37);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "C");
    BOOST_CHECK(atm->ordinal() == 36);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "CA");
    BOOST_CHECK(atm->ordinal() == 35);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "N");
    BOOST_CHECK(atm->ordinal() == 34);

    res = dynamic_cast<residue*>(*(++itr));
    BOOST_CHECK(res->name() == "PRO");
    BOOST_CHECK(res->ordinal() == 5);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "CD");
    BOOST_CHECK(atm->ordinal() == 33);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "CG");
    BOOST_CHECK(atm->ordinal() == 32);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "CB");
    BOOST_CHECK(atm->ordinal() == 31);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "O");
    BOOST_CHECK(atm->ordinal() == 30);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "C");
    BOOST_CHECK(atm->ordinal() == 29);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "CA");
    BOOST_CHECK(atm->ordinal() == 28);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "N");
    BOOST_CHECK(atm->ordinal() == 27);
}

BOOST_FIXTURE_TEST_CASE( Type_Iterator, CRN_INIT )
{
    auto crambin = rt->begin<model>();
    BOOST_CHECK(crambin->name() == "1CRN");

    auto mol = rt->begin<molecule>();
    BOOST_CHECK(mol->name() == "A");

    auto res = rt->begin<residue>();
    BOOST_CHECK(res->name() == "PRO");
    BOOST_CHECK(res->ordinal() == 5);

    ++res;
    BOOST_CHECK(res->name() == "SER");
    BOOST_CHECK(res->ordinal() == 6);

    auto atm = rt->begin<atom>();

    BOOST_CHECK(atm->name() == "N");
    BOOST_CHECK(atm->ordinal() == 27);

    ++atm;
    BOOST_CHECK(atm->name() == "CA");
    BOOST_CHECK(atm->ordinal() == 28);

    ++atm;
    BOOST_CHECK(atm->name() == "C");
    BOOST_CHECK(atm->ordinal() == 29);

    ++atm;
    BOOST_CHECK(atm->name() == "O");
    BOOST_CHECK(atm->ordinal() == 30);

    ++atm;
    BOOST_CHECK(atm->name() == "CB");
    BOOST_CHECK(atm->ordinal() == 31);

    ++atm;
    BOOST_CHECK(atm->name() == "CG");
    BOOST_CHECK(atm->ordinal() == 32);

    ++atm;
    BOOST_CHECK(atm->name() == "CD");
    BOOST_CHECK(atm->ordinal() == 33);

    ++atm;
    BOOST_CHECK(atm->name() == "N");
    BOOST_CHECK(atm->ordinal() == 34);

    ++atm;
    BOOST_CHECK(atm->name() == "CA");
    BOOST_CHECK(atm->ordinal() == 35);

    ++atm;
    BOOST_CHECK(atm->name() == "C");
    BOOST_CHECK(atm->ordinal() == 36);

    ++atm;
    BOOST_CHECK(atm->name() == "O");
    BOOST_CHECK(atm->ordinal() == 37);

    ++atm;
    BOOST_CHECK(atm->name() == "CB");
    BOOST_CHECK(atm->ordinal() == 38);

    ++atm;
    BOOST_CHECK(atm->name() == "OG");
    BOOST_CHECK(atm->ordinal() == 39);
}

BOOST_FIXTURE_TEST_CASE( Reverse_Type_Iterator, CRN_INIT )
{
    auto crambin = rt->rbegin<model>();
    BOOST_CHECK(crambin->name() == "1CRN");

    auto mol = rt->rbegin<molecule>();
    BOOST_CHECK(mol->name() == "A");

    auto res = rt->rbegin<residue>();
    BOOST_CHECK(res->name() == "SER");
    BOOST_CHECK(res->ordinal() == 6);

    ++res;
    BOOST_CHECK(res->name() == "PRO");
    BOOST_CHECK(res->ordinal() == 5);

    auto atm = rt->rbegin<atom>();
//    auto x = maral::units::angstroms((*(*atm))[0]);
//    std::cout << x << std::endl;
//    std::cout << maral::units::to_nanometers(x) << std::endl;

    BOOST_CHECK(atm->name() == "OG");
    BOOST_CHECK(atm->ordinal() == 39);

    ++atm;
    BOOST_CHECK(atm->name() == "CB");
    BOOST_CHECK(atm->ordinal() == 38);

    ++atm;
    BOOST_CHECK(atm->name() == "O");
    BOOST_CHECK(atm->ordinal() == 37);

    ++atm;
    BOOST_CHECK(atm->name() == "C");
    BOOST_CHECK(atm->ordinal() == 36);

    ++atm;
    BOOST_CHECK(atm->name() == "CA");
    BOOST_CHECK(atm->ordinal() == 35);

    ++atm;
    BOOST_CHECK(atm->name() == "N");
    BOOST_CHECK(atm->ordinal() == 34);

    ++atm;
    BOOST_CHECK(atm->name() == "CD");
    BOOST_CHECK(atm->ordinal() == 33);

    ++atm;
    BOOST_CHECK(atm->name() == "CG");
    BOOST_CHECK(atm->ordinal() == 32);

    ++atm;
    BOOST_CHECK(atm->name() == "CB");
    BOOST_CHECK(atm->ordinal() == 31);

    ++atm;
    BOOST_CHECK(atm->name() == "O");
    BOOST_CHECK(atm->ordinal() == 30);

    ++atm;
    BOOST_CHECK(atm->name() == "C");
    BOOST_CHECK(atm->ordinal() == 29);

    ++atm;
    BOOST_CHECK(atm->name() == "CA");
    BOOST_CHECK(atm->ordinal() == 28);

    ++atm;
    BOOST_CHECK(atm->name() == "N");
    BOOST_CHECK(atm->ordinal() == 27);
}

BOOST_FIXTURE_TEST_CASE( Iterator_Copy, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"iterator_copy.txt",
        !butrc::save_pattern());

    std::vector<hierarchical*> nodes;
    std::copy(rt->begin(),
            rt->end(),
            back_inserter(nodes));

    BOOST_CHECK( 17 == nodes.size() );
    cout << shallow << delimiters('[', ']') << separator(' ');
    for (auto node : nodes)
    {
        cout << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_FIXTURE_TEST_CASE( Iterator_Boost_Copy, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"iterator_boost_range.txt",
        !butrc::save_pattern());

    std::vector<hierarchical*> nodes;
//    boost::copy(*rt, back_inserter(nodes));
    boost::copy(rt->range(), back_inserter(nodes));
    BOOST_CHECK( 17 == boost::size(nodes) );

// the following call prints pointer addresses, why?!
//    boost::copy(nodes
//                | boost::adaptors::reversed,
//                std::ostream_iterator<hierarchical*>(output, "\n") );

    cout << shallow << delimiters('[', ']') << separator(' ');
    for (auto node : nodes | boost::adaptors::reversed)
    {
        cout << node << std::endl;
        BOOST_CHECK( cout.match_pattern() );
    }
}

BOOST_FIXTURE_TEST_CASE( Type_Iterator_Copy, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"type_iterator_copy.txt",
        !butrc::save_pattern());

    std::vector<atom*> atoms;
    atoms.reserve(boost::distance(rt->range<atom>()));
    BOOST_CHECK( 13 == boost::distance(rt->range<atom>()) );
    std::copy(  rt->begin<atom>(),
                rt->end<atom>(),
                back_inserter(atoms));
    BOOST_CHECK( 13 == atoms.size() );

    cout << delimiters('[', ']') << separator(' ');
    for (auto atm : atoms)
    {
        cout << atm << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }

    std::vector<residue*> rsds;
    rsds.reserve(boost::distance(rt->range<residue>()));
    std::copy(  rt->begin<residue>(),
                rt->end<residue>(),
                back_inserter(rsds));
    BOOST_CHECK( 2 == rsds.size() );

    cout << shallow << delimiters('[', ']') << separator(' ');
    for (auto res : rsds)
    {
        cout << res << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_FIXTURE_TEST_CASE( Type_Iterator_Boost_Range, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"type_iterator_boost_range.txt",
        !butrc::save_pattern());

    std::vector<atom*> atoms;
    atoms.reserve(13);

    boost::copy(rt->range<atom>(), back_inserter(atoms));
    BOOST_CHECK( 13 == boost::size(atoms) );

    cout << delimiters('[', ']') << separator(' ');
    boost::copy(atoms
                | boost::adaptors::reversed,
                std::ostream_iterator<atom*>(cout, "\n") );
    BOOST_CHECK(cout.match_pattern());

    // lambda support...
    boost::copy(rt->range<atom>()
//                | boost::adaptors::filtered(is_even()),
                | boost::adaptors::filtered(
                [](const atom* atm) { return atm->ordinal() % 2 == 0; }),
                std::ostream_iterator<atom*>(cout, "\n") );
    BOOST_CHECK(cout.match_pattern());

    std::vector<residue*> rsds;
    rsds.reserve(boost::distance(rt->range<residue>()));
    boost::copy(rt->range<residue>(), back_inserter(rsds));
    BOOST_CHECK( 2 == rsds.size() );

    cout << shallow;
    boost::copy(rsds | boost::adaptors::reversed,
                std::ostream_iterator<residue*>(cout, "\n") );
    BOOST_CHECK(cout.match_pattern());

    for (auto res : rt->range<residue>()
                  | boost::adaptors::uniqued)
    {
        cout << res << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_FIXTURE_TEST_CASE( Reverse_Iterator_Range, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"reverse_iterator_range.txt",
        !butrc::save_pattern());

    auto res = *(rt->rbegin<residue>());
    cout << delimiters('[', ']') << separator(' ');
    for (auto node : res->reverse_range())
    {
        cout << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
    boost::copy(res->reverse_range<atom>()
                | boost::adaptors::filtered(
                [](const atom* atm) { return atm->ordinal() % 2 == 1; }),
                std::ostream_iterator<atom*>(cout, "\n") );
    BOOST_CHECK(cout.match_pattern());
}

//BOOST_FIXTURE_TEST_CASE( Reverse_Iterator, CRN_INIT )
//{
//    output_test_stream cout(
//        PATTERNS_FOLDER"iterator_boost_range.txt",
//        !butrc::save_pattern());
//
//    std::cout << shallow << delimiters('[', ']') << separator(' ');
//    for (auto node : rt->reverse_range())
//    {
//        std::cout << node << std::endl;
//        //BOOST_CHECK( cout.match_pattern() );
//    }
//}

BOOST_FIXTURE_TEST_CASE( Position_Component, CRN_INIT )
{
    boost::for_each(rt->range<atom>(),
//                    [](atom* atm) { atm->center().zero(); } );
//                    [](atom* atm) { (*atm)[0] = 1.0f; } );
                    [](atom* atm) { atm->center() = { 1.0f, 2.0f, 3.0f }; } );
//                    [](atom* atm) { atm->center()[0] = 1.0f; std::cout << (*atm)[0] << std::endl; } );
//    std::cout << std::rank<point3<float>::>::value << std::endl;
    //static_assert(std::is_base_of<component::position<point3<float> >, atom>::value,
    //              "atom must have a position component");
    //static_assert(std::is_base_of<component::position<point3f>, atom>::value,
    //              "atom must have a position component");
//    static_assert(std::is_base_of<component::position<point3<float> >, molecule>::value,
//                  "molecule must have a position component");
//    std::cout << pntvec_traits<point3f>::extent::den << std::endl;
//    static_assert(pntvec_traits<point3f>::extent::den > 0, "out of range!");

    BOOST_CHECK(13 == boost::count_if(rt->range<atom>(),
                                      [](atom* atm) { return (*atm)[0] == 1.0f; } ) );
    BOOST_CHECK(13 == boost::count_if(rt->range<atom>(),
                                      [](atom* atm) { return (*atm)[1] == 2.0f; } ) );
    BOOST_CHECK(13 == boost::count_if(rt->range<atom>(),
                                      [](atom* atm) { return (*atm)[2] == 3.0f; } ) );
    //BOOST_CHECK( 0 == boost::count_if(rt->range<atom>(),
    //                                  [](atom* atm) { return (atm->center() == point3<float>().zero() ); } ) );
}

//BOOST_FIXTURE_TEST_CASE( Boost_Range_Search, ROOT_INIT )
//{
//    std::list<hierarchical*> to_be_removed;
//    boost::copy(*rt
//                | boost::adaptors::filtered(
//                [](const atom* atm) { return atm->ordinal() % 2 == 0; }),
//                std::ostream_iterator<atom*>(output, ",") );
//    boost::copy(rt->range<atom>(), back_inserter(atoms));
//    boost::erase(*rt, atoms);
//}

//BOOST_FIXTURE_TEST_CASE( Format, CRN_INIT )
//{
//    std::cout << format(tree) << rt << std::endl;
//    for (auto node : *rt)
//        std::cout << delimiters('[', ']') << separator(' ')
//             << node << std::endl;
//}

//BOOST_FIXTURE_TEST_CASE( Format, CRN_INIT )
//{
//    std::cout << rt << std::endl;
//}
