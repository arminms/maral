// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

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

    void print_model(std::ostream& out, const Md* md)
    {   do_print_model(out, md);   }

    void print_mol(std::ostream& out, const Mo* mo)
    {   do_print_mol(out, mo);   }

    void print_submol(std::ostream& out, const Sm* sm)
    {   do_print_submol(out, sm);   }

    void print_atom(std::ostream& out, const At* at)
    {   do_print_atom(out, at);   }


    void scan_root(std::istream& in, Rt* rt)
    {   do_scan_root(in, rt);   }

    void scan_model(std::istream& in, Md* md)
    {   do_scan_model(in, md);   }

    void scan_mol(std::istream& in, Mo* mo)
    {   do_scan_mol(in, mo);   }

    void scan_submol(std::istream& in, Sm* sm)
    {   do_scan_submol(in, sm);   }

    void scan_atom(std::istream& in, At* at)
    {   do_scan_atom(in, at);   }

// Implementation
    virtual ~io_format_base() {};

private:
    virtual void do_print_root(std::ostream& out, const Rt* rt) = 0;
    virtual void do_print_model(std::ostream& out, const Md* md) = 0;
    virtual void do_print_mol(std::ostream& out, const Mo* mo) = 0;
    virtual void do_print_submol(std::ostream& out, const Sm* sm) = 0;
    virtual void do_print_atom(std::ostream& out, const At* at) = 0;

    virtual void do_scan_root(std::istream& in, Rt* rt) = 0;
    virtual void do_scan_model(std::istream& in, Md* md) = 0;
    virtual void do_scan_mol(std::istream& in, Mo* mo) = 0;
    virtual void do_scan_submol(std::istream& in, Sm* sm) = 0;
    virtual void do_scan_atom(std::istream& in, At* at) = 0;
};

////////////////////////////////////////////////////////////////////////////////

template
<
    class Rt
,   class Md
,   class Mo
,   class Sm
,   class At
,   template <class,class,class,class,class> class ...F
>
    struct io_format_repository
{
    io_format_repository()
    {   push_back(new F<Rt,Md,Mo,Sm,At>...);    }

    std::vector<std::unique_ptr<io_format_base<Rt,Md,Mo,Sm,At>>> formats_;

private:
    template <typename T>
    void push_back(T* t)
    {
        formats_.push_back(
            std::unique_ptr<io_format_base<Rt,Md,Mo,Sm,At>>(t));
    }

    template<typename First, typename ...Rest>
    void push_back(First* first, Rest* ...rest)
    {
        formats_.push_back(
            std::unique_ptr<io_format_base<Rt,Md,Mo,Sm,At>>(first));
        push_back(rest...);
    }
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
,   template <class,class,class,class,class> class ...F
>
    class ioformat
{
public:
    typedef Rt root_type;
    typedef Md model_type;
    typedef Mo mol_type;
    typedef Sm submol_type;
    typedef At atom_type;

    ioformat(const long& id)
    :   id_(id)
    {
#if BOOST_WORKAROUND(__GLIBCXX__, BOOST_TESTED_AT(20130909))
#else
        BOOST_ASSERT_MSG(id < sizeof...(F),
            "file format index exceeding the max size!");
#endif  //__GLIBCXX__
    }

    static void print_root(std::ostream& out, const Rt* rt)
    {   repo_.formats_[index(out)]->print_root(out, rt);  }

    static void print_model(std::ostream& out, const Md* md)
    {   repo_.formats_[index(out)]->print_model(out, md);  }

    static void print_mol(std::ostream& out, const Mo* mo)
    {   repo_.formats_[index(out)]->print_mol(out, mo);  }

    static void print_submol(std::ostream& out, const Sm* sm)
    {   repo_.formats_[index(out)]->print_submol(out, sm);  }

    static void print_atom(std::ostream& out, const At* at)
    {   repo_.formats_[index(out)]->print_atom(out, at);  }

    static void scan_root(std::istream& in, Rt* rt)
    {   repo_.formats_[index(in)]->scan_root(in, rt);  }

    static void scan_model(std::istream& in, Md* md)
    {   repo_.formats_[index(in)]->scan_model(in, md);  }

    static void scan_mol(std::istream& in, Mo* mo)
    {   repo_.formats_[index(in)]->scan_mol(in, mo);  }

    static void scan_submol(std::istream& in, Sm* sm)
    {   repo_.formats_[index(in)]->scan_submol(in, sm);  }

    static void scan_atom(std::istream& in, At* at)
    {   repo_.formats_[index(in)]->scan_atom(in, at);  }

private:
    const long id_;
    static io_format_repository<Rt,Md,Mo,Sm,At,F...> repo_;

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
,   template <class,class,class,class,class> class ...F
>
    io_format_repository<Rt,Md,Mo,Sm,At,F...>
        ioformat<Rt,Md,Mo,Sm,At,F...>::repo_;

}    // namespace maral

#endif // MARAL_FORMAT_HPP
