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
template <typename T>
T infinity() {
  if (std::numeric_limits<T>::has_infinity) {
    return std::numeric_limits<T>::infinity();
  } else {
    return std::numeric_limits<T>::max();
  }
}

// updates distTo by relaxing all edges
template <typename T>
void relaxEdges(const Graph<T>& G, std::vector<T>& distTo) {
  int N = G.size();
  for (int vertex = 0; vertex < N; ++vertex) {
    for (const auto& [neighbour, weight] : G.neighbours(vertex)) {
      T distViaVertex = distTo.at(vertex) + weight;
      if (distViaVertex < distTo.at(neighbour)) {
        distTo.at(neighbour) = distViaVertex;
      }
    }
  }
}

template <typename T>
std::vector<T> bellmanFordZeroSource(const Graph<T>& G) {
  int N = G.size();
  // initialised with 0 this time because extra source connected with 
  // weight 0 edge to every other vertex
  std::vector<T> distTo(N, T {});
  for (int round = 0; round < N - 1; ++round) {
    relaxEdges<T>(G, distTo);
  }
  return distTo;
}

template <typename T>
bool existsNegativeCycle(const Graph<T>& G) {
  std::vector<T> distTo = bellmanFordZeroSource(G);
  std::vector<T> distToCopy {distTo};
  relaxEdges(G, distToCopy); 
  return distTo != distToCopy;
}

template <typename T>
std::vector<T> singleSourceLazyDistance(const Graph<T>& G, int source, std::vector<T> potential) {
  // alias the long name for a minimum priority queue holding
  // objects of type DistAndVertex
  using DistAndVertex = std::pair<T, int>;
  using minPQ = std::priority_queue<DistAndVertex,
                                  std::vector<DistAndVertex>,
                                  std::greater<DistAndVertex> >;
  minPQ queue {};
  queue.push({T {}, source});
  // record best distance to vertex found so far
  int N = G.size();
  std::vector<T> bestDistanceTo(N, infinity<T>());
  bestDistanceTo.at(source) = T {};
  // being in visited means we have already explored a vertex's neighbours
  // the bestDistanceTo for a vertex in visited is the true distance.
  std::vector<bool> visited(N);
  while (!queue.empty()) {
    auto [dist, current] = queue.top();
    queue.pop();
    // as we use a lazy version of Dijkstra a vertex can appear multiple
    // times in the queue.  If we have already visited the vertex we
    // take out of the queue we just go on to the next one
    if (visited.at(current)) {
      continue;
    }
    visited.at(current) = true;
    // relax all outgoing edges of current
    for (const auto& [neighbour, weight] : G.neighbours(current)) {
      T distanceViaCurrent = bestDistanceTo.at(current) + weight
        + potential.at(current) - potential.at(neighbour);
      if (bestDistanceTo.at(neighbour) > distanceViaCurrent) {
        bestDistanceTo.at(neighbour) = distanceViaCurrent;
        // lazy dijkstra: nextPoint could already be in the queue
        // we don't update it with better distance just found.
        queue.push({distanceViaCurrent, neighbour});
      }
    }
  }
  // transform bestDistanceTo to original distances
  for (std::size_t i = 0; i < bestDistanceTo.size(); ++i) {
    if (bestDistanceTo.at(i) == infinity<T>()) {
      continue;
    }
    bestDistanceTo.at(i) += potential.at(i) - potential.at(source);
  }
  return bestDistanceTo;
}

template <typename T>
std::vector<std::vector<T> >
johnsonAPSP(const Graph<T>& G) {
  int N = G.size();
  std::vector<T> potential = bellmanFordZeroSource(G);
  std::vector<std::vector<T> > resultsMatrix(N);
  for (int i = 0; i < N; ++i) {
    resultsMatrix.at(i) = singleSourceLazyDistance(G, i, potential);
  }
  return resultsMatrix;
}

template <typename T>
std::vector<std::vector<T> >
floydWarshallAPSP(const Graph<T>& G) {
  int N = G.size();
  T inf = infinity<T>();
  std::vector<std::vector<T> > 
    distanceMatrix(N, std::vector<T>(N, inf));
  // initialise with edge weights
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (G.isEdge(i, j)) {
        distanceMatrix.at(i).at(j) = G.getEdgeWeight(i, j);
      }
    }
  }
  for (int i = 0; i < N; ++i) {
    distanceMatrix.at(i).at(i) = 0;
  }
  // intermediate vertices in {0, ..., k}
  for (int k = 0; k < N; ++k) {
    for (int i = 0; i < N; ++i) {
      if (distanceMatrix.at(i).at(k) == inf) {
        continue;
      }
      for (int j = 0; j < N; ++j) {
        if (distanceMatrix.at(k).at(j) == inf) {
          continue;
        }
        T distanceViaK = distanceMatrix.at(i).at(k) + distanceMatrix.at(k).at(j);
        if (distanceViaK < distanceMatrix.at(i).at(j)) {
          distanceMatrix.at(i).at(j) = distanceViaK;
        }
      }
    }
  }
  return distanceMatrix;
}

#endif      // GRAPH_HPP_
