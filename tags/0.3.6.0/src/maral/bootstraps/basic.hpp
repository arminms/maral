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

namespace maral { namespace bootstrap { namespace basic {

typedef root_node
<
    data_model::hierarchical
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
>   molecule;

typedef submolecule_node
<
    data_model::hierarchical
,   policy::named<std::string>
,   policy::ordered<unsigned>
>   residue;

typedef atom_node
<
    data_model::hierarchical
,   policy::named<std::string>
,   policy::ordered<unsigned>
,   policy::position<mtl::point3f>
>   atom;

typedef ioformat
<
    root
,   model
,   molecule
,   residue
,   atom
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
