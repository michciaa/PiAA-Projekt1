#include <iostream>
#include <cstddef>
#include <array>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <iomanip>
#include "../include/algorithms/mergesort.h"
#include "../include/mergeSortLogger.h"
#include "../include/randomNumbersGen.h"
#include "../include/counter.h"
using namespace std;

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

void runBenchmarkTest(size_t count) {

    static vector<int> array;   
    array.clear();

    RandomElementsGenerator gen(count, 12345);
    gen.fillStructure(
        []() { array.clear(); },
        [](int v) { array.push_back(v); },
        0, 100
    );

    const double elapsedMs1 = measureExecutionTimeMs([&]() {
        MergeSort<int> mergeSort;
        mergeSort.sort(array.begin(), array.end());
    });

    cout << "Sortowanie przez scalanie dla " << count << " elementow przy 100 probach" << endl;
    cout << "Czas wykonania: " << elapsedMs1 << " ms" << endl;
    system("clear");
    saveDynamicArrayResultsToCsv(
        count,
        elapsedMs1
    );
}



int main(int argc, char *argv[]) {
    if (argc > 1) {
        const size_t count = static_cast<size_t>(strtoul(argv[1], nullptr, 10));
        runBenchmarkTest(count);
        return 0;
    }

    std::array<int, 5> n = {
        10000,
        50000,
        100000,
        500000,
        1000000
    };

    for (int i = 0; i < 100; i++) {
        for (size_t j = 0; j < n.size(); ++j) {
            runBenchmarkTest(n[j]);
        }
    }

    return 0;
}
