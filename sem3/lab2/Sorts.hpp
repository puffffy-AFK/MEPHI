#include "Sequence.hpp"
#pragma once
template <typename T>
int CompareFunction(T a, T b) {
    return a - b;
}

template <typename T>
Sequence<T>* BubbleSort(Sequence<T>* seq, int (*cmp)(T,T)) {
    Sequence<T>* result = seq->Copy();
    int length = result->GetLength();
    for (int i = 0; i < length - 1; ++i) {
        for (int j = 0; j < length - i - 1; ++j) {
            if (cmp(result->Get(j), result->Get(j + 1)) > 0) {
                result->swap(j, j + 1);
            }
        }
    }
    return result;
}

template <typename T>
Sequence<T>* ShellSort(Sequence<T>* seq, int (*cmp)(T,T)) {
    Sequence<T>* result = seq->Copy();
    int length = result->GetLength();
    for (int step = length / 2; step > 0; step /= 2) {
        for (int i = step; i < length; ++i) {
            for (int j = i - step; j >= 0 && cmp(result->Get(j), result->Get(j + step)) > 0; j -= step) {
                result->swap(j, j + step);
            }
        }
    }
    return result;
}

template <typename T>
Sequence<T>* InsertionSort(Sequence<T>* seq, int (*cmp)(T,T)) {
    Sequence<T>* result = seq->Copy();
    int length = result->GetLength();
    for (int i = 1; i < length; ++i) {
        for (int j = i; j > 0 && cmp(result->Get(j - 1), result->Get(j)) > 0; --j) {
            result->swap(j - 1, j);
        }
    }
    return result;
}
