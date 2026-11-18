// https://www.pbinfo.ro/probleme/3856/scytale

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

template <typename T>
struct Mat {
    int w, h;
    vector<T> data;
    Mat() : w(0), h(0), data(0) {}
    Mat(int w, int h) : w(w), h(h), data(w * h) {}
    T& at(int x, int y) {
        return data[y * w + x];
    }
    const T& at(int x, int y) const {
        return data[y * w + x];
    }
};

template <typename T>
ostream& operator<<(ostream& out, const Mat<T>& m) {
    for (int y = 0; y < m.h; y++) {
        for (int x = 0; x < m.w; x++) {
            out << m.at(x, y);// << " ";
        }
        out << "\n";
    }
    return out;
}

string encrypt(string msg, int m) {
    int n = msg.size();
    Mat<char> cypher(n, m);
    int x = 0, y = 0;
    for (int i = 0; i < n; i++) {
        if (x >= n) {
            y++;
            x = y;
        }
        cypher.at(x, y) = msg[i];
        x += m;
    }
    for (int i = 0; i < n; i++) {
        msg[i] = cypher.at(i, i % m);
    }
    return msg;
}

string decrypt(string msg, int m) {
    int n = msg.size();
    Mat<char> cypher(n, m);
    int x = 0, y = 0;
    for (int i = 0; i < n; i++) {
        cypher.at(i, i % m) = msg[i];
    }
    for (int i = 0; i < n; i++) {
        if (x >= n) {
            y++;
            x = y;
        }
        msg[i] = cypher.at(x, y);
        x += m;
    }
    return msg;
}

int main() {
    fstream fin("scytale.in", ios::in);
    fstream fout("scytale.out", ios::out);
    int c, m;
    string msg;
    fin >> c >> msg >> m;
    fout << (c == 1 ? encrypt(msg, m) : decrypt(msg, m)) << "\n";
    fout.close();
    fin.close();
    return 0;
}
