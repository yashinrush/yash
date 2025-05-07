#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

class Graph {
    unordered_map<string, vector<pair<string, int>>> adj; // city → [(neighbor, cost)]
    unordered_map<string, bool> visited;

public:
    void addEdge(string src, string dest, int cost) {
        adj[src].push_back({dest, cost});
        adj[dest].push_back({src, cost});  // Assuming undirected (two-way flights)
        visited[src] = false;
        visited[dest] = false;
    }

    void dfs(string city) {
        visited[city] = true;
        for (auto neighbor : adj[city]) {
            if (!visited[neighbor.first])
                dfs(neighbor.first);
        }
    }

    bool isConnected() {
        if (adj.empty()) return true;

        // Start DFS from any node
        auto start = adj.begin()->first;
        dfs(start);

        // Check if all nodes were visited
        for (auto v : visited) {
            if (!v.second)
                return false;
        }
        return true;
    }

    void display() {
        cout << "Flight network (Adjacency List):\n";
        for (auto city : adj) {
            cout << city.first << " → ";
            for (auto neighbor : city.second)
                cout << "(" << neighbor.first << ", cost=" << neighbor.second << ") ";
            cout << endl;
        }
    }
};

int main() {
    Graph g;
    g.addEdge("Mumbai", "Delhi", 2);
    g.addEdge("Mumbai", "Bangalore", 1);
    g.addEdge("Delhi", "Chennai", 3);
    g.addEdge("Bangalore", "Chennai", 4);

    g.display();

    if (g.isConnected())
        cout << "\nThe flight network is connected.\n";
    else
        cout << "\nThe flight network is NOT connected.\n";

    return 0;
}
