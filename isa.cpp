#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
using namespace std;

typedef pair<int, int> pii;

void dijkstra(const vector<vector<int>>& graph, int src, vector<int>& dist, vector<int>& prev) {
    int n = graph.size();
    dist.assign(n, numeric_limits<int>::max());
    prev.assign(n, -1);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        if (d > dist[u]) continue;
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] > 0) {
                int alt = dist[u] + graph[u][v];
                if (alt < dist[v]) {
                    dist[v] = alt;
                    prev[v] = u;
                    pq.push({alt, v});
                }
            }
        }
    }
}

void printPath(int target, const vector<int>& prev) {
    stack<int> path;
    for (int at = target; at != -1; at = prev[at])
        path.push(at);
    while (!path.empty()) {
        cout << path.top();
        path.pop();
        if (!path.empty()) cout << " -> ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Masukkan jumlah simpul: ";
    cin >> n;
    vector<vector<int>> graph(n, vector<int>(n));
    cout << "Masukkan adjacency matrix (0 jika tidak ada edge):\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> graph[i][j];

    int src, tgt;
    cout << "Masukkan simpul asal: ";
    cin >> src;
    cout << "Masukkan simpul tujuan: ";
    cin >> tgt;

    vector<int> dist, prev;
    dijkstra(graph, src, dist, prev);

    cout << "Jarak terpendek dari " << src << " ke " << tgt << " adalah: " << dist[tgt] << endl;
    cout << "Jalur: ";
    printPath(tgt, prev);

    return 0;
}