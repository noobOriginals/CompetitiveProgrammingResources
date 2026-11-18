// https://kilonova.ro/problems/3970

#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
const uint MAXS = 3000;
int main() {
    int n, S;
    cin >> n >> S;
    vector<int> h(n);
    for (int& i : h) cin >> i;
    bitset<MAXS + 1> pre;
    vector<bitset<MAXS + 1>> suf(n + 1);
    pre[0] = 1;
    suf[n][S] = 1;
    for (int i = n; i > 0; i--) suf[i - 1] = suf[i] | (suf[i] >> h[i - 1]);
    for (int i = 0; i < n; i++) {
        cout << ((pre & suf[i + 1]).none() ? "YES" : "NO") << "\n";
        pre |= pre << h[i];
    }
    return 0;
}
