// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_BOOTSTRAPS_PDB_MULTIMODEL_HPP
#define MARAL_BOOTSTRAPS_PDB_MULTIMODEL_HPP

// component classes
#include <maral/policies/b_factor.hpp>
#include <maral/policies/chainid.hpp>
#include <maral/policies/coordinates.hpp>
#include <maral/policies/formal_charge.hpp>
#include <maral/policies/icode.hpp>
#include <maral/policies/linked_position.hpp>
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
#include <maral/ioformats/pdb.hpp>

namespace maral { namespace bootstrap { namespace pdb_multimodel {

typedef root_node
<
    data_model::hierarchical
,   policy::coordinates<mtl::point3f>
>   root;

typedef model_node
<
    data_model::hierarchical
,   policy::named<std::string>
>   model;

typedef molecule_node
<
    data_model::hierarchical
,   policy::named<std::string>
,   policy::chainid<char>
>   chain;

typedef submolecule_node
<
    data_model::hierarchical
,   policy::named<std::string>
,   policy::ordered<unsigned>
,   policy::icode<char>
>   residue;

typedef atom_node
<
    data_model::hierarchical
,   policy::named<std::string>
,   policy::linked_position<mtl::point3f, policy::coordinates>
,   policy::occupancy<float>
,   policy::b_factor<float>
,   policy::formal_charge<char>
>   atom;

typedef ioformat
<
    root
,   model
,   chain
,   residue
,   atom
,   pdb_format
>   format;

}}  // namespace booststrap::pdb_multimodel

template<> struct format_traits<bootstrap::pdb_multimodel::root>
    {   typedef bootstrap::pdb_multimodel::format type; };

template<> struct format_traits<bootstrap::pdb_multimodel::model>
    {   typedef bootstrap::pdb_multimodel::format type; };

template<> struct format_traits<bootstrap::pdb_multimodel::chain>
    {   typedef bootstrap::pdb_multimodel::format type; };

template<> struct format_traits<bootstrap::pdb_multimodel::residue>
    {   typedef bootstrap::pdb_multimodel::format type; };

template<> struct format_traits<bootstrap::pdb_multimodel::atom>
    {   typedef bootstrap::pdb_multimodel::format type; };

}   // namespace maral

#endif    // MARAL_BOOTSTRAPS_PDB_MULTIMODEL_HPP
