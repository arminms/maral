// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014-2015 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_BOND_HPP
#define MARAL_BOND_HPP

#ifndef MARAL_HIERARCHICAL_HPP
#include <maral/hierarchical.hpp>
#endif // MARAL_HIERARCHICAL_HPP

#ifndef MARAL_COMPONENT_HPP
#include <maral/component.hpp>
#endif // MARAL_COMPONENT_HPP

namespace maral {

////////////////////////////////////////////////////////////////////////////////

template
<
    typename AtomType
,   typename ...Components
>
    class  bond_host
:   public Components...
{};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename AtomType
,   typename ...Components
>
    class bond_host
    <
        AtomType
    ,   data_model::hierarchical
    ,   Components...
    >
:   public data_model::leaf_node<data_model::hierarchical>
,   public Components...
{
public:
    typedef bond_host<AtomType, data_model::hierarchical, Components...>
        self_type;

/// \name Construction
//@{
    bond_host(const AtomType* first, const AtomType* second)
    :   first_(first)
    ,   second_(second)
    {
        BOOST_ASSERT_MSG(first_, "null pointer!");
        BOOST_ASSERT_MSG(second_, "null pointer!");
    }
//@}

    const AtomType* first_;
    const AtomType* second_;

private:
    virtual void do_print(std::ostream& out) const
    {}
    //{   format_traits<bond_host>::type::print_bond(out, this);  }

    virtual void do_scan(std::istream& in)
    {}
    //{   format_traits<bond_host>::type::scan_bond(in, this);  }

};

////////////////////////////////////////////////////////////////////////////////

template<typename AtomType, typename ...Components>
std::ostream& operator<< (
    std::ostream& out
,   const entity<bond_host<AtomType, data_model::hierarchical, Components...>>&
        bond)
{
    BOOST_ASSERT_MSG(bond.get() , "null bond!");
    bond->print(out);
    return out;
}

////////////////////////////////////////////////////////////////////////////////

template<typename AtomType, typename ...Components>
std::istream& operator>> (
    std::istream& in
,   entity<bond_host<AtomType, data_model::hierarchical, Components...>>& bond)
{
    BOOST_ASSERT_MSG(bond.get() , "null bond!");
    bond->scan(in);
    return in;
}

}    // namespace maral

#endif    // MARAL_BOND_HPP
