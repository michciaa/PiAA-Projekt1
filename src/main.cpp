#include <iostream>
#include <cstddef>
#include <array>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <iomanip>
#include <functional>
#include <algorithm>
#include "../include/algorithms/mergesort.h"
#include "../include/algorithms/quicksort.h"
#include "../include/algorithms/introsort.h"
#include "../include/randomNumbersGen.h"
#include "../include/counter.h"

using namespace std;

enum class SortKind {
    Merge,
    Quick,
    Intro
};

void presortPercentage(vector<int>& data, double percent, bool descending)
{
    if (data.empty() || percent <= 0.0) return;
    if (percent > 100.0) percent = 100.0;

    const size_t presortedCount = static_cast<size_t>(data.size() * percent / 100.0);
    if (presortedCount < 2) return;

    auto midIt = data.begin() + static_cast<ptrdiff_t>(presortedCount);
    if (descending) {
        sort(data.begin(), midIt, greater<int>{});
    } else {
        sort(data.begin(), midIt);
    }
}

void saveResultsToCsv(
    const string& filePath,
    size_t count,
    double elapsedMs,
    double presortedPercent,
    bool descending)
{
    const bool writeHeader = !ifstream(filePath).good();

    ofstream file(filePath, ios::app);
    if (!file.is_open()) {
        cerr << "Nie mozna zapisac pliku CSV: " << filePath << endl;
        return;
    }

    if (writeHeader) {
        file << "count,time,presortedPercent,descending\n";
    }

    file << fixed << setprecision(6)
         << count << ','
         << elapsedMs << ','
         << presortedPercent << ','
         << descending << '\n';
}

template <typename Sorter>
double benchmarkSorter(
    const vector<int>& baseData,
    const string& csvPath,
    size_t count,
    double presortedPercent,
    bool descending)
{
    vector<int> data = baseData;

    const double elapsedMs = measureExecutionTimeMs([&]() {
        Sorter sorter;
        sorter.sort(data.begin(), data.end());
    });

    saveResultsToCsv(csvPath, count, elapsedMs, presortedPercent, descending);
    return elapsedMs;
}

SortKind parseSortKind(const string& value)
{
    if (value == "quick") return SortKind::Quick;
    if (value == "intro") return SortKind::Intro;
    return SortKind::Merge;
}

string sortKindToCsvPath(SortKind kind)
{
    switch (kind) {
        case SortKind::Merge:
            return "results_merge.csv";
        case SortKind::Quick:
            return "results_quick.csv";
        case SortKind::Intro:
            return "results_intro.csv";
    }

    return "results_merge.csv";
}

string sortKindToLabel(SortKind kind)
{
    switch (kind) {
        case SortKind::Merge:
            return "MergeSort";
        case SortKind::Quick:
            return "QuickSort";
        case SortKind::Intro:
            return "IntroSort";
    }

    return "MergeSort";
}

void runBenchmarkTest(size_t count, SortKind kind, double presortedPercent = 0.0, bool descending = false)
{
    vector<int> baseData;
    baseData.reserve(count);

    RandomElementsGenerator gen(count, 12345);
    gen.fillStructure(
        [&]() { baseData.clear(); },
        [&](int v) { baseData.push_back(v); },
        0, 100
    );

    presortPercentage(baseData, presortedPercent, descending);

    double elapsedMs = 0.0;
    const string csvPath = sortKindToCsvPath(kind);

    switch (kind) {
        case SortKind::Merge:
            elapsedMs = benchmarkSorter<MergeSort<int>>(baseData, csvPath, count, presortedPercent, descending);
            break;
        case SortKind::Quick:
            elapsedMs = benchmarkSorter<QuickSort<int>>(baseData, csvPath, count, presortedPercent, descending);
            break;
        case SortKind::Intro:
            elapsedMs = benchmarkSorter<IntroSort<int>>(baseData, csvPath, count, presortedPercent, descending);
            break;
    }

    cout << "Count: " << count
         << ", sorter: " << sortKindToLabel(kind)
         << ", presort: " << presortedPercent << "%"
         << ", descending: " << (descending ? "yes" : "no") << '\n';

    cout << sortKindToLabel(kind) << ": " << elapsedMs << " ms\n";
    cout << "-----\n";
}

int main(int argc, char* argv[])
{
    double presortedPercent = (argc > 1) ? strtod(argv[1], nullptr) : 0.0;
    if (presortedPercent < 0.0) presortedPercent = 0.0;
    if (presortedPercent > 100.0) presortedPercent = 100.0;

    const bool descending = (argc > 2) ? (strtoul(argv[2], nullptr, 10) != 0) : false;
    const SortKind kind = (argc > 3) ? parseSortKind(argv[3]) : SortKind::Merge;

    array<int, 5> n = {10000, 50000, 100000, 500000, 1000000};

    for (int i = 0; i < 100; ++i) {
        for (size_t j = 0; j < n.size(); ++j) {
            runBenchmarkTest(n[j], kind, presortedPercent, descending);
        }
    }

    return 0;
}