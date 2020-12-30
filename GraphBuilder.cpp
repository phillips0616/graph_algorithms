#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "GraphBuilder.h"

using namespace std;

GraphBuilder::GraphBuilder() {
    vertexCnt = 0;
    edgeCnt = 0;
    vector<vector<int>> adjList;
};

int GraphBuilder::getNumVertices() {
    return vertexCnt;
}

int GraphBuilder::getNumEdges() {
    return edgeCnt;
}

void GraphBuilder::addVertex() {
    vector<int> x;
    adjList.push_back(x);
    vertexCnt++;
}

void GraphBuilder::addVertex(int num) {
    for(int x = 0; x < num; x++) {
        vector<int> a;
        adjList.push_back(a);
        vertexCnt++;
    }
}

void GraphBuilder::addEdge(int fromVertex, int toVertex) {
    adjList[fromVertex].push_back(toVertex);
    edgeCnt++;
}

void GraphBuilder::processFileLine(string incomingLine, bool isHeader) {
    if(isHeader) {
        addVertex(stoi(incomingLine));
    } else {
        int separator = incomingLine.find(" ");
        string vertexFrom = incomingLine.substr(0, separator);
        string vertexTo = incomingLine.substr(separator + 1, incomingLine.length());
        addEdge(stoi(vertexFrom), stoi(vertexTo));
    }
}

void GraphBuilder::buidGraphFromFile(string filename) {
    fstream file;
    file.open(filename, ios::in);
    if(file.is_open()) {
        string line;
        //first line contains the number of vertices and the number of edges separated by a space character
        getline(file, line);
        processFileLine(line, true);
        while(getline(file, line)) {
            processFileLine(line, false);
        }
        file.close();
    }
}

vector<vector<int>> GraphBuilder::getGraph() {
    return adjList;
}

void GraphBuilder::printGraphAsOutput() {
    for (int x = 0; x < adjList.size(); x++) {
        cout << x << ":";
        for(int y = 0; y < adjList[x].size(); y++) {
            if(y < adjList[x].size() - 1) {
                cout << adjList[x][y] << ",";
            } else {
                cout << adjList[x][y];
            }
        }
        cout << endl;
    }
}

