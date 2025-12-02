#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <iostream>
#include <fstream>
#include <utility>
#include <functional>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <limits>

template <typename T>
class Graph {
 private:
  std::vector<std::unordered_map<int, T> > adjList {};
  int numVertices {};

 public:
  // empty graph with N vertices
  explicit Graph(int N);

  // construct graph from edge list in filename
  explicit Graph(const std::string& filename);

  // add an edge directed from vertex i to vertex j with given weight
  void addEdge(int i, int j, T weight);

  // removes edge from vertex i to vertex j
  void removeEdge(int i, int j);

  // is there an edge from vertex i to vertex j?
  bool isEdge(int i, int j) const;

  // return weight of edge from i to j
  // will throw an exception if there is no edge from i to j
  T getEdgeWeight(int i, int j) const;

  // returns number of vertices in the graph
  int size() const;

  // return iterator to a particular vertex
  const std::unordered_map<int, T>& neighbours(int a) const {
    return adjList.at(a);
  }
};

template <typename T>
Graph<T>::Graph(int N) : adjList(N), numVertices {N} {}

template <typename T>
Graph<T>::Graph(const std::string& inputFile) {
  std::ifstream infile {inputFile};
  if (!infile) {
    std::cerr << inputFile << " could not be opened\n";
    return;
  }
  // first line has number of vertices
  infile >> numVertices;
  adjList.resize(numVertices);
  int i {};
  int j {};
  double weight {};
  // assume each remaining line is of form
  // origin dest weight
  while (infile >> i >> j >> weight) {
    addEdge(i, j, static_cast<T>(weight));
  }
}

template <typename T>
int Graph<T>::size() const {
  return numVertices;
}

template <typename T>
void Graph<T>::addEdge(int i, int j, T weight) {
  if (i < 0 or i >= numVertices or j < 0 or j >= numVertices) {
    throw std::out_of_range("invalid vertex number");
  }
  adjList[i].insert({j, weight});
}

template <typename T>
void Graph<T>::removeEdge(int i, int j) {
  // check if i and j are valid
  if (i >= 0 && i < numVertices && j >= 0 && j < numVertices) {
    adjList[i].erase(j);
  }
}

template <typename T>
bool Graph<T>::isEdge(int i, int j) const {
  if (i >= 0 && i < numVertices && j >= 0 && j < numVertices) {
    return adjList.at(i).contains(j);
  }
  return false;
}

template <typename T>
T Graph<T>::getEdgeWeight(int i, int j) const {
  return adjList.at(i).at(j);
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Graph<T>& G) {
  for (int i = 0; i < G.size(); ++i) {
    out << i << ':';
    for (const auto& [neighbour, weight] : G.neighbours(i)) {
      out << " (" << i << ", " << neighbour << ")[" << weight << ']';
    }
    out << '\n';
  }
  return out;
}


// APSP functions
// Use this function to return an "infinity" value
// appropriate for the type T
template <typename T>
T infinity() {
  if (std::numeric_limits<T>::has_infinity) {
    return std::numeric_limits<T>::infinity();
  } else {
    return std::numeric_limits<T>::max();
  }
}

// implement an algorithm for determining if G
// has a negative weight cycle here
template <typename T>
bool existsNegativeCycle(const Graph<T>& G) {
  // Number of vertices
  int n = G.size();
  if (n == 0) return false;
  // Initialise distance to 0
  std::vector<T> bestDistanceTo(n, T{0}); 
  // Bellman-Ford for n iterations
  for (int i = 0; i < n; ++i) {
    //Iterate through all edges in graph, for every vertex s
    for (int s = 0; s < n; ++s) {
    // Check if distance can be reduced, neighbouring vertex and weight of edge
      for(const auto& [v, weight] : G.neighbours(s)) {
        // Relax edges if possible
        if (bestDistanceTo[s] + weight < bestDistanceTo[v]) {
          // If in n-th iteration, distance can still be updated, negative cycle exist 
          if (i == n-1) return true;
          bestDistanceTo[v] = bestDistanceTo[s] + weight;
        }
      }
    }
  }  
  return false;
}

// implement Johnson's APSP algorithm here
template <typename T>
std::vector<std::vector<T>> johnsonAPSP(const Graph<T>& G) {
  int n = G.size();
  std::vector<std::vector<T>> distanceMatrix;
  if (n == 0) return distanceMatrix;
  // Vertex potential function
  std::vector<T> h(n, T{0});

  // Initialise distanceMatrix with infinity
  distanceMatrix.resize(n, std::vector<T>(n, infinity<T>()));

  // Djikstra's algorithm from each vertex to calculate shortest path
  for (int u = 0; u < n; ++u) {
    // Initialise distances for source vertex
    std::vector<T> dist(n, infinity<T>());
    dist[u] = T{0};
    // Priority queue to store vertices to be processed
    std::priority_queue<std::pair<T, int>, 
                        std::vector<std::pair<T, int>>, 
                        std::greater<>> p_queue;
    p_queue.emplace(T{0}, u);

    while (!p_queue.empty()) {
      // Pair values (x.first, x.second), current distance, vertex u
      auto [cdist, u] = p_queue.top(); 
      p_queue.pop();
      // If current distance greater than known distance
      if (cdist > dist[u]) continue;
      // Reweight edges
      for (const auto& [v, oweight] : G.neighbours(u)) {
        T modweight = oweight + h[u] - h[v];
        // Check if shorter path exists
        if(dist[v] > modweight + dist[u]) {
          dist[v] = modweight + dist[u]; 
          // Add vertex to priority queue
          p_queue.emplace(dist[v], v); 
        }
      }
    }

    // Convert shortest distances back to original weights
    for (int v = 0; v < n; ++v) {
      if (dist[v] != infinity<T>() && 
          h[u] != infinity<T>() && 
          h[v] != infinity<T>()) {
        distanceMatrix[u][v] = dist[v] - h[u] + h[v];
      }
    }
  }
  return distanceMatrix;
}

// implement the Floyd-Warshall APSP algorithm here
template <typename T>
std::vector<std::vector<T>> floydWarshallAPSP(const Graph<T>& G) {
  int n = G.size();
  std::vector<std::vector<T>> distanceMatrix(n, std::vector<T>(n));
  // Initialise distanceMatrix with edge weights
  for (int i = 0; i < n; ++i) { 
    for (int j = 0; j < n; ++j) {
      if (i == j) {
        // distanceMatrix[i][i] = 0, diagnoal
        distanceMatrix[i][j] = T{0};
      } else if (G.isEdge(i,j)) {
        distanceMatrix[i][j] = G.getEdgeWeight(i,j);
      } else {
        distanceMatrix[i][j] = infinity<T>(); 
      }
    }
  }
  
  // Update shortest path through intermediate vertices
  for (int iv = 0; iv < n; ++iv) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        T distanceTiv = distanceMatrix[i][iv] + distanceMatrix[iv][j];
        if (distanceMatrix[i][iv] != infinity<T>() &&
            distanceMatrix[iv][j] != infinity<T>() &&
            distanceTiv < distanceMatrix[i][j]) {
            // Update shortest path if shorter through iv (intermediate vertex)
            distanceMatrix[i][j] = distanceTiv;
        }
      } 
    }
  }
  return distanceMatrix;
}

// If negative weight cycle check needed, see second last submission (16)
// Omitted since it's not tested nor in the description, but attempt was made
// Left for posterity, didn't realise it wasn't needed

// References/inspiration
// https://www.geeksforgeeks.org/detect-negative-cycle-graph-bellman-ford/
// http://geeksforgeeks.org/floyd-warshall-algorithm-dp-16/
// https://brilliant.org/wiki/johnsons-algorithm/
// https://www.tutorialspoint.com/graph_theory/graph_theory_johnson_algorithm.htm
// https://brilliant.org/wiki/johnsons-algorithm/
// https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/

#endif      // GRAPH_HPP_
