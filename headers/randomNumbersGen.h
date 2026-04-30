#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <optional>
#include <vector>

class RandomElementsGenerator {
private:
    std::size_t nOfElements;
    std::optional<std::uint32_t> seed;

    std::uint32_t resolveSeed() const;

public:
    explicit RandomElementsGenerator(
        std::size_t size,
        std::optional<std::uint32_t> seed = std::nullopt
    );

    void setSize(std::size_t size);
    std::size_t size() const;

    void setSeed(std::optional<std::uint32_t> newSeed);
    std::optional<std::uint32_t> getSeed() const;

    std::vector<int> generatePack(int minValue, int maxValue) const;

    void fillStructure(
        const std::function<void()>& clearFn,
        const std::function<void(int)>& insertFn,
        int minValue,
        int maxValue
    ) const;
};
