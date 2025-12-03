#include "doubly_linked_list.h"
#include <iostream>

void print_and_clear(DoublyLinkedList<int> &list, const char *label) {
    std::cout << label << ": ";
    while (!list.empty()) {
        std::cout << list.front() << ' ';
        list.pop_front();
    }
    std::cout << "\n";
}

int main() {
    system("cls");
    std::cout << std::boolalpha;

    // ===== basic construction / empty =====
    DoublyLinkedList<int> list;
    std::cout << "Initially empty: " << list.empty() << " (expect true)\n";
    std::cout << "Initial size: " << list.size() << " (expect 0)\n\n";

    // ===== push_back / push_front / front / back =====
    list.push_back(10); // [10]
    list.push_back(20); // [10, 20]
    list.push_front(5); // [5, 10, 20]

    std::cout << "After pushes:\n";
    std::cout << "  size:  " << list.size() << " (expect 3)\n";
    std::cout << "  front: " << list.front() << " (expect 5)\n";
    std::cout << "  back:  " << list.back() << " (expect 20)\n\n";

    print_and_clear(list, "Contents after pushes (expect 5 10 20)");
    std::cout << "Empty after print_and_clear: " << list.empty() << " (expect true)\n\n";

    // ===== insert by index =====
    // build [1, 3, 5]
    list.push_back(1);
    list.push_back(3);
    list.push_back(5);

    // insert at head -> [0, 1, 3, 5]
    list.insert(0, 0);

    // insert in middle -> [0, 1, 2, 3, 5]
    list.insert(2, 2);

    // insert at end -> [0, 1, 2, 3, 5, 6]
    list.insert(list.size(), 6);

    std::cout << "After inserts, size: " << list.size() << " (expect 6)\n";
    print_and_clear(list, "Contents after inserts (expect 0 1 2 3 5 6)");
    std::cout << "\n";

    // ===== erase / pop_front / pop_back =====
    // rebuild [10, 20, 30, 40, 50]
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);
    list.push_back(50);

    std::cout << "Rebuilt list size: " << list.size() << " (expect 5)\n";

    // erase middle (index 2 -> value 30) -> [10, 20, 40, 50]
    list.erase(2);
    std::cout << "After erase(2), size: " << list.size() << " (expect 4)\n";

    // pop_front -> remove 10 -> [20, 40, 50]
    list.pop_front();
    std::cout << "After pop_front, front: " << list.front() << " (expect 20)\n";

    // pop_back -> remove 50 -> [20, 40]
    list.pop_back();
    std::cout << "After pop_back, back: " << list.back() << " (expect 40)\n";

    print_and_clear(list, "Contents after erase + pops (expect 20 40)");
    std::cout << "\n";

    // ===== clear =====
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    std::cout << "Before clear, size: " << list.size() << " (expect 3)\n";
    list.clear();
    std::cout << "After clear, empty: " << list.empty() << " (expect true)\n";
    std::cout << "After clear, size: " << list.size() << " (expect 0)\n\n";

    // ===== find =====
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    std::size_t idx20 = list.find(20);
    std::size_t idx99 = list.find(99);

    std::cout << "find(20): " << idx20 << " (expect 1)\n";
    std::cout << "find(99): " << idx99
              << " (expect " << list.size() << " for not found)\n";

    // ===== copy / move tests =====
    DoublyLinkedList<int> copyList(list); // copy ctor
    print_and_clear(copyList, "Copy-constructed list (expect 10 20 30)");

    DoublyLinkedList<int> assigned;
    assigned.push_back(99);
    assigned.push_back(100);
    assigned = list; // copy assignment
    print_and_clear(assigned, "Copy-assigned list (expect 10 20 30)");

    DoublyLinkedList<int> movedCtor(std::move(list)); // move ctor
    print_and_clear(movedCtor, "Move-constructed list (expect 10 20 30)");
    std::cout << "Original list after move, empty: " << list.empty()
              << " (expect true)\n";

    DoublyLinkedList<int> movedAssign;
    movedAssign.push_back(7);
    movedAssign.push_back(8);
    movedAssign = DoublyLinkedList<int>(); // move-assign from temp empty
    std::cout << "movedAssign after move-assign from empty, size: "
              << movedAssign.size() << " (expect 0)\n";

    std::cout << "\nAll tests done.\n";
    return 0;
}
