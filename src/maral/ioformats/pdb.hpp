// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
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
#include <unordered_set>
#include <type_traits>

#include <boost/algorithm/string/trim.hpp>
#include <boost/range/algorithm/reverse.hpp>
#include <boost/lexical_cast.hpp>

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

template
<
   class Rt, class Md, class Mo, class Sm, class At
>
    class pdb_format
:   public io_format_base<Rt,Md,Mo,Sm,At>
{
public:
    pdb_format();

    virtual ~pdb_format()
    {   std_residues_.clear();  }

private:
    std::unordered_set<std::string> std_residues_;
    std::size_t current_frame_, next_frame_, frame_count_;

    virtual void do_print_root(std::ostream& out, const Rt* rt);
    virtual void do_print_model(std::ostream& out, const Md* md);
    virtual void do_print_mol(std::ostream& out, const Mo* mo);
    virtual void do_print_submol(std::ostream& out, const Sm* sm);
    virtual void do_print_atom(std::ostream& out, const At* at);

    void print(std::ostream& out,
        const Rt* rt, std::size_t frame) const;
    void print(std::ostream& out,
        const Md* md, std::size_t frame) const;
    void print(std::ostream& out,
        const Mo* mo, std::size_t frame) const;
    void print(std::ostream& out,
        const Sm* sm, std::size_t frame) const;
    void print(std::ostream& out,
        const Mo* mo, const Sm* sm, const At* at,
        int ordinal = -1, std::size_t frame = 0) const;

    template <class T>
    void print_frames(std::ostream& out,
        const T* t, std::true_type) const;
    template <class T>
    void print_frames(std::ostream& out,
        const T* t, std::false_type) const;
    void print_frames(std::ostream& out,
        const Mo* mo, const Sm* sm, const At* at,
        int ordinal, std::true_type) const;
    void print_frames(std::ostream& out,
        const Mo* mo, const Sm* sm, const At* at,
        int ordinal, std::false_type) const;

    void print_chain_termination(std::ostream& out, const Mo* mo,
        const Sm* sm, int ordinal) const;

    void print_mol_chain_id(std::ostream& out,
        const Mo* mo, std::true_type) const;
    void print_mol_chain_id(std::ostream& out,
        const Mo* mo, std::false_type) const    {   out << ' ';     }

    void print_submol_name(std::ostream& out,
        const Sm* sm, std::true_type) const;
    void print_submol_name(std::ostream& out,
        const Sm* sm, std::false_type) const    {   out << "   ";   }
    void print_submol_order(std::ostream& out,
        const Sm* sm, std::true_type) const;
    void print_submol_order(std::ostream& out,
        const Sm* sm, std::false_type) const;
    void print_submol_icode(std::ostream& out,
        const Sm* sm, std::true_type) const;
    void print_submol_icode(std::ostream& out,
        const Sm* sm, std::false_type) const    {   out << ' ';   }

    void print_atom_name(std::ostream& out,
        const At* at, std::true_type) const;
    void print_atom_name(std::ostream& out,
        const At* at, std::false_type) const    {   out << " ?  ";  }
    void print_atom_order(std::ostream& out,
        const At* at, std::true_type) const;
    void print_atom_order(std::ostream& out,
        const At* at, std::false_type) const;
    void print_atom_pos(std::ostream& out,
        const At* at, std::size_t frame, std::true_type) const;
    void print_atom_pos(std::ostream& out,
        const At* at, std::size_t frame, std::false_type) const;
    void print_atom_occupancy(std::ostream& out,
        const At* at, std::true_type) const;
    void print_atom_occupancy(std::ostream& out,
        const At* at, std::false_type) const     {   out << "  1.00";  }
    void print_atom_b_factor(std::ostream& out,
        const At* at, std::true_type) const;
    void print_atom_b_factor(std::ostream& out,
        const At* at, std::false_type) const     {   out << "  0.00";  }
    void print_atom_element(std::ostream& out,
        const At* at, std::true_type) const;
    void print_atom_element(std::ostream& out,
        const At* at, std::false_type) const     {   out << "  ";  }
    void print_atom_formal_charge(std::ostream& out,
        const At* at, std::true_type) const;
    void print_atom_formal_charge(std::ostream& out,
        const At* at, std::false_type) const     {   out << "  ";  }

    virtual void do_scan_root(std::istream& in, Rt* rt);
    virtual void do_scan_model(std::istream& in, Md* md);
    virtual void do_scan_mol(std::istream& in, Mo* mo);
    virtual void do_scan_submol(std::istream& in, Sm* sm);
    virtual void do_scan_atom(std::istream& in, At* at);

    void scan_model(std::istream& in, std::string& line, Md* md);
    void scan_mol(std::istream& in, std::string& line, Mo* mo) const;
    void scan_submol(std::istream& in, std::string& line, Sm* sm) const;
    void scan_atom(std::istream& in, std::string& line, At* at) const;

    void init_frames(std::istream& in, std::true_type);
    void init_frames(std::istream& in, std::false_type) {}
    void scan_frame_number(const std::string& line,
        std::true_type) const;
    void scan_frame_number(const std::string& line,
        std::false_type) const      {}
    bool scan_coords(std::istream& in, std::string& line,
        std::size_t skip, std::true_type);
    bool scan_coords(std::istream& in, std::string& line,
        std::size_t skip, std::false_type);
    void level_coords(std::true_type) const
    {   Rt::level_coords();  }
    void level_coords(std::false_type) const {}
    std::size_t get_skip(std::true_type) const
    {   return Rt::coords_size();  }
    std::size_t get_skip(std::false_type) const
    {   return 0;   }

    void set_model_name(const std::string& name,
        Md* md, std::true_type) const   { md->name(name); }
    void set_model_name(const std::string& name,
        Md* md, std::false_type) const  {}

    void set_mol_name(const std::string& name,
        Mo* mo, std::true_type) const;
    void set_mol_name(const std::string& name,
        Mo* mo, std::false_type) const    {}
    void scan_chain_id(const std::string& line,
        Mo* mo, std::true_type) const;
    void scan_chain_id(const std::string& line,
        Mo* mo, std::false_type) const    {}

    void scan_submol_name(const std::string& line,
        Sm* sm, std::true_type) const;
    void scan_submol_name(const std::string& line,
        Sm* sm, std::false_type) const  {}
    void scan_submol_order(const std::string& line,
        Sm* sm, std::true_type) const;
    void scan_submol_order(const std::string& line,
        Sm* sm, std::false_type) const  {}
    void scan_submol_icode(const std::string& line,
        Sm* sm, std::true_type) const;
    void scan_submol_icode(const std::string& line,
        Sm* sm, std::false_type) const  {}

    void scan_atom_name(const std::string& line,
        At* at, std::true_type) const;
    void scan_atom_name(const std::string& line,
        At* at, std::false_type) const    {}
    void scan_atom_order(std::istream& in,
        At* at, std::true_type) const;
    void scan_atom_order(std::istream& in,
        At* at, std::false_type) const;
    void scan_atom_pos(const std::string& line,
        At* at, std::true_type) const;
    void scan_atom_pos(const std::string& line,
        At* at, std::false_type) const    {}
    void scan_atom_occupancy(const std::string& line,
        At* at, std::true_type) const;
    void scan_atom_occupancy(const std::string& line,
        At* at, std::false_type) const    {}
    void scan_atom_b_factor(const std::string& line,
        At* at, std::true_type) const;
    void scan_atom_b_factor(const std::string& line,
        At* at, std::false_type) const    {}
    void scan_atom_element(const std::string& line,
        At* at, std::true_type) const;
    void scan_atom_element(const std::string& line,
        At* at, std::false_type) const    {}
    void scan_atom_formal_charge(const std::string& line,
        At* at, std::true_type) const;
    void scan_atom_formal_charge(const std::string& line,
        At* at, std::false_type) const    {}

    bool is_het(const Sm* sm, std::true_type) const
    {   return (std_residues_.find(sm->name()) == std_residues_.end()); }

    bool is_het(const Sm* sm, std::false_type) const
    {   return true;    }

    template <class T>
    struct has_pos_or_lnk_pos
    :   public std::integral_constant
    <   bool,
        has_position_component<T>::value
    ||  has_linked_position_component<T>::value
    >
    {};
};

////////////////////////////////////////////////////////////////////////////////
// Implementation

#include <maral/ioformats/pdb.ipp>

}    // namespace maral

#endif // MARAL_IOFORMATS_PDB_HPP
