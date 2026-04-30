#include "headers/randomNumbersGen.h"

#include <chrono>
#include <random>
#include <stdexcept>

RandomElementsGenerator::RandomElementsGenerator(std::size_t size, std::optional<std::uint32_t> seed)
    : nOfElements(size), seed(seed) {}

void RandomElementsGenerator::setSize(std::size_t size) { nOfElements = size; }
std::size_t RandomElementsGenerator::size() const { return nOfElements; }

void RandomElementsGenerator::setSeed(std::optional<std::uint32_t> newSeed) { seed = newSeed; }
std::optional<std::uint32_t> RandomElementsGenerator::getSeed() const { return seed; }

std::uint32_t RandomElementsGenerator::resolveSeed() const {
    if (seed.has_value()) return *seed;
    return static_cast<std::uint32_t>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()
    );
}

std::vector<int> RandomElementsGenerator::generatePack(int minValue, int maxValue) const {
    if (minValue > maxValue) throw std::invalid_argument("minValue > maxValue");

    std::mt19937 rng(resolveSeed());
    std::uniform_int_distribution<int> dist(minValue, maxValue);

    std::vector<int> out;
    out.reserve(nOfElements);
    for (std::size_t i = 0; i < nOfElements; ++i) out.push_back(dist(rng));
    return out;
}

void RandomElementsGenerator::fillStructure(
    const std::function<void()>& clearFn,
    const std::function<void(int)>& insertFn,
    int minValue,
    int maxValue
) const {
    clearFn();
    const auto pack = generatePack(minValue, maxValue);
    for (int v : pack) insertFn(v);
}