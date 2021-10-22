/*
 * I haven't learnt Cpp much about templet
 * so I use C to implement it.
 * 
 * The .h file provides 6 requested interfaces:
 * 
 * emply, size, clear, insert, erase, count.
 * 
 * They basically satisfy the requests.
 */

#ifndef _SET_H
#define _SET_H

#include "LLRB.h"

struct MySet {
    LLRBTree tree;
    unsigned int size;
};
typedef struct MySet* PToMySet;

PToMySet init(void);
Bool empty(PToMySet p_set);
unsigned int size(PToMySet p_set);
void clear(PToMySet p_set);
void insert(PToMySet p_set, ValueType val);
unsigned int erase(PToMySet p_set, ValueType val);
unsigned int count(PToMySet p_set, ValueType val);

void print(PToMySet p_set);

#endif /* _SET_H */
