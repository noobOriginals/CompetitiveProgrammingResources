// https://www.pbinfo.ro/probleme/3900/myszkowski

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

int ceilDiv(int a, int b) {
    return (a + b - 1) / b;
}

struct Mat {
    int w, h;
    vector<char> data;
    char& at(int x, int y) { return data[y * w + x]; }
};

ostream& operator<<(ostream& out, Mat& m) {
    for (int y = 0; y < m.h - 1; y++) {
        for (int x = 0; x < m.w - 1; x++) {
            out << m.at(x, y) << " ";
        }
        out << m.at(m.w - 1, y) << "\n";
    }
    for (int x = 0; x < m.w - 1; x++) {
        out << m.at(x, m.h - 1) << " ";
    }
    out << m.at(m.w - 1, m.h - 1);
    return out;
}

void swapCol(Mat& m, int a, int b) {
    for (int i = 0; i < m.h; i++) {
        swap(m.at(a, i), m.at(b, i));
    }
}

string encrypt(string msg, string key) {
    Mat m;
    m.w = key.size();
    m.h = ceilDiv(msg.size(), m.w);
    m.data = vector<char>(m.w * m.h, ' ');
    memcpy(m.data.data(), msg.data(), msg.size());
    vector<char> order(key.size(), 0);
    for (int i = 1; i < key.size(); i++) order[i] = i;
    for (int i = 0; i < key.size() - 1; i++) {
        for (int j = i + 1; j < key.size(); j++) {
            if (key[i] < key[j]) continue;
            if (key[i] == key[j] && order[i] < order[j]) continue;
            swapCol(m, i, j);
            swap(key[i], key[j]);
            swap(order[i], order[j]);
        }
    }
    int midx = 0;
    for (int x = 0; x < m.w;) {
        int off = 1;
        while (key[x + off] == key[x]) off++;
        for (int y = 0; y < m.h; y++) {
            if (m.at(x, y) == ' ') goto cont;
            for (int i = 0; i < off; i++) {
                char c = m.at(x + i, y);
                if (c == ' ') goto cont;
                msg[midx++] = c;
            }
        }
    cont:
        x += off;
    }
    return msg;
}

string decrypt(string msg, string key) {
    Mat m;
    m.w = key.size();
    m.h = ceilDiv(msg.size(), m.w);
    m.data = vector<char>(m.w * m.h, ' ');
    memcpy(m.data.data(), msg.data(), msg.size());
    vector<char> order(key.size(), 0);
    for (int i = 1; i < key.size(); i++) order[i] = i;
    for (int i = 0; i < key.size() - 1; i++) {
        for (int j = i + 1; j < key.size(); j++) {
            if (key[i] < key[j]) continue;
            if (key[i] == key[j] && order[i] < order[j]) continue;
            swapCol(m, i, j);
            swap(key[i], key[j]);
            swap(order[i], order[j]);
        }
    }
    int midx = 0;
    for (int x = 0; x < m.w;) {
        int off = 1;
        while (key[x + off] == key[x]) off++;
        for (int y = 0; y < m.h; y++) {
            if (m.at(x, y) == ' ') goto cont;
            for (int i = 0; i < off; i++) {
                char& c = m.at(x + i, y);
                if (c == ' ') goto cont;
                c = msg[midx++];
            }
        }
    cont:
        x += off;
    }
    for (int i = 0; i < key.size() - 1; i++) {
        for (int j = i + 1; j < key.size(); j++) {
            if (order[i] > order[j]) {
                swapCol(m, i, j);
                swap(order[i], order[j]);
            }
        }
    }
    for (int i = 0; i < msg.size(); i++) {
        msg[i] = m.data[i];
    }
    return msg;
}

int main() {
    ifstream fin("myszkowski.in");
    ofstream fout("myszkowski.out");

    int c;
    string msg, key;
    fin >> c >> msg >> key;
    if (c == 1) {
        fout << encrypt(msg, key);
    } else {
        fout << decrypt(msg, key);
    }

    fout.close();
    fin.close();
    return 0;
}
