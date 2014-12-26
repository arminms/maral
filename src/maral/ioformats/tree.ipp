// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

////////////////////////////////////////////////////////////////////////////////
// Root

template <class Rt, class Md, class Mo, class Sm, class At>
void tree_format<Rt,Md,Mo,Sm,At>::do_print_root(
    std::ostream& out
,   const Rt* rt) const
{
    print_root_order(out, rt, has_component_ordered<Rt>());
    print_root_name(out, rt, has_component_named<Rt>());
    print_root_pos(out, rt, has_component_position<Rt>());
    if (!depth::get(out))
    {
        out << shallow << std::endl;
        for (auto node : *rt)
            out << node << std::endl;
        out << deep;
    }
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void tree_format<Rt,Md,Mo,Sm,At>::print_root_name(
    std::ostream& out
,   const Rt* rt
,   std::true_type) const
{
    //out << reinterpret_cast<component::named>(rt)->named();
    out << rt->name() << ' ';
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void tree_format<Rt,Md,Mo,Sm,At>::print_root_order(
    std::ostream& out
,   const Rt* rt
,   std::true_type) const
{
    out << rt->ordinal() << ". ";
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void tree_format<Rt,Md,Mo,Sm,At>::print_root_pos(
    std::ostream& out
,   const Rt* rt
,   std::true_type) const
{
    out << horizontal << rt->get_center();
}

////////////////////////////////////////////////////////////////////////////////
// Model

template <class Rt, class Md, class Mo, class Sm, class At>
void tree_format<Rt,Md,Mo,Sm,At>::do_print_model(
    std::ostream& out
,   const Md* md) const
{
    auto parent = md->parent();
    if (parent)
    {
        std::string trail = (parent->children()->back() == md)
                          ? "---\\"
                          : "---+";
        while (parent)
        {
            auto prev_parent = parent;
            parent = parent->parent();
            if (parent)
                trail += (parent->children()->back() == prev_parent)
                      ?  "    "
                      :  "   |";
        }
        boost::reverse(trail);
        out << trail;
    }
    print_model_order(out, md, has_component_ordered<Md>());
    print_model_name(out, md, has_component_named<Md>());
    print_model_pos(out, md, has_component_position<Md>());

    if (!depth::get(out))
    {
        out << shallow << std::endl;
        for (auto node : *md)
            out << node << std::endl;
        out << deep;
    }
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void tree_format<Rt,Md,Mo,Sm,At>::print_model_name(
    std::ostream& out
,   const Md* md
,   std::true_type) const
{
    out << md->name();
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void tree_format<Rt,Md,Mo,Sm,At>::print_model_order(
    std::ostream& out
,   const Md* md
,   std::true_type) const
{
    out << std::setw(2) << md->ordinal() << ". ";
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void tree_format<Rt,Md,Mo,Sm,At>::print_model_pos(
    std::ostream& out
,   const Md* md
,   std::true_type) const
{
    out << horizontal << md->get_center();
}

////////////////////////////////////////////////////////////////////////////////
// Molecule

template <class Rt, class Md, class Mo, class Sm, class At>
void tree_format<Rt,Md,Mo,Sm,At>::do_print_mol(
    std::ostream& out
,   const Mo* mo) const
{
    auto parent = mo->parent();
    if (parent)
    {
        std::string trail = (parent->children()->back() == mo)
                          ? "---\\"
                          : "---+";
        while (parent)
        {
            auto prev_parent = parent;
            parent = parent->parent();
            if (parent)
                trail += (parent->children()->back() == prev_parent)
                      ?  "    "
                      :  "   |";
        }
        boost::reverse(trail);
        out << trail;
    }
    print_mol_order(out, mo, has_component_ordered<Mo>());
    print_void_mol_name(out, mo, has_no_name_n_chain_id<Mo>());
    print_mol_chain_id(out, mo, has_chainid_not_name<Mo>());
    print_mol_name(out, mo, has_component_named<Mo>());
    print_mol_pos(out, mo, has_component_position<Mo>());

    if (!depth::get(out))
    {
        out << shallow << std::endl;
        for (auto node : *mo)
            out << node << std::endl;
        out << deep;
    }
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void tree_format<Rt,Md,Mo,Sm,At>::print_mol_name(
    std::ostream& out
,   const Mo* mo
,   std::true_type) const
{
    out << mo->name();
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void tree_format<Rt,Md,Mo,Sm,At>::print_mol_chain_id(
    std::ostream& out
,   const Mo* mo
,   std::true_type) const
{
    out << mo->chain_id();
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void tree_format<Rt,Md,Mo,Sm,At>::print_mol_order(
    std::ostream& out
,   const Mo* mo
,   std::true_type) const
{
    out << std::setw(2) << mo->ordinal() << ". ";
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void tree_format<Rt,Md,Mo,Sm,At>::print_mol_pos(
    std::ostream& out
,   const Mo* mo
,   std::true_type) const
{
    out << horizontal << ' ' << mo->get_center();
}

////////////////////////////////////////////////////////////////////////////////
// Submolecule

template <class Rt, class Md, class Mo, class Sm, class At>
void tree_format<Rt,Md,Mo,Sm,At>::do_print_submol(
    std::ostream& out
,   const Sm* sm) const
{
    auto parent = sm->parent();
    if (parent)
    {
        std::string trail = (parent->children()->back() == sm)
                          ? "---\\"
                          : "---+";
        while (parent)
        {
            auto prev_parent = parent;
            parent = parent->parent();
            if (parent)
                trail += (parent->children()->back() == prev_parent)
                      ?  "    "
                      :  "   |";
        }
        boost::reverse(trail);
        out << trail;
    }
    print_submol_order(out, sm, has_component_ordered<Sm>());
    print_submol_name(out, sm, has_component_named<Sm>());
    print_submol_pos(out, sm, has_component_position<Sm>());

    if (!depth::get(out))
    {
        out << shallow << std::endl;
        for (auto node : *sm)
            out << node << std::endl;
        out << deep;
    }
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void tree_format<Rt,Md,Mo,Sm,At>::print_submol_name(
    std::ostream& out
,   const Sm* sm
,   std::true_type) const
{
    out << sm->name();
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void tree_format<Rt,Md,Mo,Sm,At>::print_submol_order(
    std::ostream& out
,   const Sm* sm
,   std::true_type) const
{
    out << std::setw(3) << sm->ordinal() << ". ";
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void tree_format<Rt,Md,Mo,Sm,At>::print_submol_pos(
    std::ostream& out
,   const Sm* sm
,   std::true_type) const
{
    out << horizontal << ' ' << sm->get_center();
}

////////////////////////////////////////////////////////////////////////////////
// Atom

template <class Rt, class Md, class Mo, class Sm, class At>
void tree_format<Rt,Md,Mo,Sm,At>::do_print_atom(
    std::ostream& out
,   const At* at) const
{
    auto parent = at->parent();
    if (parent)
    {
        std::string trail = (parent->children()->back() == at)
                          ? "---\\"
                          : "---+";
        while (parent)
        {
            auto prev_parent = parent;
            parent = parent->parent();
            if (parent)
                trail += (parent->children()->back() == prev_parent)
                      ?  "    "
                      :  "   |";
        }
        boost::reverse(trail);
        out << trail;
    }
    print_atom_order(out, at, has_component_ordered<At>());
    print_atom_name(out, at, has_component_named<At>());
    print_atom_pos(out, at, has_component_position<At>());
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void tree_format<Rt,Md,Mo,Sm,At>::print_atom_name(
    std::ostream& out
,   const At* at
,   std::true_type) const
{
    out << std::setw(4) << at->name();
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void tree_format<Rt,Md,Mo,Sm,At>::print_atom_order(
    std::ostream& out
,   const At* at
,   std::true_type) const
{
    out << std::setw(5) << at->ordinal() << ". ";
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void tree_format<Rt,Md,Mo,Sm,At>::print_atom_pos(
    std::ostream& out
,   const At* at
,   std::true_type) const
{
    out << horizontal << ' ' << at->get_center();
}
