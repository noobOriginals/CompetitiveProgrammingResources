// https://www.pbinfo.ro/probleme/3883/comisia

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

static inline int log2fast(int x) { return 31 - __builtin_clz(x); }
static inline int max(int a, int b) { return a > b ? a : b; }
struct Table {
    vector<vector<int>> data;
    int operator[](int i) const { return data[0][i]; }
    int size() const { return data[0].size(); }
    void build(const vector<int>& v) {
        data.clear();
        data.resize(log2fast(v.size()) + 1);
        data[0] = v;
        int block = 1, len = v.size(), k = 1;
        while ((1 << k) <= v.size()) {
            data[k].reserve(len - block);
            for (int i = 0; i + block < len; i++) {
                data[k].push_back(max(data[k - 1][i], data[k - 1][i + block]));
            }
            len -= block;
            block <<= 1;
            k++;
        }
    }
    int query(int l, int r) const {
        int k = log2fast(r - l + 1);
        return max(data[k][l], data[k][r - (1 << k) + 1]);
    }
};

int getRight(int l, const Table& t) {
    int req = t[l], r = l;
    while (req > r - l + 1) {
        r = l + req - 1;
        if (r >= t.size()) return -1;
        req = t.query(l, r);
    }
    return r;
}

int main() {
    ifstream cin("comisia.in");
    ofstream cout("comisia.out");
    int n;
    cin >> n;
    vector<int> v(n);
    vector<long> B(n + 1);
    B[0] = 0;
    for (int& i : v) cin >> i;
    for (int i = 1; i <= n; i++) {
        cin >> B[i];
        B[i] += B[i - 1];
    }
    Table rmq;
    rmq.build(v);
    long minRisk = B.back();
    for (int i = 0; i < n; i++) {
        int r = getRight(i, rmq);
        if (r < 0) continue;
        long risk = B[r + 1] - B[i];
        if (risk < minRisk) minRisk = risk;
    }
    cout << minRisk << "\n";
    return 0;
}
