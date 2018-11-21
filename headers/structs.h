#ifndef _STRUCTS_H
#define _STRUCTS_H

typedef struct btree
{
    int cost;
    int utility;
    struct btree* leftInversion;
    struct btree* rightInversion;
 
} btree;

typedef struct inv
{
    int initCapital;
    int availableInv;
    int* listInversion;

} inv;

#endif