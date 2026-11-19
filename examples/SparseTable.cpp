#include <iostream>
#include <vector>
#include <functional>
using namespace std;

// I recommend checking out SparseTableSimple.cpp, it is easier to understand and it's better documented

template<typename T>
struct SparseTable {
    function<T(const T&, const T&)> cmp;
    int baseSize = 0;
    vector<int> off;
    vector<T> data;

    SparseTable() = default;
    SparseTable(const vector<T>& v, function<T(const T&, const T&)> compare) { build(v, compare); }

    void build(const vector<T>& v, function<T(const T&, const T&)> compare) {
        // Reset members
        cmp = compare;
        baseSize = v.size();
        off.clear();
        data.clear();

        // Precompute data size
        int levels = 32 - __builtin_clz(v.size());
        int size = v.size() * levels, diff = 1;
        for (int i = 0; i < levels; i++) { size -= diff - 1; diff <<= 1; }
        off.reserve(levels);
        data.reserve(size);

        // Base layer -> offset 0, block size 1
        off.push_back(0);
        int blocksz = 1;
        for (const T& t : v) data.push_back(t);

        // layers k >= 1
        int len = v.size(); // Length of compared array
        while ((blocksz << 1) <= v.size()) { // While current block size <= total elements
            int o = off.back(); // Current level offset
            for (int i = 0; i + blocksz < len; i++) data.push_back(cmp(data[o + i], data[o + i + blocksz])); // Copare elements
            off.push_back(o + len); // Add current offset
            len -= blocksz; // Update length
            blocksz <<= 1; // Update block size
        }
    }

    T query(int l, int r) const {
        if (r < l || r > baseSize) {
            cerr << "invalid\n";
            return T();
        }
        int k = 31 - __builtin_clz(r - l + 1); // log2 length(l, r)
        return cmp(data[off[k] + l], data[off[k] + r - (1 << k) + 1]);
    }
};

int main() {
    int n; cin >> n;
    vector<int> v(n);
    for (auto& x : v) cin >> x;

    // Builds table
    SparseTable<int> min_table(v, [](const int& a, const int& b){ return a < b ? a : b; });
    SparseTable<int> max_table(v, [](const int& a, const int& b){ return a > b ? a : b; });
    SparseTable<int> gcd_table(v, [](const int& a, const int& b){
        int x = a, y = b;
        while (y) { x %= y; swap(x, y); }
        return x;
    });

    // Interaction
    int b = 1, e = 1;
    while (cin >> b && b > 0) { // Type 0 to exit, any other range to query the table
        cin >> e;
        if (e < b || e > n) { cout << "invalid\n"; continue; }
        b--; e--;
        cout << "min : " << min_table.query(b, e) << "\n";
        cout << "max : " << max_table.query(b, e) << "\n";
        cout << "gcd : " << gcd_table.query(b, e) << "\n";
    }
    return 0;
}
