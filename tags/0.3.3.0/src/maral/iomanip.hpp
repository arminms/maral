// Boost.Maral library (Molecular Architecture Recording & Assembly Library)
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

}    // namespace maral

#endif // MARAL_IOMANIP_HPP

