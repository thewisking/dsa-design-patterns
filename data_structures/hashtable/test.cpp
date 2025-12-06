#include "hashtable.h"

#include <fcntl.h>
#include <io.h>
#include <iostream>
int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);

    std::size_t size = 15;
    Hashtable hasher(size);

    {
        Person jacob(20, L"Jacob", L"Sett", L"STUDENT", L"TOP");
        Person emily(22, L"Emily", L"Ahri", L"NURSE", L"MID");
        Person ahmad(23, L"Ahmad", L"Lee Sin", L"ENGINEER", L"JUNGLE");
        Person ahmed(24, L"Ahmed", L"Jarvan IV", L"ACCOUNTANT", L"JUNGLE");
        Person wesam(21, L"Wesam", L"Tristana", L"PHARMACY STUDENT", L"ADC");
        Person wissam(21, L"Wissam", L"Miss Fortune", L"DESIGNER", L"ADC");
        Person wessam(21, L"Wessam", L"Ziggs", L"BOMBER", L"ADC");
        Person wesam_ar(21, L"وسام", L"Caitlyn", L"STUDENT", L"ADC");
        Person liam(19, L"Liam", L"Garen", L"GAP YEAR", L"TOP");
        Person mila(20, L"Mila", L"Soraka", L"MUHANDIS", L"SUPPORT");

        hasher.hashtable_insert(&jacob);
        hasher.hashtable_insert(&emily);
        hasher.hashtable_insert(&ahmad);
        hasher.hashtable_insert(&ahmed);
        hasher.hashtable_insert(&wesam);
        hasher.hashtable_insert(&wissam);
        hasher.hashtable_insert(&wessam);
        hasher.hashtable_insert(&wesam_ar);
        hasher.hashtable_insert(&liam);
        hasher.hashtable_insert(&mila);
    }

    hasher.print(); // no collision handling:  6/10 made it with size 20; smallest size to fit all 10 is 39

    std::wstring name_to_search = L"Wesam";

    if (hasher.hashtable_lookup(name_to_search)) {
        std::wcout << name_to_search << L" found\n";
    } else {
        std::wcout << name_to_search << L" NOT found\n";
    }

    hasher.hashtable_delete(L"Wesam");

    if (hasher.hashtable_lookup(name_to_search)) {
        std::wcout << name_to_search << L" found\n";
    } else {
        std::wcout << name_to_search << L" NOT found\n";
    }
    std::wcout << hasher.get_count();

    if (false) { // comment them? nah put em in an if false!!
        std::wcout << L"Jacob: " << hasher.hash_sum(L"Jacob") << '\n';
        std::wcout << L"Emily: " << hasher.hash_sum(L"Emily") << '\n';
        std::wcout << L"Ahmad: " << hasher.hash_sum(L"Ahmad") << '\n';
        std::wcout << L"Ahmed: " << hasher.hash_sum(L"Ahmed") << '\n';
        std::wcout << L"Wesam: " << hasher.hash_sum(L"Wesam") << '\n';
        std::wcout << L"Wissam: " << hasher.hash_sum(L"Wissam") << '\n';
        std::wcout << L"Wessam: " << hasher.hash_sum(L"Wessam") << '\n';
        // english is left to right. arabic is right to left.
        // Arabic letters also connect in different ways with the previous and next letter.
        // so there's actually four letters per letter 💀. not connected. connected with
        // previous letter - connected with next letter - connected with both.
        // so I reversed my name to start from left to right and that solved half the problem.
        // so instead of masew i wrote wesam.
        // anyways back to hash tables 😴
        std::wcout << L"ماسو: " << hasher.hash_sum(L"وسام: ") << '\n';
        std::wcout << L"Liam: " << hasher.hash_sum(L"Liam") << '\n';
        std::wcout << L"Mila: " << hasher.hash_sum(L"Mila") << '\n';
    }
}

// code is the how, commets are the why!!