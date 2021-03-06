// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014-2015 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

template <typename T>
covalent_radius_db<T>::covalent_radius_db()
{
    covalent_radii_ =
    {
//         Lp (Lone Pair)
        T(0.00),
//         H                                                                                                                                                                                                                                                                                      He
        T(0.32),                                                                                                                                                                                                                                                                               T(0.46),
//         Li       Be                                                                                                                                                                                                                               B        C        N        O        F        Ne
        T(1.33), T(1.02),                                                                                                                                                                                                                         T(0.85), T(0.75), T(0.71), T(0.63), T(0.64), T(0.67),
//         Na       Mg                                                                                                                                                                                                                               Al       Si       P        S        Cl       Ar
        T(1.55), T(1.39),                                                                                                                                                                                                                         T(1.26), T(1.16), T(1.11), T(1.03), T(0.99), T(0.96),
//         K        Ca                                                                                                                                     Sc       Ti       V        Cr       Mn       Fe       Co       Ni       Cu       Zn       Ga       Ge       As       Se       Br       Kr
        T(1.96), T(1.71),                                                                                                                               T(1.48), T(1.36), T(1.34), T(1.22), T(1.19), T(1.16), T(1.11), T(1.10), T(1.12), T(1.18), T(1.24), T(1.21), T(1.21), T(1.16), T(1.14), T(1.17),
//         Rb       Sr                                                                                                                                     Y        Zr       Nb       Mo       Tc       Ru       Rh       Pd       Ag       Cd       In       Sn       Sb       Te       I        Xe
        T(2.10), T(1.85),                                                                                                                               T(1.63), T(1.54), T(1.47), T(1.38), T(1.28), T(1.25), T(1.25), T(1.20), T(1.28), T(1.36), T(1.42), T(1.40), T(1.40), T(1.36), T(1.33), T(1.31),
//         Cs       Ba       La       Ce       Pr       Nd       Pm       Sm       Eu       Gd       Tb       Dy       Ho       Er       Tm       Yb       Lu       Hf       Ta       W        Re       Os       Ir       Pt       Au       Hg       Ti       Pb       Bi       Po       At       Rn
        T(2.32), T(1.96), T(1.80), T(1.63), T(1.76), T(1.74), T(1.73), T(1.72), T(1.68), T(1.69), T(1.68), T(1.67), T(1.66), T(1.65), T(1.64), T(1.70), T(1.62), T(1.52), T(1.46), T(1.37), T(1.31), T(1.29), T(1.22), T(1.23), T(1.24), T(1.33), T(1.44), T(1.44), T(1.51), T(1.45), T(1.47), T(1.42),
//         Fr       Ra       Ac       Th       Pa       U        Np       Pu       Am       Cm       Bk       Cf       Es       Fm       Md       No       Lr       Rf       Db       Sg       Bh       Hs       Mt       Ds       Rg       Cn       Utt      Fl       Uup      Lv       Uus      Uuo  
        T(2.23), T(2.01), T(1.86), T(1.75), T(1.69), T(1.70), T(1.71), T(1.72), T(1.66), T(1.66), T(1.68), T(1.68), T(1.65), T(1.67), T(1.73), T(1.76), T(1.61), T(1.57), T(1.49), T(1.43), T(1.41), T(1.34), T(1.29), T(1.28), T(1.21), T(1.22), T(1.36), T(1.43), T(1.62), T(1.75), T(1.65), T(1.57),
//         Xx  
        T(0.00)
    };
}
