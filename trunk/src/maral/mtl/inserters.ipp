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
//    mtl/inserters.ipp
//------------------------------------------------------------------------------
// Remarks:
//    This file contains implementation of all stream inserters for maral::mtl
//    classes.
//------------------------------------------------------------------------------

/// \ingroup Inserters
/// \name Stream Inserters
/// @{

////////////////////////////////////////////////////////////////////////////////
/// \return \p bos after it has been written to.
/// \param bos the stream to write to.
/// \param pnt the point2 type to insert.
/// \remarks
/// Inserts a string representation of \p pnt to \p bos output stream. The
/// default output is formatted such that point2<int>(1,2) will appear as:
/// <pre>
/// 1
/// 2
/// </pre>
/// You can use the following stream manipulators to change the default
/// behavior:
/// \li mtl::spaces
/// \li mtl::nospaces (default)
/// \li mtl::vertical (default)
/// \li mtl::horizontal
/// \li mtl::separator (default none)
/// \li mtl::setew (default = 0)
/// \li mtl::delimiters (default none)
/// \par Example:
///
/// \snippet mtl_points.cpp point2 inserter
/// \a Output:
/// \include pntvec2.txt

template<typename CharT, typename Traits, typename Type>
inline
std::basic_ostream<CharT,Traits>&
operator << (
    std::basic_ostream<CharT,Traits>& bos,
    const point2<Type>& pnt)
{
    CharT bro = static_cast<CharT>(delimiters::get_1st(bos));
    CharT brc = static_cast<CharT>(delimiters::get_2nd(bos));
    CharT sep = static_cast<CharT>(separator::get(bos));
    CharT spc = space::get(bos) ? bos.widen(' ') : 0;
    int ew = setew::get(bos);

    std::basic_ostringstream<CharT,Traits> str;
    str.copyfmt(bos);
    str.width(0);

    if (orientation::get(bos))
        str << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << pnt[0]
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << pnt[1]
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
    else    // vertical
    {
        auto w = bos.width();
        std::basic_ostringstream<CharT,Traits> row;
        row.copyfmt(str);

        row << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << pnt[0]
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
        str << std::setw(w) << row.str();
        str << std::endl;

        row.str(std::basic_string<CharT>());
        row << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << pnt[1]
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
        str << std::setw(w) << row.str();
    }

    bos << str.str();
    return bos;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \p bos after it has been written to.
/// \param bos the stream to write to.
/// \param vec the vector2 type to insert.
/// \remarks
/// Inserts a string representation of \p vec to \p bos output stream. The
/// default output is formatted such that vector2<int>(1,2) will appear as:
/// <pre>
/// 1
/// 2
/// </pre>
/// You can use the following stream manipulators to change the default
/// behavior:
/// \li mtl::spaces
/// \li mtl::nospaces (default)
/// \li mtl::vertical (default)
/// \li mtl::horizontal
/// \li mtl::separator (default none)
/// \li mtl::setew (default = 0)
/// \li mtl::delimiters (default none)
/// \par Example:
///
/// \snippet mtl_vectors.cpp vector2 inserter
/// \a Output:
/// \include pntvec2.txt

template<typename CharT, typename Traits, typename Type>
inline
std::basic_ostream<CharT,Traits>&
operator << (
    std::basic_ostream<CharT,Traits>& bos,
    const vector2<Type>& vec)
{
    CharT bro = static_cast<CharT>(delimiters::get_1st(bos));
    CharT brc = static_cast<CharT>(delimiters::get_2nd(bos));
    CharT sep = static_cast<CharT>(separator::get(bos));
    CharT spc = space::get(bos) ? bos.widen(' ') : 0;
    int ew = setew::get(bos);

    std::basic_ostringstream<CharT,Traits> str;
    str.copyfmt(bos);
    str.width(0);

    if (orientation::get(bos))
        str << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << vec[0]
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << vec[1]
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
    else    // vertical
    {
        auto w = bos.width();
        std::basic_ostringstream<CharT,Traits> row;
        row.copyfmt(str);

        row << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << vec[0]
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
        str << std::setw(w) << row.str();
        str << std::endl;

        row.str(std::basic_string<CharT>());
        row << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << vec[1]
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
        str << std::setw(w) << row.str();
    }

    bos << str.str();
    return bos;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \p bos after it has been written to.
/// \param bos the stream to write to.
/// \param pnt the point3 type to insert.
/// \remarks
/// Inserts a string representation of \p pnt to \p bos output stream. The
/// default output is formatted such that point3<int>(1,2,3) will appear as:
/// <pre>
/// 1
/// 2
/// 3
/// </pre>
/// You can use the following stream manipulators to change the default
/// behavior:
/// \li mtl::spaces
/// \li mtl::nospaces (default)
/// \li mtl::vertical (default)
/// \li mtl::horizontal
/// \li mtl::separator (default none)
/// \li mtl::setew (default = 0)
/// \li mtl::delimiters (default none)
/// \par Example:
///
/// \snippet mtl_points.cpp point3 inserter
/// \a Output:
/// \include pntvec3.txt

template<typename CharT, typename Traits, typename Type>
inline
std::basic_ostream<CharT,Traits>&
operator << (
    std::basic_ostream<CharT,Traits>& bos,
    const point3<Type>& pnt)
{
    CharT bro = static_cast<CharT>(delimiters::get_1st(bos));
    CharT brc = static_cast<CharT>(delimiters::get_2nd(bos));
    CharT sep = static_cast<CharT>(separator::get(bos));
    CharT spc = space::get(bos) ? bos.widen(' ') : 0;
    int ew = setew::get(bos);

    std::basic_ostringstream<CharT,Traits> str;
    str.copyfmt(bos);
    str.width(0);

    if (orientation::get(bos))
        str << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << pnt[0]
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << pnt[1]
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << pnt[2]
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
    else    // vertical
    {
        auto w = bos.width();
        std::basic_ostringstream<CharT,Traits> row;
        row.copyfmt(str);

        row << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << pnt[0]
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
        str << std::setw(w) << row.str();
        str << std::endl;

        row.str(std::basic_string<CharT>());
        row << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << pnt[1]
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
        str << std::setw(w) << row.str();
        str << std::endl;

        row.str(std::basic_string<CharT>());
        row << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << pnt[2]
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
        str << std::setw(w) << row.str();
    }

    bos << str.str();
    return bos;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \p bos after it has been written to.
/// \param bos the stream to write to.
/// \param vec the vector3 type to insert.
/// \remarks
/// Inserts a string representation of \p vec to \p bos output stream. The
/// default output is formatted such that vector3<int>(1,2,3) will appear as:
/// <pre>
/// 1
/// 2
/// 3
/// </pre>
/// You can use the following stream manipulators to change the default
/// behavior:
/// \li mtl::spaces
/// \li mtl::nospaces (default)
/// \li mtl::vertical (default)
/// \li mtl::horizontal
/// \li mtl::separator (default none)
/// \li mtl::setew (default = 0)
/// \li mtl::delimiters (default none)
/// \par Example:
///
/// \snippet mtl_vectors.cpp vector3 inserter
/// \a Output:
/// \include pntvec3.txt

template<typename CharT, typename Traits, typename Type>
inline
std::basic_ostream<CharT,Traits>&
operator << (
    std::basic_ostream<CharT,Traits>& bos,
    const vector3<Type>& vec)
{
    CharT bro = static_cast<CharT>(delimiters::get_1st(bos));
    CharT brc = static_cast<CharT>(delimiters::get_2nd(bos));
    CharT sep = static_cast<CharT>(separator::get(bos));
    CharT spc = space::get(bos) ? bos.widen(' ') : 0;
    int ew = setew::get(bos);

    std::basic_ostringstream<CharT,Traits> str;
    str.copyfmt(bos);
    str.width(0);

    if (orientation::get(bos))
        str << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << vec[0]
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << vec[1]
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << vec[2]
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
    else    // vertical
    {
        auto w = bos.width();
        std::basic_ostringstream<CharT,Traits> row;
        row.copyfmt(str);

        row << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << vec[0]
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
        str << std::setw(w) << row.str();
        str << std::endl;

        row.str(std::basic_string<CharT>());
        row << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << vec[1]
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
        str << std::setw(w) << row.str();
        str << std::endl;

        row.str(std::basic_string<CharT>());
        row << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << vec[2]
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
        str << std::setw(w) << row.str();
    }

    bos << str.str();
    return bos;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \p bos after it has been written to.
/// \param bos the stream to write to.
/// \param mtx the matrix22 type to insert.
/// \remarks
/// Inserts a string representation of \p mtx to \p bos output stream. The
/// default output is formatted such that matrix22<int> mtx {1,2,3,4} will
/// appear as:
/// <pre>
/// 13
/// 24
/// </pre>
/// Note that the default output lacks any separator between elements in a row,
/// which makes it hard to read and interpret. This can be changed using
/// mtl::separator manipulator. You can use the following stream manipulators to
/// change the default behavior:
/// \li mtl::spaces
/// \li mtl::nospaces (default)
/// \li mtl::vertical (default)
/// \li mtl::horizontal
/// \li mtl::separator (default none)
/// \li mtl::setew (default = 0)
/// \li mtl::delimiters (default none)
/// \li mtl::colmajor (default)
/// \li mtl::rowmajor
/// \par Example:
///
/// \snippet mtl_matrices.cpp matrix22 inserter
/// \a Output:
/// \include matrix22.txt

template<typename CharT, typename Traits, typename Type>
inline
std::basic_ostream<CharT,Traits>&
operator << (
    std::basic_ostream<CharT,Traits>& bos,
    const matrix22<Type>& mtx)
{
    CharT bro = static_cast<CharT>(delimiters::get_1st(bos));
    CharT brc = static_cast<CharT>(delimiters::get_2nd(bos));
    CharT sep = static_cast<CharT>(separator::get(bos));
    CharT spc = space::get(bos) ? bos.widen(' ') : 0;
    int ew = setew::get(bos);

    std::basic_ostringstream<CharT,Traits> str;
    str.copyfmt(bos);
    str.width(0);

    if (orientation::get(bos))
    {
        bool row_major = (0 != order::get(bos));
        str << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(0, 0)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << (row_major ? mtx(0, 1) : mtx(1, 0))
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)

            << std::setw(ew)
            << (row_major ? mtx(1, 0) : mtx(0, 1))
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(1, 1)
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
    }
    else    // vertical
    {
        auto w = bos.width();
        std::basic_ostringstream<CharT,Traits> row;
        row.copyfmt(str);

        row << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(0, 0)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(0, 1)
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
        str << std::setw(w) << row.str();
        str << std::endl;

        row.str(std::basic_string<CharT>());
        row << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(1, 0)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(1, 1)
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
        str << std::setw(w) << row.str();
    }

    bos << str.str();
    return bos;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \p bos after it has been written to.
/// \param bos the stream to write to.
/// \param mtx the matrix33 type to insert.
/// \remarks
/// Inserts a string representation of \p mtx to \p bos output stream. The
/// default output is formatted such that matrix33<int> mtx {1,2,3,4,5,6,7,8,9}
/// will appear as:
/// <pre>
/// 147
/// 258
/// 369
/// </pre>
/// Note that the default output lacks any separator between elements in a row,
/// which makes it hard to read and interpret. This can be changed using
/// mtl::separator manipulator. You can use the following stream manipulators to
/// change the default behavior:
/// \li mtl::spaces
/// \li mtl::nospaces (default)
/// \li mtl::vertical (default)
/// \li mtl::horizontal
/// \li mtl::separator (default none)
/// \li mtl::setew (default = 0)
/// \li mtl::delimiters (default none)
/// \li mtl::colmajor (default)
/// \li mtl::rowmajor
/// \par Example:
///
/// \snippet mtl_matrices.cpp matrix33 inserter
/// \a Output:
/// \include matrix33.txt

template<typename CharT, typename Traits, typename Type>
inline
std::basic_ostream<CharT,Traits>&
operator << (
    std::basic_ostream<CharT,Traits>& bos,
    const matrix33<Type>& mtx)
{
    CharT bro = static_cast<CharT>(delimiters::get_1st(bos));
    CharT brc = static_cast<CharT>(delimiters::get_2nd(bos));
    CharT sep = static_cast<CharT>(separator::get(bos));
    CharT spc = space::get(bos) ? bos.widen(' ') : 0;
    int ew = setew::get(bos);

    std::basic_ostringstream<CharT,Traits> str;
    str.copyfmt(bos);
    str.width(0);

    if (orientation::get(bos))
    {
        bool row_major = (0 != order::get(bos));
        str << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(0, 0)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << (row_major ? mtx(0, 1) : mtx(1, 0))
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << (row_major ? mtx(0, 2) : mtx(2, 0))
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)

            << std::setw(ew)
            << (row_major ? mtx(1, 0) : mtx(0, 1))
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(1, 1)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << (row_major ? mtx(1, 2) : mtx(2, 1))
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)

            << std::setw(ew)
            << (row_major ? mtx(2, 0) : mtx(0, 2))
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << (row_major ? mtx(2, 1) : mtx(1, 2))
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(2, 2)
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
    }
    else    // vertical
    {
        auto w = bos.width();
        std::basic_ostringstream<CharT,Traits> row;
        row.copyfmt(str);

        row << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(0, 0)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(0, 1)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(0, 2)
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
        str << std::setw(w) << row.str();
        str << std::endl;

        row.str(std::basic_string<CharT>());
        row << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(1, 0)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(1, 1)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(1, 2)
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
        str << std::setw(w) << row.str();
        str << std::endl;

        row.str(std::basic_string<CharT>());
        row << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(2, 0)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(2, 1)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(2, 2)
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
        str << std::setw(w) << row.str();
    }

    bos << str.str();
    return bos;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \p bos after it has been written to.
/// \param bos the stream to write to.
/// \param mtx the matrix44 type to insert.
/// \remarks
/// Inserts a string representation of \p mtx to \p bos output stream. The
/// default output is formatted such that
/// matrix44<int> mtx {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16} will appear as:
/// <pre>
/// 15913
/// 261014
/// 371115
/// 481216
/// </pre>
/// Note that the default output lacks any separator between elements in a row,
/// which makes it hard to read and interpret. This can be changed using
/// mtl::separator manipulator. You can use the following stream manipulators to
/// change the default behavior:
/// \li mtl::spaces
/// \li mtl::nospaces (default)
/// \li mtl::vertical (default)
/// \li mtl::horizontal
/// \li mtl::separator (default none)
/// \li mtl::setew (default = 0)
/// \li mtl::delimiters (default none)
/// \li mtl::colmajor (default)
/// \li mtl::rowmajor
/// \par Example:
///
/// \snippet mtl_matrices.cpp matrix44 inserter
/// \a Output:
/// \include matrix44.txt

template<typename CharT, typename Traits, typename Type>
inline
std::basic_ostream<CharT,Traits>&
operator << (
    std::basic_ostream<CharT,Traits>& bos,
    const matrix44<Type>& mtx)
{
    CharT bro = static_cast<CharT>(delimiters::get_1st(bos));
    CharT brc = static_cast<CharT>(delimiters::get_2nd(bos));
    CharT sep = static_cast<CharT>(separator::get(bos));
    CharT spc = space::get(bos) ? bos.widen(' ') : 0;
    int ew = setew::get(bos);

    std::basic_ostringstream<CharT,Traits> str;
    str.copyfmt(bos);
    str.width(0);

    if (orientation::get(bos))
    {
        bool row_major = (0 != order::get(bos));
        str << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(0, 0)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << (row_major ? mtx(0, 1) : mtx(1, 0))
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << (row_major ? mtx(0, 2) : mtx(2, 0))
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << (row_major ? mtx(0, 3) : mtx(3, 0))
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)

            << std::setw(ew)
            << (row_major ? mtx(1, 0) : mtx(0, 1))
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(1, 1)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << (row_major ? mtx(1, 2) : mtx(2, 1))
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << (row_major ? mtx(1, 3) : mtx(3, 1))
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)

            << std::setw(ew)
            << (row_major ? mtx(2, 0) : mtx(0, 2))
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << (row_major ? mtx(2, 1) : mtx(1, 2))
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(2, 2)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << (row_major ? mtx(2, 3) : mtx(3, 2))
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)

            << std::setw(ew)
            << (row_major ? mtx(3, 0) : mtx(0, 3))
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << (row_major ? mtx(3, 1) : mtx(1, 3))
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << (row_major ? mtx(3, 2) : mtx(2, 3))
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(3, 3)
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
    }
    else    // vertical
    {
        auto w = bos.width();
        std::basic_ostringstream<CharT,Traits> row;
        row.copyfmt(str);

        row << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(0, 0)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(0, 1)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(0, 2)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(0, 3)
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
        str << std::setw(w) << row.str();
        str << std::endl;

        row.str(std::basic_string<CharT>());
        row << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(1, 0)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(1, 1)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(1, 2)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(1, 3)
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
        str << std::setw(w) << row.str();
        str << std::endl;

        row.str(std::basic_string<CharT>());
        row << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(2, 0)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(2, 1)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(2, 2)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(2, 3)
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
        str << std::setw(w) << row.str();
        str << std::endl;

        row.str(std::basic_string<CharT>());
        row << skip_if_null<CharT>(bro)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(3, 0)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(3, 1)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(3, 2)
            << skip_if_null<CharT>(sep)
            << skip_if_null<CharT>(spc)
            << std::setw(ew)
            << mtx(3, 3)
            << skip_if_null<CharT>(spc)
            << skip_if_null<CharT>(brc);
        str << std::setw(w) << row.str();
    }

    bos << str.str();
    return bos;
}

/// @}
