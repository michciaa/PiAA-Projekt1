#ifndef SORTING_ALGORITHMS_QUICKSORT_H
#define SORTING_ALGORITHMS_QUICKSORT_H
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>
#include <random>


// quicksort

template <typename T>
class QuickSort
{
private:
    template<typename Compare>
    static void quickSort(
        typename std::vector<T>::iterator start,
        typename std::vector<T>::iterator end,
        const Compare& comp
    )
    {
        if (end - start < 2) return;

        // MEDIAN-OF-THREE : znalezienie pivota poprzez medianę (wartość środkową)
        auto low = start;
        auto high = end - 1;
        auto mid = start + (end - start) / 2;

        if (comp(*mid, *low)) std::iter_swap(mid, low);

        if (comp(*high, *low)) std::iter_swap(high, low);

        if (comp(*high, *mid)) std::iter_swap(high, mid);

        T pivot = *mid;

        auto lt = start;
        auto i = start;
        auto gt = end - 1;

        while (i <= gt)
        {
            if (comp(*i, pivot))
            {
                std::iter_swap(lt, i);
                ++lt;
                ++i;
            }
            else if (comp(pivot, *i))
            {
                std::iter_swap(i, gt);
                if (gt == start) break;
                --gt;
            }
            else {
                ++i;
            }
        }

        quickSort(start, lt, comp);
        quickSort(gt + 1, end, comp);
    }


public:
    template<typename Compare = std::less<T>>
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end, Compare comp = Compare{})
    {
        quickSort(start, end, comp);
    };
};
#endif //SORTING_ALGORITHMS_QUICKSORT_H
