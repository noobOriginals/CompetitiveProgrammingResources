// https://www.pbinfo.ro/probleme/1865/summit

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int search(unsigned long long x, const vector<unsigned long long>& v) {
    int b = 0, e = v.size() - 1, m;
    while (b <= e) {
        m = (b + e) / 2;
        if (v[m] == x) {
            return m + 1;
        }
        if (v[m] > x) {
            e = m - 1;
        } else {
            b = m + 1;
        }
    }
    return 0;
}

int main() {
    ifstream fin("summit.in");
    ofstream fout("summit.out");

    int n;
    fin >> n;
    vector<unsigned long long> sum(n);
    unsigned long long last = 0, x;
    for (int i = 0; i < n; i++) {
        fin >> x;
        sum[i] = last + x;
        last = sum[i];
    }
    fout << search(sum[0], sum) << "\n";
    for (int i = 1; i < n; i++) {
        fout << search(sum[i] - sum[i - 1], sum) << "\n";
    }

    fout.close();
    fin.close();
    return 0;
}
