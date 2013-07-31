// $Id$
//------------------------------------------------------------------------------

#include <boost/test/unit_test.hpp>
//#include <boost/test/output_test_stream.hpp>
//#include <boost/mpl/list.hpp>

#include <core.hpp>

//using boost::test_tools::output_test_stream;
using namespace magma::core;

//typedef boost::mpl::list<int,float,double,long double> test_types;
//typedef boost::mpl::list<float,double,long double> float_types;

BOOST_AUTO_TEST_SUITE( Magma )

BOOST_AUTO_TEST_SUITE( Node_Iterator )

BOOST_AUTO_TEST_CASE( Core_Node_Iterator )
{
//    BOOST_CHECK_THROW( expr, my_exception );
//    BOOST_CHECK_NO_THROW( expr, throw my_exception() );

//    std::unique_ptr<molecule> root(new molecule("root"));
//    std::unique_ptr<molecule> root = make_node<molecule>("root");
    node<molecule> root = make_node<molecule>("root");
    BOOST_CHECK(dynamic_cast<abstract_node*>(root.get()));
    BOOST_CHECK(dynamic_cast<composite_node*>(root.get()));
    BOOST_CHECK(dynamic_cast<named_node*>(root.get()));
    BOOST_CHECK(dynamic_cast<child_node*>(root.get()) == nullptr);

    root->add(std::move(make_node<molecule>("empty molecule", 1)));

    node<molecule> res1 = make_node<molecule>("residue1", 1);

    node<atom> atom1(new atom("atom1"));
    res1->add(std::move(atom1));
    BOOST_CHECK(!atom1);
    node<atom> atom2 = make_node<atom>("atom2", 2);
    res1->add(std::move(atom2));
    BOOST_CHECK(!atom2);
    auto atom3 = make_node<atom>("atom3", 3);
    res1->add(std::move(atom3));
    BOOST_CHECK(!atom3);
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

//    BOOST_CHECK(dynamic_cast<abstract_node*>(&(*(root->children()->cbegin()))));
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
//    for (auto itr = root->children()->cbegin();
//        itr != root->children()->cend();
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
//    copy(test->children()->cbegin(),
//         test->children()->cend(),
//         back_inserter(newlist));

//    for (auto node : newlist)
//        std::cout << node->name() << ", " << node->ordinal() << std::endl;

    //auto itr = test->children()->cbegin();
    //boost::ptr_list<abstract_node>::const_iterator itr = test->children()->cbegin();
    //BOOST_CHECK(itr->children());

//    std::cout << "\niterator test...\n";
    //abstract_node::node_iterator itr(test.get());
//    molecule::const_iterator itr = test->cbegin();
//    molecule::const_iterator itr(root.get());
//
//    std::cout << (*itr)->name() << ", " << (*itr)->ordinal() << std::endl;
//    ++itr;
//    std::cout << (*itr)->name() << ", " << (*itr)->ordinal() << std::endl;
//    ++itr;
//    std::cout << (*itr)->name() << ", " << (*itr)->ordinal() << std::endl;
//    ++itr;
//    std::cout << (*itr)->name() << ", " << (*itr)->ordinal() << std::endl;
//    ++itr;
//    std::cout << (*itr)->name() << ", " << (*itr)->ordinal() << std::endl;
//    ++itr;
//    std::cout << (*itr)->name() << ", " << (*itr)->ordinal() << std::endl;
//    ++itr;
//    std::cout << (*itr)->name() << ", " << (*itr)->ordinal() << std::endl;
//    ++itr;
//    std::cout << (*itr)->name() << ", " << (*itr)->ordinal() << std::endl;
//    ++itr;
//    std::cout << (*itr)->name() << ", " << (*itr)->ordinal() << std::endl;
//    ++itr;
//    std::cout << (*itr)->name() << ", " << (*itr)->ordinal() << std::endl;
//    ++itr;
//    std::cout << (*itr)->name() << ", " << (*itr)->ordinal() << std::endl;

//    molecule::const_iterator itr(root.get());
//    for (unsigned i=0; i < 18; ++itr, ++i)
//        std::cout << (*itr)->name() << ", " << (*itr)->ordinal() << std::endl;

//    for (auto itr = root->cbegin(); itr != root->cend(); ++itr)
//    {
//        std::cout << (*itr)->name() << ", " << (*itr)->ordinal() << std::endl;
//        (*itr)->set_name("test");
//    }

    for (auto node : *root)
    {
        std::cout << node << std::endl;
//        node->set_name("test");
    }

//    auto itr2 = itr;
//
//    for (unsigned i=0; i < 7; ++itr2, ++i)
//        std::cout << (*itr2)->name() << ", " << (*itr2)->ordinal() << std::endl;

//    molecule::const_iterator itr(root.get());
//    for (; molecule::const_iterator(); ++itr)
//        std::cout << (*itr)->name() << ", " << (*itr)->ordinal() << std::endl;

    std::copy(
            root->begin()
          , root->end()
          , std::ostream_iterator<abstract_node*>(std::cout, "\n")
    );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
