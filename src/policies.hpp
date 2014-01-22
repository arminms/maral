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
/// \file policies.hpp
/// \brief Include file for \b atom nodes of different \b models.
///
/// \b atom.hpp is the include file that defines \b atom nodes of different \b
/// data \b models (e.g. atom_h_node, atom_r_node, atom_n_node, etc).

#ifndef MARAL_POLICIES_HPP_INCLUDED_
#define MARAL_POLICIES_HPP_INCLUDED_

namespace maral
{

////////////////////////////////////////////////////////////////////////////////
/// \brief Namespace for the different \b policy classes defined by \b Maral.
///
/// Namespace for all the policy-based classes defined by \b Maral. A \b policy
/// class is a template parameter used to transmit behavior. Policy-based class
/// design fosters assembling a class with complex behavior out of many little
/// classes (called policies), each of which takes care of only one behavioral
/// or structural aspect. Because you can mix and match policies, you can
/// achieve a combinatorial set of behaviors by using small core of elemenatry
/// components.

    namespace policies
    {

////////////////////////////////////////////////////////////////////////////////

class has_name
{
public:
/// \name Construction
//@{
    has_name(const std::string& name)
    :   name_(name) {}
//@}

/// \name Attributes
//@{
    std::string name() const
    {   return name_;   }

    void set_name(const std::string& name)
    {   name_ = name;   }
//@}

// Implementation
protected:
    std::string name_;
};

////////////////////////////////////////////////////////////////////////////////

class ordered
{
public:
/// \name Construction
//@{
    ordered(unsigned ordinal)
    : ordinal_(ordinal) {}
//@}

/// \name Attributes
//@{
    unsigned ordinal() const
    {   return ordinal_;    }

    void set_ordinal(unsigned ordinal)
    {   ordinal_ = ordinal; }
//@}

// Implementation
protected:
    unsigned ordinal_;
};

    }    // namespace policies

}    // namespace maral

#endif    // MARAL_POLICIES_HPP_INCLUDED_

