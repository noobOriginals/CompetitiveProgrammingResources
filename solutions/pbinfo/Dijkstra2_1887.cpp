// https://www.pbinfo.ro/probleme/1887/dijkstra2

#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#define INF 1000000000000

typedef pair<int, long> Node;

struct Cmp { bool operator()(const Node& a, const Node& b) { return a.second > b.second; } };

vector<long> Dijkstra(vector<vector<Node>>& G, int p) {
    vector<long> dist(G.size(), INF);
    priority_queue<Node, vector<Node>, Cmp> q;
    q.push(make_pair(p, 0));
    while (!q.empty()) {
        Node n = q.top();
        q.pop();
        if (n.second > dist[n.first]) continue;
        dist[n.first] = n.second;
        for (Node nn : G[n.first]) {
            if (n.second + nn.second < dist[nn.first]) {
                q.push(make_pair(nn.first, n.second + nn.second));
            }
        }
    }
    return dist;
}

int main() {
    ifstream cin("dijkstra2.in");
    ofstream cout("dijkstra2.out");
    int n, m, p;
    cin >> n >> m >> p;
    p--;
    vector<vector<Node>> G(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        long w;
        cin >> x >> y >> w;
        x--; y--;
        G[x].push_back(make_pair(y, w));
        G[y].push_back(make_pair(x, w));
    }
    vector<long> dist = Dijkstra(G, p);
    for (long d : dist) cout << (d < INF ? d : -1) << " ";
    cout << "\n";
    return 0;
}
