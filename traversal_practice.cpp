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
    processed[parent] = true;

    for(int i = 0; i < graph[parent].size(); i++) {
      curVertex = graph[parent][i];
      if(!processed[curVertex]) {
        //process edge (parent, curVertex)
        cout << "processing edge: " << parent << "," << curVertex << endl;
      }
      if(!discovered[curVertex]) {
        q.push(curVertex);
        discovered[curVertex] = true;
        relationships[curVertex] = parent;
      }
    }
  }
  return relationships;
}

vector<int> buildPath(int target, vector<int> relationships, vector<int> path) {
  if(relationships[target] == -1) {
    return path;
  }
  path.insert(path.begin(),relationships[target]);
  return buildPath(relationships[target], relationships, path);
}

vector<int> shortestPathBFS(int start, int target, vector<vector<int>> graph) {
  vector<int> relationships = bfs(graph, start);
  vector<int> path;
  vector<int> sp = buildPath(target, relationships, path);
  sp.push_back(target); //add the target as the last node in the path
  return sp;
}

vector<int> connections(vector<vector<int>> graph) {
  vector<bool> visited(graph.size(), false);
  vector<int> connections(graph.size(), -1);
  queue<int> q;
  int connectValue = 1;
  int parent;
  int curVertex;
  cout << "starting..." << endl;
  for(int i = 0; i < visited.size(); i++) {
    if(!visited[i]) {
      parent = i;
      q.push(parent);
      visited[parent] = true;
      connections[parent] = connectValue;
      cout << "visiting " << parent << endl;
      while(!q.empty()) {
        parent = q.front();
        cout << "parent is " << parent << endl;
        q.pop();
        for(int j = 0; j < graph[parent].size(); j++) {
          curVertex = graph[parent][j];
          if(!visited[curVertex]) {
            cout << "visiting neighbor " << parent << endl;
            visited[curVertex] = true;
            connections[curVertex] = connectValue;
            q.push(curVertex);
          }
        }
      }
      connectValue++; 
    }
  }
  return connections;
}

int main() {
  GraphBuilder gb = GraphBuilder();
  gb.buidGraphFromFile("graph.txt");

  //vector<int> shortPath = shortestPathBFS(0,3,gb.getGraph());
  vector<int> connectionsVector = connections(gb.getGraph());

  for(int x : connectionsVector) {
    cout << x << endl;
  }

  return 0;
}
