#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>
#include <cmath>

#include "algorithms/heapsort.h"

template <typename T>
class IntroSort
{
    private:
    static constexpr std::size_t INSERTION_SORT_THRESHOLD = 16;
    template <typename Compare>
    static void insertionSort(std::vector<T>& data, std::size_t low, std::size_t high, Compare& comp)
    {
        for(std::size_t i  = low + 1; i <= high; i++)
        {
            T key = data[i];
            std::size_t j = i;
            while(j > low && comp(key, data[j - 1]))
            {
                data[j] = data[j-1];
                --j;
            }
            data[j] = key;
        }
    }

    template <typename Compare>
    static std::size_t partition(std::vector<T>& data, std::size_t low, std::size_t high, Compare& comp)
    {
        const T pivot = data[high];
        std::size_t i = low;

        for(std::size_t j = low; j < high; ++j)
        {
            if(!comp(pivot, data[j]))
            {
                std::swap(data[i], data[j]);
                ++i;            
            }
        }
        std::swap(data[i], data[high]);
        return i;
    }
        template <typename Compare>
        static void introSort(std::vector<T>& data, std::size_t low, std::size_t high, int depthLimit, Compare& comp)
        {
            if(low >= high)
            {
                return;
                        
            }

            const std::size_t size = high - low + 1;

            if(size <= INSERTION_SORT_THRESHOLD)
            {
                insertionSort(data, low, high, comp);
                return;
            }

            if(depthLimit == 0)
            {
                HeapSort<T> heapSort;
                heapSort.sort(
                    data.begin() + static_cast<std::ptrdiff_t>(low),
                    data.begin() + static_cast<std::ptrdiff_t>(high + 1),
                    comp
                );
                return;
            }

            std::size_t p = partition(data, low, high, comp);

            if(p > 0)
            {
                introSort(data, low, p-1, depthLimit - 1, comp);
            }
            introSort(data, p+1, high, depthLimit - 1, comp);
        }

        public:

        template <typename Compare = std::less<T>>
        void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end, Compare comp = Compare{})
        {
            if(start == end) return;

            std::vector<T> data(start, end);

            if(data.size() > 1)
            {
                int depthLimit = 2 * static_cast<int>(std::log2(static_cast<double>(data.size())));
                introSort(data, 0, data.size() - 1, depthLimit, comp);
            }

            std::copy(data.begin(), data.end(), start);
        }
};