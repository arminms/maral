// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#include "test_connections_config.hpp"

using boost::test_tools::output_test_stream;
namespace butrc = boost::unit_test::runtime_config;

using namespace maral;

#define PATTERNS_FOLDER "patterns/"

struct CRN_INIT
{
    CRN_INIT()
    {
        using mtl::point3f;
        rt = make<root>();
        auto crambin = rt->add(std::move(make<model>("1CRN")));
        auto chn = crambin->add(std::move(make<chain>("A")));
        auto pro = chn->add(std::move(make<residue>("PRO", 5)));

        auto pro_n = pro->add(std::move(make<atom>
            ( "N", 27, point3f(9.561f, 9.108f, 13.563f))));
        auto pro_ca = pro->add(std::move(make<atom>
            ("CA", 28, point3f(9.448f, 9.034f, 15.012f))));
        auto pro_c = pro->add(std::move(make<atom>
            ( "C", 29, point3f(9.288f, 7.670f, 15.606f))));
        auto pro_o = pro->add(std::move(make<atom>
            ( "O", 30, point3f(9.490f, 7.519f, 16.819f))));
        auto pro_cb = pro->add(std::move(make<atom>
            ("CB", 31, point3f(8.230f, 9.957f, 15.345f))));
        auto pro_cg = pro->add(std::move(make<atom>
            ("CG", 32, point3f(7.338f, 9.786f, 14.114f))));
        auto pro_cd = pro->add(std::move(make<atom>
            ("CD", 33, point3f(8.366f, 9.804f, 12.958f))));

        // adding proline's bonds manually
        make<bond>(pro_n, pro_ca);  //  N-CA
        make<bond>(pro_ca, pro_c);  // CA-C
        make<bond>(pro_c, pro_o);   //  C-O
        make<bond>(pro_ca, pro_cb); // CA-CB
        make<bond>(pro_cg, pro_cb); // CG-CB
        make<bond>(pro_n, pro_cd);  //  N-CD
        make<bond>(pro_cd, pro_cg); // CD-CG

        auto ser = chn->add(std::move(make<residue>("SER", 6)));
        ser->add(std::move(make<atom>
            ( "N", 34, point3f(8.875f, 6.686f, 14.796f))));
        ser->add(std::move(make<atom>
            ("CA", 35, point3f(8.673f, 5.314f, 15.279f))));
        ser->add(std::move(make<atom>
            ( "C", 36, point3f(8.753f, 4.376f, 14.083f))));
        ser->add(std::move(make<atom>
            ( "O", 37, point3f(8.726f, 4.858f, 12.923f))));
        ser->add(std::move(make<atom>
            ("CB", 38, point3f(7.340f, 5.121f, 15.996f))));
        ser->add(std::move(make<atom>
            ("OG", 39, point3f(6.274f, 5.220f, 15.031f))));

        // adding serine's bonds by connect algorithm
        connect<bond>(ser->range<atom>());
    }

    entity<root> rt;
};

BOOST_FIXTURE_TEST_CASE( Bond_Count, CRN_INIT )
{
    BOOST_CHECK( 12 == boost::distance(rt->range<bond>()) );

    auto pro_c = rt->begin<atom>();
    std::advance(pro_c, 2);
    auto ser_n = rt->rbegin<atom>();
    std::advance(ser_n, 5);
    BOOST_CHECK( !pro_c->is_connected_to(*ser_n) );
    BOOST_CHECK( boost::find(pro_c->neighbors(), *ser_n)
             ==  boost::end(pro_c->neighbors()) );
}

BOOST_FIXTURE_TEST_CASE( Adding_Missing_Bond, CRN_INIT )
{
    connect<bond>(rt->range<atom>());
    BOOST_CHECK( 13 == boost::distance(rt->range<bond>()) );

    auto pro_c = rt->begin<atom>();
    std::advance(pro_c, 2);
    auto ser_n = rt->rbegin<atom>();
    std::advance(ser_n, 5);
    BOOST_CHECK( pro_c->is_connected_to(*ser_n) );
    BOOST_CHECK( boost::find(pro_c->neighbors(), *ser_n)
             !=  boost::end(pro_c->neighbors()) );
}

//BOOST_AUTO_TEST_CASE( Size_Test )
//{
//    for (auto bnd : rt->range<bond>())
//        std::cout << bnd->src()->name() << '-'
//                  << bnd->dst()->name()
//                  << std::endl;
//}

