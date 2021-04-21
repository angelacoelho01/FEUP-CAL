/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <limits>
#include <cmath>

template <class T> class Edge;
template <class T> class Graph;

constexpr auto INF = std::numeric_limits<double>::max();

/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */
template <class T>
class Vertex {
    T info;
    std::vector<Edge<T> *> outgoing;  // adj, for edges leaving the vertex
    std::vector<Edge<T> *> incoming; // for edges entering the vertex
    Edge<T> * addEdge(Vertex<T> *dest, double c, double f);
    Vertex(T in);

    bool visited;  // for path finding
    Edge<T> *path; // for path finding

public:
    T getInfo() const;
    std::vector<Edge<T> *> getAdj() const;
    friend class Graph<T>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {
}

template <class T>
Edge<T> *Vertex<T>::addEdge(Vertex<T> *dest, double c, double f) {
    Edge<T> * e = new Edge<T>(this, dest, c, f);
    this->outgoing.push_back(e);
    dest->incoming.push_back(e);
    return e;
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
std::vector<Edge<T> *> Vertex<T>::getAdj() const {
    return this->outgoing;
}


/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */
template <class T>
class Edge {
    Vertex<T> * orig;
    Vertex<T> * dest;
    double capacity;
    double flow;
    Edge(Vertex<T> *o, Vertex<T> *d, double c, double f=0);

public:
    double getFlow() const;
    Vertex<T> *getDest() const;

    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, double w, double f): orig(o), dest(d), capacity(w), flow(f){}

template <class T>
double Edge<T>::getFlow() const {
    return flow;
}

template <class T>
Vertex<T>* Edge<T>::getDest() const {
    return dest;
}


/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;
    Vertex<T>* findVertex(const T &inf) const;
    void resetFlows();
    bool findAugmentationPath(Vertex<T> *s, Vertex<T> *t);
    void testAndVisit(std::queue< Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual);
    double findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t);
    void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double flow);
public:
    std::vector<Vertex<T> *> getVertexSet() const;
    Vertex<T> *addVertex(const T &in);
    Edge<T> *addEdge(const T &sourc, const T &dest, double c, double f=0);
    void fordFulkerson(T source, T target);

};

template <class T>
Vertex<T> * Graph<T>::addVertex(const T &in) {
    Vertex<T> *v = findVertex(in);
    if (v != nullptr)
        return v;
    v = new Vertex<T>(in);
    vertexSet.push_back(v);
    return v;
}

template <class T>
Edge<T> * Graph<T>::addEdge(const T &sourc, const T &dest, double c, double f) {
    auto s = findVertex(sourc);
    auto d = findVertex(dest);
    if (s == nullptr || d == nullptr)
        return nullptr;
    else
        return s->addEdge(d, c, f);
}

template <class T>
Vertex<T>* Graph<T>::findVertex(const T & inf) const {
    for (auto v : vertexSet)
        if (v->info == inf)
            return v;
    return nullptr;
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}


/**
 * Finds the maximum flow in a graph using the Ford Fulkerson algorithm
 * (with the improvement of Edmonds-Karp).
 * Assumes that the graph forms a flow network from source vertex 's'
 * to sink vertex 't' (distinct vertices).
 * Receives as arguments the source and target vertices (identified by their contents).
 * The result is defined by the "flow" field of each edge.
 */
template <class T>
void Graph<T>::fordFulkerson(T source, T target) {
    // TODO
    resetFlows();
    Vertex<T> *src = findVertex(source);
    Vertex<T> *trg = findVertex(target);
    if(src == NULL || trg == NULL) return;
    //double tot = 0;
    while(findAugmentationPath(src, trg)) {
        double f = findMinResidualAlongPath(src, trg);
        augmentFlowAlongPath(src, trg, f);
        //tot += f;
    }
}

template <class T>
void Graph<T>::resetFlows() {
    // Reset the flow of all adjacent edges for each vertex
    for(Vertex<T> *vertex : vertexSet) {
        for(Edge<T>* edgeIn : vertex->incoming)
            edgeIn->flow = 0;

        for(Edge<T> *edgeOut : vertex->outgoing)
            edgeOut->flow = 0;
    }
}

template <class T>
bool Graph<T>::findAugmentationPath(Vertex<T> *s, Vertex<T> *t) { // Edmonds- Karp (breadth-first)
    std::queue<Vertex<T>*> queue;
    for(Vertex<T> *vertex : vertexSet)
        vertex->visited = false;

    queue.push(s);
    s->visited = true;

    while(!queue.empty() && !t->visited) {
        Vertex<T> *currentVertex = queue.front();
        queue.pop();

        for(Edge<T> *edgeOut : currentVertex->outgoing) // direct residual edges
            testAndVisit(queue, edgeOut, edgeOut->getDest(), edgeOut->capacity - edgeOut->flow);

        for(Edge<T> *edgeIn : currentVertex->incoming)
            testAndVisit(queue, edgeIn, edgeIn->orig, edgeIn->flow);
    }
    return t->visited;
}

template <class T>
void Graph<T>::testAndVisit(std::queue< Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual) {
    if(!w->visited && residual > 0) {
        w->visited = true;
        w->path = e;
        q.push(w);
    }
}

template <class T>
double Graph<T>::findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t) {
    double f = INF;
    Vertex<T> *vertex = t;
    while(vertex != s) {
        Edge<T>* edge = vertex->path;
        if(edge->getDest() == vertex) { // direct residual edge
            f = std::min(f, edge->capacity - edge->getFlow());
            vertex = edge->orig;
        } else { // reverse residual edge
            f = std::min(f, edge->getFlow());
            vertex = edge->getDest();
        }
    }
    return f;
}

template <class T>
void Graph<T>::augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double flow) {
    Vertex<T> *vertex = t;
    while(vertex != s) {
        Edge<T> *edge = vertex->path;
        if(edge->getDest() == vertex) { // direct residual edge
            edge->flow = edge->getFlow() + flow;
            vertex = edge->orig;
        } else { // reverse residual edge
            edge->flow = edge->getFlow() - flow;
            vertex = edge->getDest();
        }
    }
}



#endif /* GRAPH_H_ */
