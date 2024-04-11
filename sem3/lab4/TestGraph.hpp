#pragma once

#include <cassert>

#include "Graph.hpp"

void testGraphCreation() {
    Graph<int> g(5);
    assert(g.BellmanFord(0).size() == 1);
}

void testAddEdge() {
    Graph<int> g(5);
    g.addEdge(0, 1, -1);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 2);
    g.addEdge(1, 4, 2);
    g.addEdge(3, 2, 5);
    g.addEdge(3, 1, 1);
    g.addEdge(4, 3, -3);

    assert(g.BellmanFord(0).size() == 5); // All vertices should be reachable
}

void testBellmanFord() {
    Graph<int> g(5);
    g.addEdge(0, 1, -1);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 2);
    g.addEdge(1, 4, 2);
    g.addEdge(3, 2, 5);
    g.addEdge(3, 1, 1);
    g.addEdge(4, 3, -3);

    auto distances = g.BellmanFord(0);

    assert(distances[0] == 0);
    assert(distances[1] == -1);
    assert(distances[2] == 2);
    assert(distances[3] == -2);
    assert(distances[4] == 1);
}
