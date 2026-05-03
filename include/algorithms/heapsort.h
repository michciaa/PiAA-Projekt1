#ifndef SORTING_ALGORITHMS_HEAPSORT_H
#define SORTING_ALGORITHMS_HEAPSORT_H

#include <algorithm>
#include <vector>
#include <cstddef>

template <typename T>
class HeapSort
{
private:
    template <typename Compare>
    static void siftDown(std::vector<T>& data, std::size_t root, std::size_t end, Compare& comp)
    {
        while (true)
        {
            std::size_t leftChild = root * 2 + 1;

            if (leftChild > end)
            {
                return;
            }

            std::size_t swapIndex = root;

            if (comp(data[swapIndex], data[leftChild]))
            {
                swapIndex = leftChild;
            }

            std::size_t rightChild = leftChild + 1;
            if (rightChild <= end && comp(data[swapIndex], data[rightChild]))
            {
                swapIndex = rightChild;
            }

            if (swapIndex == root)
            {
                return;
            }

            std::swap(data[root], data[swapIndex]);
            root = swapIndex;
        }
    }

public:
    template <typename Compare = std::less<T>>
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end, Compare comp = Compare{})
    {
        if (start == end)
        {
            return;
        }

        std::vector<T> data(start, end);

        if (data.size() < 2)
        {
            return;
        }

        for (std::size_t startIndex = data.size() / 2; startIndex > 0; --startIndex)
        {
            siftDown(data, startIndex - 1, data.size() - 1, comp);
        }

        for (std::size_t endIndex = data.size() - 1; endIndex > 0; --endIndex)
        {
            std::swap(data[0], data[endIndex]);
            siftDown(data, 0, endIndex - 1, comp);
        }

        std::copy(data.begin(), data.end(), start);
    }
};

#endif //SORTING_ALGORITHMS_HEAPSORT_H