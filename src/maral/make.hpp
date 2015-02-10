// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_MAKE_HPP
#define MARAL_MAKE_HPP

#include <memory>

#include <boost/any.hpp>

namespace maral {

////////////////////////////////////////////////////////////////////////////////

template<class T>
struct _Unique_if
{
    typedef std::unique_ptr<T> _Single_object;
};

template<class T>
struct _Unique_if<T[]>
{
    typedef std::unique_ptr<T[]> _Unknown_bound;
};

template<class T, size_t N>
struct _Unique_if<T[N]>
{
    typedef void _Known_bound;
};

template<class T, class... Args>
typename _Unique_if<T>::_Single_object
make(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<class T>
typename _Unique_if<T>::_Unknown_bound
make(size_t n)
{
    typedef typename std::remove_extent<T>::type U;
    return std::unique_ptr<T>(new U[n]());
}

template<class T, class... Args>
typename _Unique_if<T>::_Known_bound
make(Args&&...) = delete;

template <typename T>
using entity = std::unique_ptr<T>;

//using any = boost::any;

}    // namespace maral

#endif    // MARAL_MAKE_HPP

