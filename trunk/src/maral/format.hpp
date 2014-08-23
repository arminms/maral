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
/// \file maral/format.hpp
/// \brief Include file for the format input/output stream manipulator.
///
/// \b maral/format.hpp is the header file for the format input/output stream
/// manipulator used by inserters and extractors to select the file format.

#ifndef MARAL_FORMAT_HPP
#define MARAL_FORMAT_HPP

////////////////////////////////////////////////////////////////////////////////
// Includes

#include <vector>
#include <memory>
#include <iomanip>

#include <boost/noncopyable.hpp>

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
    virtual void do_print_root(std::ostream& out, const Rt* rt) const
    {   out << "ROOT";  }
};

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
    class pdb_format
:   public Base<Rt,Md,Mo,Sm,At>
{
public:
    pdb_format()
    :   Base<Rt,Md,Mo,Sm,At>()
    {}

private:
    virtual void do_print_root(std::ostream& out, const Rt* rt) const
    {   out << "ROOT (PDB FORMAT)";  }
};

////////////////////////////////////////////////////////////////////////////////
// Abstract Base Class for Input/Output Formats

template
<
    class Rt
,   class Md
,   class Mo
,   class Sm
,   class At
>
    class io_format_base
:   boost::noncopyable
{
public:
    void print_root(std::ostream& out, const Rt* rt)
    {   do_print_root(out, rt);   }

private:
    virtual void do_print_root(std::ostream& out, const Rt* rt) const = 0;
    //virtual void do_print_model(std::ostream& out, const Md* md) const = 0;
    //virtual void do_print_mol(std::ostream& out, const Mo* mo) const = 0;
    //virtual void do_print_submol(std::ostream& out, const Sm* sm) const = 0;
    //virtual void do_print_atom(std::ostream& out, const At* at) const = 0;

    //virtual void do_scan_root(std::istream& out, Rt* rt) const = 0;
    //virtual void do_scan_model(std::istream& out, Md* md) const = 0;
    //virtual void do_scan_mol(std::istream& out, Mo* mo) const = 0;
    //virtual void do_scan_submol(std::istream& out, Sm* sm) const = 0;
    //virtual void do_scan_atom(std::istream& out, At* at) const = 0;
};

////////////////////////////////////////////////////////////////////////////////

template
<
    class Rt
,   class Md
,   class Mo
,   class Sm
,   class At
>
    struct io_format_repository
{
    io_format_repository()
    {
        formats_.push_back(std::unique_ptr<io_format_base<Rt,Md,Mo,Sm,At>>
            (new tree_format<io_format_base,Rt,Md,Mo,Sm,At>()));
        formats_.push_back(std::unique_ptr<io_format_base<Rt,Md,Mo,Sm,At>>
            (new pdb_format<io_format_base,Rt,Md,Mo,Sm,At>()));
    }

    std::vector<std::unique_ptr<io_format_base<Rt,Md,Mo,Sm,At>>> formats_;
};

////////////////////////////////////////////////////////////////////////////////
// Format Input/Output Stream Manipulator

template
<
    class Rt
,   class Md
,   class Mo
,   class Sm
,   class At
>
    class ioformat
{
public:
    ioformat(const long& id)
    :   id_(id)
    {}

    static void print_root(std::ostream& out, const Rt* rt)
    {   repo_.formats_[index(out)]->print_root(out, rt);  }

    //static long get(std::ios_base& ios)
    //{   return index(ios);  }

private:
    const long id_;
    static io_format_repository
    <
        Rt
    ,   Md
    ,   Mo
    ,   Sm
    ,   At
    >   repo_;

    static void set(std::ios_base& ios, long idx)
    {   index(ios) = idx;    }

    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT,Traits>&
    operator << (
        std::basic_ostream<CharT,Traits>& os
    ,   const ioformat& ioman)
    {
        set(os, ioman.id_);
        return os;
    }

    template<typename CharT, typename Traits>
    friend std::basic_istream<CharT,Traits>&
    operator >> (
        std::basic_istream<CharT,Traits>& is
    ,   const ioformat& ioman)
    {
        set(is, ioman.id_);
        return is;
    }

    static long& index(std::ios_base& ios)
    {
        static const int iword_idx = std::ios_base::xalloc();
        return ios.iword(iword_idx);
    }
};

template
<
    class Rt
,   class Md
,   class Mo
,   class Sm
,   class At
>
    io_format_repository<Rt,Md,Mo,Sm,At> ioformat<Rt,Md,Mo,Sm,At>::repo_;

}    // namespace maral

#endif // MARAL_FORMAT_HPP
