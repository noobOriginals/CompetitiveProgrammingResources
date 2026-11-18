// https://www.pbinfo.ro/probleme/618/inaltimi

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Copil {
    int h, i;
};

bool comp(Copil a, Copil b) {
    return a.h <= b.h;
}

int main() {
    int n, x;
    vector<Copil> v;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        Copil c;
        c.h = x;
        c.i = i;
        v.push_back(c);
    }
    sort(v.begin(), v.end(), comp);
    for (int i = 0; i < n; i++) {
        cout << v[i].i + 1 << " ";
    }
    cout << "\n";
    return 0;
}
