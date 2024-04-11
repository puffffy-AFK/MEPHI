#include <chrono>
#include <memory>
#include <iostream>
#include <vector>
#include <fstream>

#include "SharedPtr.hpp"
#include "UniquePtr.hpp"

#define ll long long

using namespace std;

template <typename Func, typename... Args>
auto timeDecorator(Func func, Args... args) {
    auto start = chrono::high_resolution_clock::now();
    func(args...);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    return diff.count();
}

template <typename PointerType>
void testPerformance(int numPointers) {
    vector<PointerType> pointers;
    for (int i = 0; i < numPointers; ++i) {
        PointerType ptr(new int(i));
        pointers.push_back(std::move(ptr));
    }

    for (int i = 0; i < numPointers; ++i) {
        *pointers[i] = i * 2;
    }

    for (int i = 0; i < numPointers; ++i) {
        PointerType ptr(new int(i * 3));
        pointers[i] = std::move(ptr);
    }
    pointers.clear();
}

int main() {
    std::ofstream csvFile;
    csvFile.open("performance.csv");
    csvFile << "numPointers,SharedPtr,STL_SharedPtr,UniquePtr,STL_UniquePtr\n";

    for (ll numPointers = 1e3; numPointers <= 1e7; numPointers *= 10) {
        cout << "====================================================================\n";
        cout << "Testing for " << numPointers << " pointers:\n";

        // Test with your SharedPtr
        double time = timeDecorator(testPerformance<SharedPtr<int>>, numPointers);
        cout << "My SharedPtr took " << time << " seconds for " << numPointers << " pointers.\n";
        csvFile << numPointers << "," << time;

        // Test with STL SharedPtr
        time = timeDecorator(testPerformance<shared_ptr<int>>, numPointers);
        cout << "STL SharedPtr took " << time << " seconds for " << numPointers << " pointers.\n";
        csvFile << "," << time;

        // Test with your UniquePtr
        time = timeDecorator(testPerformance<UniquePtr<int>>, numPointers);
        cout << "My UniquePtr took " << time << " seconds for " << numPointers << " pointers.\n";
        csvFile << "," << time;

        // Test with STL UniquePtr
        time = timeDecorator(testPerformance<unique_ptr<int>>, numPointers);
        cout << "STL UniquePtr took " << time << " seconds for " << numPointers << " pointers.\n";
        csvFile << "," << time << "\n";
    }
    csvFile.close();

    return 0;
}
