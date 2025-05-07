#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

int n;  
vector<string> office;  
vector<vector<int>> adj;  

void prims(){
    vector<int> visit(n, 0);  // Array to track visited cities
    int mincost = 0, count = n - 1, minIndex = -1, cost = 0;

    // Start with the first city (index 0)
    visit[0] = 1;
    cout << "Shortest Path: " << office[0] << " -> ";

    while (count--) {
        mincost = INT_MAX;

        // Find the minimum cost edge that connects the visited cities to an unvisited city
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (visit[i] == 1 && adj[i][j] != 0 && adj[i][j] < mincost && visit[j] == 0) {
                    mincost = adj[i][j];
                    minIndex = j;
                }
            }
        }

        // If no edge is found, the graph might be disconnected
        if (minIndex == -1) {
            cout << "The graph is disconnected.\n";
            return;
        }

        visit[minIndex] = 1;
        cout << office[minIndex] << " -> ";
        cost += mincost;
    }

    cout << "Total cost: " << cost << endl;
}

int main() {
    cout << "Enter the number of cities: ";
    cin >> n;

    office.resize(n);
    adj.resize(n, vector<int>(n, 0));  // Adjacency matrix

    cout << "Enter the names of the cities: ";
    for (int i = 0; i < n; i++) {
        cin >> office[i];
    }

    cout << "Enter the cost matrix (use 0 if there's no direct connection between two cities):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "Cost from " << office[i] << " to " << office[j] << ": ";
            cin >> adj[i][j];
        }
    }

    prims();

    return 0;
}
