#pragma once

#include <string>
class Hashtable;

class Person {
  private:
    friend class Hashtable;

    int age;

    // wstring cuz I wanted arabic
    std::wstring name;
    std::wstring main_champion = L"Yummi";
    std::wstring job = L"UNEMPLOYED";
    std::wstring lane = L"support";

    // I was thinking of making a Node class just for this, but then I rememebered that we
    // shouldn't treat objects as objects. just because this is a Person, doesn't mean it
    // shouldn't store the next pointer. Really the only thing that can see it is the hashtable.
    Person *next = nullptr;

  public:
    Person() = default;
    Person(int age, std::wstring name, std::wstring main_champion, std::wstring job, std::wstring lane)
        : age(age), name(std::move(name)), main_champion(std::move(main_champion)),
          job(std::move(job)), lane(std::move(lane)) {}
};