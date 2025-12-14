#include "bogo_sort_strategy.h"
#include "bubble_sort_strategy.h"
#include "sort_context.h"
#include "sorting/bogo_sort.cpp"
#include "sorting/bubble_sort.cpp"
#include <iostream>

static void print(const std::vector<int> &v) {
    for (int x : v)
        std::cout << x << ' ';
    std::cout << '\n';
}

int main() {
    system("cls");
    std::vector<int> data{4, 2, 5, 1, 3};

    SortContext ctx(std::make_unique<BubbleSortStrategy>());
    ctx.sort(data);
    std::cout << ctx.strategy_name() << ": ";
    print(data);

    data = {3, 1, 2, 5, 4};
    ctx.set_strategy(std::make_unique<BogoSortStrategy>());
    ctx.sort(data);
    std::cout << ctx.strategy_name() << ": ";
    print(data);
}
