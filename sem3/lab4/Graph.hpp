#pragma once

#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <unordered_map>

// Структура для представления ребра графа
template<typename T>
struct Edge {
    T source, destination;
    int weight;
};

template<typename T>
class Graph {
    int V; // Количество вершин
    std::vector<Edge<T>> edges; // Вектор рёбер
    std::unordered_map<T, std::unordered_map<T, int>> adjacencyMatrix; // Матрица смежности

public:
    Graph(int numVertices) : V(numVertices) {}

    // Добавление ребра в граф
    void addEdge(const T& source, const T& destination, int weight) {
        edges.push_back({source, destination, weight});
        adjacencyMatrix[source][destination] = weight;
        adjacencyMatrix[destination][source] = weight;
    }

    // Функция для вывода графа
    void printGraph() {
        std::cout << "Граф:" << std::endl;
        for (const auto& edge : edges) {
            std::cout << edge.source << " -> " << edge.destination << " : " << edge.weight << std::endl;
        }
    }

    // Функция для красивого вывода матрицы смежности
    void beautyPrintMatrix() {
        std::cout << "Матрица смежности:" << std::endl;

        // Вывод индексов вершин
        std::cout << "      ";
        for (const auto& pair : adjacencyMatrix) {
            std::cout << std::setw(3) << pair.first << " ";
        }
        std::cout << std::endl;

        // Вывод матрицы смежности
        for (const auto& row : adjacencyMatrix) {
            std::cout << std::setw(3) << row.first << " | ";
            for (const auto& pair : adjacencyMatrix) {
                if (row.second.find(pair.first) != row.second.end()) {
                    std::cout << std::setw(3) << row.second.at(pair.first) << " ";
                } else {
                    std::cout << std::setw(3) << "." << " ";
                }
            }
            std::cout << std::endl;
        }
    }


    // Функция для поиска кратчайших путей из источника до всех вершин графа
    std::unordered_map<T, int> BellmanFord(const T& source) {
        std::unordered_map<T, int> dist; // Расстояния до всех вершин
        for (const auto& pair : adjacencyMatrix) {
            dist[pair.first] = std::numeric_limits<int>::max();
        }
        dist[source] = 0; // Расстояние до исходной вершины равно 0

        // Релаксация всех рёбер V-1 раз
        for (int i = 1; i <= V - 1; ++i) {
            for (const auto& edge : edges) {
                if (dist[edge.source] != std::numeric_limits<int>::max() && dist[edge.source] + edge.weight < dist[edge.destination]) {
                    dist[edge.destination] = dist[edge.source] + edge.weight;
                }
            }
        }

        // Проверка наличия циклов с отрицательным весом
        for (const auto& edge : edges) {
            if (dist[edge.source] != std::numeric_limits<int>::max() && dist[edge.source] + edge.weight < dist[edge.destination]) {
                std::cout << "Граф содержит цикл с отрицательным весом" << std::endl;
                return dist;
            }
        }

        return dist;
    }


    // Функция для вывода кратчайших расстояний от источника
    void printShortestDistances(const std::unordered_map<T, int>& distances, const T& source) {
        std::cout << "Кратчайшие расстояния от источника " << source << " к остальным вершинам:" << std::endl;
        for (const auto& pair : distances) {
            std::cout << "Вершина " << pair.first << ": " << pair.second << std::endl;
        }
    }
};
