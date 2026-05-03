#pragma once

#include <cstddef>
#include <cstdint>
#include <chrono>
#include <functional>
#include <optional>
#include <random>
#include <stdexcept>
#include <vector>

class RandomElementsGenerator {
private:
    std::size_t nOfElements;
    std::optional<std::uint32_t> seed;

    std::uint32_t resolveSeed() const {
        if (seed.has_value()) {
            return *seed;
        }
        return static_cast<std::uint32_t>(
            std::chrono::high_resolution_clock::now().time_since_epoch().count()
        );
    }

public:
    explicit RandomElementsGenerator(
        std::size_t size,
        std::optional<std::uint32_t> seed = std::nullopt
    ) : nOfElements(size), seed(seed) {}

    void setSize(std::size_t size) { nOfElements = size; }
    std::size_t size() const { return nOfElements; }

    void setSeed(std::optional<std::uint32_t> newSeed) { seed = newSeed; }
    std::optional<std::uint32_t> getSeed() const { return seed; }

    std::vector<int> generatePack(int minValue, int maxValue) const {
        if (minValue > maxValue) {
            throw std::invalid_argument("minValue > maxValue");
        }

        std::mt19937 rng(resolveSeed());
        std::uniform_int_distribution<int> dist(minValue, maxValue);

        std::vector<int> out;
        out.reserve(nOfElements);
        for (std::size_t i = 0; i < nOfElements; ++i) {
            out.push_back(dist(rng));
        }
        return out;
    }

    void fillStructure(
        const std::function<void()>& clearFn,
        const std::function<void(int)>& insertFn,
        int minValue,
        int maxValue
    ) const {
        clearFn();
        const auto pack = generatePack(minValue, maxValue);
        for (int v : pack) {
            insertFn(v);
        }
    }
};
