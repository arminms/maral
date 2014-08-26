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
/// \file maral/ioformats/tree.hpp
/// \brief Include file for the tree i/o format.
///
/// \b maral/ioformats/tree.hpp is the header file for the tree input/output
/// format.

#ifndef MARAL_IOFORMATS_TREE_HPP
#define MARAL_IOFORMATS_TREE_HPP

////////////////////////////////////////////////////////////////////////////////
// Includes

#include <type_traits>

#ifndef MARAL_HAS_MEMBER_HPP
#include <maral/has_member.hpp>
#endif // MARAL_HAS_MEMBER_HPP

namespace maral {

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt
,   class Md
,   class Mo
,   class Sm
,   class At
>
    class tree_format
:   public Base<Rt,Md,Mo,Sm,At>
{
public:
    tree_format()
    :   Base<Rt,Md,Mo,Sm,At>()
    {}

private:
    virtual void do_print_root(std::ostream& out, const Rt* rt) const;
    //virtual void do_print_model(std::ostream& out, const Md* md) const;
    //virtual void do_print_mol(std::ostream& out, const Mo* mo) const;
    //virtual void do_print_submol(std::ostream& out, const Sm* sm) const;
    //virtual void do_print_atom(std::ostream& out, const At* at) const;

    void print_root_name(std::ostream& out, const Rt* rt, std::true_type) const;
    void print_root_order(std::ostream& out, const Rt* rt, std::true_type) const;
    void print_root_pos(std::ostream& out, const Rt* rt, std::true_type) const;
    void print_root_name(std::ostream& out, const Rt* rt, std::false_type) const
    {   out << "ROOT";  }
    void print_root_order(std::ostream& out, const Rt* rt, std::false_type) const
    {}
    void print_root_pos(std::ostream& out, const Rt* rt, std::false_type) const
    {}
};

////////////////////////////////////////////////////////////////////////////////
// Implementation

#include <maral/ioformats/tree.ipp>

}    // namespace maral

#endif // MARAL_IOFORMATS_TREE_HPP
