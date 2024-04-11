#pragma once

#include <chrono>

// Декоратор для измерения времени работы алгоритма
template<typename Func, typename... Args>
auto measureAlgorithmTime(Func&& func, Args&&... args) {
    auto start = std::chrono::steady_clock::now();
    auto result = std::forward<Func>(func)(std::forward<Args>(args)...);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Время выполнения алгоритма: " << elapsed_seconds.count() << " секунд.\n";
    return result;
}
