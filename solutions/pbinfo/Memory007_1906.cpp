// https://www.pbinfo.ro/probleme/1906/memory007

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    ifstream fin("memory007.in");
    ofstream fout("memory007.out");

    int n, m, a, b, x;
    long sum = 0;
    fin >> n >> m >> a >> b;
    vector<bool> app(b - a + 1, false);
    for (int i = 0; i < n; i++) {
        fin >> x;
        app[x - a] = true;
    }
    int idx = 0;
    fin >> x;
    for (int i = 0; i < (int) app.size(); i++) {
        if (app[i]) {
            idx++;
            if (idx == x) {
                sum += i + a;
                fin >> x;
            }
        }
    }
    fout << sum << "\n";

    fout.close();
    fin.close();
    return 0;
}
