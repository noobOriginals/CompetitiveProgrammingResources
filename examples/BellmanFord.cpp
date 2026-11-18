// Compared to Dijkstra, this algorithm allows negative weights, but it's worst-case complexity is O(n * m)

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define INF 1000000000

vector<int> BellmanFord(vector<vector<pair<int, int>>>& G, int start) {
    vector<int> dist(G.size(), INF);
    queue<pair<int, int>> q;
    q.push(make_pair(start, 0));
    while (!q.empty()) {
        pair<int, int> n = q.front();
        q.pop();
        if (n.second > dist[n.first]) continue; // Distance is greater, we discard this node
        dist[n.first] = n.second; // We save the better distance and continue processing consecutive nodes
        for (pair<int, int>& nn : G[n.first]) {
            q.push(make_pair(nn.first, n.second + nn.second));
        }
    }
    return dist;
}

int main() {
    int n, s;
    cin >> n >> s;
    vector<vector<pair<int, int>>> G(n);
    int x, y, w;
    while (cin >> x >> y >> w) {
        G[x].push_back(make_pair(y, w));
        G[y].push_back(make_pair(x, w)); // Comment for oriented graphs
    }
    vector<int> dist = BellmanFord(G, s);
    for (int n : dist) cout << (n < INF ? n : -1) << " ";
    cout << "\n";
    return 0;
}
