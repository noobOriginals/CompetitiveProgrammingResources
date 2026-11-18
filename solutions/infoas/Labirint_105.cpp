// https://infoas.ro/problema/labirint

#include <iostream>
#include <fstream>
#include <queue>
#include <cmath>
using namespace std;

struct Node {
    int x, y, d;
    Node() : x(0), y(0), d(0) {}
    Node(int x, int y) : x(x), y(y), d(0) {}
    Node(int x, int y, int d) : x(x), y(y), d(d) {}
    bool inBounds(const Node& min, const Node& max) { return x >= min.x && x <= max.x && y >= min.y && y <= max.y; }
    bool operator==(const Node& other) { return x == other.x && y == other.y; }
    bool operator!=(const Node& other) { return !(*this == other); }
};

int matA[1000][1000];
int matB[1000][1000];

#define trypush(nnn, mat) { \
    Node node = nnn; \
    if (node.inBounds(min, max) && mat[node.x][node.y] == 0) nodes.push(node); \
}

int getDistance(Node a, Node b, int mat[1000][1000], int w, int h) {
    Node minBound(0, 0), maxBound(w - 1, h - 1);
    Node dir[4] = {Node(1, 0), Node(-1, 0), Node(0, 1), Node(0, -1)};
    int d = 1000001;
    for (int i = 0; i < 4; i++) {
        Node n(a.x + dir[i].x, a.y + dir[i].y);
        if (n.inBounds(minBound, maxBound) && mat[n.x][n.y] < 0) {
            long t = abs(mat[n.x][n.y] - mat[b.x][b.y]) + 2;
            if (t < d) d = t;
        }
    }
    return d;
}

int main() {
    ifstream fin("labirint.in");
    ofstream fout("labirint.out");

    int w, h, d;
    char c;
    fin >> h >> w;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            fin >> c;
            matA[x][y] = (int) (c - '0');
            matB[x][y] = (int) (c - '0');
        }
    }

    Node min(0, 0), max(w - 1, h - 1);

    queue<Node> nodes;
    nodes.push(Node(0, 0, -1));
    while (!nodes.empty()) {
        Node n = nodes.front();
        nodes.pop();
        matA[n.x][n.y] = n.d;
        trypush(Node(n.x + 1, n.y, n.d - 1), matA);
        trypush(Node(n.x - 1, n.y, n.d - 1), matA);
        trypush(Node(n.x, n.y + 1, n.d - 1), matA);
        trypush(Node(n.x, n.y - 1, n.d - 1), matA);
    }
    nodes.push(Node(max.x, max.y, -1));
    while (!nodes.empty()) {
        Node n = nodes.front();
        nodes.pop();
        matB[n.x][n.y] = n.d;
        trypush(Node(n.x + 1, n.y, n.d - 1), matB);
        trypush(Node(n.x - 1, n.y, n.d - 1), matB);
        trypush(Node(n.x, n.y + 1, n.d - 1), matB);
        trypush(Node(n.x, n.y - 1, n.d - 1), matB);
    }

    d = abs(matA[0][0] - matA[max.x][max.y]) + 1;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (matA[x][y] != 1) {
                fout << "0";
                continue;
            }
            int da = getDistance(Node(x, y), Node(0, 0), matA, w , h);
            int db = getDistance(Node(x, y), Node(w - 1, h - 1), matB, w, h);
            int dist = da + db - 1;
            if (dist < d) {
                fout << "1";
            } else {
                fout << "0";
            }
        }
        fout << "\n";
    }

    fout.close();
    fin.close();
    return 0;
}
