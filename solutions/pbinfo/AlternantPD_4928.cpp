// https://www.pbinfo.ro/probleme/4928/alternantpd

#include <iostream>

using namespace std;

long long v[91];

long long T(int n) {
    v[1] = 2;
    v[2] = 3;
    for (int i = 3; i <= n; i++) {
        v[i] = v[i - 1] + v[i - 2];
    }
    return v[n];
}

int main() {
    int n;
    cin >> n;
    cout << T(n) << "\n";
    return 0;
}
