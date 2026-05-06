#pragma once

#include <chrono>
#include <functional>
#include <utility>

/*
Przykładowe użycie (helper) :
const double elapsedMs = measureExecutionTimeMs([&]() {
    someFunctionCall();
});
*/
template <typename Func, typename... Args>
double measureExecutionTimeMs(Func&& func, Args&&... args) {
    const auto start = std::chrono::steady_clock::now();
    std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
    const auto end = std::chrono::steady_clock::now();

    const double ms = std::chrono::duration<double, std::milli>(end - start).count();
    return (ms < 0.0) ? 0.0 : ms;
}
