// $Id$
//------------------------------------------------------------------------------

#include <iostream>

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
//#include <boost/mpl/list.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>

#include <node.hpp>
#include <hierarchical.hpp>
#include <policies.hpp>
#include <atom.hpp>
#include <molecule.hpp>
#include <output.hpp>

using boost::test_tools::output_test_stream;
using namespace maral;
//using namespace maral::model;

typedef atom_h_node<model::hierarchical> atom;
typedef molecule_h_node<model::hierarchical> molecule;

//typedef boost::mpl::list<int,float,double,long double> test_types;
//typedef boost::mpl::list<float,double,long double> float_types;

struct ROOT_INIT
{
    ROOT_INIT()
    {
        root = make_node<molecule>("root");
        root->add(std::move(make_node<molecule>("empty molecule", 1)));

        node<molecule> res1 = make_node<molecule>("residue1", 1);

        res1->add(std::move(make_node<atom>("atom1")));
        res1->add(std::move(make_node<atom>("atom2", 2)));
        res1->add(std::move(make_node<atom>("atom3", 3)));
        res1->add(std::move(make_node<atom>("atom4", 4)));

        root->add(std::move(res1));

        root->add(std::move(make_node<atom>("inserted atom1", 1)));
        root->add(std::move(make_node<atom>("inserted atom2", 2)));

        node<molecule> res2 = make_node<molecule>("residue2", 2);
        res2->add(std::move(make_node<atom>("atom5", 5)));
        res2->add(std::move(make_node<atom>("atom6", 6)));
        res2->add(std::move(make_node<atom>("atom7", 7)));
        root->add(std::move(res2));

        node<molecule> chain = make_node<molecule>("chain1", 1);
        node<molecule> res4 = make_node<molecule>("residue4", 4);
        res4->add(std::move(make_node<atom>("atom8", 8)));
        res4->add(std::move(make_node<atom>("atom9", 9)));
        chain->add(std::move(res4));
        root->add(std::move(chain));

        root->add(std::move(make_node<atom>("inserted atom3", 3)));
        root->add(std::move(make_node<atom>("inserted atom4", 4)));
    }

    node<molecule> root;
};

BOOST_AUTO_TEST_SUITE( Maral )

BOOST_AUTO_TEST_SUITE( H_Model )

BOOST_AUTO_TEST_CASE( Size_Test )
{
    node<atom> atm(new atom("atom1"));
    BOOST_CHECK(sizeof(hierarchical::node_type) == sizeof(atm));
    BOOST_CHECK(sizeof(hierarchical::hierarchy_type) == (2 * sizeof(atm)));
    BOOST_CHECK(sizeof(hierarchical) == sizeof atm);
    BOOST_CHECK(sizeof(model::composite_node<hierarchical>) == (4 * sizeof(atm)));
    BOOST_CHECK(sizeof(model::leaf_node<hierarchical>) == (2 * sizeof(atm)));
    BOOST_CHECK(sizeof(model::root_node<hierarchical>) == (4 * sizeof(atm)));
    BOOST_CHECK(sizeof(policies::has_name) == sizeof(std::string));
    BOOST_CHECK(sizeof(policies::ordered) == sizeof(unsigned));
    BOOST_CHECK(sizeof(atom) == (4 * sizeof(atm)));
    BOOST_CHECK(sizeof(molecule) == (6 * sizeof(atm)));
}

BOOST_AUTO_TEST_CASE( Dynamic_Casts )
{
    node<molecule> mol = make_node<molecule>("Test");
    BOOST_CHECK(dynamic_cast<hierarchical*>(mol.get()));
    BOOST_CHECK(dynamic_cast<model::composite_node<hierarchical>*>(mol.get()));
    BOOST_CHECK(dynamic_cast<policies::has_name*>(mol.get()));
    BOOST_CHECK(dynamic_cast<model::leaf_node<hierarchical>*>(mol.get()) == nullptr);
    BOOST_CHECK(dynamic_cast<model::root_node<hierarchical>*>(mol.get()) == nullptr);
    BOOST_CHECK(dynamic_cast<atom*>(mol.get()) == nullptr);
}

BOOST_AUTO_TEST_CASE( Make_Node )
{
    node<molecule> root = make_node<molecule>("root");

    node<atom> atom1(new atom("atom1"));
    root->add(std::move(atom1));
    BOOST_CHECK(!atom1);

    node<atom> atom2 = make_node<atom>("atom2", 2);
    root->add(std::move(atom2));
    BOOST_CHECK(!atom2);

    auto atom3 = make_node<atom>("atom3", 3);
    root->add(std::move(atom3));
    BOOST_CHECK(!atom3);

    root->add(std::move(make_node<atom>("atom4", 4)));

    BOOST_CHECK(4 == root->children()->size());
}

BOOST_FIXTURE_TEST_CASE( Node_Iterator, ROOT_INIT )
{
    auto itr = root->begin();

    molecule* mol = dynamic_cast<molecule*>(*itr);
    BOOST_CHECK(mol->name() == "empty molecule");
    BOOST_CHECK(mol->ordinal() == 1);

    mol = dynamic_cast<molecule*>(*(++itr));
    BOOST_CHECK(mol->name() == "residue1");
    BOOST_CHECK(mol->ordinal() == 1);

    atom* atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "atom1");
    BOOST_CHECK(atm->ordinal() == 1);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "atom2");
    BOOST_CHECK(atm->ordinal() == 2);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "atom3");
    BOOST_CHECK(atm->ordinal() == 3);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "atom4");
    BOOST_CHECK(atm->ordinal() == 4);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "inserted atom1");
    BOOST_CHECK(atm->ordinal() == 1);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "inserted atom2");
    BOOST_CHECK(atm->ordinal() == 2);

    mol = dynamic_cast<molecule*>(*(++itr));
    BOOST_CHECK(mol->name() == "residue2");
    BOOST_CHECK(mol->ordinal() == 2);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "atom5");
    BOOST_CHECK(atm->ordinal() == 5);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "atom6");
    BOOST_CHECK(atm->ordinal() == 6);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "atom7");
    BOOST_CHECK(atm->ordinal() == 7);

    mol = dynamic_cast<molecule*>(*(++itr));
    BOOST_CHECK(mol->name() == "chain1");
    BOOST_CHECK(mol->ordinal() == 1);

    mol = dynamic_cast<molecule*>(*(++itr));
    BOOST_CHECK(mol->name() == "residue4");
    BOOST_CHECK(mol->ordinal() == 4);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "atom8");
    BOOST_CHECK(atm->ordinal() == 8);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "atom9");
    BOOST_CHECK(atm->ordinal() == 9);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "inserted atom3");
    BOOST_CHECK(atm->ordinal() == 3);

    atm = dynamic_cast<atom*>(*(++itr));
    BOOST_CHECK(atm->name() == "inserted atom4");
    BOOST_CHECK(atm->ordinal() == 4);
}

BOOST_FIXTURE_TEST_CASE( Iterator_Copy, ROOT_INIT )
{
    output_test_stream output;
    std::vector<hierarchical*> nodes;
    std::copy(root->begin(),
            root->end(),
            back_inserter(nodes));
    BOOST_CHECK( 18 == nodes.size() );
    for (auto node : nodes)
        output << node << ',';
    BOOST_CHECK( output.is_equal(
            "empty molecule, 1,"
            "residue1, 1,"
            "atom1, 1,"
            "atom2, 2,"
            "atom3, 3,"
            "atom4, 4,"
            "inserted atom1, 1,"
            "inserted atom2, 2,"
            "residue2, 2,"
            "atom5, 5,"
            "atom6, 6,"
            "atom7, 7,"
            "chain1, 1,"
            "residue4, 4,"
            "atom8, 8,"
            "atom9, 9,"
            "inserted atom3, 3,"
            "inserted atom4, 4," ) );
}

BOOST_FIXTURE_TEST_CASE( Iterator_Boost_Range, ROOT_INIT )
{
    output_test_stream output;
    std::vector<hierarchical*> nodes;
//    boost::copy(*root, back_inserter(nodes));
    boost::copy(root->range(), back_inserter(nodes));
    BOOST_CHECK( 18 == boost::size(nodes) );
    for (auto node : nodes | boost::adaptors::reversed)
        output << node << ',';
    BOOST_CHECK( output.is_equal(
            "inserted atom4, 4,"
            "inserted atom3, 3,"
            "atom9, 9,"
            "atom8, 8,"
            "residue4, 4,"
            "chain1, 1,"
            "atom7, 7,"
            "atom6, 6,"
            "atom5, 5,"
            "residue2, 2,"
            "inserted atom2, 2,"
            "inserted atom1, 1,"
            "atom4, 4,"
            "atom3, 3,"
            "atom2, 2,"
            "atom1, 1,"
            "residue1, 1,"
            "empty molecule, 1,") );
}

BOOST_FIXTURE_TEST_CASE( Type_Iterator, ROOT_INIT )
{
    auto atm = root->begin<atom>();

    BOOST_CHECK(atm->name() == "atom1");
    BOOST_CHECK(atm->ordinal() == 1);

    ++atm;
    BOOST_CHECK(atm->name() == "atom2");
    BOOST_CHECK(atm->ordinal() == 2);

    ++atm;
    BOOST_CHECK(atm->name() == "atom3");
    BOOST_CHECK(atm->ordinal() == 3);

    ++atm;
    BOOST_CHECK(atm->name() == "atom4");
    BOOST_CHECK(atm->ordinal() == 4);

    ++atm;
    BOOST_CHECK(atm->name() == "inserted atom1");
    BOOST_CHECK(atm->ordinal() == 1);

    ++atm;
    BOOST_CHECK(atm->name() == "inserted atom2");
    BOOST_CHECK(atm->ordinal() == 2);

    ++atm;
    BOOST_CHECK(atm->name() == "atom5");
    BOOST_CHECK(atm->ordinal() == 5);

    ++atm;
    BOOST_CHECK(atm->name() == "atom6");
    BOOST_CHECK(atm->ordinal() == 6);

    ++atm;
    BOOST_CHECK(atm->name() == "atom7");
    BOOST_CHECK(atm->ordinal() == 7);

    ++atm;
    BOOST_CHECK(atm->name() == "atom8");
    BOOST_CHECK(atm->ordinal() == 8);

    ++atm;
    BOOST_CHECK(atm->name() == "atom9");
    BOOST_CHECK(atm->ordinal() == 9);

    ++atm;
    BOOST_CHECK(atm->name() == "inserted atom3");
    BOOST_CHECK(atm->ordinal() == 3);

    ++atm;
    BOOST_CHECK(atm->name() == "inserted atom4");
    BOOST_CHECK(atm->ordinal() == 4);

    auto mol = root->begin<molecule>();
    BOOST_CHECK(mol->name() == "empty molecule");
    BOOST_CHECK(mol->ordinal() == 1);

    ++mol;
    BOOST_CHECK(mol->name() == "residue1");
    BOOST_CHECK(mol->ordinal() == 1);

    ++mol;
    BOOST_CHECK(mol->name() == "residue2");
    BOOST_CHECK(mol->ordinal() == 2);

    ++mol;
    BOOST_CHECK(mol->name() == "chain1");
    BOOST_CHECK(mol->ordinal() == 1);

    ++mol;
    BOOST_CHECK(mol->name() == "residue4");
    BOOST_CHECK(mol->ordinal() == 4);
}

BOOST_FIXTURE_TEST_CASE( Type_Iterator_Copy, ROOT_INIT )
{
    output_test_stream output;
    std::vector<atom*> atoms;

    atoms.reserve(13);
    std::copy(  root->begin<atom>(),
                root->end<atom>(),
                back_inserter(atoms));
    BOOST_CHECK( 13 == atoms.size() );

    for (auto atm : atoms)
        output << atm << ',';
    BOOST_CHECK(
        output.is_equal(
        "atom1, 1,"
        "atom2, 2,"
        "atom3, 3,"
        "atom4, 4,"
        "inserted atom1, 1,"
        "inserted atom2, 2,"
        "atom5, 5,"
        "atom6, 6,"
        "atom7, 7,"
        "atom8, 8,"
        "atom9, 9,"
        "inserted atom3, 3,"
        "inserted atom4, 4," ) );

    std::vector<molecule*> mols;
    mols.reserve(5);
    std::copy(  root->begin<molecule>(),
                root->end<molecule>(),
                back_inserter(mols));
    BOOST_CHECK( 5 == mols.size() );

    for (auto mol : mols)
        output << mol << ',';
    BOOST_CHECK(
        output.is_equal(
        "empty molecule, 1,"
        "residue1, 1,"
        "residue2, 2,"
        "chain1, 1,"
        "residue4, 4," ) );
}

BOOST_FIXTURE_TEST_CASE( Type_Iterator_Boost_Range, ROOT_INIT )
{
    output_test_stream output;
    std::vector<atom*> atoms;
    atoms.reserve(13);

    boost::copy(root->range<atom>(), back_inserter(atoms));
    BOOST_CHECK( 13 == boost::size(atoms) );

    boost::copy(atoms
                | boost::adaptors::reversed,
                std::ostream_iterator<atom*>(output, ",") );
    BOOST_CHECK(
        output.is_equal(
        "inserted atom4, 4,"
        "inserted atom3, 3,"
        "atom9, 9,"
        "atom8, 8,"
        "atom7, 7,"
        "atom6, 6,"
        "atom5, 5,"
        "inserted atom2, 2,"
        "inserted atom1, 1,"
        "atom4, 4,"
        "atom3, 3,"
        "atom2, 2,"
        "atom1, 1," ) );

    // lambda support...
    boost::copy(root->range<atom>()
//                | boost::adaptors::filtered(is_even()),
                | boost::adaptors::filtered(
                [](const atom* atm) { return atm->ordinal() % 2 == 0; }),
                std::ostream_iterator<atom*>(output, ",") );
    BOOST_CHECK( output.is_equal(
            "atom2, 2,"
            "atom4, 4,"
            "inserted atom2, 2,"
            "atom6, 6,"
            "atom8, 8,"
            "inserted atom4, 4,") );

    std::vector<molecule*> mols;
    mols.reserve(5);
    boost::copy(root->range<molecule>(), back_inserter(mols));
    BOOST_CHECK( 5 == mols.size() );

    boost::copy(mols | boost::adaptors::reversed,
                std::ostream_iterator<molecule*>(output, ",") );
    BOOST_CHECK(
        output.is_equal(
        "residue4, 4,"
        "chain1, 1,"
        "residue2, 2,"
        "residue1, 1,"
        "empty molecule, 1,") );

    for (auto mol : root->range<molecule>()
                  | boost::adaptors::uniqued)
        output << mol << ',';
    BOOST_CHECK(
        output.is_equal(
        "empty molecule, 1,"
        "residue1, 1,"
        "residue2, 2,"
        "chain1, 1,"
        "residue4, 4,") );
}

BOOST_AUTO_TEST_SUITE_END() // H_Model

BOOST_AUTO_TEST_SUITE_END() // Maral
