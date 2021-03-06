// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_IOFORMATS_TREE_HPP
#define MARAL_IOFORMATS_TREE_HPP

////////////////////////////////////////////////////////////////////////////////
// Includes

#include <type_traits>

#include <boost/range/algorithm/reverse.hpp>

#ifndef MARAL_COMPONENT_HPP
#include <maral/component.hpp>
#endif // MARAL_COMPONENT_HPP

#ifndef MARAL_FORMAT_HPP
#include <maral/format.hpp>
#endif // MARAL_FORMAT_HPP

#ifndef MARAL_MTL_INSERTERS_HPP
#include <maral/mtl/inserters.hpp>
#endif // MARAL_MTL_INSERTERS_HPP

#ifndef MARAL_IOMANIP_HPP
#include <maral/iomanip.hpp>
#endif // MARAL_IOMANIP_HPP

namespace maral {

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
class tree_format
:   public io_format_base<Rt,Md,Mo,Sm,At>
{
public:
    tree_format()
    :   io_format_base<Rt,Md,Mo,Sm,At>()
    {}

private:
    virtual void do_print_root(std::ostream& out, const Rt* rt);
    virtual void do_print_model(std::ostream& out, const Md* md);
    virtual void do_print_mol(std::ostream& out, const Mo* mo);
    virtual void do_print_submol(std::ostream& out, const Sm* sm);
    virtual void do_print_atom(std::ostream& out, const At* at);

    virtual void do_scan_root(std::istream& in, Rt* rt)     {}
    virtual void do_scan_model(std::istream& in, Md* md)    {}
    virtual void do_scan_mol(std::istream& in, Mo* mo)      {}
    virtual void do_scan_submol(std::istream& in, Sm* sm)   {}
    virtual void do_scan_atom(std::istream& in, At* at)     {}

    void print_root_name(std::ostream& out,
        const Rt* rt, std::true_type) const;
    void print_root_order(std::ostream& out,
        const Rt* rt, std::true_type) const;
    void print_root_pos(std::ostream& out,
        const Rt* rt, std::true_type) const;
    void print_root_name(std::ostream& out,
        const Rt* rt, std::false_type) const    {   out << "ROOT";  }
    void print_root_order(std::ostream& out,
        const Rt* rt, std::false_type) const    {}
    void print_root_pos(std::ostream& out,
        const Rt* rt, std::false_type) const    {}

    void print_model_name(std::ostream& out,
        const Md* md, std::true_type) const;
    void print_model_order(std::ostream& out,
        const Md* md, std::true_type) const;
    void print_model_pos(std::ostream& out,
        const Md* md, std::true_type) const;
    void print_model_name(std::ostream& out,
        const Md* md, std::false_type) const    {   out << "MODEL";  }
    void print_model_order(std::ostream& out,
        const Md* md, std::false_type) const    {}
    void print_model_pos(std::ostream& out,
        const Md* md, std::false_type) const    {}

    void print_void_mol_name(std::ostream& out,
        const Mo* mo, std::true_type) const     {   out << "MOL";  }
    void print_mol_name(std::ostream& out,
        const Mo* mo, std::true_type) const;
    void print_mol_chain_id(std::ostream& out,
        const Mo* mo, std::true_type) const;
    void print_mol_order(std::ostream& out,
        const Mo* mo, std::true_type) const;
    void print_mol_pos(std::ostream& out,
        const Mo* mo, std::true_type) const;
    void print_void_mol_name(std::ostream& out,
        const Mo* mo, std::false_type) const    {}
    void print_mol_name(std::ostream& out,
        const Mo* mo, std::false_type) const    {}
    void print_mol_chain_id(std::ostream& out,
        const Mo* mo, std::false_type) const    {}
    void print_mol_order(std::ostream& out,
        const Mo* mo, std::false_type) const    {}
    void print_mol_pos(std::ostream& out,
        const Mo* mo, std::false_type) const    {}

    void print_submol_name(std::ostream& out,
        const Sm* sm, std::true_type) const;
    void print_submol_order(std::ostream& out,
        const Sm* sm, std::true_type) const;
    void print_submol_pos(std::ostream& out,
        const Sm* sm, std::true_type) const;
    void print_submol_name(std::ostream& out,
        const Sm* sm, std::false_type) const    {   out << "SUBMOL";  }
    void print_submol_order(std::ostream& out,
        const Sm* sm, std::false_type) const    {}
    void print_submol_pos(std::ostream& out,
        const Sm* sm, std::false_type) const    {}

    void print_atom_name(std::ostream& out,
        const At* at, std::true_type) const;
    void print_atom_order(std::ostream& out,
        const At* at, std::true_type) const;
    void print_atom_pos(std::ostream& out,
        const At* at, std::true_type) const;
    void print_atom_name(std::ostream& out,
        const At* at, std::false_type) const    {   out << "ATOM";  }
    void print_atom_order(std::ostream& out,
        const At* at, std::false_type) const    {}
    void print_atom_pos(std::ostream& out,
        const At* at, std::false_type) const    {}

    template <class T>
    struct has_no_name_n_chain_id
    :   public std::integral_constant
    <   bool
    ,   !(has_chainid_component<T>::value
    &&    has_name_component<T>::value)
    >
    {};

    template <class T>
    struct has_chainid_not_name
    :   public std::integral_constant
    <   bool
    ,   has_chainid_component<T>::value
    && !has_name_component<T>::value>
    {};

};

////////////////////////////////////////////////////////////////////////////////
// Implementation

#include <maral/ioformats/tree.ipp>

}    // namespace maral

#endif // MARAL_IOFORMATS_TREE_HPP
