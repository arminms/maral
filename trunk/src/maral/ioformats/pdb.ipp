// Boost.Maral library (Molecular Architecture Recording & Assembly Library)
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

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
void pdb_format<Base,Rt,Md,Mo,Sm,At>::do_scan_root(
    std::istream& in
,   Rt* rt) const
{
    std::string line;
    while (getline(in, line))
    {
        std::string record_name = line.substr(0, 6);

        if ("HEADER" == record_name)
        {
            auto model = make_node<Md>();
            if (line.length() >= 64)
                set_model_name( line.substr(62, 4), model.get()
                              , has_member_name<Md>());
            else
                set_model_name("PDB", model.get(), has_member_name<Md>());
            scan_model(in, line, model.get());
            rt->add(std::move(model));
            break;
        }

        if ("ATOM  " == record_name || "HETATM" == record_name)
        {
            if (' ' == line[21])
            {
                auto model = make_node<Md>();
                set_model_name("PDB", model.get(), has_member_name<Md>());
                scan_model(in, line, model.get());
                rt->add(std::move(model));
            }
            else
            {
                auto mol = make_node<Mo>();
                scan_mol(in, line, mol.get());
                rt->add(std::move(mol));
            }
        }
    }
    //if (!in) rt->children()->clear();
}

////////////////////////////////////////////////////////////////////////////////

//template
//<
//    template <class,class,class,class,class> class Base
//,   class Rt, class Md, class Mo, class Sm, class At
//>
//inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::print_root_name(
//    std::ostream& out
//,   const Rt* rt
//,   std::true_type) const
//{
//    //out << reinterpret_cast<policy::named>(rt)->named();
//    out << rt->name() << ' ';
//}

////////////////////////////////////////////////////////////////////////////////

//template
//<
//    template <class,class,class,class,class> class Base
//,   class Rt, class Md, class Mo, class Sm, class At
//>
//inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::print_root_order(
//    std::ostream& out
//,   const Rt* rt
//,   std::true_type) const
//{
//    out << rt->ordinal() << ". ";
//}

////////////////////////////////////////////////////////////////////////////////

//template
//<
//    template <class,class,class,class,class> class Base
//,   class Rt, class Md, class Mo, class Sm, class At
//>
//inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::print_root_pos(
//    std::ostream& out
//,   const Rt* rt
//,   std::true_type) const
//{
//    out << horizontal << rt->get_center();
//}

////////////////////////////////////////////////////////////////////////////////
// Model

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
void pdb_format<Base,Rt,Md,Mo,Sm,At>::scan_model(
    std::istream& in
,   std::string& line
,   Md* md) const
{
    while (getline(in, line))
    {
        std::string record_name = line.substr(0, 6);
        if ("ATOM  " == record_name || "HETATM" == record_name)
        {
            if (line[21] == ' ')
            {
                if ("   " == line.substr(17, 3))
                {
                    auto atm = make_node<At>();
                    scan_atom(in, line, atm.get());
                    md->add(std::move(atm));
                }
                else
                {
                    auto submol = make_node<Sm>();
                    scan_submol(in, line, submol.get());
                    md->add(std::move(submol));
                }
            }
            else
            {
                do
                {
                    auto mol = make_node<Mo>();
                    scan_mol(in, line, mol.get());
                    md->add(std::move(mol));
                    record_name = line.substr(0, 6);
                } while ("HETATM" == record_name);
            }
        }
    }
    //if (!in) md->remove_all();
}

////////////////////////////////////////////////////////////////////////////////

//template
//<
//    template <class,class,class,class,class> class Base
//,   class Rt, class Md, class Mo, class Sm, class At
//>
//inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::print_model_order(
//    std::ostream& out
//,   const Md* md
//,   std::true_type) const
//{
//    out << std::setw(2) << md->ordinal() << ". ";
//}

////////////////////////////////////////////////////////////////////////////////

//template
//<
//    template <class,class,class,class,class> class Base
//,   class Rt, class Md, class Mo, class Sm, class At
//>
//inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::print_model_pos(
//    std::ostream& out
//,   const Md* md
//,   std::true_type) const
//{
//    out << horizontal << md->get_center();
//}

////////////////////////////////////////////////////////////////////////////////
// Molecule

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
void pdb_format<Base,Rt,Md,Mo,Sm,At>::scan_mol(
    std::istream& in
,   std::string& line
,   Mo* mo) const
{
    char chain = line[21];
    scan_chain_id(line, mo, has_member_chain_id<Mo>());
    do
    {
        std::string record_name = line.substr(0, 6);
        if ("ATOM  " == record_name || "HETATM" == record_name)
        {
            if ("   " == line.substr(17, 3))
            {
                auto atm = make_node<At>();
                scan_atom(in, line, atm.get());
                mo->add(std::move(atm));
            }
            else
            {
                do
                {
                    auto submol = make_node<Sm>();
                    scan_submol(in, line, submol.get());
                    mo->add(std::move(submol));
                    record_name = line.substr(0, 6);
                } while (( "ATOM  " == record_name
                        || "HETATM" == record_name)
                        && line[21] == chain);
            }
            if (line[21] != chain)
                break;
        }
        if ("TER   " == record_name)
            break;
    } while (getline(in, line));
    //if (!in) mo->remove_all();
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::scan_chain_id(
    const std::string& line
,   Mo* mo
,   std::true_type) const
{
    mo->chain_id(line[21]);
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::set_mol_name(
    const std::string& name
,   Mo* mo
,   std::true_type) const
{
    mo->name(name);
}

////////////////////////////////////////////////////////////////////////////////

//template
//<
//    template <class,class,class,class,class> class Base
//,   class Rt, class Md, class Mo, class Sm, class At
//>
//inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::print_mol_order(
//    std::ostream& out
//,   const Mo* mo
//,   std::true_type) const
//{
//    out << std::setw(2) << mo->ordinal() << ". ";
//}

////////////////////////////////////////////////////////////////////////////////

//template
//<
//    template <class,class,class,class,class> class Base
//,   class Rt, class Md, class Mo, class Sm, class At
//>
//inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::print_mol_pos(
//    std::ostream& out
//,   const Mo* mo
//,   std::true_type) const
//{
//    out << horizontal << ' ' << mo->get_center();
//}

////////////////////////////////////////////////////////////////////////////////
// Submolecule

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
void pdb_format<Base,Rt,Md,Mo,Sm,At>::scan_submol(
    std::istream& in
,   std::string& line
,   Sm* sm) const
{
    char chain = line[21];
    std::string res_seq = line.substr(22, 4);

    scan_submol_name(line, sm, has_member_name<Sm>());
    scan_submol_order(line, sm, has_member_ordinal<Sm>());
    do
    {
        std::string record_name = line.substr(0, 6);
        if ("ATOM  " == record_name || "HETATM" == record_name)
        {
            if (line[21] != chain)
                break;
            if (res_seq == line.substr(22, 4))
            {
                auto atm = make_node<At>();
                scan_atom(in, line, atm.get());
                sm->add(std::move(atm));
            }
            else
                break;
        }
        else if ("ANISOU" == record_name)
            continue;
        else
            break;
    } while (getline(in, line));
    //if (!in) sm->remove_all();
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::scan_submol_name(
    const std::string& line
,   Sm* sm
,   std::true_type) const
{
    sm->name(line.substr(17, 3));
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::scan_submol_order(
    const std::string& line
,   Sm* sm
,   std::true_type) const
{
    std::string res_seq = line.substr(22, 4);
    boost::trim(res_seq);
    sm->ordinal(boost::lexical_cast<decltype(sm->ordinal())>(res_seq));
}

////////////////////////////////////////////////////////////////////////////////

//template
//<
//    template <class,class,class,class,class> class Base
//,   class Rt, class Md, class Mo, class Sm, class At
//>
//inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::print_submol_pos(
//    std::ostream& out
//,   const Sm* sm
//,   std::true_type) const
//{
//    out << horizontal << ' ' << sm->get_center();
//}

////////////////////////////////////////////////////////////////////////////////
// Atom

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
void pdb_format<Base,Rt,Md,Mo,Sm,At>::scan_atom(
    std::istream& in
,   std::string& line
,   At* at) const
{
    scan_atom_order(line, at, has_member_ordinal<At>());
    scan_atom_name(line, at, has_member_name<At>());
    scan_atom_pos(line, at, has_member_position<At>());
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::scan_atom_name(
    const std::string& line
,   At* at
,   std::true_type) const
{
    at->name(line.substr(12, 4));
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::scan_atom_order(
    const std::string& line
,   At* at
,   std::true_type) const
{
    std::string serial = line.substr(6, 5);
    boost::trim(serial);
    //typedef decltype(std::declval<At>().ordinal()) ordinal_type;
    at->ordinal(boost::lexical_cast<decltype(at->ordinal())>(serial));
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::scan_atom_pos(
    const std::string& line
,   At* at
,   std::true_type) const
{
    typedef typename std::remove_reference<decltype((*at)[0])>::type coord_type;
    std::string
    coord = line.substr(30, 8); boost::trim(coord);
    (*at)[0] = boost::lexical_cast<coord_type>(coord);
    coord = line.substr(38, 8); boost::trim(coord);
    (*at)[1] = boost::lexical_cast<coord_type>(coord);
    coord = line.substr(46, 8); boost::trim(coord);
    (*at)[2] = boost::lexical_cast<coord_type>(coord);
}
