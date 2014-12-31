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

#ifndef MARAL_POLICIES_HPP
#include <maral/policies.hpp>
#endif // MARAL_POLICIES_HPP

#ifndef MARAL_ROOT_HPP
#include <maral/root.hpp>
#endif // MARAL_ROOT_HPP

#ifndef MARAL_MODEL_HPP
#include <maral/model.hpp>
#endif // MARAL_MODEL_HPP

#ifndef MARAL_MOLECULE_HPP
#include <maral/molecule.hpp>
#endif // MARAL_MOLECULE_HPP

#ifndef MARAL_SUBMOLECULE_HPP
#include <maral/submolecule.hpp>
#endif // MARAL_SUBMOLECULE_HPP

#ifndef MARAL_ATOM_HPP
#include <maral/atom.hpp>
#endif // MARAL_ATOM_HPP

#ifndef MARAL_FORMAT_HPP
#include <maral/format.hpp>
#endif // MARAL_FORMAT_HPP

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