// https://www.pbinfo.ro/probleme/2637/zoo

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

typedef long long int64;

struct Shape {
    int n, m;
    Shape(int n, int m) {
        this->n = n;
        this->m = m;
    }
    int size() const {
        return m * n;
    }
};

int flatten(int i, int j, const Shape& shape) {
    return i * shape.m + j;
}

struct Mat {
    Shape shape_;
    vector<int64> data_;
    Mat(const Shape& shape) : shape_(shape), data_(shape.size(), 0) {}
    int64& operator[](int index) {
        return data_[index];
    }
    int64& at(int i, int j) {
        return data_[flatten(i, j, shape_)];
    }
};

int main() {
    fstream fin("zoo.in", ios::in);
    fstream fout("zoo.out", ios::out);
    int n, m, q;

    fin >> n >> m;
    Shape s(n + 1, m + 1);
    n = s.n;
    m = s.m;
    Mat mat(s);

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            fin >> mat.at(i, j);
            mat.at(i, j) += mat.at(i, j - 1) + mat.at(i - 1, j) - mat.at(i - 1, j - 1);
        }
    }

    fin >> q;
    int i1, j1, i2, j2;
    for (int i = 0; i < q; i++) {
        fin >> i1 >> j1 >> i2 >> j2;
        i1 -= 1;
        j1 -= 1;
        fout << mat.at(i2, j2) - mat.at(i2, j1) - mat.at(i1, j2) + mat.at(i1, j1) << "\n";
    }

    fout.close();
    fin.close();
    return 0;
}
