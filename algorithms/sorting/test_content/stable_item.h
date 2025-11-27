// tests/stable_item.h
#pragma once

struct StableItem {
    int key;            // value used for sorting
    int original_index; // track original position
};

// Comparator by key only (used by std::stable_sort)
struct StableItemKeyLess {
    bool operator()(const StableItem &a, const StableItem &b) const {
        return a.key < b.key;
    }
};

// Equality so std::vector<StableItem>::operator== works
inline bool operator==(const StableItem &a, const StableItem &b) {
    return a.key == b.key && a.original_index == b.original_index;
}

// Comparisons so your sort can compare StableItem
inline bool operator<(const StableItem &a, const StableItem &b) {
    return a.key < b.key;
}

inline bool operator>(const StableItem &a, const StableItem &b) {
    return a.key > b.key;
}
