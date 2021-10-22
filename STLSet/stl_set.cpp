#include <iostream>
#include <set>

#define TIMES 10000

int main()
{
    std::set<int> s;
    std::set<int>::iterator iter;
    for (int i = 0; i < TIMES; i++) {
        int cmd, num;
        std::cin >> cmd >> num;
        if (cmd) {
            s.insert(num);
            std::cout << "insert " << num << std::endl;
            std::cout << "now: ";
            for (iter = s.begin(); iter != s.end(); iter++) {
                std::cout << *iter << " ";
            }
            std::cout << std::endl;
        } else {
            s.erase(num);
            std::cout << "erase " << num << std::endl;
            std::cout << "now: ";
            for (iter = s.begin(); iter != s.end(); iter++) {
                std::cout << *iter << " ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << "finally: " << std::endl;
    for (iter = s.begin(); iter != s.end(); iter++) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
    s.clear();
}