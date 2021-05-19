#include "graphviewer.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;
using Node = GraphViewer::Node;
using Edge = GraphViewer::Edge;

void read(std::string path, std::vector<std::vector<int>>& info) {
    std::ifstream file(path);

    if(file) {
        std::string line;

        getline(file, line);
        std::stringstream ssNumLines(line);
        int numLines = 0;
        ssNumLines >> numLines;

        for(int i = 0; i < numLines; i++) {
            getline(file, line);
            std::stringstream ss(line);
            int n1 = 0, n2 = 0, n3 = 0;
            ss >> n1 >> n2 >> n3;
            info.push_back(std::vector<int>{n1, n2, n3});
        }
    }
}


void ex3() {
    GraphViewer gv;
    gv.setCenter(sf::Vector2f(500, 500));

    std::vector<std::vector<int>> nodes, edges;
    read("../TP7_graphviewer/resources/map1/nodes.txt", nodes);
    read("../TP7_graphviewer/resources/map1/edges.txt", edges);

    for(int i = 0; i < nodes.size(); i++) {
        int id = nodes.at(i).at(0);
        int x = nodes.at(i).at(1);
        int y = nodes.at(i).at(2);
        gv.addNode(id, sf::Vector2f((float) x, (float) y));
    }

    for(int i = 0; i < edges.size(); i++) {
        int id = edges.at(i).at(0);
        int fromNode = edges.at(i).at(1);
        int toNode = edges.at(i).at(2);
        gv.addEdge(id, gv.getNode(fromNode), gv.getNode(toNode));
    }


    gv.createWindow(1000, 1000);
    gv.join();
}

