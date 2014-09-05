// Boost.Maral library (Molecular Architecture Recording & Assembly Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_IOFORMATS_PDB_HPP
#define MARAL_IOFORMATS_PDB_HPP

////////////////////////////////////////////////////////////////////////////////
// Includes

#include <sstream>
#include <algorithm>
#include <type_traits>

#include <boost/algorithm/string/trim.hpp>

#ifndef MARAL_MTL_INSERTERS_HPP
#include <maral/mtl/inserters.hpp>
#endif // MARAL_MTL_INSERTERS_HPP

#ifndef MARAL_HAS_MEMBER_HPP
#include <maral/has_member.hpp>
#endif // MARAL_HAS_MEMBER_HPP

#ifndef MARAL_IOMANIP_HPP
#include <maral/iomanip.hpp>
#endif // MARAL_IOMANIP_HPP

namespace maral {

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
    class pdb_format
:   public Base<Rt,Md,Mo,Sm,At>
{
public:
    pdb_format()
    :   Base<Rt,Md,Mo,Sm,At>()
    {}

private:
    virtual void do_print_root(std::ostream& out, const Rt* rt) const   {}
    virtual void do_print_model(std::ostream& out, const Md* md) const  {}
    virtual void do_print_mol(std::ostream& out, const Mo* mo) const    {}
    virtual void do_print_submol(std::ostream& out, const Sm* sm) const {}
    virtual void do_print_atom(std::ostream& out, const At* at) const   {}

    virtual void do_scan_root(std::istream& in, Rt* rt) const;
    virtual void do_scan_model(std::istream& in, Md* md) const  {}
    virtual void do_scan_mol(std::istream& in, Mo* mo) const    {}
    virtual void do_scan_submol(std::istream& in, Sm* sm) const {}
    virtual void do_scan_atom(std::istream& in, At* at) const   {}

    //void scan_root(std::istream& in, std::string& line, Rt* rt) const;
    void scan_model(std::istream& in, std::string& line, Md* md) const;
    void scan_mol(std::istream& in, std::string& line, Mo* mo) const;
    void scan_submol(std::istream& in, std::string& line, Sm* sm) const;
    void scan_atom(std::istream& in, std::string& line, At* at) const;

    //void scan_root_name(std::istream& out,
    //    Rt* rt, std::true_type) const;
    //void scan_root_order(std::istream& out,
    //    Rt* rt, std::true_type) const;
    //void scan_root_pos(std::istream& out,
    //    Rt* rt, std::true_type) const;
    //void scan_root_name(std::istream& out,
    //    Rt* rt, std::false_type) const    {}
    //void scan_root_order(std::istream& out,
    //    Rt* rt, std::false_type) const    {}
    //void scan_root_pos(std::istream& out,
    //    Rt* rt, std::false_type) const    {}

    void set_model_name(const std::string& name,
        Md* md, std::true_type) const   { md->name(name); }
    //void print_model_order(std::istream& out,
    //    const Md* md, std::true_type) const;
    //void print_model_pos(std::istream& out,
    //    const Md* md, std::true_type) const;
    void set_model_name(const std::string& name,
        Md* md, std::false_type) const  {}
    //void print_model_order(std::istream& out,
    //    const Md* md, std::false_type) const    {}
    //void print_model_pos(std::istream& out,
    //    const Md* md, std::false_type) const    {}

    void scan_chain_id(const std::string& line,
        Mo* mo, std::true_type) const;
    void set_mol_name(const std::string& name,
        Mo* mo, std::true_type) const;
    //void print_mol_order(std::ostream& out,
    //    const Mo* mo, std::true_type) const;
    //void print_mol_pos(std::ostream& out,
    //    const Mo* mo, std::true_type) const;
    void scan_chain_id(const std::string& line,
        Mo* mo, std::false_type) const    {}
    void set_mol_name(const std::string& name,
        Mo* mo, std::false_type) const    {}
    //void print_mol_order(std::ostream& out,
    //    const Mo* mo, std::false_type) const    {}
    //void print_mol_pos(std::ostream& out,
    //    const Mo* mo, std::false_type) const    {}

    void scan_submol_name(const std::string& in,
        Sm* sm, std::true_type) const;
    void scan_submol_order(const std::string& out,
        Sm* sm, std::true_type) const;
    //void print_submol_pos(std::ostream& out,
    //    const Sm* sm, std::true_type) const;
    void scan_submol_name(const std::string& in,
        Sm* sm, std::false_type) const  {}
    void scan_submol_order(const std::string& out,
        Sm* sm, std::false_type) const  {}
    //void print_submol_pos(std::ostream& out,
    //    const Sm* sm, std::false_type) const    {}

    //void print_atom_name(std::ostream& out,
    //    const At* at, std::true_type) const;
    //void print_atom_order(std::ostream& out,
    //    const At* at, std::true_type) const;
    //void print_atom_pos(std::ostream& out,
    //    const At* at, std::true_type) const;
    //void print_atom_name(std::ostream& out,
    //    const At* at, std::false_type) const    {   out << "ATOM";  }
    //void print_atom_order(std::ostream& out,
    //    const At* at, std::false_type) const    {}
    //void print_atom_pos(std::ostream& out,
    //    const At* at, std::false_type) const    {}

    void scan_atom_name(const std::string& line,
        At* at, std::true_type) const;
    void scan_atom_order(const std::string& line,
        At* at, std::true_type) const;
    void scan_atom_pos(const std::string& line,
        At* at, std::true_type) const;
    void scan_atom_name(const std::string& line,
        At* at, std::false_type) const    {}
    void scan_atom_order(const std::string& line,
        At* at, std::false_type) const    {}
    void scan_atom_pos(const std::string& line,
        At* at, std::false_type) const    {}
};

////////////////////////////////////////////////////////////////////////////////
// Implementation

#include <maral/ioformats/pdb.ipp>

}    // namespace maral

#endif // MARAL_IOFORMATS_PDB_HPP
