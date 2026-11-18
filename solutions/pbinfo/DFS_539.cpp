// https://www.pbinfo.ro/probleme/539/dfs

#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<int> G[101];

int main() {
    ifstream cin("dfs.in");
    ofstream cout("dfs.out");
    int n, m, x;
    cin >> n >> m >> x;

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    for (int i = 0; i < n; i++) {
        sort(G[i].rbegin(), G[i].rend());
    }

    vector<bool> visited(n, false);
    stack<int> stk;
    stk.push(x - 1);
    while (!stk.empty()) {
        int n = stk.top();
        stk.pop();
        if (visited[n]) continue;
        cout << n + 1 << " ";
        visited[n] = true;
        for (int nxt : G[n]) stk.push(nxt);
    }
    cout << "\n";

    return 0;
}
