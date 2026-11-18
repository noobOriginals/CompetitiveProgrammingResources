// https://www.pbinfo.ro/probleme/3206/nrinversiuni

#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> vec;

long total(vec& v, int b, int e, vec& aux) {
    if (b >= e) return 0;
    int m = (b + e) / 2;
    long t = total(v, b, m, aux) + total(v, m + 1, e, aux);
    int i = b, j = m + 1, x = b;
    while (i <= m && j <= e) {
        if (v[i] > v[j]) {
            aux[x++] = v[i++];
            t += e - j + 1;
        } else {
            aux[x++] = v[j++];
        }
    }
    while (i <= m) aux[x++] = v[i++];
    while (j <= e) aux[x++] = v[j++];
    while (b <= e) {
        v[b] = aux[b];
        b++;
    }
    return t;
}

int main() {
    int n;
    cin >> n;
    vec v(n), aux(n);
    for (auto& x : v) cin >> x;
    cout << total(v, 0, n - 1, aux) << "\n";
    return 0;
}
