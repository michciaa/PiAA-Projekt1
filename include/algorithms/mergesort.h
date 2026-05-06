#ifndef SORTING_ALGORITHMS_MERGESORT_H
#define SORTING_ALGORITHMS_MERGESORT_H
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
// sortowanie przez scalanie

template <typename T>
class MergeSort
{
private:
    template<typename Compare>

    static void mergeRanges(
        typename std::vector<T>::iterator start,
        typename std::vector<T>::iterator mid,
        typename std::vector<T>::iterator end,
        std::vector<T>& buffer,
        const Compare& comp
    )
    {
        auto left = start;
        auto right = mid;
        auto out = buffer.begin();

        while (left != mid && right != end)
        {
            if (!comp(*right, *left)) *out++ = *left++;
            else *out++ = *right++;
        }

        while (left != mid)
        {
            *out++ = *left++;
        }

        while (right != end)
        {
            *out++ = *right++;
        }

        std::move(buffer.begin(), out, start);
    }

    template<typename Compare>
    static void mergeSort(
        typename std::vector<T>::iterator start,
        typename std::vector<T>::iterator end,
        std::vector<T>& buffer,
        const Compare& comp
    )
    {
        const auto count = std::distance(start, end);
        if (count < 2) return;

        auto mid = start + count / 2;
        mergeSort(start, mid, buffer, comp);
        mergeSort(mid, end, buffer, comp);
        mergeRanges(start, mid, end, buffer, comp);
    }


public:
    template <typename Compare = std::less<T>>
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end, Compare comp = Compare{})
    {
        const auto count = std::distance(start, end);
        if (count < 2) return;
        std::vector<T> buffer(static_cast<std::size_t>(count));
        mergeSort(start, end, buffer, comp);

    };
};
#endif //SORTING_ALGORITHMS_MERGESORT_H
