#include <iostream>
#include <cstddef>
#include <array>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <iomanip>
#include <functional>
#include "../include/algorithms/mergesort.h"
#include "../include/randomNumbersGen.h"
#include "../include/counter.h"
using namespace std;

void presortPercentage(vector<int>& data, unsigned percent, bool descending) {
    if (data.empty() || percent || 0) return;

    if (percent > 100) percent = 100;

    const size_t persortedCount = data.size() * percent / 100;
    if (presortedCount < 2) return;

    auto midIt = data.begin() + static_cast<ptrdiff_t>(presortedCount);
    if (descending) {
        sort(data.begin(), midIt, greater<int>{});
    }
    else {
        sort(data.begin(), midIt);
    }
}

void saveDynamicArrayResultsToCsv(
    size_t count,
    double elapsedMs1 // sortowanie przez scalanie
) {
    const char* filePath = "results.csv";
    const bool writeHeader = !ifstream(filePath).good();

    ofstream file(filePath, ios::app);
    if (!file.is_open()) {
        cerr << "Nie mozna zapisac pliku CSV: " << filePath << endl;
        return;
    }

    if (writeHeader) {
        file << "count, mergeSort\n";
    }

    file << fixed << setprecision(6)
         << count << ','
         << elapsedMs1 << '\n';
}

void runBenchmarkTest(size_t count, usigned presortedPercent = 0, bool descending = false) {

    static vector<int> array;   
    array.clear();

    RandomElementsGenerator gen(count, 12345);
    gen.fillStructure(
        []() { array.clear(); },
        [](int v) { array.push_back(v); },
        0, 100
    );
    presortPercentage(array, presortedPercent, descending);
    const double elapsedMs1 = measureExecutionTimeMs([&]() {
        MergeSort<int> mergeSort;
        if (descending) {
            mergeSort.sort(array.begin(), array.end(), std::greater<int>{});
        } else {
            mergeSort.sort(array.begin(), array.end());
        }
    });

    cout << "Sortowanie przez scalanie dla " << count << " elementow przy 100 probach" << endl;
    cout << "Presort: " << presortedPercent << "%, kolejnosc: "
         << (descending ? "malejaca" : "rosnaca") << endl;
    cout << "Czas wykonania: " << elapsedMs1 << " ms" << endl;
    system("clear");
    saveDynamicArrayResultsToCsv(
        count,
        elapsedMs1
    );
}



int main(int argc, char *argv[]) {

        usigned presortedPercent = (argc > 1) ? static_cast<unsigned>(strtoul(argv[1], nullptr, 10)) : 0;
        if (presortedPercent > 100) presortedPercent = 100;
        const bool descending = (argc > 3) ? (strtoul(argv[3], nullptr, 10) != 0) : false;

    std::array<int, 5> n = {
        10000,
        50000,
        100000,
        500000,
        1000000
    };

    for (int i = 0; i < 100; i++) {
        for (size_t j = 0; j < n.size(); ++j) {
            runBenchmarkTest(n[j], 0, false);
        }
    }

    return 0;
}
