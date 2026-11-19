#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> DFS(vector<vector<int>>& G, int start) {
    vector<int> path;
    vector<bool> visited(G.size(), false);
    stack<int> stk; // using stack: processes nodes from the last one pushed to the stack
    stk.push(start);
    while (!stk.empty()) {
        int n = stk.top();
        stk.pop();
        if (visited[n]) continue; // skip outdated entries
        visited[n] = true;
        path.push_back(n);
        for (int nn : G[n]) if (!visited[nn]) stk.push(nn);
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
    vector<int> path = DFS(G, x);
    for (int n : path) cout << n << " ";
    cout << "\n";
    return 0;
}
