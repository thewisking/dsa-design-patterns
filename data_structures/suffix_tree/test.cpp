#include "suffix_tree.h"
#include <iostream>

int main() {
    SuffixTreeSimple st("banana"); // builds "banana$"

    std::cout << std::boolalpha;
    std::cout << "contains(\"ana\"):   " << st.contains("ana") << "\n";   // true
    std::cout << "contains(\"nana\"):  " << st.contains("nana") << "\n";  // true
    std::cout << "contains(\"apple\"): " << st.contains("apple") << "\n"; // false

    auto occ = st.occurrences("ana");
    std::cout << "occurrences(\"ana\"): ";
    for (auto i : occ)
        std::cout << i << " ";
    std::cout << "\n"; // should print: 1 3

    return 0;
}
