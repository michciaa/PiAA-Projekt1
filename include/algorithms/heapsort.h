#ifndef SORTING_ALGORITHMS_HEAPSORT_H
#define SORTING_ALGORITHMS_HEAPSORT_H
#include <vector>
#include <algorithm>
#include <cstddef>

template <typename T>
class Heap
{
private:
    typename std::vector<T>::iterator heapBegin;
    typename std::vector<T>::iterator heapEnd;

  public:
    Heap(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end) : heapBegin(start), heapEnd(end)
    {
        for (std::size_t root = size() / 2; root > 0; --root)
        {
            std::size_t rootIndex = root;
            while (true)
            {
                std::size_t leftChild = rootIndex * 2;
                if (leftChild > size())
                {
                    break;
                }


                std::size_t maxIndex = rootIndex;
                if ((*this)[static_cast<int>(maxIndex)] < (*this)[static_cast<int>(leftChild)])
                {
                    maxIndex = leftChild;
                }


                std::size_t rightChild = leftChild + 1;
                if (rightChild <= size() && (*this)[static_cast<int>(maxIndex)] < (*this)[static_cast<int>(rightChild)])
                {
                    maxIndex = rightChild;
                }

                if (maxIndex == rootIndex) break;

                std::iter_swap(
                    heapBegin + static_cast<std::ptrdiff_t>(rootIndex - 1),
                    heapBegin + static_cast<std::ptrdiff_t>(maxIndex - 1)
                );
                rootIndex = maxIndex;
            }
        }

    }
    void removeMax();
    std::size_t size();
    bool empty();
    T& operator[](int index);
};

template <typename T>
void Heap<T>::removeMax()
{
    if (empty()) return;

    std::iter_swap(heapBegin, heapEnd - 1);
    --heapEnd;

    if (!empty())
    {
        std::size_t rootIndex = 1;
        while (true)
        {
            std::size_t leftChild = rootIndex * 2;
            if (leftChild > size()) break;

            std::size_t maxIndex = rootIndex;
            if ((*this)[static_cast<int>(maxIndex)] < (*this)[static_cast<int>(leftChild)]) maxIndex = leftChild;

            std::size_t rightChild = leftChild + 1;
            if (rightChild <= size() && (*this)[static_cast<int>(maxIndex)] < (*this)[static_cast<int>(rightChild)]) maxIndex = rightChild;

            if (maxIndex == rootIndex) break;

            std::iter_swap(
                heapBegin + static_cast<std::ptrdiff_t>(rootIndex - 1),
                heapBegin + static_cast<std::ptrdiff_t>(maxIndex - 1)
            );

            rootIndex = maxIndex;
        }
    }
}

template <typename T>
std::size_t Heap<T>::size()
{
    return static_cast<std::size_t>(heapEnd - heapBegin);
}

template <typename T>
bool Heap<T>::empty()
{
    
    return heapBegin == heapEnd;
}

template <typename T>
T& Heap<T>::operator[](int index)
{
    return *(heapBegin + static_cast<std::ptrdiff_t>(index - 1));
}


// sortowanie przez kopcowanie

template <typename T>
class HeapSort
{
public:
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        if (end - start < 2) return;
        Heap<T> heap(start, end);
        while (!heap.empty())
        {
            heap.removeMax();
        }
    };
};

#endif //SORTING_ALGORITHMS_HEAPSORT_H
