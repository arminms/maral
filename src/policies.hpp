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

namespace maral {

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

namespace policies {

////////////////////////////////////////////////////////////////////////////////

template <typename Type>
    class named
{
public:
/// \name Construction
//@{
    named(const Type& name)
    :   name_(name) {}
//@}

/// \name Attributes
//@{
    Type name() const
    {   return name_;   }

    void set_name(const Type& name)
    {   name_ = name;   }
//@}

// Implementation
protected:
    Type name_;
};

////////////////////////////////////////////////////////////////////////////////

template <typename Type>
    class ordered
{
public:
/// \name Construction
//@{
    ordered(Type ordinal)
    : ordinal_(ordinal) {}
//@}

/// \name Attributes
//@{
    Type ordinal() const
    {   return ordinal_;    }

    void set_ordinal(Type ordinal)
    {   ordinal_ = ordinal; }
//@}

// Implementation
protected:
    Type ordinal_;
};

////////////////////////////////////////////////////////////////////////////////

template <typename Type>
    class position
{
    static_assert(
        type_traits<Type>::extent::den > 1,
        "need a fixed-size vector type :(");

public:
/// \name Construction
//@{
    position()
    {   pos_.zero();    }

    position(const Type& pos)
    :   pos_(pos)
    {}
//@}

/// \name Attributes
//@{
    Type& center()
    {   return pos_;    }

    Type get_center() const
    {   return pos_;    }

    void set_center(const Type& pos)
    {   pos_ = pos; }
//@}

/// \name Operators
//@{
    typename type_traits<Type>::reference operator[]
        (const unsigned idx)
    {   return pos_[idx];   }
//    typename type_traits<Type>::value_type operator[]
//        (const unsigned idx) const;
//    {   return pos_[idx]; }
//@}

// Implementation
protected:
    Type pos_;
};

}}    // namespaces

#endif    // MARAL_POLICIES_HPP_INCLUDED_

