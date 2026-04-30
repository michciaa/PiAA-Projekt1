#pragma once

#include <chrono>
#include <functional>
#include <utility>

/*
Przykładowe użycie :
const double elapsedMs = measureExecutionTimeMs([&]() {
    someFunctionCall();
});
*/
template <typename Func, typename... Args>
double measureExecutionTimeMs(Func&& func, Args&&... args) {
    const auto start = std::chrono::high_resolution_clock::now();
    std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
    const auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::milli>(end - start).count();
}
