// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_BOOTSTRAPS_PDB_HPP
#define MARAL_BOOTSTRAPS_PDB_HPP

// component classes
#include <maral/policies/b_factor.hpp>
#include <maral/policies/chainid.hpp>
#include <maral/policies/formal_charge.hpp>
#include <maral/policies/icode.hpp>
#include <maral/policies/named.hpp>
#include <maral/policies/occupancy.hpp>
#include <maral/policies/ordered.hpp>
#include <maral/policies/position.hpp>

// data model
#include <maral/hierarchical.hpp>

// host classes
#include <maral/root.hpp>
#include <maral/model.hpp>
#include <maral/molecule.hpp>
#include <maral/submolecule.hpp>
#include <maral/atom.hpp>

// file format classes
#include <maral/ioformats/tree.hpp>
#include <maral/ioformats/pdb.hpp>

namespace maral { namespace bootstrap { namespace pdb {

typedef root_node
<
    data_model::hierarchical
>   root;

typedef model_node
<
    data_model::hierarchical
,   component::named<std::string>
>   model;

typedef molecule_node
<
    data_model::hierarchical
,   component::named<std::string>
,   component::chainid<char>
>   chain;

typedef submolecule_node
<
    data_model::hierarchical
,   component::named<std::string>
,   component::ordered<unsigned>
,   component::icode<char>
>   residue;

typedef atom_node
<
    data_model::hierarchical
,   component::named<std::string>
,   component::position<mtl::point3f>
,   component::occupancy<float>
,   component::b_factor<float>
,   component::formal_charge<char>
>   atom;

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

// convenient enumeration for the file format
// selection, e.g. format(tree) rather than format(1)
enum { pdb, tree };

}}  // namespace booststrap::pdb


template<> struct format_traits<bootstrap::pdb::root>
    {   typedef bootstrap::pdb::format type; };

template<> struct format_traits<bootstrap::pdb::model>
    {   typedef bootstrap::pdb::format type; };

template<> struct format_traits<bootstrap::pdb::chain>
    {   typedef bootstrap::pdb::format type; };

template<> struct format_traits<bootstrap::pdb::residue>
    {   typedef bootstrap::pdb::format type; };

template<> struct format_traits<bootstrap::pdb::atom>
    {   typedef bootstrap::pdb::format type; };

}   // namespace maral

#endif    // MARAL_BOOTSTRAPS_PDB_HPP
