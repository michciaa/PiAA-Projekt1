#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>

template <typename T>
class QuickSort
{
    private:

    template <typename Compare>
    static std::size_t partition(std::vector<T>& data, std::size_t low, std::size_t high, Compare& comp)
    {
        const T pivot = data[high];
        std::size_t i = low;

        for (std::size_t j = low; j < high; ++j) {
            if (!comp(pivot, data[j])) 
            {
                std::swap(data[i], data[j]);
                ++i;
            }
        }
        std::swap(data[i], data[high]);
        return i;
    }

    template <typename Compare>
    static void quickSort(std::vector<T>& data, std::size_t low, std::size_t high, Compare& comp)
    {
        if(low >= high)
        {
            return;
        }

        std::size_t p = partition(data, low, high, comp);
        if(p > 0) 
        {
            quickSort(data, low, p - 1, comp);
        }

        quickSort(data, p + 1, high, comp);
    }

    public:
    template <typename Compare = std::less<T>>
    void sort(typename std::vector<T>::iterator start,
    typename std::vector<T>::iterator end, 
    Compare comp = Compare{}
    )
    {
        if(start==end) return;

        std::vector<T> data(start, end);
        if(data.size() > 1) {
            quickSort(data, 0, data.size() - 1, comp);
        }
        std::copy(data.begin(), data.end(), start);
    }




};