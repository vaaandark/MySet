#ifndef _LLRB_H
#define _LLRB_H

#include <cstddef>
#include <iostream>

enum Color { Red = 0, Black };
Color reverseColor(Color color) {
    if (color == Black) {
        return Red;
    } else {
        return Black;
    }
}

template <typename KeyType>
class Set {
private:
    struct TreeNode {
        KeyType key;
        TreeNode *left = nullptr;
        TreeNode *right = nullptr;
        Color color;
    };

    TreeNode *root = nullptr;
    size_t tree_size = 0;

    bool isRed(const TreeNode *node) const {
        return (node && node->color == Red);
    }

    void colorFlip(TreeNode *p) const;
    TreeNode *rotateLeft(TreeNode *f) const;
    TreeNode *rotateRight(TreeNode *f) const;
    TreeNode *clearTree(TreeNode *p) const;
    TreeNode *findNode(TreeNode *p, KeyType key) const;
    TreeNode *findMin(TreeNode *p) const;
    TreeNode *moveRedRight(TreeNode *f) const;
    TreeNode *moveRedLeft(TreeNode *f) const;
    TreeNode *fixUp(TreeNode *p) const;
    TreeNode *removeMin(TreeNode *t) const;
    TreeNode *newNode(KeyType key) const;
    TreeNode *insertRec(TreeNode *t, KeyType key);
    TreeNode *eraseRec(TreeNode *t, KeyType key);
    void printNode(TreeNode *p) const;


public:
    ~Set() {
        clearTree(this->root);
    }

    bool empty() const { return (tree_size == 0); }

    size_t size() const { return this->tree_size; }

    void clear() { clearTree(this); }

    void insert(const KeyType& key) {
        this->root = insertRec(this->root, key);
        this->root->color = Black;
        this->tree_size++;
    }

    size_t erase(const KeyType& key) {
        if (findNode(this->root, key) == nullptr) {
            return 0;
        }
        this->root = eraseRec(this->root, key);
        if (this->root) {
            this->root->color = Black;
        }
        this->tree_size--;
        return 1;
    }

    size_t count(const KeyType& key) {
        if (findNode(this->root, key)) {
            return 1;
        } else {
            return 0;
        }
    }

    void printTree() {
        if (root) {
            printNode(root);
        }
        std::cout << std::endl;
    }

};


template <typename KeyType>
void Set<KeyType>::colorFlip(TreeNode *p) const {
    p->color = reverseColor(p->color);
    p->left->color = reverseColor(p->left->color);
    p->right->color = reverseColor(p->right->color);
}

template <typename KeyType>
typename Set<KeyType>::TreeNode *Set<KeyType>::rotateLeft(TreeNode *f) const {
    TreeNode *new_father = f->right;
    f->right = new_father->left;
    new_father->left = f;
    new_father->color = f->color;
    f->color = Red;
    return new_father;
}

template <typename KeyType>
typename Set<KeyType>::TreeNode *Set<KeyType>::rotateRight(TreeNode *f) const {
    TreeNode *new_father = f->left;
    f->left = new_father->right;
    new_father->right = f;
    new_father->color = f->color;
    f->color = Red;
    return new_father;
}

template <typename KeyType>
typename Set<KeyType>::TreeNode *Set<KeyType>::clearTree(TreeNode *p_t) const {
    if (p_t) {
        p_t->left = clearTree(p_t->left);
        p_t->right = clearTree(p_t->right);
        delete p_t;
        return nullptr;
    } else {
        return nullptr;
    }
}

template <typename KeyType>
typename Set<KeyType>::TreeNode *Set<KeyType>::findNode(TreeNode *p, KeyType key) const {
    if (!p) {
        return nullptr;
    }
    if (key < p->key) {
        return findNode(p->left, key);
    } else if (key > p->key) {
        return findNode(p->right, key);
    } else {
        return p;
    }
}

template <typename KeyType>
typename Set<KeyType>::TreeNode *Set<KeyType>::findMin(TreeNode *p) const {
    if (!p) {
        return nullptr;
    }
    while (p->left) {
        p = p->left;
    }
    return p;
}

template <typename KeyType>
typename Set<KeyType>::TreeNode *Set<KeyType>::moveRedRight(TreeNode *p) const {
    colorFlip(p);
    if (p->left && isRed(p->left->left)) {
        p = rotateRight(p);
        colorFlip(p);
    }
    return p;
}

template <typename KeyType>
typename Set<KeyType>::TreeNode *Set<KeyType>::moveRedLeft(TreeNode *p) const {
    colorFlip(p);
    if (p->right && isRed(p->right->left)) {
        p->right = rotateRight(p->right); /* generate a 4-node */
        p = rotateLeft(p);                /* two red-links in a line */
        colorFlip(p);                   /* split the 4-node */
    }
    return p;
}

template <typename KeyType>
typename Set<KeyType>::TreeNode *Set<KeyType>::fixUp(TreeNode* p) const {
    if (!isRed(p->left) && isRed(p->right)) {
        p = rotateLeft(p);
    }

    if (isRed(p->left) && isRed(p->left->left)) {
        p = rotateRight(p);
    }

    if (isRed(p->left) && isRed(p->right)) {
        colorFlip(p);
    }
    return p;
}

template <typename KeyType>
typename Set<KeyType>::TreeNode *Set<KeyType>::removeMin(TreeNode *t) const {
    if (!t) {
        return nullptr;
    }

    if (!t->left) {
        delete t;
        return nullptr;
    }

    if (!isRed(t->left) && !isRed(t->left->left)) {
        t = moveRedLeft(t);
    }

    t->left = removeMin(t->left);

    return fixUp(t);
}

template <typename KeyType>
typename Set<KeyType>::TreeNode *Set<KeyType>::newNode(KeyType key) const {
    TreeNode *new_node = new TreeNode;
    if (!new_node) {
        return nullptr;
    }
    new_node->key = key;
    new_node->color = Red;
    new_node->left = new_node->right = nullptr;
    return new_node;
}

template <typename KeyType>
typename Set<KeyType>::TreeNode *Set<KeyType>::insertRec(TreeNode *t, KeyType key) {
    if (!t) {
        return newNode(key);
    }

    if (key < t->key) {
        t->left = insertRec(t->left, key);
    } else if (key > t->key) {
        t->right = insertRec(t->right, key);
    }

    if (isRed(t->right) && !isRed(t->left)) {
        t = rotateLeft(t);
    }

    if (t->left && t->left->left && isRed(t->left) && isRed(t->left->left)) {
        t = rotateRight(t);
    }

    if (t->left && t->right && isRed(t->left) && isRed(t->right)) {
        colorFlip(t);
    }

    return t;
}

template <typename KeyType>
typename Set<KeyType>::TreeNode *Set<KeyType>::eraseRec(TreeNode *t, KeyType key) {
    if (!t) {
        return nullptr;
    }
    if (key < t->key) {
        if (t->left) {
            if (!isRed(t->left) && !isRed(t->left->left)) {
                t = moveRedLeft(t);
            }
            t->left = eraseRec(t->left, key);
        }
    } else {
        if (isRed(t->left)) {
            t = rotateRight(t);
        }
        if (key == t->key && !t->right) {
            delete t;
            return nullptr;
        }
        if (t->right) {
            if (!isRed(t->right) && !isRed(t->right->left)) {
                t = moveRedRight(t);
            }
            if (key == t->key) {
                t->key = (findMin(t->right))->key;
                t->right = removeMin(t->right);
            } else {
                t->right = eraseRec(t->right, key);
            }
        }
    }
    return fixUp(t);
}

template <typename KeyType>
void Set<KeyType>::printNode(TreeNode *p) const {
    if (!p) {
        return;
    }
    printNode(p->left);
    std::cout << p->key << " ";
    printNode(p->right);
} 


#endif /* _LLRB_H */