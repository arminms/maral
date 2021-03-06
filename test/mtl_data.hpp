// $Id$
//------------------------------------------------------------------------------

//#define PATTERNS_FOLDER "../../../patterns/"
#define PATTERNS_FOLDER "patterns/"

// Ref: Snyder L.C., Basch H. Molecular wave functions and properties:
// tabulated form SCF calculation in a Guassian basis set, John Wiley & Sons,
// p T-74, 1972
//
// Layout:
// [0]  C1       H6
// [3]  C2       |
// [6]  H1  H5 - C2 - H4
// [9]  H2       |
// [12] H3  H2 - C1 - H3
// [15] H4       |
// [18] H5       H1
// [21] H6

#define DEFINE_ETHYL T ETHYL[] = \
{ \
    0.00000000f,  0.00000000f,  0.00000000f, \
    0.00000000f,  0.00000000f,  2.91589999f, \
    1.69855762f, -0.98066292f, -0.69996772f, \
   -1.69855762f, -0.98066792f, -0.69996772f, \
    0.00000000f,  1.96132584f, -0.69996772f, \
    1.69855762f,  0.98066292f,  3.61586168f, \
    0.00000000f, -1.96132579f,  3.61586168f, \
   -1.69855762f,  0.98066292f,  3.61586168f, \
}; \

/*
T COMPERR[] =
{
    1.0E+5f,
    1.0e-10f,
    1.0e-9f,
};

T SRC1[16] =
{
    1, 2, 3, 4,
    5, 6, 7, 8,
    9,-4,-3,-2,
   -1, 0, 1, 2
};

T SRC2[16] =
{
    7,  2, 3, -3,
    5, -1, 7,  8,
    0, -4, 3, -2,
    1,  0, 1, -5
};

T ADD[16] =
{
    8,  4,  6,  1,
   10,  5, 14, 16,
    9, -8,  0, -4,
    0,  0,  2, -3
};

T SUB[16] =
{
   -6, 0,  0, 7,
    0, 7,  0, 0,
    9, 0, -6, 0,
   -2, 0,  0, 7
};

T MULT[16] =
{
    47,  14,  23,  32,
    55, -24,  -5,  14,
     9, -36, -39, -42,
    15,  -2,  -5,  -8
};

T TRANS[16] =
{
    7,  5,  0,  1,
    2, -1, -4,  0,
    3,  7,  3,  1,
   -3,  8, -2, -5
};
*/
