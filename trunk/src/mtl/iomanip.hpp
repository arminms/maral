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
/// \file mtl/iomanip.hpp
/// \brief Include file for the input/output stream manipulators used by
/// inserters and extractors of maral::mtl.
///
/// \b mtl/iomanip.hpp is the header file for all the templates and
/// typedefs that implement the input/output stream manipulators used by
/// inserters and extractors of maral::mtl's point, vector, matrix, ... classes.

#ifndef MARAL_MTL_IOMANIP_HPP
#define MARAL_MTL_IOMANIP_HPP

namespace maral { namespace mtl {

/// \ingroup omanip
/// \name Output Stream Manipulators
/// @{

template <typename Argument>
class skip_if_null
{
    static_assert(
        std::is_integral<Argument>::value,
        "need an integral type :(");

public:
    skip_if_null(const Argument& arg)
    :   arg_(arg)
    {}

private:
    const Argument arg_;

    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT,Traits>&
    operator<< (
        std::basic_ostream<CharT,Traits>& os
    ,   const skip_if_null& oman)
    {
        if (oman.arg_) os << oman.arg_;
        return os;
    }
};

////////////////////////////////////////////////////////////////////////////////
// Zero-argument Input/Output Stream Manipulator Template

template <typename Argument, int Id>
class zero_arg_iomanip
{
public:
    enum { id = Id };

    zero_arg_iomanip(const Argument& arg = true)
    :   arg_(arg)
    {}

    static long get(std::ios_base& ios)
    {   return zero_arg_iomanip::flag(ios);  }

    static void set(std::ios_base& ios)
    {   zero_arg_iomanip::flag(ios) = 1;    }

    static void unset(std::ios_base& ios)
    {   zero_arg_iomanip::flag(ios) = 0;    }

private:
    const Argument arg_;

    static long& flag(std::ios_base& ios)
    {
        static const int iword_idx = std::ios_base::xalloc();
        return ios.iword(iword_idx);
    }
};

////////////////////////////////////////////////////////////////////////////////
// Orientation Input/Output Stream Manipulators

typedef zero_arg_iomanip<bool, 0> orientation;

template<typename CharT, typename Traits>
inline
std::basic_ostream<CharT, Traits>&
vertical(std::basic_ostream<CharT, Traits>& os)
{
    orientation::unset(os);
    return os;
}

template<typename CharT, typename Traits>
inline
std::basic_ostream<CharT, Traits>&
horizontal(std::basic_ostream<CharT, Traits>& os)
{
    orientation::set(os);
    return os;
}

template<typename CharT, typename Traits>
inline
std::basic_istream<CharT, Traits>&
vertical(std::basic_istream<CharT, Traits>& is)
{
    orientation::unset(is);
    return is;
}

template<typename CharT, typename Traits>
inline
std::basic_istream<CharT, Traits>&
horizontal(std::basic_istream<CharT, Traits>& is)
{
    orientation::set(is);
    return is;
}

////////////////////////////////////////////////////////////////////////////////
// Space Output Stream Manipulator

typedef zero_arg_iomanip<bool, 1> space;

////////////////////////////////////////////////////////////////////////////////
/// \return \p os after manipulating the output.
/// \param os the stream to manipulate.
/// \remarks
/// Stream manipulator for putting spaces around elements of vectors, matrices.

template<typename CharT, typename Traits>
inline
std::basic_ostream<CharT, Traits>&
spaces(std::basic_ostream<CharT, Traits>& os)
{
    space::set(os);
    return os;
}

template<typename CharT, typename Traits>
inline
std::basic_ostream<CharT, Traits>&
nospaces(std::basic_ostream<CharT, Traits>& os)
{
    space::unset(os);
    return os;
}

////////////////////////////////////////////////////////////////////////////////
// Order Majority Input/Output Stream Manipulators

typedef zero_arg_iomanip<bool, 2> order;

template<typename CharT, typename Traits>
inline
std::basic_ostream<CharT, Traits>&
colmajor(std::basic_ostream<CharT, Traits>& os)
{
    order::unset(os);
    return os;
}

template<typename CharT, typename Traits>
inline
std::basic_ostream<CharT, Traits>&
rowmajor(std::basic_ostream<CharT, Traits>& os)
{
    order::set(os);
    return os;
}

template<typename CharT, typename Traits>
inline
std::basic_istream<CharT, Traits>&
colmajor(std::basic_istream<CharT, Traits>& is)
{
    order::unset(is);
    return is;
}

template<typename CharT, typename Traits>
inline
std::basic_istream<CharT, Traits>&
rowmajor(std::basic_istream<CharT, Traits>& is)
{
    order::set(is);
    return is;
}

////////////////////////////////////////////////////////////////////////////////
// One-argument Output Stream Manipulator Template

template <typename Argument, int Id>
class one_arg_omanip
{
    static_assert(
        std::is_integral<Argument>::value,
        "need an integral type :(");

public:
    enum { id = Id };

    one_arg_omanip(const Argument& arg)
    :   arg_(arg)
    {}

    static long get(std::ios_base& ios)
    {   return one_arg_omanip::flag(ios);  }

    static void set(std::ios_base& ios, long flag)
    {   one_arg_omanip::flag(ios) = flag;    }

private:
    const Argument arg_;

    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT,Traits>&
    operator<< (
        std::basic_ostream<CharT,Traits>& os
    ,   const one_arg_omanip& oman)
    {
        set(os, long(oman.arg_));
        return os;
    }

    static long& flag(std::ios_base& ios)
    {
        static const int iword_idx = std::ios_base::xalloc();
        return ios.iword(iword_idx);
    }
};

////////////////////////////////////////////////////////////////////////////////
// One-argument Output Stream Manipulators

typedef one_arg_omanip<char, 1> setew;

////////////////////////////////////////////////////////////////////////////////
// One-argument Input/Output Stream Manipulator Template

template <typename Argument, int Id>
class one_arg_iomanip
{
    static_assert(
        std::is_integral<Argument>::value,
        "need an integral type :(");

public:
    enum { id = Id };

    one_arg_iomanip(const Argument& arg)
    :   arg_(arg)
    {}

    static long get(std::ios_base& ios)
    {   return one_arg_iomanip::flag(ios);  }

    static void set(std::ios_base& ios, long flag)
    {   one_arg_iomanip::flag(ios) = flag;    }

private:
    const Argument arg_;

    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT,Traits>&
    operator << (
        std::basic_ostream<CharT,Traits>& os
    ,   const one_arg_iomanip& ioman)
    {
        set(os, long(ioman.arg_));
        return os;
    }

    template<typename CharT, typename Traits>
    friend std::basic_istream<CharT,Traits>&
    operator >> (
        std::basic_istream<CharT,Traits>& is
    ,   const one_arg_iomanip& ioman)
    {
        set(is, long(ioman.arg_));
        return is;
    }

    static long& flag(std::ios_base& ios)
    {
        static const int iword_idx = std::ios_base::xalloc();
        return ios.iword(iword_idx);
    }
};

////////////////////////////////////////////////////////////////////////////////
// One-argument Input/Output Stream Manipulators

typedef one_arg_iomanip<char, 0> separator;

////////////////////////////////////////////////////////////////////////////////
// Two-arguments Output Stream Manipulator Template

template <typename Arg1, typename Arg2, int Id>
class two_arg_omanip
{
    static_assert(
    std::is_integral<Arg1>::value && std::is_integral<Arg2>::value,
        "need an integral type :(");

public:
    enum { id = Id };

    two_arg_omanip(const Arg1& arg1, const Arg2& arg2 = 0)
    :   arg1_(arg1)
    ,   arg2_(arg2 ? arg2 : arg1)
    {}

    static long get_1st(std::ios_base& ios)
    {   return two_arg_omanip::flag1(ios);  }

    static void set_1st(std::ios_base& ios, long flag)
    {   two_arg_omanip::flag1(ios) = flag;    }

    static long get_2nd(std::ios_base& ios)
    {   return two_arg_omanip::flag2(ios);  }

    static void set_2nd(std::ios_base& ios, long flag)
    {   two_arg_omanip::flag2(ios) = flag;    }

private:
    const Arg1 arg1_;
    const Arg2 arg2_;

    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT,Traits>&
    operator<< (
        std::basic_ostream<CharT,Traits>& os
    ,   const two_arg_omanip& oman)
    {
        set_1st(os, long(oman.arg1_));
        set_2nd(os, long(oman.arg2_));
        return os;
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
};

////////////////////////////////////////////////////////////////////////////////
// One-argument Output Stream Manipulators

/// @}

/// \ingroup imanip
/// \name Input Stream Manipulators
/// @{

////////////////////////////////////////////////////////////////////////////////
// One-argument Input Stream Manipulator Template

template <typename Argument, int Id>
class one_arg_imanip
{
    static_assert(
    std::is_integral<Argument>::value,
        "need an integral type :(");

public:
    enum { id = Id };

    one_arg_imanip(const Argument& arg)
    : arg_(arg)
    {}

    static long get(std::ios_base& ios)
    {   return one_arg_imanip::flag(ios);  }

    static void set(std::ios_base& ios, long flag)
    {   one_arg_imanip::flag(ios) = flag;    }

private:
    const Argument arg_;

    template<typename CharT, typename Traits>
    friend std::basic_istream<CharT,Traits>&
    operator<< (
        std::basic_istream<CharT,Traits>& is
    ,   const one_arg_imanip& iman)
    {
        set(is, long(iman.arg_));
        return is;
    }

    static long& flag(std::ios_base& ios)
    {
        static const int iword_idx = std::ios_base::xalloc();
        return ios.iword(iword_idx);
    }
};

////////////////////////////////////////////////////////////////////////////////
// One-argument Input Stream Manipulators

////////////////////////////////////////////////////////////////////////////////
// Two-arguments Output Stream Manipulator Template

template <typename Arg1, typename Arg2, int Id>
class two_arg_iomanip
{
    static_assert(
    std::is_integral<Arg1>::value && std::is_integral<Arg2>::value,
        "need an integral type :(");

public:
    enum { id = Id };

    two_arg_iomanip(const Arg1& arg1, const Arg2& arg2 = 0)
    :   arg1_(arg1)
    ,   arg2_(arg2 ? arg2 : arg1)
    {}

    static long get_1st(std::ios_base& ios)
    {   return two_arg_iomanip::flag1(ios);  }

    static void set_1st(std::ios_base& ios, long flag)
    {   two_arg_iomanip::flag1(ios) = flag;    }

    static long get_2nd(std::ios_base& ios)
    {   return two_arg_iomanip::flag2(ios);  }

    static void set_2nd(std::ios_base& ios, long flag)
    {   two_arg_iomanip::flag2(ios) = flag;    }

private:
    const Arg1 arg1_;
    const Arg2 arg2_;

    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT,Traits>&
    operator << (
        std::basic_ostream<CharT,Traits>& os
    ,   const two_arg_iomanip& ioman)
    {
        set_1st(os, long(ioman.arg1_));
        set_2nd(os, long(ioman.arg2_));
        return os;
    }

    template<typename CharT, typename Traits>
    friend std::basic_istream<CharT,Traits>&
    operator >> (
        std::basic_istream<CharT,Traits>& is
    ,   const two_arg_iomanip& ioman)
    {
        set_1st(is, long(ioman.arg1_));
        set_2nd(is, long(ioman.arg2_));
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
};

////////////////////////////////////////////////////////////////////////////////
// Two-argument Input/Output Stream Manipulators

typedef two_arg_iomanip<char,char,0> delimiters;

/// @}
}}    // namespaces

#endif // MARAL_MTL_IOMANIP_HPP
