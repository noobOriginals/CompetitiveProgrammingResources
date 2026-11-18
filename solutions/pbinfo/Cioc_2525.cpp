// https://www.pbinfo.ro/probleme/2525/cioc

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Range {
    int b, e;
};

int part(vector<long>& v, Range r, int p) {
    swap(v[p], v[r.e]);
    int i = r.b, j = r.b;
    while (j < r.e) {
        if (v[j] < v[r.e]) {
            swap(v[j], v[i]);
            i++;
        }
        j++;
    }
    swap(v[r.e], v[i]);
    return i;
}

long select(vector<long> v, int i) {
    Range r = { 0, (int) v.size() - 1 };
    while (r.b < r.e) {
        int p = (r.b + r.e) / 2;
        p = part(v, r, p);
        if (p == i) {
            return v[p];
        } else if (p < i) {
            r.b = p + 1;
        } else {
            r.e = p - 1;
        }
    }
    return v[r.e];
}

int main() {
    ifstream fin("cioc.in");
    ofstream fout("cioc.out");

    int c, n, k;
    fin >> c >> n >> k;
    vector<long> v(n);
    for (auto& x : v) fin >> x;

    long last = select(v, k - 1);
    if (c == 1) {
        k = 0;
        for (auto& x : v) {
            if (x <= last) k++;
        }
        fout << k << "\n";
    } else {
        for (auto& x : v) {
            fout << x << " ";
            if (x <= last) fout << 2 * x << " ";
        }
        fout << "\n";
    }

    fout.close();
    fin.close();
    return 0;
}
