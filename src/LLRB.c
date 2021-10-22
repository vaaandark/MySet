#include "LLRB.h"

static Position left_rotate(Position f)
{
    Position new_father = f->right;
    f->right = new_father->left;
    new_father->left = f;
    new_father->color = f->color;
    f->color = Red;
    return new_father;
}

static Position right_rotate(Position f)
{
    Position new_father = f->left;
    f->left = new_father->right;
    new_father->right = f;
    new_father->color = f->color;
    f->color = Red;
    return new_father;
}

static Bool is_red(Position p)
{
    if (!p) {
        return FALSE;
    }
    return (p->color == Red);
}

static void flip_color(Position f)
{
    f->color = !f->color;
    f->left->color = !f->left->color;
    f->right->color = !f->right->color;
}

Position LLRB_make_empty(LLRBTree t)
{
    if (t) {
        t->left = LLRB_make_empty(t->left);
        t->right = LLRB_make_empty(t->right);
        free(t);
        return NULL;
    }
}

Position LLRB_find(LLRBTree t, ValueType val)
{
    if (!t) {
        return NULL;
    }
    if (val < t->val) {
        return LLRB_find(t->left, val);
    } else if (val > t->val) {
        return LLRB_find(t->right, val);
    } else {
        return t;
    }
}

static Position LLRB_find_min(LLRBTree t)
{
    if (!t) {
        return NULL;
    }
    while (t->left) {
        t = t->left;
    }
    return t;
}

static Position move_red_right(Position p)
{
    if (!p) {
        return NULL;
    }
    flip_color(p);
    if (p->left && is_red(p->left->left)) {
        p = right_rotate(p);
        flip_color(p);
    }
    return p;
}

static Position move_red_left(Position p)
{
    if (!p) {
        return NULL;
    }
    flip_color(p);
    if (p->right && is_red(p->right->left)) {
        p->right = right_rotate(p->right); /* generate a 4-node */
        p = left_rotate(p);                /* two red-links in a line */
        flip_color(p);                   /* split the 4-node */
    }
    return p;
}

Position fix_up(Position p)
{
    if (!is_red(p->left) && is_red(p->right)) {
        p = left_rotate(p);
    }

    if (is_red(p->left) && is_red(p->left->left)) {
        p = right_rotate(p);
    }

    if (is_red(p->left) && is_red(p->right)) {
        flip_color(p);
    }

    return p;
}

Position LLRB_remove_max(LLRBTree t)
{
    if (!t) {
        return NULL;
    }
    if (!t->right) {
        free(t);
        return NULL;
    } /* already the max or the tree is empty */

    /* find a red-link and move it down the right spine */
    if (is_red(t->left)) {
        t = right_rotate(t);
    }
    if (!is_red(t->right) && !is_red(t->right->left)) {
        t = move_red_right(t);
    }

    t->right = LLRB_remove_max(t->right);

    /* fix up on the way back */
    return fix_up(t);
}

Position LLRB_remove_min(LLRBTree t)
{
    if (!t) {
        return NULL;
    }

    if (!t->left) {
        free(t);
        return NULL;
    }

    if (!is_red(t->left) && !is_red(t->left->left)) {
        t = move_red_left(t);
    }

    t->left = LLRB_remove_min(t->left);

    return fix_up(t);
}

static Position LLRB_new_node(ValueType val)
{
    Position new_node = (Position)malloc(sizeof(struct TreeNode));
    if (!new_node) {
        return NULL;
    }
    new_node->val = val;
    new_node->color = Red;
    new_node->left = new_node->right = NULL;
    return new_node;
}

Position LLRB_insert(LLRBTree t, ValueType val)
{
    t = LLRB_insert_rec(t, val);
    t->color = Black;
    return t;
}

static Position LLRB_insert_rec(LLRBTree t, ValueType val)
{
    if (!t) {
        return LLRB_new_node(val);
    }

    if (val < t->val) {
        t->left = LLRB_insert_rec(t->left, val);
    } else if (val > t->val) {
        t->right = LLRB_insert_rec(t->right, val);
    }

    if (is_red(t->right) && !is_red(t->left)) {
        t = left_rotate(t);
    }

    if (t->left && t->left->left && is_red(t->left) && is_red(t->left->left)) {
        t = right_rotate(t);
    }

    if (t->left && t->right && is_red(t->left) && is_red(t->right)) {
        flip_color(t);
    }

    return t;
}

Position LLRB_delete(LLRBTree t, ValueType val)
{
    t = LLRB_delete_rec(t, val);
    if (t) {
        t->color = Black;
    }
    return t;
}

static Position LLRB_delete_rec(LLRBTree t, ValueType val)
{
    if (!t) {
        return NULL;
    }
    if (val < t->val) {
        if (t->left) {
            if (!is_red(t->left) && !is_red(t->left->left)) {
                t = move_red_left(t);
            }
            t->left = LLRB_delete_rec(t->left, val);
        }
    } else {
        if (is_red(t->left)) {
            t = right_rotate(t);
        }
        if (val == t->val && !t->right) {
            free(t);
            return NULL;
        }
        if (t->right) {
            if (!is_red(t->right) && !is_red(t->right->left)) {
                t = move_red_right(t);
            }
            if (val == t->val) {
                t->val = (LLRB_find_min(t->right))->val;
                t->right = LLRB_remove_min(t->right);
            } else {
                t->right = LLRB_delete_rec(t->right, val);
            }
        }
    }
    return fix_up(t);
}

// void p(LLRBTree t)
// {
//     if (!t) {
//         return;
//     }
//     printf("%d是头节点\n", t->val);
//     LLRB_print(t);
//     printf("\n");
// }

void LLRB_print(LLRBTree t)
{
    if (!t) {
        return;
    } else {
        LLRB_print(t->left);
        // printf("%d(%s) ", t->val, t->color == Red ? "Red" : "Black");
        printf("%d ", t->val);
        LLRB_print(t->right);
    }
}