// https://www.pbinfo.ro/probleme/4676/elicopter

#include <iostream>
#include <fstream>
using namespace std;

struct node {
    short x = 0, y = 0;
    node() = default;
    node(short x, short y) : x(x), y(y) {}
    bool valid(node max) { return x >= 0 && x < max.x && y >= 0 && y < max.y; }
};

node dim;
int map[1000][1000];

int traceidx = 0;
int trace[1000][1000];

int stkidx = 0;
node stk[1000000];
bool visit(int h) {
    stkidx = 0;
    traceidx++;
    for (short y = 0; y < dim.y; y++) {
        if (map[y][0] > h) continue;
        stk[++stkidx] = node(0, y);
    }
    while (stkidx > 0) {
        node n = stk[stkidx--];
        if (!n.valid(dim)) continue;
        if (map[n.y][n.x] > h) continue;
        if (trace[n.y][n.x] == traceidx) continue;
        if (n.x == dim.x - 1) return true;
        trace[n.y][n.x] = traceidx;
        stk[++stkidx] = node(n.x - 1, n.y);
        stk[++stkidx] = node(n.x, n.y - 1);
        stk[++stkidx] = node(n.x, n.y + 1);
        stk[++stkidx] = node(n.x + 1, n.y);
    }
    return false;
}

int main() {
    ifstream fin("elicopter.in");
    ofstream fout("elicopter.out");

    fin >> dim.y >> dim.x;
    for (short y = 0; y < dim.y; y++) {
        for (short x = 0; x < dim.x; x++) {
            fin >> map[y][x];
        }
    }

    int minh = 1, maxh = 1000000;
    int lasth = maxh, h;
    while (minh <= maxh) {
        h = (minh + maxh) / 2;
        if (visit(h)) {
            lasth = h;
            maxh = h - 1;
        } else {
            minh = h + 1;
        }
    }
    fout << lasth << "\n";

    fout.close();
    fin.close();
    return 0;
}
