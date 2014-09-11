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
// Default constructor

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
pdb_format<Base, Rt, Md, Mo, Sm, At>::pdb_format()
:   Base<Rt,Md,Mo,Sm,At>()
,   std_residues_(53)
{
    // based on: http://www.rcsb.org/pdb/static.do?p=file_formats/pdb/index.html

    std_residues_.insert(
    {
        // amino acids
        "ALA", "ARG", "ASN", "ASP", "ASX", "CYS", "GLN", "GLU", "GLX", "GLY",
        "HIS", "ILE", "LEU", "LYS", "MET", "PHE", "PRO", "SER", "THR", "TRP",
        "TYR", "UNK", "VAL",
        "CYH", "CSH", "CSH", "CSS", "CYX",  // cystein synonyms
        "ILU", "PRZ", "TRY,"    // isoleucine, proline and tryptphan synonyms
        "ACE", "NME",
        // nucleic acids
        "A", "+A", "C", "+C", "G", "+G", "I", "+I", "T", "+T", "U", "+U",
        "DA", "DC", "DG", "DT"
    } );
}

////////////////////////////////////////////////////////////////////////////////
// Root

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
void pdb_format<Base, Rt, Md, Mo, Sm, At>::do_print_root(
std::ostream& out
, const Rt* rt) const
{
    //if (1 == rt->children()->size()
    //&&  1 == boost::distance(rt->range<Md>()))
    //{
    //    out << *(rt->begin<Md>());
    //    return;
    //}

    int ordinal = 1;
    auto spos = rt->begin<Sm>();
    Sm* prev_sm = (spos == rt->end<Sm>()) ? nullptr : *spos;
    auto mpos = rt->begin<Mo>();
    Mo* prev_mo = (mpos == rt->end<Mo>()) ? nullptr : *mpos;
    for (auto at : rt->range<At>())
    {
        Sm* sm = at->parent() ? dynamic_cast<Sm*>(at->parent()) : nullptr;
        Mo* mo = (sm && sm->parent())
               ? dynamic_cast<Mo*>(sm->parent()) : nullptr;
        if (prev_mo && prev_mo != mo)
            if (prev_sm && !is_het(prev_sm, has_policy_named<Sm>()))
                print_chain_termination(out, prev_mo, prev_sm, ordinal++);
        print_atom(out, mo, sm, at, ordinal++);
        out << std::endl;
         prev_mo = mo; prev_sm = sm;
    }
    if (prev_sm && !is_het(prev_sm, has_policy_named<Sm>()))
        print_chain_termination(out, prev_mo, prev_sm, ordinal++);
    out << "END" << std::string(77, ' ') << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base, Rt, Md, Mo, Sm, At>::print_chain_termination(
std::ostream& out
, const Mo* mo
, const Sm* sm
, int ordinal) const
{
    out << "TER   " << std::setw(5) << ordinal << "      ";
    print_submol_name(out, sm, has_policy_named<Sm>());
    out << ' ';
    if (mo)
        print_mol_chain_id(out, mo, has_policy_chainid<Mo>());
    print_submol_order(out, sm, has_policy_ordered<Sm>());
    // iCode later...
    out << std::string(54, ' ') << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

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
                              , has_policy_named<Md>());
            else
                set_model_name("PDB", model.get(), has_policy_named<Md>());
            scan_model(in, line, model.get());
            rt->add(std::move(model));
            break;
        }

        if ("ATOM  " == record_name || "HETATM" == record_name)
        {
            if (' ' == line[21])
            {
                auto model = make_node<Md>();
                set_model_name("PDB", model.get(), has_policy_named<Md>());
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
}

////////////////////////////////////////////////////////////////////////////////
// Model

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
void pdb_format<Base, Rt, Md, Mo, Sm, At>::do_print_model(
std::ostream& out
, const Md* md) const
{
    int ordinal = 1;
    auto spos = md->begin<Sm>();
    Sm* prev_sm = (spos == md->end<Sm>()) ? nullptr : *spos;
    auto mpos = md->begin<Mo>();
    Mo* prev_mo = (mpos == md->end<Mo>()) ? nullptr : *mpos;
    for (auto at : md->range<At>())
    {
        Sm* sm = at->parent() ? dynamic_cast<Sm*>(at->parent()) : nullptr;
        Mo* mo = (sm && sm->parent())
               ? dynamic_cast<Mo*>(sm->parent()) : nullptr;
        if (prev_mo && prev_mo != mo)
            if (prev_sm && !is_het(prev_sm, has_policy_named<Sm>()))
                print_chain_termination(out, prev_mo, prev_sm, ordinal++);
        print_atom(out, mo, sm, at, ordinal++);
        out << std::endl;
         prev_mo = mo; prev_sm = sm;
    }
    if (prev_sm && !is_het(prev_sm, has_policy_named<Sm>()))
        print_chain_termination(out, prev_mo, prev_sm, ordinal++);
    out << "END" << std::string(77, ' ') << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
void pdb_format<Base,Rt,Md,Mo,Sm,At>::do_scan_model(
    std::istream& in
,   Md* md) const
{
    std::string line;
    while (getline(in, line))
    {
        std::string record_name = line.substr(0, 6);
        if ("HEADER" == record_name)
        {
            if (line.length() >= 64)
                set_model_name( line.substr(62, 4), md
                              , has_policy_named<Md>());
            else
                set_model_name("PDB", md, has_policy_named<Md>());
        }
        else
            set_model_name("PDB", md, has_policy_named<Md>());
        scan_model(in, line, md);
    }
}

////////////////////////////////////////////////////////////////////////////////

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
    do
    {
        std::string record_name = line.substr(0, 6);
        if ("ATOM  " == record_name || "HETATM" == record_name)
        {
            if (line.length() < 54) continue;
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
                    do
                    {
                        auto submol = make_node<Sm>();
                        scan_submol(in, line, submol.get());
                        md->add(std::move(submol));
                        record_name = line.substr(0, 6);
                    }   while ( "ATOM  " == record_name
                             || "HETATM" == record_name);
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
                }   while ("HETATM" == record_name);
            }
        }
    } while (getline(in, line));
}

////////////////////////////////////////////////////////////////////////////////
// Molecule

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
void pdb_format<Base, Rt, Md, Mo, Sm, At>::do_print_mol(
std::ostream& out
, const Mo* mo) const
{
    int ordinal = 1;
    At* at = nullptr;
    for (auto atm : mo->range<At>())
    {
        at = atm;
        print_atom(out, mo, at, ordinal++);
        out << std::endl;
    }
    if (at)
    {
        Sm* sm = at->parent() ? dynamic_cast<Sm*>(at->parent()) : nullptr;
        if (sm && !is_het(sm, has_policy_named<Sm>()))
            print_chain_termination(out, mo, sm, ordinal++);
    }
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::print_mol_chain_id(
    std::ostream& out
,   const Mo* mo
,   std::true_type) const
{
    out << mo->chain_id();
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
void pdb_format<Base,Rt,Md,Mo,Sm,At>::do_scan_mol(
    std::istream& in
,   Mo* mo) const
{
    std::string line;
    while (getline(in, line))
    {
        std::string record_name = line.substr(0, 6);
        if ("ATOM  " == record_name || "HETATM" == record_name)
        {
            if (line.length() < 21) continue;
            scan_mol(in, line, mo);
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

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
    scan_chain_id(line, mo, has_policy_chainid<Mo>());
    set_mol_name(line.substr(21, 1), mo, has_policy_named<Mo>());
    do
    {
        std::string record_name = line.substr(0, 6);
        if ("ATOM  " == record_name || "HETATM" == record_name)
        {
            if (line.length() < 54) continue;
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
                }   while (( "ATOM  " == record_name
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
// Submolecule

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
void pdb_format<Base, Rt, Md, Mo, Sm, At>::do_print_submol(
std::ostream& out
, const Sm* sm) const
{
    Mo* mo = (sm && sm->parent()) ? dynamic_cast<Mo*>(sm->parent()) : nullptr;
    int ordinal = 1;
    for (auto at : sm->range<At>())
        print_atom(out, mo, sm, at, ordinal++);
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::print_submol_name(
    std::ostream& out
,   const Sm* sm
,   std::true_type) const
{
    out << std::setw(3) << sm->name();
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::print_submol_order(
    std::ostream& out
,   const Sm* sm
,   std::true_type) const
{
    out << std::setw(4) << sm->ordinal();
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
void pdb_format<Base,Rt,Md,Mo,Sm,At>::do_scan_submol(
    std::istream& in
,   Sm* sm) const
{
    std::string line;
    while (getline(in, line))
    {
        std::string record_name = line.substr(0, 6);
        if ("ATOM  " == record_name || "HETATM" == record_name)
        {
            if (line.length() < 22) continue;
            scan_submol(in, line, sm);
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

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
    std::string res_seq = line.substr(22, 5);
    if ("     " == res_seq)
        return;
    scan_submol_name(line, sm, has_policy_named<Sm>());
    try
    {
        scan_submol_order(line, sm, has_policy_ordered<Sm>());
    }
    catch (const boost::bad_lexical_cast &)
    {
        std::cerr << "PDB syntax error > " << line << '<' << std::endl;
    }
    do
    {
        std::string record_name = line.substr(0, 6);
        if ("ATOM  " == record_name || "HETATM" == record_name)
        {
            if (line.length() < 54) continue;
            if (line[21] != chain)
                break;
            if (res_seq == line.substr(22, 5))
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
    std::string res_name = line.substr(17, 3);
    boost::trim(res_name);
    sm->name(res_name);
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
// Atom

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
void pdb_format<Base,Rt,Md,Mo,Sm,At>::do_print_atom(
    std::ostream& out
,   const At* at) const
{
    Sm* sm = at->parent() ? dynamic_cast<Sm*>(at->parent()) : nullptr;
    Mo* mo = (sm && sm->parent()) ? dynamic_cast<Mo*>(sm->parent()) : nullptr;
    print_atom(out, mo, sm, at);
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::print_atom(
    std::ostream& out
,   const Mo* mo
,   const At* at
,   int ordinal) const
{
    Sm* sm = at->parent() ? dynamic_cast<Sm*>(at->parent()) : nullptr;
    print_atom(out, mo, sm, at, ordinal);
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::print_atom(
    std::ostream& out
,   const Mo* mo
,   const Sm* sm
,   const At* at
,   int ordinal) const
{
    if (sm)
        if (is_het(sm, has_policy_named<Sm>()))
            out << "HETATM";
        else
            out << "ATOM  ";
    else
        out << "HETATM";

    if (-1 == ordinal)
        print_atom_order(out, at, has_policy_ordered<At>());
    else
        out << std::setw(5) << ordinal;

    out << ' ';
    print_atom_name(out, at, has_policy_named<At>());
    out << ' ';

    if (sm)
        print_submol_name(out, sm, has_policy_named<Sm>());
    else
        out << "   ";

    out << ' ';
    if (mo)
        print_mol_chain_id(out, mo, has_policy_chainid<Mo>());
    else
        out << ' ';

    if (sm)
        print_submol_order(out, sm, has_policy_ordered<Sm>());
    else
        out << "    ";

    out << "    ";
    print_atom_pos(out, at, has_policy_position<At>());
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::print_atom_name(
    std::ostream& out
,   const At* at
,   std::true_type) const
{
    out << std::setw(4) << at->name();
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::print_atom_order(
    std::ostream& out
,   const At* at
,   std::true_type) const
{
    out << std::setw(5) << at->ordinal();
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::print_atom_pos(
    std::ostream& out
,   const At* at
,   std::true_type) const
{
    out << std::fixed << std::setprecision(3)
        << std::setw(8) << (*at)[0]
        << std::setw(8) << (*at)[1]
        << std::setw(8) << (*at)[2];
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::print_atom_pos(
    std::ostream& out
,   const At* at
,   std::false_type) const
{
    out << "   0.000"
        << "   0.000"
        << "   0.000";
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
void pdb_format<Base,Rt,Md,Mo,Sm,At>::do_scan_atom(
    std::istream& in
,   At* at) const
{
    std::string line;
    while (getline(in, line))
    {
        std::string record_name = line.substr(0, 6);
        if ("ATOM  " == record_name || "HETATM" == record_name)
        {
            scan_atom_name(line, at, has_policy_named<At>());
            try
            {
                scan_atom_order(line, at, has_policy_ordered<At>());
                scan_atom_pos(line, at, has_policy_position<At>());
            }
            catch (const boost::bad_lexical_cast &)
            {
                std::cerr << "PDB syntax error > " << line  << '<'
                          << std::endl;
            }
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

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
    scan_atom_name(line, at, has_policy_named<At>());
    try
    {
        scan_atom_order(line, at, has_policy_ordered<At>());
        scan_atom_pos(line, at, has_policy_position<At>());
    }
    catch (const boost::bad_lexical_cast &)
    {
        std::cerr << "PDB syntax error > " << line  << '<' << std::endl;
    }
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
