// https://www.pbinfo.ro/probleme/250/interclasare1

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

vector<int> get_arr(istream& in) {
    int n;
    in >> n;
    vector<int> v(n);
    for (auto& x : v) {
        in >> x;
    }
    return v;
}

ostream& operator<<(ostream& os, const vector<int>& v) {
    for (size_t i = 1; i <= v.size(); i++) {
        os << v[i - 1] << " ";
        if (i % 10 == 0) {
            os << "\n";
        }
    }
    return os;
}

void insert(int x, vector<int>& v, int i) {
    if (i >= v.size()) {
        v.push_back(x);
    }
    v.push_back(0);
    size_t memSz = (v.size() - i - 1) * sizeof(int);
    int* ptr = v.data();
    int* copy = (int*)malloc(memSz);
    memcpy(copy, &ptr[i], memSz);
    memcpy(&ptr[i + 1], copy, memSz);
    free(copy);
    ptr[i] = x;
}

int findX(int x, const vector<int>& v) {
    int b, e, m;
    b = 0;
    e = v.size() - 1;
    while (b <= e) {
        m = (b + e) / 2;
        if (v[m] == x) {
            return m;
        }
        if (v[m] < x) {
            b = m + 1;
        } else {
            e = m - 1;
        }
    }
    return -1;
}

int main() {
    fstream fin("interclasare1.in", ios::in);
    fstream fout("interclasare1.out", ios::out);

    vector<int> A = get_arr(fin);
    vector<int> B = get_arr(fin);

    vector<int> C;
    int i, j;
    i = j = 0;
    while (i < A.size() && j < B.size()) {
        if (A[i] > B[j]) {
            if (findX(B[j], C) == -1) {
                C.push_back(B[j]);
            }
            j++;

        } else {
            if (findX(A[i], C) == -1) {
                C.push_back(A[i]);
            }
            i++;
        }
    }
    while (i < A.size()) {
        C.push_back(A[i]);
        i++;
    }
    while (j < B.size()) {
        C.push_back(B[j]);
        j++;
    }

    fout << C << "\n";

    fout.close();
    fin.close();
    return 0;
}
