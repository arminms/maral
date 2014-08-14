////////////////////////////////////////////////////////////////////////////////
//
//                                  MARAL
//            (Molecular Architectural Record & Assembly Library)
//
//        Copyright (C) by Armin Madadkar-Sobhani arminms@gmail.com
//
//                 See the LICENSE file for terms of use
//
//------------------------------------------------------------------------------
// $Id$
//------------------------------------------------------------------------------
/// \file policies/named.hpp
/// \brief Include file for named policy class.
///
/// \b named.hpp is the include file that defines \b named structural policy
/// class.

#ifndef MARAL_POLICIES_NAMED_HPP
#define MARAL_POLICIES_NAMED_HPP

namespace maral {

////////////////////////////////////////////////////////////////////////////////
/// \brief Namespace for the different \b policy classes defined by \b Maral.
///
/// Namespace for all the policy-based classes defined by \b Maral. A \b policy
/// class is used as a template parameter to transmit behavioral and/or
/// structural features to nodes. Policy-based class design fosters assembling
/// a class with complex behavior out of many little classes (called policies),
/// each of which takes care of only one behavioral and/or structural aspect.
/// Because you can mix and match policies, you can achieve a combinatorial set
/// of behaviors by using small core of elemenatry components.

namespace policies {

////////////////////////////////////////////////////////////////////////////////
/// \brief Structural policy for assigning name to nodes.
///
/// \param T Type of the string to be used as name (e.g. std::string,
/// std::wstring, ...).
/// \remarks
/// named is a structural policy class that allows assigning a name to a node,
/// so it can be accessed or changed later.

template <typename T>
    class named
{
public:
/// \name Construction
//@{
    named(const T& name)
    :   name_(name)
    {}
//@}

/// \name Attributes
//@{
    T name() const
    {   return name_;   }

    void name(const T& name)
    {   name_ = name;   }
//@}

// Implementation
protected:
    T name_;
};

}}    // namespaces

#endif    // MARAL_POLICIES_NAMED_HPP

