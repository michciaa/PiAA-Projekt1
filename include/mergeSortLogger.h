#pragma once

#include <cstddef>
#include <iostream>

#include "arrays.h"

template<typename T, std::size_t N = 100>
class MergeSortLogger {
public:
    static void printRange(std::ostream& out, const Array<T, N>& array, std::size_t left, std::size_t right) {
        out << "[";
        for (std::size_t i = left; i <= right; ++i) {
            out << array[i];
            if (i < right) {
                out << " ";
            }
        }
        out << "]";
    }

    static void printWhole(std::ostream& out, const Array<T, N>& array) {
        if (array.empty()) {
            out << "[]";
            return;
        }
        printRange(out, array, 0, array.size() - 1);
    }

    static void logStart(std::ostream& out, std::size_t& stage, const Array<T, N>& array) {
        out << "Etap " << stage++ << ": start | cala: ";
        printWhole(out, array);
        out << std::endl;
    }
};
