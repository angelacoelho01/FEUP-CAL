#include "graphviewer.h"

#include <vector>
#include <unistd.h>
#include <iostream>

using namespace std;
using Node = GraphViewer::Node;
using Edge = GraphViewer::Edge;

void ex2() {
    GraphViewer gv;
    gv.setCenter(sf::Vector2f(500, 500));
    gv.createWindow(1000, 1000);

    // Add nodes
    vector<sf::Vector2f> nodes = {
            sf::Vector2f(300, 50),
            sf::Vector2f(318, 58),
            sf::Vector2f(325, 75),
            sf::Vector2f(318, 93),
            sf::Vector2f(300, 100),
            sf::Vector2f(282, 93),
            sf::Vector2f(275, 75),
            sf::Vector2f(282, 58),
            sf::Vector2f(150, 200),
            sf::Vector2f(300, 200),
            sf::Vector2f(450, 200),
            sf::Vector2f(300, 400),
            sf::Vector2f(200, 550),
            sf::Vector2f(400, 550)
    };

    for(int i = 0; i < nodes.size(); i++)
        gv.addNode(i, nodes.at(i));


    // Add edges
    vector<pair<int, int>> edges = {
            pair<int, int>(0, 1),
            pair<int, int>(1, 2),
            pair<int, int>(2, 3),
            pair<int, int>(3, 4),
            pair<int, int>(4, 5),
            pair<int, int>(5, 6),
            pair<int, int>(6, 7),
            pair<int, int>(7, 0),
            pair<int, int>(4, 9),
            pair<int, int>(9, 8),
            pair<int, int>(9, 10),
            pair<int, int>(9, 11),
            pair<int, int>(11, 12),
            pair<int, int>(11, 13)
    };

    for(int i = 0; i < edges.size(); i++)
        gv.addEdge(i, gv.getNode(edges.at(i).first), gv.getNode(edges.at(i).second), Edge::EdgeType::UNDIRECTED);

    for(int i = 0; i < 30; i++) {
        Node &node12 = gv.getNode(12);
        Node &node13 = gv.getNode(13);
        gv.lock();

        if(i % 2 == 0) {
            node12.setPosition(sf::Vector2f(250, 550));
            node13.setPosition(sf::Vector2f(350, 550));
        } else {
            node12.setPosition(sf::Vector2f(200, 550));
            node13.setPosition(sf::Vector2f(400, 550));
        }
        gv.unlock();
        sleep(sf::seconds(1));
    }

    gv.join();
}

