#ifndef _STRUCTS_H
#define _STRUCTS_H
typedef struct invHistory
{
    int capital;
    int utility;
    int length;
    int* details;
} invHistory;


typedef struct btree
{
    int status;
    int level;
    int currentCost;
    int currentUtility;
    int cost;
    int utility;
    struct btree* previousInversion;
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