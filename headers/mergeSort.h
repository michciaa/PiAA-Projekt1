#pragma once

#include <iostream>
#include "./arrays.h"

template<typename T, std::size_t N = 100>
class MergeSort {
private:
    static void merge(Array<T, N>& array, std::size_t left, std::size_t mid, std::size_t right) {
        const std::size_t leftSize = mid - left + 1;
        const std::size_t rightSize = right - mid;

        static T leftPart[N];
        static T rightPart[N];

        for (std::size_t i = 0; i < leftSize; ++i) {
            leftPart[i] = array[left+i];
        }

        for (std::size_t j = 0; j < rightSize; ++j) {
            rightPart[j] = array[mid + 1 + j];
        }

        std::size_t i = 0, j = 0;
        std::size_t k = left;

        while (i < leftSize && j < rightSize) {
            if (leftPart[i] <= rightPart[j]) {
                array[k++] = leftPart[i++];
            }
            else {
                array[k++] = rightPart[j++];
            }
        }

        while (i < leftSize) {
            array[k++] = leftPart[i++];
        }

        while (j < rightSize) {
            array[k++] = rightPart[j++];
        }
    }

    template<typename OnSplit, typename OnMerge>
    static void sortRange(Array<T, N>& array, std::size_t left, std::size_t right, OnSplit onSplit, OnMerge onMerge) {
        if (left >= right) return;
        const std::size_t mid = left + (right - left) / 2;

        onSplit(left, mid, right, array);          // etap podziału
        sortRange(array, left, mid, onSplit, onMerge);
        sortRange(array, mid + 1, right, onSplit, onMerge);
        merge(array, left, mid, right);
        onMerge(left, right, array);               // etap scalania
    }

public:
        template<typename OnSplit, typename OnMerge>
        static void sort(Array<T, N>& array, OnSplit onSplit, OnMerge onMerge) {
            if (array.size() < 2) return;
            sortRange(array, 0, array.size() - 1, onSplit, onMerge);
        }

        static void sort(Array<T, N>& array) {
            if (array.size() < 2) return;
            sortRange(array, 0, array.size() - 1,
                [](std::size_t, std::size_t, std::size_t, const Array<T, N>&) {},
                [](std::size_t, std::size_t, const Array<T, N>&) {}
            );
        }
};