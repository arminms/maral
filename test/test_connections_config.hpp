// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

// due to inclusion of <windows.h> by header only boost::test, we need
// the following define to prevent problem with std::numeric_limits
#if defined(_MSC_VER)
#   define NOMINMAX
#endif  //_MSC_VER

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>

#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/uniqued.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/count_if.hpp>
#include <boost/range/algorithm/find.hpp>
#include <boost/range/algorithm/for_each.hpp>

#include <maral/components/atomic_number.hpp>
#include <maral/components/b_factor.hpp>
#include <maral/components/chainid.hpp>
#include <maral/components/connections.hpp>
#include <maral/components/covalent_radius.hpp>
#include <maral/components/formal_charge.hpp>
#include <maral/components/icode.hpp>
#include <maral/components/name.hpp>
#include <maral/components/occupancy.hpp>
#include <maral/components/order.hpp>
#include <maral/components/position.hpp>

#include <maral/root.hpp>
#include <maral/model.hpp>
#include <maral/molecule.hpp>
#include <maral/submolecule.hpp>
#include <maral/atom.hpp>
#include <maral/bond.hpp>

#include <maral/ioformats/pdb.hpp>
#include <maral/ioformats/tree.hpp>

#include <maral/algorithms/connect.hpp>

namespace maral {

typedef root_host
<
    datamodel::hierarchical
>   root;

typedef model_host
<
    datamodel::hierarchical
,   component::name<>
>   model;

typedef molecule_host
<
    datamodel::hierarchical
,   component::name<>
,   component::chainid<>
>   chain;

typedef submolecule_host
<
    datamodel::hierarchical
,   component::name<>
,   component::order<>
,   component::icode<>
>   residue;

typedef atom_host
<
    datamodel::hierarchical
,   component::name<>
,   component::order<>
,   component::position<>
,   component::occupancy<>
,   component::b_factor<>
,   component::formal_charge<>
,   component::atomic_number<>
,   component::covalent_radius<>
,   component::connections<hierarchical>
>   atom;

typedef bond_host
<
    atom
,   datamodel::hierarchical
,   component::connections<hierarchical>
>   bond;

typedef ioformat
<
    root
,   model
,   chain
,   residue
,   atom
,   pdb_format
,   tree_format
>   format;

enum { pdb, tree };

template<> struct format_traits<root>
    {   typedef format type; };

template<> struct format_traits<model>
    {   typedef format type; };

template<> struct format_traits<chain>
    {   typedef format type; };

template<> struct format_traits<residue>
    {   typedef format type; };

template<> struct format_traits<atom>
    {   typedef format type; };

}   // namespace maral
