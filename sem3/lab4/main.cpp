#include "Graph.hpp"
#include "TimeMeasure.hpp"
#include "TestGraph.hpp"

void manualInput() {
    std::cout << "Enter the number of vertices: ";
    int numVertices;
    std::cin >> numVertices;
    if (numVertices <= 0) {
        while (numVertices <= 0) {
            std::cout << "Invalid number of vertices. Please try again: ";
            std::cin >> numVertices;
        }
    }
    Graph<std::string> graph(numVertices);
    std::string start, end;
    int weight;

    while (true) {
        std::cout << "Enter edge (start end weight), or 'done' to finish: ";
        std::cin >> start;
        if (start == "done") break;
        std::cin >> end >> weight;
        graph.addEdge(start, end, weight);
    }

    graph.printGraph();
    graph.beautyPrintMatrix();

    std::string startVertex;
    std::cout << "Enter the start vertex: ";
    std::cin >> startVertex;

    auto distances = measureAlgorithmTime([&graph, startVertex](){ return graph.BellmanFord(startVertex); });
    graph.printShortestDistances(distances, startVertex);
}

int main() {
    while (true) {
        std::cout << "Enter 1 to run tests, 2 for manual input, or 'exit' to quit: ";
        std::string choice;
        std::cin >> choice;

        if (choice == "1") {
            std::cout << "Running tests...\n";
            testGraphCreation();
            testAddEdge();
            testBellmanFord();
            std::cout << "All tests passed!\n";
        } else if (choice == "2") {
            manualInput();
        } else if (choice == "exit") {
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
