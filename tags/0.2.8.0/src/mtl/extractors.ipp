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
// Filename:
//    mtl/extractors.ipp
//------------------------------------------------------------------------------
// Remarks:
//    This file contains implementation of all stream extractors for maral::mtl
//    classes.
//------------------------------------------------------------------------------

/// \ingroup Extractors
/// \name Stream Extractors
/// @{

////////////////////////////////////////////////////////////////////////////////
/// \return \p bis after extracting from it.
/// \param bis the stream to extract from.
/// \param pnt the point2 type to extract.
/// \pre std::ios::skipws flag must be set.
/// \remarks
/// Extracts \p pnt from \p bis input stream. The default input must be
/// formatted such that point2<int>(1,2) appears as:
/// <pre>
/// 1
/// 2
/// </pre>
/// You can use the following stream manipulators to change the default
/// behavior:
/// \li mtl::vertical (default)
/// \li mtl::horizontal
/// \li mtl::separator (default space)
/// \li mtl::delimiters (default none)
/// \par Example:
///
/// \snippet mtl_points.cpp point2 extractor
/// \a Input:
/// \include pntvec2.txt

template<typename CharT, typename Traits, typename Type>
inline
std::basic_istream<CharT,Traits>&
operator >> (
    std::basic_istream<CharT,Traits>& bis,
    point2<Type>& pnt)
{
    constexpr auto max = std::numeric_limits<std::streamsize>::max();
    CharT bro = static_cast<CharT>(delimiters::get_1st(bis));
    CharT brc = static_cast<CharT>(delimiters::get_2nd(bis));
    CharT sep = static_cast<CharT>(separator::get(bis));
    Type val[2];

    if (bro)
        bis.ignore(max, bro);

    bis >> val[0];

    if (sep && orientation::get(bis))
        bis.ignore(max, sep);

    if (brc && orientation::get(bis) == 0)
    {
        bis.ignore(max, brc);
        bis.ignore(max, bro);
    }

    bis >> val[1];

    if (brc)
        bis.ignore(max, brc);

    if (bis)
        pnt.set(val);

    return bis;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \p bis after extracting from it.
/// \param bis the stream to extract from.
/// \param pnt the point3 type to extract.
/// \pre std::ios::skipws flag must be set.
/// \remarks
/// Extracts \p pnt from \p bis input stream. The default input must be
/// formatted such that point3<int>(1,2,3) appears as:
/// <pre>
/// 1
/// 2
/// 3
/// </pre>
/// You can use the following stream manipulators to change the default
/// behavior:
/// \li mtl::vertical (default)
/// \li mtl::horizontal
/// \li mtl::separator (default space)
/// \li mtl::delimiters (default none)
/// \par Example:
///
/// \snippet mtl_points.cpp point3 extractor
/// \a Input:
/// \include pntvec3.txt

template<typename CharT, typename Traits, typename Type>
inline
std::basic_istream<CharT,Traits>&
operator >> (
    std::basic_istream<CharT,Traits>& bis,
    point3<Type>& pnt)
{
    constexpr auto max = std::numeric_limits<std::streamsize>::max();
    CharT bro = static_cast<CharT>(delimiters::get_1st(bis));
    CharT brc = static_cast<CharT>(delimiters::get_2nd(bis));
    CharT sep = static_cast<CharT>(separator::get(bis));
    Type val[3];

    if (bro)
        bis.ignore(max, bro);

    for (auto i=0; i < 3; ++i)
    {
        bis >> val[i];

        if (sep && orientation::get(bis) && i < 2)
            bis.ignore(max, sep);

        if (brc && orientation::get(bis) == 0)
        {
            bis.ignore(max, brc);
            if (2 == i)
                break;
            bis.ignore(max, bro);
        }
    }

    if (brc && orientation::get(bis))
        bis.ignore(max, brc);

    if (bis)
        pnt.set(val);

    return bis;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \p bis after extracting from it.
/// \param bis the stream to extract from.
/// \param vec the vector2 type to extract.
/// \pre std::ios::skipws flag must be set.
/// \remarks
/// Extracts \p vec from \p bis input stream. The default input must be
/// formatted such that vector2<int>(1,2) appears as:
/// <pre>
/// 1
/// 2
/// </pre>
/// You can use the following stream manipulators to change the default
/// behavior:
/// \li mtl::vertical (default)
/// \li mtl::horizontal
/// \li mtl::separator (default space)
/// \li mtl::delimiters (default none)
/// \par Example:
///
/// \snippet mtl_vectors.cpp vector2 extractor
/// \a Input:
/// \include pntvec2.txt

template<typename CharT, typename Traits, typename Type>
inline
std::basic_istream<CharT,Traits>&
operator >> (
    std::basic_istream<CharT,Traits>& bis,
    vector2<Type>& vec)
{
    constexpr auto max = std::numeric_limits<std::streamsize>::max();
    CharT bro = static_cast<CharT>(delimiters::get_1st(bis));
    CharT brc = static_cast<CharT>(delimiters::get_2nd(bis));
    CharT sep = static_cast<CharT>(separator::get(bis));
    Type val[2];

    if (bro)
        bis.ignore(max, bro);

    bis >> val[0];

    if (sep && orientation::get(bis))
        bis.ignore(max, sep);

    if (brc && orientation::get(bis) == 0)
    {
        bis.ignore(max, brc);
        bis.ignore(max, bro);
    }

    bis >> val[1];

    if (brc)
        bis.ignore(max, brc);

    if (bis)
        vec.set(val);

    return bis;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \p bis after extracting from it.
/// \param bis the stream to extract from.
/// \param vec the vector3 type to extract.
/// \pre std::ios::skipws flag must be set.
/// \remarks
/// Extracts \p vec from \p bis input stream. The default input must be
/// formatted such that vector3<int>(1,2,3) appears as:
/// <pre>
/// 1
/// 2
/// 3
/// </pre>
/// You can use the following stream manipulators to change the default
/// behavior:
/// \li mtl::vertical (default)
/// \li mtl::horizontal
/// \li mtl::separator (default space)
/// \li mtl::delimiters (default none)
/// \par Example:
///
/// \snippet mtl_vectors.cpp vector3 extractor
/// \a Input:
/// \include pntvec3.txt

template<typename CharT, typename Traits, typename Type>
inline
std::basic_istream<CharT,Traits>&
operator >> (
    std::basic_istream<CharT,Traits>& bis,
    vector3<Type>& vec)
{
    constexpr auto max = std::numeric_limits<std::streamsize>::max();
    CharT bro = static_cast<CharT>(delimiters::get_1st(bis));
    CharT brc = static_cast<CharT>(delimiters::get_2nd(bis));
    CharT sep = static_cast<CharT>(separator::get(bis));
    Type val[3];

    if (bro)
        bis.ignore(max, bro);

    for (auto i=0; i < 3; ++i)
    {
        bis >> val[i];

        if (sep && orientation::get(bis) && i < 2)
            bis.ignore(max, sep);

        if (brc && orientation::get(bis) == 0)
        {
            bis.ignore(max, brc);
            if (2 == i)
                break;
            bis.ignore(max, bro);
        }
    }

    if (brc && orientation::get(bis))
        bis.ignore(max, brc);

    if (bis)
        vec.set(val);

    return bis;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \p bis after extracting from it.
/// \param bis the stream to extract from.
/// \param mtx the matrix22 type to extract.
/// \pre std::ios::skipws flag must be set.
/// \remarks
/// Extracts \p mtx from \p bis input stream. The default input must be
/// formatted such that matrix22<int> m {1,2,3,4} appears as:
/// <pre>
/// 1 3
/// 2 4
/// </pre>
/// You can use the following stream manipulators to change the default
/// behavior:
/// \li mtl::vertical (default)
/// \li mtl::horizontal
/// \li mtl::separator (space)
/// \li mtl::delimiters (default none)
/// \li mtl::colmajor (default)
/// \li mtl::rowmajor
/// \par Example:
///
/// \snippet mtl_matrices.cpp matrix22 extractor
/// \a Input:
/// \include matrix22.txt

template<typename CharT, typename Traits, typename Type>
inline
std::basic_istream<CharT,Traits>&
operator >> (
    std::basic_istream<CharT,Traits>& bis,
    matrix22<Type>& mtx)
{
    constexpr auto max = std::numeric_limits<std::streamsize>::max();
    CharT bro = static_cast<CharT>(delimiters::get_1st(bis));
    CharT brc = static_cast<CharT>(delimiters::get_2nd(bis));
    CharT sep = static_cast<CharT>(separator::get(bis));
    Type val[4];

    if (bro)
        bis.ignore(max, bro);

    if (orientation::get(bis))
    {
        for (auto i=0; i < 4; ++i)
        {
            bis >> val[i];
            if (sep && i < 3)
                bis.ignore(max, sep);
        }
        if (brc)
            bis.ignore(max, brc);
    }
    else
    {
        for (auto i=0; i < 4; ++i)
        {
            bis >> val[i];
            if (i%2)
            {
                if (bro)
                {
                    bis.ignore(max, brc);
                    if (3 == i)
                        break;
                    bis.ignore(max, bro);
                }
                continue;
            }
            if (sep)
                bis.ignore(max, sep);
        }
    }

    if (bis)
    {
        if (order::get(bis) || orientation::get(bis) == 0)
            mtx.set_transpose(val);
        else
            mtx.set(val);
    }

    return bis;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \p bis after extracting from it.
/// \param bis the stream to extract from.
/// \param mtx the matrix33 type to extract.
/// \pre std::ios::skipws flag must be set.
/// \remarks
/// Extracts \p mtx from \p bis input stream. The default input must be
/// formatted such that matrix33<int> m {1,2,3,4,5,6,7,8,9} appears as:
/// <pre>
/// 1 4 7
/// 2 5 8
/// 3 6 9
/// </pre>
/// You can use the following stream manipulators to change the default
/// behavior:
/// \li mtl::vertical (default)
/// \li mtl::horizontal
/// \li mtl::separator (space)
/// \li mtl::delimiters (default none)
/// \li mtl::colmajor (default)
/// \li mtl::rowmajor
/// \par Example:
///
/// \snippet mtl_matrices.cpp matrix33 extractor
/// \a Input:
/// \include matrix33.txt

template<typename CharT, typename Traits, typename Type>
inline
std::basic_istream<CharT,Traits>&
operator >> (
    std::basic_istream<CharT,Traits>& bis,
    matrix33<Type>& mtx)
{
    constexpr auto max = std::numeric_limits<std::streamsize>::max();
    CharT bro = static_cast<CharT>(delimiters::get_1st(bis));
    CharT brc = static_cast<CharT>(delimiters::get_2nd(bis));
    CharT sep = static_cast<CharT>(separator::get(bis));
    Type val[9];

    if (bro)
        bis.ignore(max, bro);

    if (orientation::get(bis))
    {
        for (auto i=0; i < 9; ++i)
        {
            bis >> val[i];
            if (sep && i < 8)
                bis.ignore(max, sep);
        }
        if (brc)
            bis.ignore(max, brc);
    }
    else
    {
        for (auto i=0; i < 9; ++i)
        {
            bis >> val[i];
            if (i%3 == 2)
            {
                if (bro)
                {
                    bis.ignore(max, brc);
                    if (8 == i)
                        break;
                    bis.ignore(max, bro);
                }
                continue;
            }
            if (sep)
                bis.ignore(max, sep);
        }
    }

    if (bis)
    {
        if (order::get(bis) || orientation::get(bis) == 0)
            mtx.set_transpose(val);
        else
            mtx.set(val);
    }

    return bis;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \p bis after extracting from it.
/// \param bis the stream to extract from.
/// \param mtx the matrix44 type to extract.
/// \pre std::ios::skipws flag must be set.
/// \remarks
/// Extracts \p mtx from \p bis input stream. The default input must be
/// formatted such that matrix44<int> m {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}
/// appears as:
/// <pre>
/// 1 5 9 13
/// 2 6 10 14
/// 3 7 11 15
/// 4 8 12 16
/// </pre>
/// You can use the following stream manipulators to change the default
/// behavior:
/// \li mtl::vertical (default)
/// \li mtl::horizontal
/// \li mtl::separator (space)
/// \li mtl::delimiters (default none)
/// \li mtl::colmajor (default)
/// \li mtl::rowmajor
/// \par Example:
///
/// \snippet mtl_matrices.cpp matrix44 extractor
/// \a Input:
/// \include matrix44.txt

template<typename CharT, typename Traits, typename Type>
inline
std::basic_istream<CharT,Traits>&
operator >> (
    std::basic_istream<CharT,Traits>& bis,
    matrix44<Type>& mtx)
{
    constexpr auto max = std::numeric_limits<std::streamsize>::max();
    CharT bro = static_cast<CharT>(delimiters::get_1st(bis));
    CharT brc = static_cast<CharT>(delimiters::get_2nd(bis));
    CharT sep = static_cast<CharT>(separator::get(bis));
    Type val[16];

    if (bro)
        bis.ignore(max, bro);

    if (orientation::get(bis))
    {
        for (auto i=0; i < 16; ++i)
        {
            bis >> val[i];
            if (sep && i < 15)
                bis.ignore(max, sep);
        }
        if (brc)
            bis.ignore(max, brc);
    }
    else
    {
        for (auto i=0; i < 16; ++i)
        {
            bis >> val[i];
            if (i%4 == 3)
            {
                if (bro)
                {
                    bis.ignore(max, brc);
                    if (15 == i)
                        break;
                    bis.ignore(max, bro);
                }
                continue;
            }
            if (sep)
                bis.ignore(max, sep);
        }
    }

    if (bis)
    {
        if (order::get(bis) || orientation::get(bis) == 0)
            mtx.set_transpose(val);
        else
            mtx.set(val);
    }

    return bis;
}

/// @}
