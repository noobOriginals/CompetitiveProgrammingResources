// https://www.pbinfo.ro/probleme/845/pattern

#include <iostream>
#include <cmath>
using namespace std;

char mat[1024][1024];
void patt(int sx, int sy, int n) {
    if (n == 1) {
        mat[sx][sy] = 0;
        return;
    }
    int h = n / 2;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < h; x++) {
            mat[y + sy][x + sx] = 1;
        }
    }
    patt(sx + h, sy, h);
    patt(sx, sy + h, h);
    patt(sx + h, sy + h, h);
}

int main() {
    int n;
    cin >> n;
    n = pow(2, n);
    patt(0, 0, n);
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            cout << (int) mat[y][x] << " ";
        }
        cout << "\n";
    }
    return 0;
}
