// Compared to Sparse Tables, this aproach allows point updates, meaning that you can update the initial array's elements from one value to another
// This is helpful in some situations, but when only querying is needed, use Sparse Tables.
// Complexity: build - O(n log n), query & update - O(log n)

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define INF 1000000000

static inline int log2ceil(int x) {
    int log = 31 - __builtin_clz(x);
    return log + ((1 << log) != x);
}
static inline int min(int a, int b) { return a < b ? a : b; }

// In binary trees that are stored in a 0-indexed array, each parent node n has left child = 2 * n + 1 and right child = 2 * n + 2

void build(vector<int>& v, int l, int r, vector<int>& tree, int node) { // complexity O(n log n)
    int i = l + 1, minimum = v[l];
    while (i <= r) { minimum = min(minimum, v[i]); i++; } // calculate minimum over current range
    tree[node] = minimum;
    if (l == r) return; // leaf node
    int m = (l + r) / 2;
    build(v, l, m, tree, 2 * node + 1); // left child = 2 * n + 1
    build(v, m + 1, r, tree, 2 * node + 2); // right child = 2 * n + 2
}

int query(int l, int r, const vector<int>& tree, int node, int nl, int nr) { // complexity O(log n)
    if (r < nl || l > nr) return INF; // fully outside of queried range, not useful
    if (l <= nl && r >= nr) return tree[node]; // fully inside, return value
    int m = (nl + nr) / 2;
    int leftQuery = query(l, r, tree, 2 * node + 1, nl, m); // query left side
    int rightQuery = query(l, r, tree, 2 * node + 2, m + 1, nr); // query right side
    return min(leftQuery, rightQuery); // return minimum
}

void update(int x, int i, vector<int>& tree, int node, int nl, int nr) { // complexity O(log n)
    if (nl == nr) { tree[node] = x; return; } // first update leaf node
    int m = (nl + nr) / 2;
    if (i <= m) update(x, i, tree, 2 * node + 1, nl, m); // first update sub-ranges
    else update(x, i, tree, 2 * node + 2, m + 1, nr); // first update sub-ranges
    tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]); // now update current node, takes the minimum of its two children nodes
}

int main() {
    int n; cin >> n;
    vector<int> v(n);
    for (auto& x : v) cin >> x;

    vector<int> tree((1 << (log2ceil(n) + 1)) - 1); // length = 2 ^ ceil(log2(n)) - 1
    build(v, 0, n - 1, tree, 0);

    // Interaction
    string cmd;
    int b = 1, e = 1;
    while (cin >> cmd && cmd != "quit") {
        cin >> b >> e;
        if (cmd == "q") {
            if (b < 1 || e < b || e > n) { cout << "invalid range\n"; continue; }
            b--; e--;
            cout << "min : " << query(b, e, tree, 0, 0, n - 1) << "\n";
        } else if (cmd == "u") {
            if (e < 1 || e > n) { cout << "invalid index\n"; continue; }
            e--;
            update(b, e, tree, 0, 0, n - 1);
        } else {
            cout << "invalid command\n";
        }
    }
    return 0;
}
