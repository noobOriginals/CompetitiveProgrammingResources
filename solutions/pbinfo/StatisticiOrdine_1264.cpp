// https://www.pbinfo.ro/probleme/1264/statisticiordine

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
int part(vector<unsigned int>& v, int b, int e, int p) {
    swap(v[e], v[p]);
    int i, j;
    i = j = b;
    while (j < e) {
        if (v[j] < v[e]) {
            swap(v[j], v[i]);
            i++;
        }
        j++;
    }
    swap(v[e], v[i]);
    return i;
}
unsigned int select(vector<unsigned int>& v, int b, int e, int k) {
    if (b >= e) return v[e];
    int p = (b + e) / 2;
    p = part(v, b, e, p);
    if (p == k) return v[p];
    if (p < k) return select(v, p + 1, e, k);
    return select(v, b, p - 1, k);
}
int main() {
    ifstream fin("statisticiordine.in");
    ofstream fout("statisticiordine.out");
    int n, k;
    fin >> n >> k;
    vector<unsigned int> v(n);
    for (auto& x : v) {
        fin >> x;
    }
    fout << select(v, 0, n - 1, k- 1) << "\n";
    fout.close();
    fin.close();
    return 0;
}
