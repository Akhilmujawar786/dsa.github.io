#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int INF = INT_MAX; 

struct Edge {
    int to;
    int weight;

    Edge(int _to, int _weight) : to(_to), weight(_weight) {}
};


vector<int> dijkstra(const vector<vector<Edge>>& graph, int source, int numNodes) {
    vector<int> dist(numNodes, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (const Edge& e : graph[u]) {
            int v = e.to;
            int weight = e.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    
    int numNodes = 5; 
    vector<vector<Edge>> graph(numNodes);

    
    
    graph[0].push_back(Edge(1, 5));  
    graph[0].push_back(Edge(2, 10));  
    graph[1].push_back(Edge(3, 7));   
    graph[2].push_back(Edge(3, 3));   
    graph[3].push_back(Edge(4, 8));  

    
    vector<int> shortestDistances = dijkstra(graph, 0, numNodes);

   
    cout << "Shortest distances from the laundry facility (node 0):" << endl;
    for (int i = 0; i < numNodes; ++i) {
        cout << "Node " << i << ": " << shortestDistances[i] << " units" << endl;
    }

    return 0;
}
