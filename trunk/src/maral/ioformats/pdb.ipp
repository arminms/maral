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
// Default constructor

template <class Rt, class Md, class Mo, class Sm, class At>
pdb_format<Rt, Md, Mo, Sm, At>::pdb_format()
:   io_format_base<Rt,Md,Mo,Sm,At>()
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

template <class Rt, class Md, class Mo, class Sm, class At>
void pdb_format<Rt, Md, Mo, Sm, At>::do_print_root(
    std::ostream& out
,   const Rt* rt) const
{
    auto pos = rt->template begin<Md>();
    auto md = (pos == rt->template end<Md>() ? nullptr : *pos);
    if (md)
        if (boost::distance(rt->template range<At>())
        ==  boost::distance(md->template range<At>()))
        {
            do_print_model(out, md);
            return;
        }
        else
            print_frames(out, rt, has_policy_coordinates<Rt>());
    else
        print_frames(out, rt, has_policy_coordinates<Rt>());
    out << "END" << std::string(77, ' ') << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt, Md, Mo, Sm, At>::print_root(
    std::ostream& out
,   const Rt* rt
,   std::size_t frame) const
{
    int ordinal = 1;
    bool has_std_res = false;
    for (auto at : rt->template range<At>())
    {
        Sm* sm = at->parent() ? dynamic_cast<Sm*>(at->parent()) : nullptr;
        Mo* mo = (sm && sm->parent())
               ? dynamic_cast<Mo*>(sm->parent()) : nullptr;
        print_atom(out, mo, sm, at, ordinal++, frame);
        out << std::endl;
        if (!has_std_res && sm && !is_het(sm, has_policy_named<Sm>()))
            has_std_res = true;
        if (mo &&  at == *(mo->template rbegin<At>()) && has_std_res)
        {
            print_chain_termination(out, mo, sm, ordinal++);
            has_std_res = false;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt, Md, Mo, Sm, At>::print_frames(
    std::ostream& out
,   const Rt* rt
,   std::true_type) const
{
    std::size_t frames_count = rt->frames_size();
    if (1 == frames_count)
        print_root(out, rt, 0);
    else
    {
        std::size_t start = frames::get_1st(out);
        std::size_t last = frames::get_2nd(out);
        std::size_t stride = frames::get_3rd(out);
        if (0 == start) ++start;
        if (last > frames_count || 0 == last) last = frames_count;
        if (0 == stride) stride = 1;
        frames_count = ((last - start) / stride) + 1;
        if (start) --start;

        if (frames_count > 1)
            out << "NUMMDL    "
                << std::left  << std::setw(4) << frames_count
                << std::right << std::string(66, ' ') << std::endl;
        for (std::size_t i = start, frame = 1; i < last; i += stride, ++frame)
        {
            if (frames_count > 1)
                out << "MODEL     "
                    << std::setw(4) << frame
                    << std::string(66, ' ') << std::endl;
            print_root(out, rt, i);
            if (frames_count > 1)
                out << "ENDMDL" << std::string(74, ' ') << std::endl;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt, Md, Mo, Sm, At>::print_frames(
    std::ostream& out
,   const Rt* rt
,   std::false_type) const
{
    print_root(out, rt, 0);
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt, Md, Mo, Sm, At>::print_chain_termination(
    std::ostream& out
,   const Mo* mo
,   const Sm* sm
,   int ordinal) const
{
    out << "TER   " << std::setw(5) << ordinal << "      ";
    print_submol_name(out, sm, has_policy_named<Sm>());
    out << ' ';
    if (mo)
        print_mol_chain_id(out, mo, has_policy_chainid<Mo>());
    print_submol_order(out, sm, has_policy_ordered<Sm>());
    print_submol_icode(out, sm, has_policy_icode<Sm>());
    out << std::string(53, ' ') << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
void pdb_format<Rt,Md,Mo,Sm,At>::do_scan_root(
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

template <class Rt, class Md, class Mo, class Sm, class At>
void pdb_format<Rt, Md, Mo, Sm, At>::do_print_model(
    std::ostream& out
,   const Md* md) const
{
    print_frames(out, md, has_policy_coordinates<Rt>());
    out << "END" << std::string(77, ' ') << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt, Md, Mo, Sm, At>::print_model(
    std::ostream& out
,   const Md* md
,   std::size_t frame) const
{
    int ordinal = 1;
    bool has_std_res = false;
    for (auto at : md->template range<At>())
    {
        Sm* sm = at->parent() ? dynamic_cast<Sm*>(at->parent()) : nullptr;
        Mo* mo = (sm && sm->parent())
               ? dynamic_cast<Mo*>(sm->parent()) : nullptr;
        print_atom(out, mo, sm, at, ordinal++, frame);
        out << std::endl;
        if (!has_std_res && sm && !is_het(sm, has_policy_named<Sm>()))
            has_std_res = true;
        if (mo && at == *(mo->template rbegin<At>()) && has_std_res)
        {
            print_chain_termination(out, mo, sm, ordinal++);
            has_std_res = false;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt, Md, Mo, Sm, At>::print_frames(
    std::ostream& out
,   const Md* md
,   std::true_type) const
{
    std::size_t frames_count = Rt::frames_size();
    if (1 == frames_count)
        print_model(out, md, 0);
    else
    {
        std::size_t start = frames::get_1st(out);
        std::size_t last = frames::get_2nd(out);
        std::size_t stride = frames::get_3rd(out);
        if (0 == start) ++start;
        if (last > frames_count || 0 == last) last = frames_count;
        if (0 == stride) stride = 1;
        frames_count = ((last - start) / stride) + 1;
        if (start) --start;

        if (frames_count > 1)
            out << "NUMMDL    "
                << std::left  << std::setw(4) << frames_count
                << std::right << std::string(66, ' ') << std::endl;
        for (std::size_t i = start, frame = 1; i < last; i += stride, ++frame)
        {
            if (frames_count > 1)
                out << "MODEL     "
                    << std::setw(4) << frame
                    << std::string(66, ' ') << std::endl;
            print_model(out, md, i);
            if (frames_count > 1)
                out << "ENDMDL" << std::string(74, ' ') << std::endl;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt, Md, Mo, Sm, At>::print_frames(
    std::ostream& out
,   const Md* md
,   std::false_type) const
{
    print_model(out, md, 0);
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
void pdb_format<Rt,Md,Mo,Sm,At>::do_scan_model(
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

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::scan_model(
    std::istream& in
,   std::string& line
,   Md* md) const
{
    std::size_t skip = get_skip(has_policy_coordinates<Rt>());
    do
    {
        scan_frame_number(line, has_policy_coordinates<Rt>());
        if (scan_coords(in, line, skip, has_policy_coordinates<Rt>()))
            break;

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
    level_coords(has_policy_coordinates<Rt>());
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::scan_frame_number(
    const std::string& line
,   std::true_type) const
{
    if (0 == line.compare(0, 6, "NUMMDL"))
        Rt::reserve_frames_size(std::stoi(line.substr(10, 4)));
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline bool pdb_format<Rt,Md,Mo,Sm,At>::scan_coords(
    std::istream& in
,   std::string& line
,   std::size_t skip
,   std::true_type) const
{
    if (0 == line.compare(0, 6, "MODEL "))
    {
        std::size_t frame = std::stoi(line.substr(10, 4));
        if (1 == frame)
        {
            if (Rt::frames_size() < frame)
                Rt::add_frame(1, skip, 99999);
        }
        else
        {
            //auto prev_size = Rt::coords_size();
            if (Rt::frames_size() < frame)
                Rt::add_frame(1, skip);
            while (getline(in, line))
            {
                if (0 == line.compare(0, 6, "ENDMDL"))
                {
                    break;
                }

                if (0 == line.compare(0, 5, "ATOM ")
                ||  0 == line.compare(0, 6, "HETATM"))
                {
                    typename std::remove_reference
                        <decltype(Rt::coord(0))>::type coord;
                    typedef typename std::remove_reference
                        <decltype(coord[0])>::type value_type;
                    std::string
                    value = line.substr(30, 8); boost::trim(value);
                    coord[0] = boost::lexical_cast<value_type>(value);
                    value = line.substr(38, 8); boost::trim(value);
                    coord[1] = boost::lexical_cast<value_type>(value);
                    value = line.substr(46, 8); boost::trim(value);
                    coord[2] = boost::lexical_cast<value_type>(value);
                    /* auto idx =*/ Rt::add_coord(coord, frame - 1);
                    //if (idx > prev_size)
                    //    std::cerr << "ERROR!" << std::endl;
                }
            }
        }
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline bool pdb_format<Rt,Md,Mo,Sm,At>::scan_coords(
    std::istream& in
,   std::string& line
,   std::size_t skip
,   std::false_type) const
{
    return line.compare(0, 6, "ENDMDL") == 0 ? true : false;
}

////////////////////////////////////////////////////////////////////////////////
// Molecule

template <class Rt, class Md, class Mo, class Sm, class At>
void pdb_format<Rt, Md, Mo, Sm, At>::do_print_mol(
    std::ostream& out
,   const Mo* mo) const
{
    print_frames(out, mo, has_policy_coordinates<Rt>());
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt, Md, Mo, Sm, At>::print_mol(
    std::ostream& out
,   const Mo* mo
,   std::size_t frame) const
{
    int ordinal = 1;
    bool has_std_res = false;
    Sm* sm = nullptr;
    for (auto at : mo->template range<At>())
    {
        sm = at->parent() ? dynamic_cast<Sm*>(at->parent()) : nullptr;
        print_atom(out, mo, sm, at, ordinal++, frame);
        out << std::endl;
        if (!has_std_res && sm && !is_het(sm, has_policy_named<Sm>()))
            has_std_res = true;
    }
    auto pos = mo->template rbegin<At>();
    auto at = (pos != mo->template rend<At>()) ? *pos : nullptr;
    if (at && has_std_res)
        print_chain_termination(out, mo, sm, ordinal++);
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt, Md, Mo, Sm, At>::print_frames(
    std::ostream& out
,   const Mo* mo
,   std::true_type) const
{
    std::size_t frames_count = Rt::frames_size();
    if (1 == frames_count)
        print_mol(out, mo, 0);
    else
    {
        std::size_t start = frames::get_1st(out);
        std::size_t last = frames::get_2nd(out);
        std::size_t stride = frames::get_3rd(out);
        if (0 == start) ++start;
        if (last > frames_count || 0 == last) last = frames_count;
        if (0 == stride) stride = 1;
        frames_count = ((last - start) / stride) + 1;
        if (start) --start;

        if (frames_count > 1)
            out << "NUMMDL    "
                << std::left  << std::setw(4) << frames_count
                << std::right << std::string(66, ' ') << std::endl;
        for (std::size_t i = start, frame = 1; i < last; i += stride, ++frame)
        {
            if (frames_count > 1)
                out << "MODEL     "
                    << std::setw(4) << frame
                    << std::string(66, ' ') << std::endl;
            print_mol(out, mo, i);
            if (frames_count > 1)
                out << "ENDMDL" << std::string(74, ' ') << std::endl;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt, Md, Mo, Sm, At>::print_frames(
    std::ostream& out
,   const Mo* mo
,   std::false_type) const
{
    print_mol(out, mo, 0);
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::print_mol_chain_id(
    std::ostream& out
,   const Mo* mo
,   std::true_type) const
{
    out << mo->get_chain_id();
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
void pdb_format<Rt,Md,Mo,Sm,At>::do_scan_mol(
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

template <class Rt, class Md, class Mo, class Sm, class At>
void pdb_format<Rt,Md,Mo,Sm,At>::scan_mol(
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

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::scan_chain_id(
    const std::string& line
,   Mo* mo
,   std::true_type) const
{
    mo->set_chain_id(line[21]);
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::set_mol_name(
    const std::string& name
,   Mo* mo
,   std::true_type) const
{
    mo->name(name);
}

////////////////////////////////////////////////////////////////////////////////
// Submolecule

template <class Rt, class Md, class Mo, class Sm, class At>
void pdb_format<Rt, Md, Mo, Sm, At>::do_print_submol(
    std::ostream& out
,   const Sm* sm) const
{
    print_frames(out, sm, has_policy_coordinates<Rt>());
}

////////////////////////////////////////////////////////////////////////////////
// Submolecule

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt, Md, Mo, Sm, At>::print_submol(
    std::ostream& out
,   const Sm* sm
,   std::size_t frame) const
{
    Mo* mo = (sm && sm->parent()) ? dynamic_cast<Mo*>(sm->parent()) : nullptr;
    int ordinal = 1;
    for (auto at : sm->template range<At>())
    {
        print_atom(out, mo, sm, at, ordinal++, frame);
        out << std::endl;
    }
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt, Md, Mo, Sm, At>::print_frames(
    std::ostream& out
,   const Sm* sm
,   std::true_type) const
{
    std::size_t frames_count = Rt::frames_size();
    if (1 == frames_count)
        print_submol(out, sm, 0);
    else
    {
        std::size_t start = frames::get_1st(out);
        std::size_t last = frames::get_2nd(out);
        std::size_t stride = frames::get_3rd(out);
        if (0 == start) ++start;
        if (last > frames_count || 0 == last) last = frames_count;
        if (0 == stride) stride = 1;
        frames_count = ((last - start) / stride) + 1;
        if (start) --start;

        if (frames_count > 1)
            out << "NUMMDL    "
                << std::left  << std::setw(4) << frames_count
                << std::right << std::string(66, ' ') << std::endl;
        for (std::size_t i = start, frame = 1; i < last; i += stride, ++frame)
        {
            if (frames_count > 1)
                out << "MODEL     "
                    << std::setw(4) << frame
                    << std::string(66, ' ') << std::endl;
            print_submol(out, sm, i);
            if (frames_count > 1)
                out << "ENDMDL" << std::string(74, ' ') << std::endl;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt, Md, Mo, Sm, At>::print_frames(
    std::ostream& out
,   const Sm* sm
,   std::false_type) const
{
    print_submol(out, sm, 0);
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::print_submol_name(
    std::ostream& out
,   const Sm* sm
,   std::true_type) const
{
    out << std::setw(3) << sm->name();
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::print_submol_order(
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

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::print_submol_order(
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

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::print_submol_icode(
    std::ostream& out
,   const Sm* sm
,   std::true_type) const
{
        out << sm->get_icode();
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
void pdb_format<Rt,Md,Mo,Sm,At>::do_scan_submol(
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

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::scan_submol(
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

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::scan_submol_name(
    const std::string& line
,   Sm* sm
,   std::true_type) const
{
    std::string res_name = line.substr(17, 3);
    boost::trim(res_name);
    sm->name(res_name);
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::scan_submol_order(
    const std::string& line
,   Sm* sm
,   std::true_type) const
{
    std::string res_seq = line.substr(22, 4);
    boost::trim(res_seq);
    sm->ordinal(boost::lexical_cast<decltype(sm->ordinal())>(res_seq));
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::scan_submol_icode(
    const std::string& line
,   Sm* sm
,   std::true_type) const
{
    sm->set_icode(line[26]);
}

////////////////////////////////////////////////////////////////////////////////
// Atom

template <class Rt, class Md, class Mo, class Sm, class At>
void pdb_format<Rt,Md,Mo,Sm,At>::do_print_atom(
    std::ostream& out
,   const At* at) const
{
    Sm* sm = at->parent() ? dynamic_cast<Sm*>(at->parent()) : nullptr;
    Mo* mo = (sm && sm->parent()) ? dynamic_cast<Mo*>(sm->parent()) : nullptr;
    print_frames(out, mo, sm, at, -1, has_policy_coordinates<Rt>());
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::print_atom(
    std::ostream& out
,   const Mo* mo
,   const Sm* sm
,   const At* at
,   int ordinal
,   std::size_t frame) const
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
    //print_atom_pos(out, at, has_policy_position<At>());
    print_atom_pos(out, at, frame, has_pos_or_lnk_pos<At>());
    out << std::setprecision(2);
    print_atom_occupancy(out, at, has_policy_occupancy<At>());
    print_atom_b_factor(out, at, has_policy_b_factor<At>());
    out << std::string(12, ' ');
    print_atom_formal_charge(out, at, has_policy_formal_charge<At>());
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt, Md, Mo, Sm, At>::print_frames(
    std::ostream& out
,   const Mo* mo
,   const Sm* sm
,   const At* at
,   int ordinal
,   std::true_type) const
{
    std::size_t frames_count = Rt::frames_size();
    if (1 == frames_count)
        print_atom(out, mo, sm, at, ordinal, 0);
    else
    {
        std::size_t start = frames::get_1st(out);
        std::size_t last = frames::get_2nd(out);
        std::size_t stride = frames::get_3rd(out);
        if (0 == start) ++start;
        if (last > frames_count || 0 == last) last = frames_count;
        if (0 == stride) stride = 1;
        frames_count = ((last - start) / stride) + 1;
        if (start) --start;
        unsigned reset = atomordinal::get(out);

        for (std::size_t i = start, frame = 1; i < last; i += stride, ++frame)
        {
            if (frames_count > 1)
                out << "MODEL     "
                << std::setw(4) << frame
                << std::string(66, ' ') << std::endl;
            print_atom(out, mo, sm, at, ordinal, i);
            if (frames_count > 1)
            {
                out << std::endl << "ENDMDL"
                    << std::string(74, ' ') << std::endl;
                if (i != last - 1)
                    atomordinal::set(out, reset);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt, Md, Mo, Sm, At>::print_frames(
    std::ostream& out
,   const Mo* mo
,   const Sm* sm
,   const At* at
,   int ordinal
,   std::false_type) const
{
    print_atom(out, mo, sm, at, ordinal, 0);
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::print_atom_name(
    std::ostream& out
,   const At* at
,   std::true_type) const
{
    out << std::setw(4) << at->name();
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::print_atom_order(
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

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::print_atom_order(
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

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::print_atom_pos(
    std::ostream& out
,   const At* at
,   std::size_t frame
,   std::true_type) const
{
    out << std::setw(8) << (*at)(0, frame)
        << std::setw(8) << (*at)(1, frame)
        << std::setw(8) << (*at)(2, frame);
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::print_atom_pos(
    std::ostream& out
,   const At* at
,   std::size_t frame
,   std::false_type) const
{
    out << "   0.000"
        << "   0.000"
        << "   0.000";
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::print_atom_occupancy(
    std::ostream& out
,   const At* at
,   std::true_type) const
{
    out << std::setw(6) << at->get_occupancy();
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::print_atom_b_factor(
    std::ostream& out
,   const At* at
,   std::true_type) const
{
    out << std::setw(6) << at->get_b_factor();
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::print_atom_formal_charge(
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

template <class Rt, class Md, class Mo, class Sm, class At>
void pdb_format<Rt,Md,Mo,Sm,At>::do_scan_atom(
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

template <class Rt, class Md, class Mo, class Sm, class At>
void pdb_format<Rt,Md,Mo,Sm,At>::scan_atom(
    std::istream& in
,   std::string& line
,   At* at) const
{
    scan_atom_name(line, at, has_policy_named<At>());
    try
    {
        scan_atom_order(in, at, has_policy_ordered<At>());
        scan_atom_pos(line, at, has_policy_position<At>());
        scan_atom_pos(line, at, has_policy_linked_position<At>());
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

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::scan_atom_name(
    const std::string& line
,   At* at
,   std::true_type) const
{
    at->name(line.substr(12, 4));
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::scan_atom_order(
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

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::scan_atom_order(
    std::istream& in
,   At* at
,   std::false_type) const
{
    unsigned ord = atomordinal::get(in);
    atomordinal::set(in, ++ord);
}

////////////////////////////////////////////////////////////////////////////////

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::scan_atom_pos(
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

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::scan_atom_occupancy(
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

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::scan_atom_b_factor(
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

template <class Rt, class Md, class Mo, class Sm, class At>
inline void pdb_format<Rt,Md,Mo,Sm,At>::scan_atom_formal_charge(
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
