#pragma once

#include "person.h"
#include <iostream>
#include <string>
#include <vector>

class Hashtable {
  private:
    std::size_t m_size;
    std::vector<Person *> m_hashtable;
    std::size_t m_count = 0;

    bool handle_collision(Person *current_occupant, Person *&humanling) {
        if (!current_occupant->next) {
            current_occupant->next = humanling;
            m_count++;
            return true;
        }
        while (current_occupant->next) {
            current_occupant = current_occupant->next;
        }
        current_occupant->next = humanling;
        m_count++;
        return true;
    }

  public:
    Hashtable(std::size_t size) : m_size(size), m_hashtable(m_size, nullptr) {}
    Hashtable() : m_size(10), m_hashtable(m_size, nullptr) {}

    std::size_t get_count() { return m_count; }

    Person *hashtable_lookup(std::wstring name) {
        for (Person *humanling : m_hashtable) {
            if (humanling) {
                if (humanling->name == name) {
                    return humanling;
                }
                while (humanling->next) {
                    humanling = humanling->next;
                    if (humanling->name == name) {
                        return humanling;
                    }
                }
            }
        }
        return nullptr;
    }

    Person *hashtable_delete(std::wstring name) {
        for (Person *&humanling : m_hashtable) { // pass by reference. I didn't know that.
            Person *current = humanling;
            Person *prev = nullptr;

            while (current) {
                if (current->name == name) {
                    if (prev) {
                        prev->next = current->next;
                    } else {
                        humanling = current->next;
                    }
                    --m_count;
                    return current;
                }
                prev = current;
                current = current->next;
            }
        }
        return nullptr;
    }

    bool hashtable_insert(Person *humanling) {
        if (!humanling) {
            return false;
        }
        std::size_t index = hash_sum(humanling->name);

        if (m_hashtable[index]) {
            if (handle_collision(m_hashtable[index], humanling)) {
                return true;
            }
            return false;
        }
        m_hashtable[index] = humanling;
        m_count++;
        return true;
    }

    // this is public cuz I wanted to play with it in the test.cpp file
    std::size_t hash_sum(const std::wstring name) {
        std::size_t sum = 0;
        for (wchar_t character : name) {
            // note that we add before multiplying so that names with same characters
            // like liam and mila have different values.
            sum = ((sum + character) * character) % m_size;
        }
        return sum;
    }

    void print() {
        int i = 0;
        for (Person *element : m_hashtable) {
            std::wcout << L"Person " << i << L":  ";

            if (i++ < 10) {
                std::wcout << " "; // judgemental eyes: 👀👀 (I aint doing for age cba)
            }

            if (element == nullptr) {
                std::wcout << L"empty slot ";
            } else {
                std::wcout << L"name: " << element->name << L"    age: " << element->age;
                while (element->next) {
                    element = element->next;
                    std::wcout << " ----> " << L"name: " << element->name << L"    age: " << element->age;
                }
            }

            std::wcout << '\n';
        }
        return;
    }
};