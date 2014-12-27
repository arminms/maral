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

// header(s) for required components
#include <maral/components/b_factor.hpp>
#include <maral/components/chainid.hpp>
#include <maral/components/coordinates.hpp>
#include <maral/components/formal_charge.hpp>
#include <maral/components/icode.hpp>
#include <maral/components/linked_position.hpp>
#include <maral/components/name.hpp>
#include <maral/components/occupancy.hpp>
#include <maral/components/order.hpp>

// headers for host classes
#include <maral/root.hpp>
#include <maral/model.hpp>
#include <maral/molecule.hpp>
#include <maral/submolecule.hpp>
#include <maral/atom.hpp>

// header(s) for required file formats
#include <maral/ioformats/pdb.hpp>

namespace maral { namespace bootstrap { namespace pdb_multimodel {

// seeding the host classes with the
// data model and required components
typedef root_host
<
    data_model::hierarchical
,   component::coordinates<mtl::point3f>
>   root;

typedef model_host
<
    data_model::hierarchical
,   component::name<std::string>
>   model;

typedef molecule_host
<
    data_model::hierarchical
,   component::name<std::string>
,   component::chainid<char>
>   chain;

typedef submolecule_host
<
    data_model::hierarchical
,   component::name<std::string>
,   component::order<unsigned>
,   component::icode<char>
>   residue;

typedef atom_host
<
    data_model::hierarchical
,   component::name<std::string>
,   component::linked_position<mtl::point3f, component::coordinates>
,   component::occupancy<float>
,   component::b_factor<float>
,   component::formal_charge<char>
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
>   format;

}}  // namespace booststrap::pdb_multimodel

// finally defining the type traits required for iostreams
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
