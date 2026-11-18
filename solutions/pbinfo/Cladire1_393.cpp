// https://www.pbinfo.ro/probleme/393/cladire1

#include <iostream>
#include <fstream>

using namespace std;

int mat[1001][1001];

int moduri(int n, int m) {
    if (n < 1 || m < 1 || n > 1000 || m > 1000) {
        return 0;
    }
    if (mat[n][m] == -1) {
        return 0;
    }
    if (n == 1 && m == 1) {
        return 1;
    }
    if (mat[n][m] == 0) {
        mat[n][m] = (moduri(n - 1, m) + moduri(n, m - 1)) % 9901;
    }
    return mat[n][m];
}

int main() {
    fstream fin("cladire1.in", ios::in);
    fstream fout("cladire1.out", ios::out);

    int n, m, k;
    fin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        int x, y;
        fin >> x >> y;
        mat[x][y] = -1;
    }

    fout << moduri(n, m) << "\n";

    fout.close();
    fin.close();
    return 0;
}
