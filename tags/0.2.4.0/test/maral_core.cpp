// $Id$
//------------------------------------------------------------------------------

#include <iostream>

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
//#include <boost/mpl/list.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <core.hpp>

using boost::test_tools::output_test_stream;
using namespace maral::core;

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

BOOST_AUTO_TEST_SUITE( Core )

BOOST_AUTO_TEST_CASE( Size_Test )
{
    node<atom> atm(new atom("atom1"));
    BOOST_CHECK(sizeof(abstract_node::node_type) == sizeof(atm));
    BOOST_CHECK(sizeof(abstract_node::hierarchy_type) == (2 * sizeof(atm)));
    BOOST_CHECK(sizeof(abstract_node) == sizeof atm);
    BOOST_CHECK(sizeof(composite_node<abstract_node>) == (4 * sizeof(atm)));
    BOOST_CHECK(sizeof(leaf_node<abstract_node>) == (2 * sizeof(atm)));
    BOOST_CHECK(sizeof(root_node<abstract_node>) == (4 * sizeof(atm)));
    BOOST_CHECK(sizeof(has_name) == sizeof(std::string));
    BOOST_CHECK(sizeof(ordered) == sizeof(unsigned));
    BOOST_CHECK(sizeof(atom) == (4 * sizeof(atm)));
    BOOST_CHECK(sizeof(molecule) == (6 * sizeof(atm)));
}

BOOST_AUTO_TEST_CASE( Dynamic_Casts )
{
    node<molecule> mol = make_node<molecule>("Test");
    BOOST_CHECK(dynamic_cast<abstract_node*>(mol.get()));
    BOOST_CHECK(dynamic_cast<composite_node<abstract_node>*>(mol.get()));
    BOOST_CHECK(dynamic_cast<has_name*>(mol.get()));
    BOOST_CHECK(dynamic_cast<leaf_node<abstract_node>*>(mol.get()) == nullptr);
    BOOST_CHECK(dynamic_cast<root_node<abstract_node>*>(mol.get()) == nullptr);
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
    std::vector<abstract_node*> nodes;
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
    std::vector<abstract_node*> nodes;
//    boost::copy(*root, back_inserter(nodes));
    boost::copy(root->range(), back_inserter(nodes));
    BOOST_CHECK( 18 == boost::size(nodes) );
    boost::copy( nodes | boost::adaptors::reversed,
             std::ostream_iterator<abstract_node*>(output, ",") );
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
                std::ostream_iterator<abstract_node*>(output, ",") );
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
                std::ostream_iterator<abstract_node*>(output, ",") );
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
                std::ostream_iterator<abstract_node*>(output, ",") );
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

//BOOST_AUTO_TEST_CASE( Core_Node_Iterator )
//{
//    BOOST_CHECK(dynamic_cast<abstract_node*>(&(*(root->children()->begin()))));
//    std::cout << "size of node_type: " << sizeof(abstract_node::node_type) << std::endl;
//    std::cout << "size of pointer: " << sizeof test << std::endl;
//    std::cout << "size of node_type: " << sizeof(abstract_node::node_type) << std::endl;
//    std::cout << "size of hierarchy_type: " << sizeof(abstract_node::hierarchy_type) << std::endl;
//    std::cout << "size of abstract_node: " << sizeof(abstract_node) << std::endl;
//    std::cout << "size of composite_node: " << sizeof(composite_node) << std::endl;
//    std::cout << "size of child_node: " << sizeof(child_node) << std::endl;
//    std::cout << "size of named_node: " << sizeof(named_node) << std::endl;
//    std::cout << "size of ordinal_node: " << sizeof(ordinal_node) << std::endl;
//    std::cout << "size of atom: " << sizeof(atom) << std::endl;
//    std::cout << "size of atom2: " << sizeof(atom2) << std::endl;
//    std::cout << "size of molecule: " << sizeof(molecule) << std::endl;

//    std::cout << "size of int: " << sizeof(int) << std::endl;
//    for (auto itr = root->children()->begin();
//        itr != root->children()->end();
//        ++itr)
//    {
//        std::cout << (*itr)->name() << std::endl;
//        BOOST_CHECK(dynamic_cast<abstract_node*>((*itr).get()));
//        BOOST_CHECK(dynamic_cast<child_node*>((*itr).get()));
//
//    }

//    for (auto node : *root->children())
//    {
//        std::cout << node->name() << ", " << node->ordinal() << std::endl;
//        BOOST_CHECK(dynamic_cast<abstract_node*>(node));
//        BOOST_CHECK(dynamic_cast<child_node*>(node));
//    }

//    abstract_node::hierarchy_type newlist;
//    copy(test->children()->begin(),
//         test->children()->end(),
//         back_inserter(newlist));

//    for (auto node : newlist)
//        std::cout << node->name() << ", " << node->ordinal() << std::endl;

    //auto itr = test->children()->begin();
    //boost::ptr_list<abstract_node>::const_iterator itr = test->children()->begin();
    //BOOST_CHECK(itr->children());

//    for (auto pos = root->begin(); pos != root->end(); ++pos)
//    {
//        std::cout << pos->name() << ", " << pos->ordinal()
//                << " ," << (*(*pos))[5] << std::endl;
//         *pos = new molecule("test"); // WRONG!
//         (*pos)->set_name("test"); // OK
//    }

//    for (const auto& node : *root)
//    {
//        std::cout << node << ", " << (*node)[5] <<std::endl;
//        node->set_name("test");
//    }

//    for (molecule::const_type_iterator<atom> pos(root.get());
//        pos != molecule::const_type_iterator<atom>(root.get(), true);
//        ++pos)
//        std::cout << pos->name() << ", " << pos->ordinal() << std::endl;

//    for (auto pos = root->begin<atom>(); pos != root->end<atom>(); ++pos)
//        std::cout << pos->name() << ", " << pos->ordinal() << std::endl;

//    for (auto pos = root->begin<atom>(); pos != root->end<atom>(); ++pos)
//        std::cout << *pos << std::endl;
//

//    for (auto pos = root->begin<atom>(has_ordinal<atom>(3));
//        pos != root->end<atom>(has_ordinal<atom>(3));
//        ++pos)
//        std::cout << *pos << std::endl;

//    for (auto pos = root->begin<atom>([] (const atom* atom) -> bool { return atom->ordinal() == 3; });
//        pos != root->end<atom>([] (const atom* atom) -> bool { return atom->ordinal() == 3; });
//        ++pos)
//        std::cout << *pos << std::endl;

//    std::cout << std::endl;
//    for (auto pos = root->begin<composite_node>(); pos != root->end<composite_node>(); ++pos)
//        std::cout << pos->name() << ", " << pos->ordinal() << std::endl;
//
//    std::cout << std::endl;
//    for (auto pos = root->begin<child_node>(); pos != root->end<child_node>(); ++pos)
//        std::cout << pos->name() << ", " << pos->ordinal() << std::endl;

//    unsigned count = 0;
//    for (auto pos = root->begin<molecule>(); pos != root->end<molecule>(); ++pos)
//    {
//        std::cout << pos->name() << ", " << pos->ordinal() << std::endl;
//        pos->add(std::move(make_node<atom>("on the fly atom", ++count)));
//    }
//
//    std::cout << std::endl;
//    for (auto node : *root)
//        std::cout << node << std::endl;

//    auto pos2 = itr;
//
//    for (unsigned i=0; i < 7; ++pos2, ++i)
//        std::cout << pos2->name() << ", " << pos2->ordinal() << std::endl;

//    molecule::const_iterator itr(root.get());
//    for (; molecule::const_iterator(); ++itr)
//        std::cout << (*itr)->name() << ", " << (*itr)->ordinal() << std::endl;

//    std::copy(
//            root->begin()
//          , root->end()
//          , std::ostream_iterator<abstract_node*>(std::cout, "\n")
//    );

//    std::vector<abstract_node*> nodes;
//    nodes.reserve(20);
//    std::copy(root->begin(),
//            root->end(),
//            back_inserter(nodes));
//    for (auto node : nodes)
//        std::cout << node << std::endl;

//    std::vector<atom*> atoms;
//    atoms.reserve(20);
//    std::copy(root->begin<atom>(),
//            root->end<atom>(),
//            back_inserter(atoms));
//    for (auto atom : atoms)
//        std::cout << atom << std::endl;

//    std::vector<atom*> atoms(root->begin<atom>(), root->end<atom>());
//    for (auto atom : atoms)
//        std::cout << atom << std::endl;

//    std::vector<atom*> atoms(
//          root->begin<atom>(has_ordinal<atom>(3))
//        , root->end<atom>(has_ordinal<atom>(3)));
//    for (auto atom : atoms)
//        std::cout << atom << std::endl;

//    std::vector<atom*> atoms;
//    atoms.reserve(20);
//    for (auto pos = root->begin<atom>(); pos != root->end<atom>(); ++pos)
//        atoms.push_back(*pos);
//    for (auto pos = atoms.cbegin() ; pos != atoms.cend(); ++pos)
//        std::cout << *pos << std::endl;

//    std::vector<abstract_node*> nodes;
//    std::copy(root->begin(),
//            root->end(),
//            back_inserter(nodes));
//    for (auto node : nodes)
//        std::cout << node << std::endl;

//    std::vector<abstract_node*> nodes;
//    boost::copy(*root, back_inserter(nodes));
//    boost::copy( nodes | boost::adaptors::reversed,
//             std::ostream_iterator<abstract_node*>(std::cout, "\n") );
//    std::cout << boost::count(nodes);
//}

BOOST_AUTO_TEST_SUITE_END() // Core

BOOST_AUTO_TEST_SUITE_END() // Maral
