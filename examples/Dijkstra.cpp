// We always process the smallest total distance first, such that when we process a node, we know that that's the shortest path to it.
// Complexity: O((n + m) log n)

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define INF 1000000000

typedef pair<int, int> Node;

struct Cmp { bool operator()(const Node& a, const Node& b) { return a.second > b.second; } };

vector<int> Dijkstra(vector<vector<Node>>& G, int p) {
    vector<int> dist(G.size(), INF);
    priority_queue<Node, vector<Node>, Cmp> q; // priority queue always puts smallest distance first in queue
    q.push(make_pair(p, 0));
    while (!q.empty()) {
        Node n = q.top();
        q.pop();
        if (n.second >= dist[n.first]) continue; // skip outdated entries
        dist[n.first] = n.second; // processed the node, so this means that it's distance is final, as we always process the shortest total distance
        for (Node nn : G[n.first]) {
            // Push if distance is smaller than already visited
            if (n.second + nn.second < dist[nn.first]) { // this condition is an optimization, so that each node is visited once
                q.push(make_pair(nn.first, n.second + nn.second));
            }
        }
    }
    return dist;
}

int main() {
    int n, m, p;
    cin >> n >> m >> p;
    vector<vector<Node>> G(n);
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        G[x].push_back(make_pair(y, w));
        G[y].push_back(make_pair(x, w)); // Comment for oriented graphs
    }
    vector<int> dist = Dijkstra(G, p);
    for (int d : dist) cout << (d < INF ? d : -1) << " ";
    cout << "\n";
    return 0;
}
