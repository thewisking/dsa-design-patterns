#include "selection_sort.h"
#include <vector>

template <typename T>
void SelectionSort<T>::sort(std::vector<T> &data) const {

    auto size = data.size();

    if (size == 0) {
        return;
    }
    auto currentMin = data[0];
    auto currentItem = data[0];
    
    for(auto i = 0; i < size; i++){
        for(auto j = i; j < size; j++){
            if(currentItem > currentMin){
                currentMin = currentItem;
            }
        }
        data[i] = currentMin;
        currentMin = data[i+1];
    }
    return;
}