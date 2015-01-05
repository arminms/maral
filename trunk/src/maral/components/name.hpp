// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_COMPONENTS_NAME_HPP
#define MARAL_COMPONENTS_NAME_HPP

namespace maral {

////////////////////////////////////////////////////////////////////////////////
/// \brief Namespace for the different \b component classes defined by \b Maral.
///
/// Namespace for all the component classes defined by \b Maral. A \b component
/// class is used as a variadic template parameter to transmit behavioral and/or
/// structural features to host classes. Combinatorial class design fosters
/// assembling a class with complex behavior out of many little classes (called
/// components), each of which takes care of only one behavioral and/or
/// structural aspect. Because you can mix and match components, you can achieve
/// a combinatorial set of behaviors by using small core of elemenatry
/// components.

namespace component {

////////////////////////////////////////////////////////////////////////////////
/// \brief Structural component for assigning name to nodes.
///
/// \param CharT Type of the character to be used the name string (e.g. char,
///  char16_t,char32_t, wchar_t, ...).
/// \remarks
/// name is a structural component class that allows assigning a name to a node,
/// so it can be accessed or changed later.

template <typename CharT = char>
    class name_component
{
public:
/// \name Construction
//@{
    name_component(const std::basic_string<CharT>& name = "")
    :   name_(name)
    {}
//@}

/// \name Attributes
//@{
    std::basic_string<CharT> name() const
    {   return name_;   }

    void name(const std::basic_string<CharT>& name)
    {   name_ = name;   }
//@}

// Implementation
private:
    std::basic_string<CharT> name_;
};

template <typename CharT = char>
using name = name_component<CharT>;

}}    // maral::component

#endif    // MARAL_COMPONENTS_NAME_HPP
