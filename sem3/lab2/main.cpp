#include <iostream>
#include <chrono>
#include <random>

#include "Sorts.hpp"
#include "Sorts.hpp"
#include "SharedPtr.hpp"
#include "UniquePtr.hpp"
#include "LinkedListSequence.hpp"
#include "ArraySequence.hpp"

using namespace std;


template <typename T, template <typename> class PtrType>
void testSort(PtrType<Sequence<T>>& sequence, Sequence<T>* (*sortFunction)(Sequence<T>*, int (*)(T, T)), int (*compareFunction)(T, T), int testType) {
    auto start = chrono::high_resolution_clock::now();
    PtrType<Sequence<T>> sortedSeq(sortFunction(sequence.get(), compareFunction));
    auto end = chrono::high_resolution_clock::now();

    cout << "Time: ";
    cout << chrono::duration_cast<chrono::duration<double>>(end - start).count() << " seconds" << endl;
    if (testType == 2) {
        cout << "Sorted Sequence: ";
        for (int i = 0; i < sortedSeq->GetLength(); ++i) {
            cout << sortedSeq->Get(i) << " ";
        }
        cout << endl;
    }
    cout << "----------------------------------------\n";
}

template <typename T, template <typename> class PtrType>
void testSequence(int seqType, int sortType, int begin, int end, int maxLength, int step, int testType) {
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(begin, end);

    PtrType<Sequence<T>> sequence;
    if (seqType == 1) {
        sequence = PtrType<Sequence<T>>(new LinkedListSequence<T>());
    } else {
        sequence = PtrType<Sequence<T>>(new ArraySequence<T>());
    }

    for (int len = step; len <= maxLength; len += step) {
        cout << "===========================================================\n";
        cout << "Length: " << len << endl;

        sequence->Clear();
        for (int j = 0; j < len; ++j) {
            sequence->Append(distr(gen));
        }
        if (testType == 2) {
            cout << "Sequence: ";
            for (int i = 0; i < sequence->GetLength(); ++i) {
                cout << sequence->Get(i) << " ";
            }
            cout << endl;
        }

        // Bubble sort
        cout << "Bubble sort:" << endl;
        testSort(sequence, BubbleSort, CompareFunction, testType);

        // Shell sort
        cout << "Shell sort:" << endl;
        testSort(sequence, ShellSort, CompareFunction, testType);

        // Insertion sort
        cout << "Insertion sort:" << endl;
        testSort(sequence, InsertionSort, CompareFunction, testType);
    }

    return;
}


int main() {
    cout << "Выберите тип ptr:\n";
    cout << "1. SharedPtr\n";
    cout << "2. UniquePtr\n";

    int ptrType;
    cin >> ptrType;

    if (ptrType != 1 && ptrType != 2) {
        cout << "Неверный тип ptr\n";
        return 1;
    }

    cout << "Выберите тип последовательности:\n";
    cout << "1. LinkedListSequence\n";
    cout << "2. DynamicArraySequence\n";

    int seqType;
    cin >> seqType;

    if (seqType != 1 && seqType != 2) {
        cout << "Неверный тип последовательности\n";
        return 1;
    }

    cout << "Выберите режим тестирования:\n";
    cout << "1. Автоматическое тестрование\n";
    cout << "2. Ручное тестирование\n";

    int testType;
    cin >> testType;

    int begin = 0, end = 10000, maxLength = 3000, step = 1000;
    if (testType == 2) {
        cout << "Введите начало диапазона значений:\n";
        cin >> begin;
        cout << "Введите конец диапазона значений:\n";
        cin >> end;

        cout << "Введите максимальную длину последовательности:\n";
        cin >> maxLength;
    
        cout << "Введите шаг:\n";
        cin >> step;
    }


    if (ptrType == 1) {
        testSequence<int, SharedPtr>(seqType, 1, begin, end, maxLength, step, testType);
    } else {
        testSequence<int, UniquePtr>(seqType, 1, begin, end, maxLength, step, testType);
    }

    return 0;
}