// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014-2015 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

template <typename CharT>
chemical_symbols_db<CharT>::chemical_symbols_db()
:   map_(241)
{
    symbols_ = 
    {
        "Lp",   // Lone Pair
         "H",                                                                                                                                                                                    "He",
        "Li", "Be",                                                                                                                                                 "B",  "C",  "N",  "O",  "F", "Ne",
        "Na", "Mg",                                                                                                                                                "Al", "Si",  "P",  "S", "Cl", "Ar",
         "K", "Ca",                                                                                    "Sc", "Ti",  "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr",
        "Rb", "Sr",                                                                                     "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te",  "I", "Xe",
        "Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu", "Hf", "Ta",  "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Ti", "Pb", "Bi", "Po", "At", "Rn",
        "Fr", "Ra", "Ac", "Th", "Pa",  "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm", "Md", "No", "Lr", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg", "Cn","Utt", "Fl","Uup", "Lv","Uus","Uuo",
        "Xx"
    };

    map_.insert(
    {
        { "Lp",	  0 },{  "H",   1 },{ "He",   2 },{ "Li",   3 },{ "Be",   4 },
        {  "B",   5 },{  "C",   6 },{  "N",   7 },{  "O",   8 },{  "F",   9 },
        { "Ne",  10 },{ "Na",  11 },{ "Mg",  12 },{ "Al",  13 },{ "Si",  14 },
        {  "P",  15 },{  "S",  16 },{ "Cl",  17 },{ "Ar",  18 },{  "K",  19 },
        { "Ca",  20 },{ "Sc",  21 },{ "Ti",  22 },{  "V",  23 },{ "Cr",  24 },
        { "Mn",  25 },{ "Fe",  26 },{ "Co",  27 },{ "Ni",  28 },{ "Cu",  29 },
        { "Zn",  30 },{ "Ga",  31 },{ "Ge",  32 },{ "As",  33 },{ "Se",  34 },
        { "Br",  35 },{ "Kr",  36 },{ "Rb",  37 },{ "Sr",  38 },{  "Y",  39 },
        { "Zr",  40 },{ "Nb",  41 },{ "Mo",  42 },{ "Tc",  43 },{ "Ru",  44 },
        { "Rh",  45 },{ "Pd",  46 },{ "Ag",  47 },{ "Cd",  48 },{ "In",  49 },
        { "Sn",  50 },{ "Sb",  51 },{ "Te",  52 },{  "I",  53 },{ "Xe",  54 },
        { "Cs",  55 },{ "Ba",  56 },{ "La",  57 },{ "Ce",  58 },{ "Pr",  59 },
        { "Nd",  60 },{ "Pm",  61 },{ "Sm",  62 },{ "Eu",  63 },{ "Gd",  64 },
        { "Tb",  65 },{ "Dy",  66 },{ "Ho",  67 },{ "Er",  68 },{ "Tm",  69 },
        { "Yb",  70 },{ "Lu",  71 },{ "Hf",  72 },{ "Ta",  73 },{  "W",  74 },
        { "Re",  75 },{ "Os",  76 },{ "Ir",  77 },{ "Pt",  78 },{ "Au",  79 },
        { "Hg",  80 },{ "Ti",  81 },{ "Pb",  82 },{ "Bi",  83 },{ "Po",  84 },
        { "At",  85 },{ "Rn",  86 },{ "Fr",  87 },{ "Ra",  88 },{ "Ac",  89 },
        { "Th",  90 },{ "Pa",  91 },{ "U",   92 },{ "Np",  93 },{ "Pu",  94 },
        { "Am",  95 },{ "Cm",  96 },{ "Bk",  97 },{ "Cf",  98 },{ "Es",  99 },
        { "Fm", 100 },{ "Md", 101 },{ "No", 102 },{ "Lr", 103 },{ "Rf", 104 },
        { "Db", 105 },{ "Sg", 106 },{ "Bh", 107 },{ "Hs", 108 },{ "Mt", 109 },
        { "Ds", 110 },{ "Rg", 111 },{ "Cn", 112 },{"Utt", 113 },{ "Fl", 114 },
        {"Uup", 115 },{ "Lv", 116 },{"Uus", 117 },{"Uuo", 118 },{ "Xx", 119 },
        // all caps
        { "LP",	  0 },{  "H",   1 },{ "HE",   2 },{ "LI",   3 },{ "BE",   4 },
        {  "B",   5 },{  "C",   6 },{  "N",   7 },{  "O",   8 },{  "F",   9 },
        { "NE",  10 },{ "NA",  11 },{ "MG",  12 },{ "AL",  13 },{ "SI",  14 },
        {  "P",  15 },{  "S",  16 },{ "CL",  17 },{ "AR",  18 },{  "K",  19 },
        { "CA",  20 },{ "SC",  21 },{ "TI",  22 },{  "V",  23 },{ "CR",  24 },
        { "MN",  25 },{ "FE",  26 },{ "CO",  27 },{ "NI",  28 },{ "CU",  29 },
        { "ZN",  30 },{ "GA",  31 },{ "GE",  32 },{ "AS",  33 },{ "SE",  34 },
        { "BR",  35 },{ "KR",  36 },{ "RB",  37 },{ "SR",  38 },{  "Y",  39 },
        { "ZR",  40 },{ "NB",  41 },{ "MO",  42 },{ "TC",  43 },{ "RU",  44 },
        { "RH",  45 },{ "PD",  46 },{ "AG",  47 },{ "CD",  48 },{ "IN",  49 },
        { "SN",  50 },{ "SB",  51 },{ "TE",  52 },{  "I",  53 },{ "XE",  54 },
        { "CS",  55 },{ "BA",  56 },{ "LA",  57 },{ "CE",  58 },{ "PR",  59 },
        { "ND",  60 },{ "PM",  61 },{ "SM",  62 },{ "EU",  63 },{ "GD",  64 },
        { "TB",  65 },{ "DY",  66 },{ "HO",  67 },{ "ER",  68 },{ "TM",  69 },
        { "YB",  70 },{ "LU",  71 },{ "HF",  72 },{ "TA",  73 },{  "W",  74 },
        { "RE",  75 },{ "OS",  76 },{ "IR",  77 },{ "PT",  78 },{ "AU",  79 },
        { "HG",  80 },{ "TI",  81 },{ "PB",  82 },{ "BI",  83 },{ "PO",  84 },
        { "AT",  85 },{ "RN",  86 },{ "FR",  87 },{ "RA",  88 },{ "AC",  89 },
        { "TH",  90 },{ "PA",  91 },{ "U",   92 },{ "NP",  93 },{ "PU",  94 },
        { "AM",  95 },{ "CM",  96 },{ "BK",  97 },{ "CF",  98 },{ "ES",  99 },
        { "FM", 100 },{ "MD", 101 },{ "NO", 102 },{ "LR", 103 },{ "RF", 104 },
        { "DB", 105 },{ "SG", 106 },{ "BH", 107 },{ "HS", 108 },{ "MT", 109 },
        { "DS", 110 },{ "RG", 111 },{ "CN", 112 },{"UTT", 113 },{ "FL", 114 },
        {"UUP", 115 },{ "LV", 116 },{"UUS", 117 },{"UUO", 118 },{ "XX", 119 }
    } );

    //std::cout << map_.size() << std::endl;
    //std::cout << map_.max_size() << std::endl;

    //for (auto elem = map_.begin(); elem != map_.end(); ++elem)
        //std::cout << elem->first.capacity() << std::endl;
    //for (std::pair<const std::basic_string<CharT>, unsigned>& elem : map_)
    //    elem.first.shrink_to_fit();
}
