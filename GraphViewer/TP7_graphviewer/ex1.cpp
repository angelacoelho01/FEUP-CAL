#include "graphviewer.h"

using namespace std;
using Node = GraphViewer::Node;
using Edge = GraphViewer::Edge;

void ex1() {
    // Instantiate GraphViewer
    GraphViewer gv;

    // Set coordinates of window center
    gv.setCenter(sf::Vector2f(300, 300));

    // Create node
    Node &node0 = gv.addNode(0, sf::Vector2f(200, 300));
    node0.setColor(GraphViewer::BLUE); // Change color

    // Create a blue node with ID 1 at (400, 300)
    Node &node1 = gv.addNode(1, sf::Vector2f(400, 300));
    node1.setColor(GraphViewer::BLUE);

    // Bidirectional edge
    Edge &edge0 = gv.addEdge(0, node0, node1, GraphViewer::Edge::EdgeType::UNDIRECTED);

    // Directed edge
    // Edge &edge0 = gv.addEdge(0, node0, node1, GraphViewer::Edge::EdgeType::DIRECTED);

    // Remove node 1
    gv.removeNode(1);

    // Add new node with id 2 at (500, 300)
    Node &node2 = gv.addNode(2, sf::Vector2f(500, 300));

    // Add black edge between nodes 0 and 2
    Edge &edge1 = gv.addEdge(1, node0, node2, GraphViewer::Edge::EdgeType::UNDIRECTED);

    // Add a label to vertex 2 with text
    node2.setLabel("This is a vertex");

    // Add a label to edge1 with text
    edge1.setLabel("This is an edge");

    // Make node2 green
    node2.setColor(GraphViewer::GREEN);

    // Make edges yellow
    for(Edge *edge : gv.getEdges())
        edge->setColor(GraphViewer::YELLOW);

    // Make the "background.png" image the background
    gv.setBackground("../TP7_graphviewer/resources/background.png");

    // Create Window
    gv.createWindow(600, 600);

    // Join viewer thread (blocks till window closed)
    gv.join();
}
