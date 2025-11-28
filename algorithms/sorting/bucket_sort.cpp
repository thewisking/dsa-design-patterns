#include "bucket_sort.h"
template <typename T>
void BucketSort<T>::sort(std::vector<T> &data) const {
    size_t B = 6;
    size_t size = data.size();
    if (size <= 1) {
        return;
    }
    T max = data[0];
    for (T x : data) {
        if (x > max) {
            max = x;
        }
    }
    std::vector<std::vector<T>> buckets(B);
    for (size_t i = 0; i < size; i++) {
        double normalized = static_cast<double>(data[i]) / (max + 1);
        size_t bucketNumber = static_cast<size_t>(B * normalized);
        if (bucketNumber == B) {
            bucketNumber = B - 1;
        }
        buckets[bucketNumber].push_back(data[i]);
    }

    size_t index = 0;
    for (auto &bucket : buckets) {
        std::sort(bucket.begin(), bucket.end()); // can replace this with my insertion sort but nah
        for (const T &element : bucket) {
            data[index++] = element;
        }
    }
    return;
}
