/*
 * The five fuctions are used to be called by MySet:
 *
 * LLRB_make_empty  : clean up all the nodes of a tree
 * LLRB_find        : find the node by its value
 * LLRB_insert      : insert a node in a tree
 * LLRB_delete      : remove a node from a tree
 * LLRB_print       : print the node
 * 
 */
#ifndef _LLRB_H
#define _LLRB_H

#include <stdio.h>
#include <stdlib.h>

typedef int Bool;

#define TRUE 1
#define FALSE 0

typedef int ValueType;

typedef struct TreeNode* Position;
typedef struct TreeNode* LLRBTree;

enum Color { Red = 0, Black };

struct TreeNode
{
    ValueType val;
    Position left;
    Position right;
    enum Color color;
};

Position LLRB_make_empty(LLRBTree t);

Position LLRB_find(LLRBTree t, ValueType val);

Position LLRB_insert(LLRBTree t, ValueType val);
Position LLRB_delete(LLRBTree t, ValueType val);

void LLRB_print(LLRBTree t);


static Position left_rotate(Position f);
static Position right_rotate(Position f);
static Bool is_red(Position p);
static void flip_color(Position f);

static Position LLRB_find_min(LLRBTree t);

static Position move_red_right(Position p);
static Position move_red_left(Position p);

static Position fix_up(Position p);

static Position LLRB_remove_max(LLRBTree t);
static Position LLRB_remove_min(LLRBTree t);

static Position LLRB_new_node(ValueType val);

static Position LLRB_insert_rec(LLRBTree t, ValueType val);
static Position LLRB_delete_rec(LLRBTree t, ValueType val);

#endif /* _LLRB_H */
