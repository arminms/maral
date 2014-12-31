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
    auto spos = rt->template begin<Sm>();
    Sm* prev_sm = (spos == rt->template end<Sm>()) ? nullptr : *spos;
    auto mpos = rt->template begin<Mo>();
    Mo* prev_mo = (mpos == rt->template end<Mo>()) ? nullptr : *mpos;
    for (auto at : rt->template range<At>())
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
        if (0 == line.compare(0, 6, "HEADER"))
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

        if (0 == line.compare(0, 5, "ATOM ")
        ||  0 == line.compare(0, 6, "HETATM"))
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
    auto spos = md->template begin<Sm>();
    Sm* prev_sm = (spos == md->template end<Sm>()) ? nullptr : *spos;
    auto mpos = md->template begin<Mo>();
    Mo* prev_mo = (mpos == md->template end<Mo>()) ? nullptr : *mpos;
    for (auto at : md->template range<At>())
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
        if (0 == line.compare(0, 6, "HEADER"))
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
        if ( 0 == line.compare(0, 5, "ATOM ")
        ||   0 == line.compare(0, 6, "HETATM") )
        {
            if (line.length() < 54) continue;
            if (line[21] == ' ')
            {
                if (0 == line.compare(17, 3, "   "))
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
                    }   while (0 == line.compare(0, 5, "ATOM ")
                        ||     0 == line.compare(0, 6, "HETATM"));
                }
            }
            else
            {
                do
                {
                    auto mol = make_node<Mo>();
                    scan_mol(in, line, mol.get());
                    md->add(std::move(mol));
                }   while (0 == line.compare(0, 6, "HETATM"));
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
    for (auto atm : mo->template range<At>())
    {
        at = atm;
        print_atom(out, mo, at, ordinal++);
        out << std::endl;
    }
    //for (auto at : mo->template range<At>())
    //{
    //    print_atom(out, mo, at, ordinal++);
    //    out << std::endl;
    //}
    //auto pos = mo->template rbegin<At>();
    //auto at = (pos != mo->template rend<At>()) ? *pos : nullptr;
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
    out << mo->get_chain_id();
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
        if (0 == line.compare(0, 5, "ATOM ")
        ||  0 == line.compare(0, 6, "HETATM"))
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
        if (0 == line.compare(0, 5, "ATOM ")
        ||  0 == line.compare(0, 6, "HETATM"))
        {
            if (line.length() < 54) continue;
            if (0 == line.compare(17, 3, "   "))
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
                }   while ((0 == line.compare(0, 5, "ATOM ")
                    ||      0 == line.compare(0, 6, "HETATM"))
                    &&      line[21] == chain);
            }
            if (line[21] != chain)
                break;
        }
        if (0 == line.compare(0, 3, "TER"))
            break;
    } while (getline(in, line));
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
    mo->set_chain_id(line[21]);
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
    for (auto at : sm->template range<At>())
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
    out << std::setw(4);
    if (sm->ordinal() < 10000)
        out << sm->ordinal();
    else if (sm->ordinal() < 0x10000)
        out << std::uppercase << std::hex << sm->ordinal() << std::dec;
    else
        out << "****";
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
,   std::false_type) const
{
    unsigned ordinal = submolordinal::get(out);
    out << std::setw(4);
    if (++ordinal < 10000)
        out << ordinal;
    else if (ordinal < 0x10000)
        out << std::uppercase << std::hex << ordinal << std::dec;
    else
        out << "****";
    submolordinal::set(out, ordinal);
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::print_submol_icode(
    std::ostream& out
,   const Sm* sm
,   std::true_type) const
{
        out << sm->get_icode();
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
        if (0 == line.compare(0, 5, "ATOM ")
        ||  0 == line.compare(0, 6, "HETATM"))
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
    scan_submol_icode(line, sm, has_policy_icode<Sm>());
    do
    {
        if (0 == line.compare(0, 5, "ATOM ")
        ||  0 == line.compare(0, 6, "HETATM"))
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
        else if (0 == line.compare(0, 6, "ANISOU")
             ||  0 == line.compare(0, 6, "SIGUIJ")
             ||  0 == line.compare(0, 6, "SIGATM"))
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

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::scan_submol_icode(
    const std::string& line
,   Sm* sm
,   std::true_type) const
{
    sm->set_icode(line[26]);
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

    out << std::setw(5);
    if (-1 == ordinal)
        print_atom_order(out, at, has_policy_ordered<At>());
    else
    {
        if (ordinal < 100000)
            out << ordinal;
        else if (ordinal < 0x100000)
            out << std::uppercase << std::hex << ordinal << std::dec;
        else
            out << "*****";
    }

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
    {
        print_submol_order(out, sm, has_policy_ordered<Sm>());
        print_submol_icode(out, sm, has_policy_icode<Sm>());
    }
    else
        out << "     ";

    out << "   " << std::fixed << std::setprecision(3);
    print_atom_pos(out, at, has_policy_position<At>());
    out << std::setprecision(2);
    print_atom_occupancy(out, at, has_policy_occupancy<At>());
    print_atom_b_factor(out, at, has_policy_b_factor<At>());
    out << std::string(12, ' ');
    print_atom_formal_charge(out, at, has_policy_formal_charge<At>());
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
    if (at->ordinal() < 100000)
        out << at->ordinal();
    else if (at->ordinal() < 0x100000)
        out << std::uppercase << std::hex << at->ordinal() << std::dec;
    else
        out << "*****";
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
,   std::false_type) const
{
    unsigned ordinal = atomordinal::get(out);
    if (++ordinal < 100000)
        out << ordinal;
    else if (ordinal < 0x100000)
        out << std::uppercase << std::hex << ordinal << std::dec;
    else
        out << "*****";
    atomordinal::set(out, ordinal);
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
    out << std::setw(8) << (*at)[0]
        << std::setw(8) << (*at)[1]
        << std::setw(8) << (*at)[2];
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::print_atom_occupancy(
    std::ostream& out
,   const At* at
,   std::true_type) const
{
    out << std::setw(6) << at->get_occupancy();
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::print_atom_b_factor(
    std::ostream& out
,   const At* at
,   std::true_type) const
{
    out << std::setw(6) << at->get_b_factor();
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::print_atom_formal_charge(
    std::ostream& out
,   const At* at
,   std::true_type) const
{
    if (0 == at->get_formal_charge())
        out << "  ";
    else
    {
        std::ostringstream tmp;
        tmp << std::showpos << int(at->get_formal_charge());
        std::string chg = tmp.str();
        boost::reverse(chg);
        out << std::setw(2) << chg;
    }
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
        if (0 == line.compare(0, 5, "ATOM ")
        ||  0 == line.compare(0, 6, "HETATM"))
        {
            scan_atom(in, line, at);
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
        scan_atom_order(in, at, has_policy_ordered<At>());
        scan_atom_pos(line, at, has_policy_position<At>());
        scan_atom_occupancy(line, at, has_policy_occupancy<At>());
        scan_atom_b_factor(line, at, has_policy_b_factor<At>());
        scan_atom_formal_charge(line, at, has_policy_formal_charge<At>());
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
    std::istream& in
,   At* at
,   std::true_type) const
{
    decltype(at->ordinal()) ord =
        (decltype(at->ordinal()))atomordinal::get(in);
    at->ordinal(++ord);
    atomordinal::set(in, ord);
    // following lines can be commented out in case of CONECT processing...
    //
    //std::string serial = line.substr(6, 5);
    //boost::trim(serial);
    //at->ordinal(boost::lexical_cast<decltype(at->ordinal())>(serial));
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::scan_atom_order(
    std::istream& in
,   At* at
,   std::false_type) const
{
    unsigned ord = atomordinal::get(in);
    atomordinal::set(in, ++ord);
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

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::scan_atom_occupancy(
    const std::string& line
,   At* at
,   std::true_type) const
{
    if (line.length() > 59)
    {
        std::string occ = line.substr(54, 6); boost::trim(occ);
        at->set_occupancy(
            boost::lexical_cast<decltype(at->get_occupancy())>(occ));
    }
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::scan_atom_b_factor(
    const std::string& line
,   At* at
,   std::true_type) const
{
    if (line.length() > 65)
    {
        std::string bf = line.substr(60, 6); boost::trim(bf);
        at->set_b_factor(
            boost::lexical_cast<decltype(at->get_b_factor())>(bf));
    }
}

////////////////////////////////////////////////////////////////////////////////

template
<
    template <class,class,class,class,class> class Base
,   class Rt, class Md, class Mo, class Sm, class At
>
inline void pdb_format<Base,Rt,Md,Mo,Sm,At>::scan_atom_formal_charge(
    const std::string& line
,   At* at
,   std::true_type) const
{
    if (line.length() > 79)
        if (0 != line.compare(78, 2, "  "))
        {
            std::string chg = line.substr(78, 2);
            boost::reverse(chg);
            at->set_formal_charge(std::stoi(chg));
        }
}