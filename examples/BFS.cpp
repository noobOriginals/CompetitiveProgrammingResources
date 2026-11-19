#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> BFS(vector<vector<int>>& G, int start) {
    vector<int> path;
    vector<bool> visited(G.size(), false);
    queue<int> q; // using queue: processes nodes from the first pushed to the queue
    q.push(start);
    while (!q.empty()) {
        int n = q.front();
        q.pop();
        if (visited[n]) continue; // skip outdated entries
        visited[n] = true;
        path.push_back(n);
        for (int nn : G[n]) if (!visited[nn]) q.push(nn);
    }
    return path;
}

int main() {
    int n, m, x;
    cin >> n >> m >> x;
    vector<vector<int>> G(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x); // Comment for oriented graphs
    }
    vector<int> path = BFS(G, x);
    for (int n : path) cout << n << " ";
    cout << "\n";
    return 0;
}
