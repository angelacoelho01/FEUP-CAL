/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"

#include <sstream>
#include <iostream>


template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
    T info;						// content of the vertex
    std::vector<Edge<T> > adj;		// outgoing edges

    double dist = 0;
    Vertex<T> *path = NULL;
    int queueIndex = 0; 		// required by MutablePriorityQueue

    bool visited = false;		// auxiliary field
    bool processing = false;	// auxiliary field

    void addEdge(Vertex<T> *dest, double w);

public:
    Vertex(T in);
    T getInfo() const;
    double getDist() const;
    Vertex *getPath() const;

    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex<T> *d, double w);
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;    // vertex set

public:
    Vertex<T> *findVertex(const T &in) const;
    bool addVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w);
    int getNumVertex() const;
    std::vector<Vertex<T> *> getVertexSet() const;

    // Fp06 - single source
    void unweightedShortestPath(const T &s);    //TODO...
    void dijkstraShortestPath(const T &s);      //TODO...
    void bellmanFordShortestPath(const T &s);   //TODO...
    std::vector<T> getPath(const T &origin, const T &dest) const;   //TODO...

    // Fp06 - all pairs
    void floydWarshallShortestPath();   //TODO...
    std::vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    std::queue<Vertex<T>*> queue;
    Vertex<T>* originVertex = findVertex(orig);
    for(Vertex<T>* v : vertexSet) {
        v->dist = INF;
        v->path = NULL;
    }
    originVertex->dist = 0;
    queue.push(originVertex);
    while(!queue.empty()) {
        Vertex<T>* v = queue.front();
        queue.pop();
        for(Edge<T> e : v->adj) {
            if(e.dest->getDist() == INF) {
                queue.push(e.dest);
                e.dest->dist = v->getDist() + 1;
                e.dest->path = v;
            }
        }
    }
}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    MutablePriorityQueue<Vertex<T>> priorityQueue;
    Vertex<T> *originVertex = findVertex(origin);
    for(Vertex<T>* v : vertexSet) {
        v->dist = INF;
        v->path = NULL;
    }
    originVertex->dist = 0;
    priorityQueue.insert(originVertex);
    while(!priorityQueue.empty()) {
        Vertex<T> *v = priorityQueue.extractMin();
        for(Edge<T> e : v->adj) {
            if(e.dest->getDist() > v->getDist() + e.weight) {
                if(e.dest->queueIndex == 0) {
                    priorityQueue.insert(e.dest);
                } else {
                    priorityQueue.decreaseKey(e.dest);
                }
                e.dest->dist = v->getDist() + e.weight;
                e.dest->path = v;
                priorityQueue.decreaseKey(e.dest);
            }
        }
    }
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    // TODO implement this
    Vertex<T> *originVertex = findVertex(orig);
    for(Vertex<T> *v : vertexSet) {
        v->dist = INF;
        v->path = NULL;
    }
    originVertex->dist = 0;
    for(unsigned i = 0; i < vertexSet.size(); i++) {
        for(Vertex<T> *v : vertexSet) {
            for (Edge<T> e : v->adj) {
                if (e.dest->getDist() > v->getDist() + e.weight) {
                    e.dest->dist = v->getDist() + e.weight;
                    e.dest->path = v;
                }
            }
        }
    }
    for(Vertex<T> * v : vertexSet) {
        for(Edge<T> e : v->adj) {
            if (e.dest->getDist() > v->getDist() + e.weight) {
                e.dest->dist = v->getDist() + e.weight;
                e.dest->path = v;
                std::cout << "There are cycles of negative weight.\n" << std::endl;
            }
        }
    }
}


template<class T>
std::vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
    std::vector<T> res;
    Vertex<T> *originVertex = findVertex(origin), *destVertex = findVertex(dest);
    if(originVertex == NULL || destVertex == NULL) return res;
    res.push_back(destVertex->getInfo());
    while(originVertex != destVertex) {
        if(destVertex->getPath() == NULL) return std::vector<T>();
        destVertex = destVertex->getPath();
        res.insert(res.begin(), destVertex->getInfo());
    }
    return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    // TODO implement this
}

template<class T>
std::vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
    std::vector<T> res;
    // TODO implement this
    return res;
}


#endif /* GRAPH_H_ */
