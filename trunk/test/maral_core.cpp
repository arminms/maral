// $Id$
//------------------------------------------------------------------------------

#include <iostream>

#include <boost/test/unit_test.hpp>
//#include <boost/test/output_test_stream.hpp>
//#include <boost/mpl/list.hpp>

#include <core.hpp>

//using boost::test_tools::output_test_stream;
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

BOOST_AUTO_TEST_CASE( Dynamic_Casts )
{
    node<molecule> root = make_node<molecule>("root");
    BOOST_CHECK(dynamic_cast<abstract_node*>(root.get()));
    BOOST_CHECK(dynamic_cast<composite_node*>(root.get()));
    BOOST_CHECK(dynamic_cast<named_node*>(root.get()));
    BOOST_CHECK(dynamic_cast<child_node*>(root.get()) == nullptr);
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

BOOST_FIXTURE_TEST_CASE( Core_Node_Iterator, ROOT_INIT )
{
    std::vector<abstract_node*> nodes;
    std::copy(root->begin(),
            root->end(),
            back_inserter(nodes));
    for (auto node : nodes)
        std::cout << node << std::endl;
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
