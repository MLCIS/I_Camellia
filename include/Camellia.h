#include "basiclib.h"


#ifndef _CAMELLIA
    #define _CAMELLIA  OK

    typedef struct Camellia_block {
        Block   *       LEFT;
        Block   *      RIGHT;
        Block   *    primary;
        int               id;
        struct Camellia_block * next;
    }CBlock;

/*
 *  functions area
 *
 */
static Uchar S_BOX[256] =  {

    173,15,164,162,235,38,137,32,85,87,46,30,201,196,18,42,
    226,17,5,155,82,179,77,55,19,24,183,74,63,222,107,253,
    104,236,136,184,101,35,197,133,72,168,113,59,14,135,40,84,
    126,247,161,190,79,31,105,25,186,194,214,189,89,78,202,28,
    114,204,0,106,139,44,88,149,195,22,80,122,254,141,178,138,
    234,232,71,92,224,109,97,244,110,199,250,20,26,218,166,230,
    191,187,145,209,11,144,52,66,10,231,192,174,182,150,70,203,
    239,108,241,119,176,29,154,12,7,134,125,140,129,252,206,124,
    177,157,172,248,212,94,169,127,132,3,33,148,151,115,160,131,
    225,96,112,219,23,128,102,21,147,167,208,76,142,152,180,238,
    9,34,93,120,246,117,165,69,217,81,50,221,228,91,13,99,
    255,223,43,37,100,8,245,198,249,215,242,220,158,251,60,57,
    170,27,143,200,153,67,90,185,233,175,171,45,16,53,83,39,
    73,2,156,98,51,1,159,62,61,213,95,205,211,210,64,47,
    36,111,216,188,48,146,207,243,123,229,116,49,181,240,56,121,
    227,41,68,103,118,130,163,75,65,193,86,54,237,58,4,6,
};


/*
 * Camellia  main fucntion 
 * run this function to encript and  decript
 *
 * d_or_e == false  is encript ,true is to decirpt   ( false = 0 ,true = 1)
 *
 */
Block *
Camellia(Block * origin,Block * key_block ,Bool d_or_e);


Bool
F(Block *,Block*);

Bool
FL(Block * left,Block * key);

Bool
FL_1(Block * left,Block *key);


/*
*  the component of F
*/
Bool
_s(Block * left );

/**
* for log and debug
*/
Bool
Log_Cammellia_block(Block * b);

Bool
Log_block(Block * b);

Block *
key_gen(int n,Block *);

Bool
_h(Block * left );


Block *
new_Camellia_block(Block * primary);

Block*
M(Block *);

Bool
_single_Round(Block * key,Block * left,Block * right,lambda_2 func);

Block *
Key_A(Block * key);

#endif
