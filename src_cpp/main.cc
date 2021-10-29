#include "LLRB.h"
int main() {
    Set<int> set;
    set.insert(1);
    set.printTree();
    set.insert(2);
    set.printTree();
    set.erase(1);
    set.printTree();
    set.erase(2);
    set.printTree();
    return 0;
}