// $Id$
//------------------------------------------------------------------------------

#include <fstream>

#include <iostream>
#include <list>
#include <ratio>

#define BOOST_TEST_MODULE Maral Master Test Suite
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>
//#include <boost/mpl/list.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>

#include <mtl/mtl.hpp>
#include <traits.hpp>
#include <node.hpp>
#include <hierarchical.hpp>
#include <policies.hpp>
#include <atom.hpp>
#include <molecule.hpp>
#include <root.hpp>
#include <inserters.hpp>

#define PATTERNS_FOLDER "patterns/"

using boost::test_tools::output_test_stream;
using namespace maral;
using namespace maral::mtl;
//using namespace maral::model;
namespace utrc = boost::unit_test::runtime_config;

typedef atom_h_node
<
    model::hierarchical
,   point3<float>
//,   policies::ordered<unsigned>
//,   std::vector<float>
> atom;

typedef molecule_h_node
<
    model::hierarchical
//,   policies::position<point3f>
> molecule;

typedef root_h_node
<
    model::hierarchical
,   std::string
> root;

struct CRN_INIT
{
    CRN_INIT()
    {
        rt = make_node<root>("1CRN");
        node<molecule> chain = make_node<molecule>("A");

        node<molecule> res = make_node<molecule>("PRO", 5);
        res->add(std::move(make_node<atom>( "N", 27, point3f(9.561f, 9.108f, 13.563f))));
        res->add(std::move(make_node<atom>("CA", 28, point3f(9.448f, 9.034f, 15.012f))));
        res->add(std::move(make_node<atom>( "C", 29, point3f(9.288f, 7.670f, 15.606f))));
        res->add(std::move(make_node<atom>( "O", 30, point3f(9.490f, 7.519f, 16.819f))));
        res->add(std::move(make_node<atom>("CB", 31, point3f(8.230f, 9.957f, 15.345f))));
        res->add(std::move(make_node<atom>("CG", 32, point3f(7.338f, 9.786f, 14.114f))));
        res->add(std::move(make_node<atom>("CD", 33, point3f(8.366f, 9.804f, 12.958f))));
        chain->add(std::move(res));

        res = make_node<molecule>("SER", 6);
        res->add(std::move(make_node<atom>( "N", 34, point3f(8.875f, 6.686f, 14.796f))));
        res->add(std::move(make_node<atom>("CA", 35, point3f(8.673f, 5.314f, 15.279f))));
        res->add(std::move(make_node<atom>( "C", 36, point3f(8.753f, 4.376f, 14.083f))));
        res->add(std::move(make_node<atom>( "O", 37, point3f(8.726f, 4.858f, 12.923f))));
        res->add(std::move(make_node<atom>("CB", 38, point3f(7.340f, 5.121f, 15.996f))));
        res->add(std::move(make_node<atom>("OG", 39, point3f(6.274f, 5.220f, 15.031f))));
        chain->add(std::move(res));

        rt->add(std::move(chain));
    }

    node<root> rt;
};

BOOST_AUTO_TEST_SUITE( Maral )

BOOST_AUTO_TEST_SUITE( H_Model )

BOOST_AUTO_TEST_CASE( Size_Test )
{
    node<atom> atm(new atom("atom1"));
    BOOST_CHECK(sizeof(hierarchical::node_type) == sizeof(atm));
//    BOOST_CHECK(sizeof(hierarchical::hierarchy_type) == (2 * sizeof(atm)));
    BOOST_CHECK(sizeof(hierarchical) == sizeof atm);
//    BOOST_CHECK(sizeof(model::composite_node<hierarchical>) == (4 * sizeof(atm)));
    BOOST_CHECK(sizeof(model::leaf_node<hierarchical>) == (2 * sizeof(atm)));
//    BOOST_CHECK(sizeof(model::root_node<hierarchical>) == (4 * sizeof(atm)));
    BOOST_CHECK(sizeof(policies::named<std::string>) == sizeof(std::string));
    BOOST_CHECK(sizeof(policies::ordered<unsigned>) == sizeof(unsigned));

    //BOOST_CHECK(sizeof(atom) == (4 * sizeof(atm)));
    //BOOST_CHECK(sizeof(molecule) == (6 * sizeof(atm)));
}

BOOST_AUTO_TEST_CASE( Dynamic_Casts )
{
    node<molecule> mol = make_node<molecule>("Test");
    BOOST_CHECK(dynamic_cast<hierarchical*>(mol.get()));
    BOOST_CHECK(dynamic_cast<model::composite_node<hierarchical>*>(mol.get()));
    BOOST_CHECK(dynamic_cast<policies::named<std::string>*>(mol.get()));
    BOOST_CHECK(dynamic_cast<model::leaf_node<hierarchical>*>(mol.get()) == nullptr);
    BOOST_CHECK(dynamic_cast<model::root_node<hierarchical>*>(mol.get()) == nullptr);
    BOOST_CHECK(dynamic_cast<atom*>(mol.get()) == nullptr);
}

BOOST_AUTO_TEST_CASE( Composite_Add )
{
    auto rt = make_node<root>("root");
    //std::cout << rt.get() << std::endl;

    node<atom> atom1(new atom("atom1"));
    rt->add(std::move(atom1));
    BOOST_CHECK(!atom1);

    node<atom> atom2 = make_node<atom>("atom2", 2);
    rt->add(std::move(atom2));
    BOOST_CHECK(!atom2);

    auto atom3 = make_node<atom>("atom3", 3);
    rt->add(std::move(atom3));
    BOOST_CHECK(!atom3);

    rt->add(std::move(make_node<atom>("atom4", 4)));

    BOOST_CHECK(4 == rt->children()->size());

    for (auto atm : *rt)
    {
        BOOST_CHECK(atm->parent() == rt.get());
    }

    //auto atoms = make_node<atom[]>(5);
    //rt->add(std::move(atoms), 5);

    //for (auto atm : *rt)
    //    std::cout << delimiters('[', ']') << separator(' ')
    //         << atm << std::endl;
}

BOOST_FIXTURE_TEST_CASE( Root_Tree, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"root_tree.txt",
        !utrc::save_pattern());

    cout << rt.get() << std::endl;
    BOOST_CHECK(cout.match_pattern());
    for (auto node : *rt)
    {
        cout << delimiters('[', ']') << separator(' ')
             << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_FIXTURE_TEST_CASE( Composite_Insert, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"composite_insert.txt",
        !utrc::save_pattern());

    {
        auto pos = rt->begin<atom>();
        auto parent = (*pos)->parent();
        parent->insert(pos, std::move(make_node<atom>("B27")));
        pos += 3;
        parent->insert(pos, std::move(make_node<atom>("B30")));
        std::advance(pos, 4);
        parent = (*pos)->parent();
        parent->insert(pos, std::move(make_node<atom>("B34")));
    }
    {
        auto pos = rt->begin();
        auto parent = (*pos)->parent();
        parent->insert(pos, std::move(make_node<molecule>("B4 A")));
        ++pos;
        parent = (*pos)->parent();
        parent->insert(pos, std::move(make_node<molecule>("B4 PRO")));
        std::advance(pos, 10);
        parent = (*pos)->parent();
        parent->insert(pos, std::move(make_node<molecule>("B4 SER")));
    }
    for (auto node : *rt)
    {
        cout << delimiters('[', ']') << separator(' ')
             << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_FIXTURE_TEST_CASE( Composite_Remove, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"composite_remove.txt",
        !utrc::save_pattern());

    auto pos = rt->begin<molecule>();
    auto proline = *(++pos);
    std::list<atom*> to_be_removed;
    boost::copy(
        rt->range<atom>()
        |   boost::adaptors::filtered(
        [=] (const atom* atm)
            { return (atm->parent() == proline); }),
        back_inserter(to_be_removed) );

    for (auto atm : to_be_removed)
    {
        cout << delimiters('[', ']') << separator(' ')
             << atm << std::endl;
        BOOST_CHECK(cout.match_pattern());
        auto removed = proline->remove(atm);
        BOOST_CHECK(nullptr == removed->parent());
    }

    for (auto node : *rt)
    {
        cout << delimiters('[', ']') << separator(' ')
             << node << std::endl;
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
        !utrc::save_pattern());

    // erasing all atoms in the proline
    auto proline = *(++(rt->begin<molecule>()));

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

    for (auto node : *rt)
    {
        cout << delimiters('[', ']') << separator(' ')
             << node << std::endl;
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

    molecule* mol = dynamic_cast<molecule*>(*itr);
    BOOST_CHECK(mol->name() == "A");
    BOOST_CHECK(mol->ordinal() == 1);

    mol = dynamic_cast<molecule*>(*(++itr));
    BOOST_CHECK(mol->name() == "PRO");
    BOOST_CHECK(mol->ordinal() == 5);

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

    mol = dynamic_cast<molecule*>(*(++itr));
    BOOST_CHECK(mol->name() == "SER");
    BOOST_CHECK(mol->ordinal() == 6);

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

BOOST_FIXTURE_TEST_CASE( Iterator_Copy, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"iterator_copy.txt",
        !utrc::save_pattern());

    std::vector<hierarchical*> nodes;
    std::copy(rt->begin(),
            rt->end(),
            back_inserter(nodes));

    BOOST_CHECK( 16 == nodes.size() );
    for (auto node : nodes)
    {
        cout << delimiters('[', ']') << separator(' ')
             << node << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_FIXTURE_TEST_CASE( Iterator_Boost_Range, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"iterator_boost_range.txt",
        !utrc::save_pattern());

    std::vector<hierarchical*> nodes;
//    boost::copy(*rt, back_inserter(nodes));
    boost::copy(rt->range(), back_inserter(nodes));
    BOOST_CHECK( 16 == boost::size(nodes) );

// the following call prints pointer addresses, why?!
//    boost::copy(nodes
//                | boost::adaptors::reversed,
//                std::ostream_iterator<hierarchical*>(output, "\n") );

    for (auto node : nodes | boost::adaptors::reversed)
    {
        cout << delimiters('[', ']') << separator(' ')
             << node << std::endl;
        BOOST_CHECK( cout.match_pattern() );
    }
}

BOOST_FIXTURE_TEST_CASE( Type_Iterator, CRN_INIT )
{
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

    auto mol = rt->begin<molecule>();
    BOOST_CHECK(mol->name() == "A");
    BOOST_CHECK(mol->ordinal() == 1);

    ++mol;
    BOOST_CHECK(mol->name() == "PRO");
    BOOST_CHECK(mol->ordinal() == 5);

    ++mol;
    BOOST_CHECK(mol->name() == "SER");
    BOOST_CHECK(mol->ordinal() == 6);
}

BOOST_FIXTURE_TEST_CASE( Type_Iterator_Copy, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"type_iterator_copy.txt",
        !utrc::save_pattern());

    std::vector<atom*> atoms;
    atoms.reserve(boost::distance(rt->range<atom>()));
    BOOST_CHECK( 13 == boost::distance(rt->range<atom>()) );
    std::copy(  rt->begin<atom>(),
                rt->end<atom>(),
                back_inserter(atoms));
    BOOST_CHECK( 13 == atoms.size() );

    for (auto atm : atoms)
    {
        cout << delimiters('[', ']') << separator(' ')
             << atm << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }

    std::vector<molecule*> mols;
    mols.reserve(boost::distance(rt->range<molecule>()));
    std::copy(  rt->begin<molecule>(),
                rt->end<molecule>(),
                back_inserter(mols));
    BOOST_CHECK( 3 == mols.size() );

    for (auto mol : mols)
    {
        cout << delimiters('[', ']') << separator(' ')
             << mol << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_FIXTURE_TEST_CASE( Type_Iterator_Boost_Range, CRN_INIT )
{
    output_test_stream cout(
        PATTERNS_FOLDER"type_iterator_boost_range.txt",
        !utrc::save_pattern());

    std::vector<atom*> atoms;
    atoms.reserve(13);

    boost::copy(rt->range<atom>(), back_inserter(atoms));
    BOOST_CHECK( 13 == boost::size(atoms) );

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

    std::vector<molecule*> mols;
    mols.reserve(boost::distance(rt->range<molecule>()));
    boost::copy(rt->range<molecule>(), back_inserter(mols));
    BOOST_CHECK( 3 == mols.size() );

    boost::copy(mols | boost::adaptors::reversed,
                std::ostream_iterator<molecule*>(cout, "\n") );
    BOOST_CHECK(cout.match_pattern());

    for (auto mol : rt->range<molecule>()
                  | boost::adaptors::uniqued)
    {
        cout << delimiters('[', ']') << separator(' ')
             << mol << std::endl;
        BOOST_CHECK(cout.match_pattern());
    }
}

BOOST_FIXTURE_TEST_CASE( Position_Policy, CRN_INIT )
{
    boost::for_each(rt->range<atom>(),
//                    [](atom* atm) { atm->center().zero(); } );
//                    [](atom* atm) { (*atm)[0] = 1.0f; } );
                    [](atom* atm) { atm->center() = { 1.0f, 2.0f, 3.0f }; } );
//                    [](atom* atm) { atm->center()[0] = 1.0f; std::cout << (*atm)[0] << std::endl; } );
//    std::cout << std::rank<point3<float>::>::value << std::endl;
    static_assert(std::is_base_of<policies::position<point3<float> >, atom>::value,
                  "atom must have a position policy");
    static_assert(std::is_base_of<policies::position<point3f>, atom>::value,
                  "atom must have a position policy");
//    static_assert(std::is_base_of<policies::position<point3<float> >, molecule>::value,
//                  "molecule must have a position policy");
//    std::cout << type_traits<point3f>::extent::den << std::endl;
    static_assert(type_traits<point3f>::extent::den > 0, "out of range!");

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

BOOST_AUTO_TEST_SUITE_END() // H_Model

BOOST_AUTO_TEST_SUITE_END() // Maral
