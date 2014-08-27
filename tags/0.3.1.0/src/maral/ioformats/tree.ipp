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
//    tree.ipp
//------------------------------------------------------------------------------
// Remarks:
//    This file contains implementation of tree i/o format.
//------------------------------------------------------------------------------

template
<
    template <class,class,class,class,class> class Base
,   class Rt
,   class Md
,   class Mo
,   class Sm
,   class At
>
void tree_format<Base,Rt,Md,Mo,Sm,At>::do_print_root(
    std::ostream& out
,   const Rt* rt) const
{
    print_root_order(out, rt, has_member_ordinal<Rt>());
    print_root_name(out, rt, has_member_name<Rt>());
    print_root_pos(out, rt, has_member_position<Rt>());
}

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
inline void tree_format<Base,Rt,Md,Mo,Sm,At>::print_root_name(
    std::ostream& out
,   const Rt* rt
,   std::true_type) const
{
    //out << reinterpret_cast<policies::named>(rt)->named();
    out << rt->name() << ' ';
}

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
inline void tree_format<Base,Rt,Md,Mo,Sm,At>::print_root_order(
    std::ostream& out
,   const Rt* rt
,   std::true_type) const
{
    out << rt->ordinal() << ". ";
}

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
inline void tree_format<Base,Rt,Md,Mo,Sm,At>::print_root_pos(
    std::ostream& out
,   const Rt* rt
,   std::true_type) const
{
    out << mtl::horizontal
        << rt->get_center();
}

////////////////////////////////////////////////////////////////////////////////

