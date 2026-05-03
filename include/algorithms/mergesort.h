#pragma once 
#include <vector>
#include <algorithm>
#include <functional>

// sortowanie przez scalanie

template <typename T>
class MergeSort
{
private:
    template<typename Compare>
    static void merge(
        std::vector<T>& data,
        std::size_t left,
        std::size_t right,
        Compare& comp
    )
    {
        if (left >= right) {
            return;
        }

        std::size_t mid = left + (right - left) / 2;
        merge(data, left, mid, comp);
        merge(data, mid + 1, right, comp);

        std::vector<T> temp;
        temp.reserve(right - left + 1);

        std::size_t i = left;
        std::size_t j = mid + 1;

        while (i <= mid && j <= right) {
            if (!comp(data[j], data[i])) {
                temp.push_back(data[i++]);
            } else {
                temp.push_back(data[j++]);
            }
        }

        while (i <= mid) {
            temp.push_back(data[i++]);
        }

        while (j <= right) {
            temp.push_back(data[j++]);
        }

        for (std::size_t k = 0; k < temp.size(); ++k) {
            data[left + k] = temp[k];
        }
    }

public:
    template <typename Compare = std::less<T>>
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end, Compare comp = Compare{})
    {
        if (start == end) {
            return;
        }

        std::vector<T> data(start, end);
        merge(data, 0, data.size() - 1, comp);
        std::copy(data.begin(), data.end(), start);
    }
};
