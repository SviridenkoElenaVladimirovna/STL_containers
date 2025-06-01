/*
Sviridenko Elena st130482@student.spbu.ru
A template container that implements a STL-style.
It supports iterators, standard concepts, error handling, and standard operators
*/
#include <iostream>
#include "CyclicalList.h"

template <typename List>
void print_list(const List& lst) {
    for (const auto& elem : lst) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

int main() {
    CyclicalList<int> intList;
    intList.push_back(5);
    intList.push_back(10);
    intList.push_back(20);

    std::cout << "Integer list size: " << intList.size() << '\n';
    std::cout << "Front: " << intList.front() << ", Back: " << intList.back() << '\n';
    std::cout << "Elements: ";
    print_list(intList);

    intList.push_front(7);
    std::cout << "After push_front(7): ";
    print_list(intList);

    intList.pop_front();
    std::cout << "After pop_front(): ";
    print_list(intList);

    intList.clear();

    CyclicalList<std::string> strList;
    strList.push_back("cherry");
    strList.push_back("apple");
    strList.push_back("banana");

    std::cout << "String list size: " << strList.size() << '\n';
    std::cout << "Front: " << strList.front() << ", Back: " << strList.back() << '\n';
    std::cout << "Elements: ";
    print_list(strList);

    strList.push_front("date");
    std::cout << "After push_front(\"date\"): ";
    print_list(strList);

    strList.pop_front();
    std::cout << "After pop_front(): ";
    print_list(strList);

    strList.clear();

    return 0;
}
