// https://www.pbinfo.ro/probleme/1598/coada1

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Queue {
    int f = 0;
    vector<int> data;
    void push(int x) { data.push_back(x); }
    int pop() { f++; if (f > data.size() / 2) resize(); return data[f - 1]; }
    int front() { return data[f]; }
    int back() { return data.back(); }
    void resize() {
        if (f >= data.size()) {
            data.clear();
            f = 0;
            return;
        }
        for (int i = 0; i < data.size() - f; i++) {
            swap(data[i], data[i + f]);
        }
        data.resize(data.size() - f);
        data.shrink_to_fit();
        f = 0;
    }
    int size() { return data.size() - f; }
    int& operator[](int idx) { return data[idx + f]; }
};

int src(Queue& v, int x) {
    for (int i = 0; i < v.size(); i++) {
        if (x == v[i]) {
            return i;
        }
    }
    return -2;
}

int main() {
    ifstream fin("coada1.in");
    ofstream fout("coada1.out");

    int m, x;
    string op;
    Queue v;
    fin >> m;
    for (int i = 0; i < m; i++) {
        fin >> op >> x;
        int idx = src(v, x);
        if (op == "query") {
            fout << idx + 1 << "\n";
        } else {
            if (idx >= 0) {
                for (int j = 0; j <= idx; j++) {
                    v.pop();
                }
            }
            v.push(x);
        }
    }

    fout.close();
    fin.close();
    return 0;
}
