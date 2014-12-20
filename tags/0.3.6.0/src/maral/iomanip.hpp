// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_IOMANIP_HPP
#define MARAL_IOMANIP_HPP

#ifndef MARAL_MTL_IOMANIP_HPP
#include <maral/mtl/iomanip.hpp>
#endif // MARAL_MTL_IOMANIP_HPP

namespace maral {

////////////////////////////////////////////////////////////////////////////////
// Bringing MTL's iomanip into Maral's namesapce

template <typename Argument>
    using skip_if_null = mtl::skip_if_null<Argument>;

template <typename Argument, int Id>
    using zero_arg_iomanip = mtl::zero_arg_iomanip<Argument, Id>;

template <typename Argument, int Id>
    using one_arg_imanip = mtl::one_arg_imanip<Argument, Id>;

template <typename Argument, int Id>
    using one_arg_omanip = mtl::one_arg_omanip<Argument, Id>;

template <typename Argument, int Id>
    using one_arg_iomanip = mtl::one_arg_iomanip<Argument, Id>;

template <typename Arg1, typename Arg2, int Id>
    using two_arg_omanip = mtl::two_arg_omanip<Arg1, Arg2, Id>;

template <typename Arg1, typename Arg2, int Id>
    using two_arg_iomanip = mtl::two_arg_iomanip<Arg1, Arg2, Id>;

using mtl::vertical;
using mtl::horizontal;
using mtl::spaces;
using mtl::nospaces;
using mtl::colmajor;
using mtl::rowmajor;

using orientation = mtl::orientation;
using space = mtl::space;
using order = mtl::order;
using setew = mtl::setew;
using separator = mtl::separator;
using delimiters = mtl::delimiters;

////////////////////////////////////////////////////////////////////////////////
// Depth Output Stream Manipulator

typedef zero_arg_iomanip<bool, 3> depth;

////////////////////////////////////////////////////////////////////////////////
/// \return \p os after manipulating the output.
/// \param os the stream to manipulate.
/// \remarks
/// Stream manipulator for sending all the children to output stream.

template<typename CharT, typename Traits>
inline
std::basic_ostream<CharT, Traits>&
deep(std::basic_ostream<CharT, Traits>& os)
{
    depth::unset(os);
    return os;
}

template<typename CharT, typename Traits>
inline
std::basic_ostream<CharT, Traits>&
shallow(std::basic_ostream<CharT, Traits>& os)
{
    depth::set(os);
    return os;
}

////////////////////////////////////////////////////////////////////////////////
// Ordinal Output Stream Manipulator

typedef one_arg_iomanip<unsigned, 1> atomordinal;
typedef one_arg_iomanip<unsigned, 2> submolordinal;

////////////////////////////////////////////////////////////////////////////////
// Two-arguments Input/Output Stream Manipulator Template

template
<
    typename Arg1
,   typename Arg2
,   typename Arg3
,   int Id>
class three_arg_iomanip
{
    static_assert(
        std::is_integral<Arg1>::value
    &&  std::is_integral<Arg2>::value
    &&  std::is_integral<Arg3>::value
    ,   "need an integral type :(");

public:
    enum { id = Id };

    three_arg_iomanip(
        const Arg1& arg1
    ,   const Arg2& arg2 = 0
    ,   const Arg3& arg3 = 0)
    :   arg1_(arg1)
    ,   arg2_(arg2)
    ,   arg3_(arg3)
    {}

    static long get_1st(std::ios_base& ios)
    {   return three_arg_iomanip::flag1(ios);  }

    static void set_1st(std::ios_base& ios, long flag)
    {   three_arg_iomanip::flag1(ios) = flag;    }

    static long get_2nd(std::ios_base& ios)
    {   return three_arg_iomanip::flag2(ios);  }

    static void set_2nd(std::ios_base& ios, long flag)
    {   three_arg_iomanip::flag2(ios) = flag;    }

    static long get_3rd(std::ios_base& ios)
    {   return three_arg_iomanip::flag3(ios);  }

    static void set_3rd(std::ios_base& ios, long flag)
    {   three_arg_iomanip::flag3(ios) = flag;    }

private:
    const Arg1 arg1_;
    const Arg2 arg2_;
    const Arg3 arg3_;

    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT,Traits>&
    operator << (
        std::basic_ostream<CharT,Traits>& os
    ,   const three_arg_iomanip& ioman)
    {
        set_1st(os, long(ioman.arg1_));
        set_2nd(os, long(ioman.arg2_));
        set_3rd(os, long(ioman.arg3_));
        return os;
    }

    template<typename CharT, typename Traits>
    friend std::basic_istream<CharT,Traits>&
    operator >> (
        std::basic_istream<CharT,Traits>& is
    ,   const three_arg_iomanip& ioman)
    {
        set_1st(is, long(ioman.arg1_));
        set_2nd(is, long(ioman.arg2_));
        set_3rd(is, long(ioman.arg3_));
        return is;
    }

    static long& flag1(std::ios_base& ios)
    {
        static const int iword_idx = std::ios_base::xalloc();
        return ios.iword(iword_idx);
    }

    static long& flag2(std::ios_base& ios)
    {
        static const int iword_idx = std::ios_base::xalloc();
        return ios.iword(iword_idx);
    }

    static long& flag3(std::ios_base& ios)
    {
        static const int iword_idx = std::ios_base::xalloc();
        return ios.iword(iword_idx);
    }
};

////////////////////////////////////////////////////////////////////////////////
// Three-argument Input/Output Stream Manipulators

// frames(start, end, stride)
typedef three_arg_iomanip<unsigned, unsigned, unsigned, 0> frames;

}    // namespace maral

#endif // MARAL_IOMANIP_HPP
