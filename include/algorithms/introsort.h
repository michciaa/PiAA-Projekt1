#ifndef SORTING_ALGORITHMS_INTROSORT_H
#define SORTING_ALGORITHMS_INTROSORT_H
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>
#include <cmath>
#include <iterator>

#include "./heapsort.h"

// sortowanie introspektywne | QuickSort + HeapSort

template <typename T>
class IntroSort
{
private:

    template<typename Compare>
    static std::size_t medianOfThree(std::vector<T>& data, std::size_t low, std::size_t high, Compare& comp)
    {
        std::size_t mid = low + (high - low) / 2;
        if (comp(data[mid], data[low])) std::swap(data[mid], data[low]);

        if (comp(data[high], data[low])) std::swap(data[high], data[low]);

        if (comp(data[high], data[mid])) std::swap(data[high], data[mid]);

        return mid;
    }

    template<typename Compare>
    static std::size_t partition(
        std::vector<T>& data,
        std::size_t low,
        std::size_t high,
        Compare& comp
    )
    {
        std::size_t pivotIndex = medianOfThree(data, low, high, comp);
        std::swap(data[pivotIndex], data[high]);

        const T pivot = data[high];
        std::size_t i = low;

        for (std::size_t j = low; j < high; ++j)
        {
            if (!comp(pivot, data[j]))
            {
                std::swap(data[i], data[j]);
                ++i;
            }
        }

        std::swap(data[i], data[high]);
        return i;

    }

    template<typename Compare>
    static void introSort(
        std::vector<T>& data,
        std::size_t low,
        std::size_t high,
        int depthLimit,
        Compare& comp
    )
    {
        if (low >= high) return;

        if (depthLimit == 0)
        {
            HeapSort<T> heapSort;
            heapSort.sort(
                data.begin() + static_cast<std::ptrdiff_t>(low),
                data.begin() + static_cast<std::ptrdiff_t>(high + 1)
            );
            return;
        }

        std::size_t pivotIndex = partition(data, low, high, comp);

        if (pivotIndex > low) introSort(data, low, pivotIndex - 1, depthLimit - 1, comp);

        if (pivotIndex < high) introSort(data, pivotIndex + 1, high, depthLimit - 1, comp);
    }

public:
    template <typename Compare = std::less<T>>
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end, Compare comp = Compare{})
    {
        if (start == end) return;

        std::vector<T> data(start, end);

        if (data.size() > 1)
        {
            int depthLimit = 2 * static_cast<int>(std::log2(static_cast<double>(data.size())));
            introSort(data, 0, data.size() - 1, depthLimit, comp);
        }

        std::copy(data.begin(), data.end(), start);
    } ;
};
#endif //SORTING_ALGORITHMS_INTROSORT_H
