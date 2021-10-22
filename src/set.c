#include "set.h"

PToMySet init(void)
{
    PToMySet p_set = (PToMySet)malloc(sizeof(struct MySet));
    p_set->size = 0;
    p_set->tree = NULL;
    return p_set;
}

Bool empty(PToMySet p_set)
{
    return (size(p_set) ? TRUE : FALSE);
}

unsigned int size(PToMySet p_set)
{
    return p_set->size;
}

void clear(PToMySet p_set)
{
    p_set->size = 0;
    p_set->tree = LLRB_make_empty(p_set->tree);
}

void insert(PToMySet p_set, ValueType val)
{
    p_set->size++;
    p_set->tree = LLRB_insert(p_set->tree, val);
}

unsigned int erase(PToMySet p_set, ValueType val)
{
    if (count(p_set, val)) {
        p_set->tree = LLRB_delete(p_set->tree, val);
        p_set->size--;
        return 1;
    } else {
        return 0;
    }
}

unsigned int count(PToMySet p_set, ValueType val)
{
    return (LLRB_find(p_set->tree, val) ? 1 : 0);
}

void print(PToMySet s)
{
    LLRB_print(s->tree);
    printf("\n");
}