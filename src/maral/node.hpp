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
/// \file node.hpp
/// \brief Include file for \b node and \b make_node.
///
/// \b node.hpp is the include file that defines \b node and \b make_node.

#ifndef MARAL_NODE_HPP
#define MARAL_NODE_HPP

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
    make_node(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<class T>
    typename _Unique_if<T>::_Unknown_bound
    make_node(size_t n)
{
    typedef typename std::remove_extent<T>::type U;
    return std::unique_ptr<T>(new U[n]());
}

template<class T, class... Args>
    typename _Unique_if<T>::_Known_bound
    make_node(Args&&...) = delete;

template <typename T>
    using node = std::unique_ptr<T>;

}    // namespace maral

#endif    // MARAL_NODE_HPP

