#include <string>
#include <vector>
using namespace std;

class GraphBuilder {
    
    private:
        vector<vector<int>> adjList;
        int vertexCnt;
        int edgeCnt;
        void processFileLine(string line, bool isHeader);
    public:
        GraphBuilder();
        int getNumVertices();
        int getNumEdges();
        void buidGraphFromFile(string filename);
        void addVertex();
        void addVertex(int num);
        void addEdge(int fromVertex, int toVertex);
        vector<vector<int>> getGraph();
        void printGraphAsOutput();
};