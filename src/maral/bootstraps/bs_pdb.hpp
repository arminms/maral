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

// header(s) for required components
#include <maral/components/atomic_number.hpp>
#include <maral/components/b_factor.hpp>
#include <maral/components/chainid.hpp>
#include <maral/components/covalent_radius.hpp>
#include <maral/components/formal_charge.hpp>
#include <maral/components/icode.hpp>
#include <maral/components/name.hpp>
#include <maral/components/occupancy.hpp>
#include <maral/components/order.hpp>
#include <maral/components/position.hpp>

// headers for host classes
#include <maral/root.hpp>
#include <maral/model.hpp>
#include <maral/molecule.hpp>
#include <maral/submolecule.hpp>
#include <maral/atom.hpp>

// header(s) for required file formats
#include <maral/ioformats/tree.hpp>
#include <maral/ioformats/pdb.hpp>

namespace maral { namespace bootstrap { namespace pdb {

// seeding the host classes with the
// data model and required components
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
,   component::position<>
,   component::occupancy<>
,   component::b_factor<>
,   component::formal_charge<>
,   component::atomic_number<>
,   component::covalent_radius<>
>   atom;

// defining format class
typedef ioformat
<
// first types of host classes
    root
,   model
,   chain
,   residue
,   atom
// now required file format(s)
,   pdb_format
,   tree_format
>   format;

// convenient enumeration for the file format
// selection, e.g. format(tree) rather than format(1)
enum { pdb, tree };

}}  // namespace booststrap::pdb

// finally defining the type traits required for iostreams
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
