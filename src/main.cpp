#include <iostream>
#include <cstddef>
#include <array>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <iomanip>
#include <functional>
#include <algorithm>

// Sorting Algorithms
#include "../include/algorithms/mergesort.h"
#include "../include/algorithms/quicksort.h"
#include "../include/algorithms/introsort.h"

// Utils: random numbers generator + execution timer
#include "../include/utils/randomNumbersGen.h"
#include "../include/utils/counter.h"


using namespace std;

enum class SortType
{
    Merge,
    Quick,
    Intro
};


// N elements to be pre-sorted before (% of elements from beginning)
void presortPercentage(vector<int>& data, double percent, bool descending)
{
    if (data.empty() || percent <= 0.0) return;
    if (percent > 100.0) percent = 100.0;

    const size_t presortedCount = static_cast<size_t>(data.size() * percent / 100.0);
    if (presortedCount < 2) return;

    auto midItem = data.begin() + static_cast<ptrdiff_t>(presortedCount);
    if (descending) sort(data.begin(), midItem, greater<int>{});
    else sort(data.begin(), midItem);
}


// Helper function to save results of sorting algorithms to CSV file (with measured time in milliseconds)

void saveResultsToCsv(
    const string& filePath,
    size_t count,
    double elapsedMs,
    double presortedPercent,
    bool descending
)
{
    const bool writeHeader = !ifstream(filePath).good();

    ofstream file(filePath, ios::app);
    if (!file.is_open())
    {
        cerr << "Nie można zapisać pliku CSV: " << filePath << endl;
        return;
    }

    if (writeHeader) file << "count,time,presortedPercentage,descending\n";

    file << fixed << setprecision(6)
        << count << ","
        << elapsedMs << ","
        << presortedPercent << ","
        << descending << "\n";
}


// Sorting + time couting preparation with certain type of algorithm

template <typename Sorter>
double benchmarkSorter(
    const vector<int>& rawData,
    const string& csvPath,
    size_t count,
    double presortedPercent,
    bool descending
)
{
    vector<int> data = rawData;
    const double elapsedMs = measureExecutionTimeMs([&]() {
        Sorter sorter;
        sorter.sort(data.begin(), data.end());
    });

    saveResultsToCsv(
        csvPath,
        count,
        elapsedMs,
        presortedPercent,
        descending
    );
    
    return elapsedMs;
}

// Choosing type of sortation (based on phrase in command line)

SortType parseSortType(const string& value)
{
    if (value == "quick") return SortType::Quick;
    if (value == "intro") return SortType::Intro;
    return SortType::Merge;
}

// Pair od Label & Filename to certain sorting algorithm

pair<string, string> sortTypeToFile(SortType kind)
{
    switch (kind)
    {
    case SortType::Merge:
        return {"MergeSort", "results_merge.csv" };
    case SortType::Quick:
        return {"QuickSort", "results_quick.csv" };
    case SortType::Intro:
        return {"IntroSort", "results_intro.csv" };
    }

    return { "MergeSort", "results_merge.csv" };
}

// Running a single test

void runBenchmarkTest(
    size_t count,
    SortType kind,
    double presortedPercent = 0.0,
    bool descending = false
)
{
    vector<int> rawData;
    rawData.reserve(count);

    RandomElementsGenerator engine(count);
    engine.fillStructure(
        [&]() {rawData.clear(); },
        [&](int v) {rawData.push_back(v); },
        0, 100
    );

    presortPercentage(rawData, presortedPercent, descending);

    double elapsedMs = 0.0;
    const auto filePair = sortTypeToFile(kind);
    const std::string& label = filePair.first;
    const std::string& csvPath = filePair.second;

    switch (kind)
    {
    case SortType::Merge:
        elapsedMs = benchmarkSorter<MergeSort<int>>(rawData, csvPath, count, presortedPercent, descending);
        break;
    case SortType::Quick:
        elapsedMs = benchmarkSorter<QuickSort<int>>(rawData, csvPath, count, presortedPercent, descending);
        break;
    case SortType::Intro:
        elapsedMs = benchmarkSorter<IntroSort<int>>(rawData, csvPath, count, presortedPercent, descending);
        break;
    }

    cout << "Count: " << count
        << ", sorter: " << label
        << ", presort: " << presortedPercent << "%"
        << ", descending: " << (descending ? "yes" : "no") << '\n';
    
    cout << label << ": " << elapsedMs << " ms\n";
    cout << "------------------\n";



}


// Running whole simulation

int main(int argc, char* argv[])
{
    double presortedPercent = (argc > 1) ? strtod(argv[1], nullptr) : 0.0;
    if (presortedPercent < 0.0) presortedPercent = 0.0;
    if (presortedPercent > 100.0) presortedPercent = 100.0;

    const bool descending = (argc > 2) ? (strtoul(argv[2], nullptr, 10) != 0) : false;
    const SortType kind = (argc > 3) ? parseSortType(argv[3]) : SortType::Merge;

    array<int, 5> n = {
        10000, 
        50000, 
        100000, 
        500000, 
        1000000
    };

    // For each array size, run 100 repetitions (iterate repetitions inside) so
    // results for a given size are computed consecutively.
    for (size_t j = 0; j < n.size(); ++j)
    {
        for (int i = 0; i < 100; ++i)
        {
            runBenchmarkTest(n[j], kind, presortedPercent, descending);
        }
    }

    return 0;
}
