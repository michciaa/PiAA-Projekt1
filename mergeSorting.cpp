#include <iostream>
#include <cstddef>
#include <array>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include "headers/arrays.h"
#include "headers/mergeSort.h"
#include "headers/mergeSortLogger.h"
#include "headers/randomNumbersGen.h"
#include "headers/counter.h"
using namespace std;
constexpr std::size_t N = 1000000;

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
    if (count > N) {
        cerr << "count > N (" << N << ")\n";
        return;
    }

    static Array<int, N> array;   // <-- było: Array<int, N> array;
    array.clear();

    RandomElementsGenerator gen(count, 12345);
    gen.fillStructure(
        []() { array.clear(); },
        [](int v) { array.addElement(v); },
        0, 100
    );

    const double elapsedMs1 = measureExecutionTimeMs([&]() {
        MergeSort<int, N>::sort(array);
    });

    cout << "Sortowanie przez scalanie dla " << count << " elementow przy 100 probach" << endl;
    cout << "Czas wykonania: " << elapsedMs1 << " ms" << endl;
    system("CLS");
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
