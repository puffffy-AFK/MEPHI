#include <iostream>
#include <vector>

#include "SharedPtr.hpp"
#include "UniquePtr.hpp"

template <typename Container>
void printSequence(const Container& sequence) {
    std::cout << "[";
    for (const auto& element : sequence) {
        std::cout << element << (&element == &sequence.back() ? "" : ", ");
    }
    std::cout << "]";
    std::cout << std::endl;
}

template <typename T, template <typename> class PtrType>
void testSequence() {
    int index;
    T value;

    PtrType<std::vector<T>> sequence = PtrType<std::vector<T>>(new std::vector<T>());

    std::vector<T> subSequence;

    while (true) {
        int choice;
        std::cout << "Choose operation:" << std::endl;
        std::cout << "1. Append" << std::endl;
        std::cout << "2. Get Subsequence" << std::endl;
        std::cout << "3. Print Sequence" << std::endl;
        std::cout << "4. Quit" << std::endl;
        std::cout << "====================" << std::endl;
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter value to append: ";
                std::cin >> value;
                sequence->push_back(value);
                break;
            case 2:
                std::cout << "Enter start index: ";
                std::cin >> index;
                std::cout << "Enter subsequence length: ";
                std::cin >> value;
                if (index >= 0 && index < sequence->size()) {
                    subSequence.assign(sequence->begin() + index,
                                       sequence->begin() + index + value);
                    printSequence(subSequence);
                } else {
                    std::cout << "Invalid index" << std::endl;
                }
                break;
            case 3:
                printSequence(*sequence);
                break;
            case 4:
                return;
            default:
                std::cout << "Invalid choice" << std::endl;
                break;
        }
    }
}

int main() {
    int choice;
    std::cout << "Choose pointer type:" << std::endl;
    std::cout << "1. SharedPtr" << std::endl;
    std::cout << "2. UniquePtr" << std::endl;
    std::cout << "====================" << std::endl;
    std::cin >> choice;

    switch (choice) {
        case 1:
            testSequence<int, SharedPtr>();
            break;
        case 2:
            testSequence<int, UniquePtr>();
            break;
        default:
            std::cout << "Invalid choice" << std::endl;
            break;
    }

    return 0;
}
