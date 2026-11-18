// https://www.pbinfo.ro/probleme/1327/sirpie

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
    while (a != b) {
        a -= a > b ? b : 0;
        b -= b > a ? a : 0;
    }
    return a;
}

void ins(vector<int>& v, int idx, int x) {
    v.push_back(x);
    for (int i = v.size() - 1; i > idx; i--) swap(v[i - 1], v[i]);
}

void rem(vector<int>& v, int idx) {
    for (int i = idx; i < v.size() - 1; i++) swap(v[i], v[i + 1]);
    v.pop_back();
}

void show(ostream& out, vector<int>& v, vector<int>& buff) {
    if (v.empty()) {
        for (int& x : buff) out << x << " ";
        out << "\n";
        return;
    }
    for (int i = 0; i < v.size(); i++) {
        if (!buff.empty()) if (gcd(buff.back(), v[i]) != 1) continue;
        buff.push_back(v[i]);
        rem(v, i);
        show(out, v, buff);
        ins(v, i, buff.back());
        buff.pop_back();
    }
}

int main() {
    ifstream fin("sirpie.in");
    ofstream fout("sirpie.out");
    int n;
    fin >> n;
    vector<int> v(n), buff;
    for (int& x : v) fin >> x;
    sort(v.begin(), v.end());
    show(fout, v, buff);
    return 0;
}
