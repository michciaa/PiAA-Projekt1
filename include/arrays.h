#pragma once

#include <cstddef>
#include <iostream>

template<typename T, std::size_t N = 100>
class Array {
private:

    T elements[N]{};
    std::size_t length = 0;

public:
    Array() = default;
    ~Array() = default;

    bool empty() const {
        return length == 0;
    }

    std::size_t size() const {
        return length;
    }

    void clear() {
        length = 0;
    }

    void addElement(const T& value) {
        if (length < N) elements[length++] = value;
    }

    T& operator[](std::size_t index) {
        return elements[index];
    }

    const T& operator[](std::size_t index) const {
        return elements[index];
    }

    void show() const {
        for (std::size_t i = 0; i < length; ++i) {
            std::cout << elements[i] << std::endl;
        }
    }
};
