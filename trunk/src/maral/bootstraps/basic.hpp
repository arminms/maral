// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_BOOTSTRAPS_BASIC_HPP
#define MARAL_BOOTSTRAPS_BASIC_HPP

// component classes
#include <maral/policies/chainid.hpp>
#include <maral/policies/named.hpp>
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

namespace maral { namespace bootstrap { namespace basic {

typedef root_node
<
    data_model::hierarchical
,   component::named<std::string>
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
>   molecule;

typedef submolecule_node
<
    data_model::hierarchical
,   component::named<std::string>
,   component::ordered<unsigned>
>   residue;

typedef atom_node
<
    data_model::hierarchical
,   component::named<std::string>
,   component::ordered<unsigned>
,   component::position<mtl::point3f>
>   atom;

typedef ioformat
<
    root
,   model
,   molecule
,   residue
,   atom
,   tree_format
>   format;

}}  // namespace booststrap::basic

template<> struct format_traits<bootstrap::basic::root>
    {   typedef bootstrap::basic::format type; };

template<> struct format_traits<bootstrap::basic::model>
    {   typedef bootstrap::basic::format type; };

template<> struct format_traits<bootstrap::basic::molecule>
    {   typedef bootstrap::basic::format type; };

template<> struct format_traits<bootstrap::basic::residue>
    {   typedef bootstrap::basic::format type; };

template<> struct format_traits<bootstrap::basic::atom>
    {   typedef bootstrap::basic::format type; };

}   // namespace maral

#endif    // MARAL_BOOTSTRAPS_BASIC_HPP
