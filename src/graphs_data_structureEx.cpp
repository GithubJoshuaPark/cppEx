#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <algorithm> // For std::find
#include "helloEx.h" // for printLine
#include "graphs_data_structureEx.h"

/**
 * @brief A class representing an unweighted, undirected graph using an adjacency list.
 */
class Graph {
private:
    // Adjacency list: maps a vertex to a list of its neighbors.
    std::map<int, std::list<int>> adjList;

    /**
     * @brief A recursive helper function for Depth-First Search.
     * @param v The current vertex being visited.
     * @param visited A map to keep track of visited vertices.
     */
    void DFSHelper(int v, std::map<int, bool>& visited) {
        // Mark the current node as visited and print it
        visited[v] = true;
        std::cout << v << " ";

        // Recur for all the vertices adjacent to this vertex
        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                DFSHelper(neighbor, visited);
            }
        }
    }

public:
    /**
     * @brief Adds an edge between two vertices, creating them if they don't exist.
     * Since the graph is undirected, an edge is added in both directions.
     */
    void addEdge(int src, int dest) {
        // Check if the edge already exists to avoid duplicates.
        // This makes the representation cleaner.
        auto& src_neighbors = adjList[src];
        if (std::find(src_neighbors.begin(), src_neighbors.end(), dest) == src_neighbors.end()) {
            src_neighbors.push_back(dest);
        }

        auto& dest_neighbors = adjList[dest];
        if (std::find(dest_neighbors.begin(), dest_neighbors.end(), src) == dest_neighbors.end()) {
            dest_neighbors.push_back(src);
        }
    }

    /**
     * @brief Prints the adjacency list representation of the graph.
     */
    void printGraph() {
        printLine("Graph Adjacency List");
        for (const auto& pair : adjList) {
            std::cout << "Vertex " << pair.first << ":";
            for (int neighbor : pair.second) {
                std::cout << " -> " << neighbor;
            }
            std::cout << std::endl;
        }
    }

    /**
     * @brief Prints an adjacency matrix representation of the graph.
     */
    void print2DGraph() {
        printLine("Adjacency Matrix Representation");
        if (adjList.empty()) {
            std::cout << "Graph is empty." << std::endl;
            return;
        }

        // 1. Find the maximum vertex number to determine matrix size.
        int max_vertex = 0;
        for (const auto& pair : adjList) {
            if (pair.first > max_vertex) {
                max_vertex = pair.first;
            }
            for (int neighbor : pair.second) {
                if (neighbor > max_vertex) {
                    max_vertex = neighbor;
                }
            }
        }

        // 2. Create and populate the adjacency matrix.
        int matrix_size = max_vertex + 1;
        std::vector<std::vector<int>> matrix(matrix_size, std::vector<int>(matrix_size, 0));

        for (const auto& pair : adjList) {
            for (int neighbor : pair.second) {
                matrix[pair.first][neighbor] = 1;
            }
        }

        // 3. Print the matrix with headers.
        std::cout << "   |";
        for (int i = 0; i < matrix_size; ++i) std::cout << " " << i;
        std::cout << "\n---+";
        for (int i = 0; i < matrix_size; ++i) std::cout << "--";
        std::cout << std::endl;

        for (int i = 0; i < matrix_size; ++i) {
            std::cout << " " << i << " |";
            for (int j = 0; j < matrix_size; ++j) {
                std::cout << " " << matrix[i][j];
            }
            std::cout << std::endl;
        }
    }

    /**
     * @brief Performs a Breadth-First Search (BFS) traversal starting from a given vertex.
     * @param startVertex The vertex to start the traversal from.
     */
    void BFS(int startVertex) {
        std::cout << "\nBreadth-First Search (starting from vertex " << startVertex << "): ";
        std::map<int, bool> visited;
        std::queue<int> queue;

        visited[startVertex] = true;
        queue.push(startVertex);

        while (!queue.empty()) {
            int v = queue.front();
            std::cout << v << " ";
            queue.pop();

            for (int neighbor : adjList[v]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.push(neighbor);
                }
            }
        }
        std::cout << std::endl;
    }

    /**
     * @brief Performs a Depth-First Search (DFS) traversal starting from a given vertex.
     * @param startVertex The vertex to start the traversal from.
     */
    void DFS(int startVertex) {
        std::cout << "\nDepth-First Search (starting from vertex " << startVertex << "): ";
        std::map<int, bool> visited;
        DFSHelper(startVertex, visited);
        std::cout << std::endl;
    }
};

void graphs_data_structureEx(void) {
    printLine("Graphs Data Structure Example");

    Graph g;
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    g.printGraph();
    g.print2DGraph();

    g.BFS(2);
    g.DFS(2);
}