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

// header(s) for required components
#include <maral/components/chainid.hpp>
#include <maral/components/name.hpp>
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

namespace maral { namespace bootstrap { namespace basic {

// seeding the host classes with the
// data model and required components
typedef root_host
<
    data_model::hierarchical
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
>   molecule;

typedef submolecule_host
<
    data_model::hierarchical
,   component::name<std::string>
,   component::order<unsigned>
>   residue;

typedef atom_host
<
    data_model::hierarchical
,   component::name<std::string>
,   component::order<unsigned>
,   component::position<mtl::point3f>
>   atom;

// defining format class
typedef ioformat
<
// first types of host classes
    root
,   model
,   molecule
,   residue
,   atom
// now required file format(s)
,   tree_format
>   format;

}}  // namespace booststrap::basic

// finally defining the type traits required for iostreams
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
