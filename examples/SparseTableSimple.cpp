// This has the same memory complexity like the SparseTable implementation in a contiguous array, but that has better cache behaviour
// so in practical implementations with large arrays that version behaves better (is faster) than this one, but not by a lot
// Complexity: build - O(n log n), query - O(1)

#include <iostream>
#include <vector>
using namespace std;

static inline int log2fast(int i) {
    return 31 - __builtin_clz(i); // basically O(1), fast CPU instruction. log2 from cmath can also be used
}

static inline int min(int a, int b) {
    return a < b ? a : b;
}

// Example (max number picked)
//  1   4   2   8   5   9  10  11  13  12   3  14   6  18  15  16   7  17  20  19   : block size = 1  (2 ^ k, k = 0)
//  4   4   8   8   9  10  11  13  13  12  14  14  18  18  16  16  17  20  20       : block size = 2  (2 ^ k, k = 1)
//  8   8   9  10  11  13  13  13  14  14  18  18  18  18  17  20  20               : block size = 4  (2 ^ k, k = 2)
// 11  13  13  13  14  14  18  18  18  18  18  20  20                               : block size = 8  (2 ^ k, k = 3)
// 18  18  18  20  20                                                               : block size = 16 (2 ^ k, k = 4)

int main() {
    int n; cin >> n;
    vector<int> v(n);
    for (auto& x : v) cin >> x;

    vector<vector<int>> table(log2fast(n) + 1); // number of levels is max k + 1, and max k is just log2(n)
    table[0].reserve(n); // reserve memory, faster than push_back()
    for (int i : v) table[0].push_back(i); // first level (k = 0) has blocksize = 1, so it is just v
    int blocksize = 1; // always represents the blocksize of level k - 1 (blocksize = 2 ^ (k - 1)), so current blocksize is blocksize << 1
    int len = n; // always represents the length of level k - 1
    int k = 1; // always represents current level
    while ((blocksize << 1) <= n) { // while current blocksize fits the vector
        table[k].reserve(len - blocksize); // reserve memory
        for (int i = 0; i + blocksize < len; i++) { // each range that we must get from last level
            table[k].push_back(min(table[k - 1][i], table[k - 1][i + blocksize])); // compute from last level
        }
        len -= blocksize; // Update length
        blocksize <<= 1; // update blocksize
        k++; // update level
    }

    // Interaction
    int b = 1, e = 1;
    while (cin >> b && b > 0) { // type 0 to exit, any other range to query the table
        cin >> e;
        if (e < b || e > n) { cout << "invalid\n"; continue; }
        b--; e--;

        // Query: complexity O(1)
        int k = log2fast(e - b + 1); // what level fits the sequence
        int ans = min(table[k][b], table[k][e - (1 << k) + 1]); // query the two overlapping sequences and get the answer

        cout << "min : " << ans << "\n";
    }
    return 0;
}
