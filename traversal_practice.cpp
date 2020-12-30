#include <iostream>
#include <vector>
#include <queue>
#include "GraphBuilder.h"

using namespace std;



vector<int> bfs(vector<vector<int>> graph, int start) {
  vector<bool> discovered(graph.size(), false);
  vector<bool> processed(graph.size(), false);
  vector<int> relationships(graph.size(), -1);
  queue<int> q;
  int parent;
  int curVertex;

  q.push(start);
  discovered[start] = true;

  while(!q.empty()) {
    parent = q.front();
    q.pop();
    cout << "processing vertex: " << parent << endl;
    processed[parent] = true;

    for(int i = 0; i < graph[parent].size(); i++) {
      curVertex = graph[parent][i];
      if(!processed[curVertex]) {
        //process edge (parent, curVertex)
        cout << "processing edge: " << parent << "," << curVertex << endl;
      }

      if(!discovered[curVertex])
        q.push(curVertex);
        discovered[curVertex] = true;
        relationships[curVertex] = parent;
    }
  }
  return relationships;
}

vector<int> buildPath(int target, vector<int> relationships, vector<int> path) {
  if(relationships[target] == -1) {
    return path;
  }
  path.push_back(relationships[target]);
  return buildPath(relationships[target], relationships, path);
}

vector<int> shortestPathBFS(int start, int target, vector<vector<int>> graph) {
  vector<int> relationships = bfs(graph, start);
  vector<int> path;
  return buildPath(target, relationships, path);
}

int main() {
  GraphBuilder gb = GraphBuilder();
  gb.buidGraphFromFile("graph.txt");

  vector<int> shortPath = shortestPathBFS(0,3,gb.getGraph());

  for(int x : shortPath) {
    cout << x << endl;
  }

  return 0;
}
