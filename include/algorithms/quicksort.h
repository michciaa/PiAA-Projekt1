#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>
#include <random>

template <typename T>
class QuickSort
{
private:
    template <typename Compare>
    static void quickSort(std::vector<T>& data, std::size_t low, std::size_t high, Compare& comp)
    {
        if (low >= high) {
            return;
        }

        // Median-of-three jako prosty wybór lepszego pivota
        std::size_t mid = low + (high - low) / 2;

        if (comp(data[mid], data[low])) {
            std::swap(data[mid], data[low]);
        }
        if (comp(data[high], data[low])) {
            std::swap(data[high], data[low]);
        }
        if (comp(data[high], data[mid])) {
            std::swap(data[high], data[mid]);
        }

        T pivot = data[mid];

        std::size_t lt = low;
        std::size_t i = low;
        std::size_t gt = high;

        while (i <= gt) {
            if (comp(data[i], pivot)) {
                std::swap(data[lt], data[i]);
                ++lt;
                ++i;
            } else if (comp(pivot, data[i])) {
                std::swap(data[i], data[gt]);
                if (gt == 0) break;
                --gt;
            } else {
                ++i;
            }
        }

        if (lt > 0) {
            quickSort(data, low, lt - 1, comp);
        }

        quickSort(data, gt + 1, high, comp);
    }

public:
    template <typename Compare = std::less<T>>
    void sort(
        typename std::vector<T>::iterator start,
        typename std::vector<T>::iterator end,
        Compare comp = Compare{}
    )
    {
        if (start == end) return;

        std::vector<T> data(start, end);

        if (data.size() > 1) {
            quickSort(data, 0, data.size() - 1, comp);
        }

        std::copy(data.begin(), data.end(), start);
    }
};