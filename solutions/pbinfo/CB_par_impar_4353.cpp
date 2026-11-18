// https://www.pbinfo.ro/probleme/4353/cb-par-impar

#include <iostream>
#include <vector>
#include <random>

using namespace std;

void swap(int& a, int& b) {
    int buff = a;
    a = b;
    b = buff;
}

int partition(vector<int>& v, int b, int e, int p_idx) {
    int i, j;
    swap(v[e], v[p_idx]);
    i = j = b;
    while (j < e) {
        if (v[j] < v[e]) {
            swap(v[i], v[j]);
            i++;
        }
        j++;
    }
    swap(v[e], v[i]);
    return i;
}

void sort(vector<int>& v, int b, int e) {
    if (b >= e) {
        return;
    }
    int p_idx = rand() % (e + 1 - b) + b;
    p_idx = partition(v, b, e, p_idx);
    sort(v, b, p_idx - 1);
    sort(v, p_idx + 1, e);
}

int find(vector<int>& v, int b, int e, int item) {
    int m;
    while (b <= e) {
        m = (b + e) / 2;
        if (v[m] == item) {
            return m;
        }
        if (v[m] < item) {
            b = m + 1;
        } else {
            e = m - 1;
        }
    }
    return -1;
}

int main() {
    int n, m;

    cin >> n;
    vector<int> x(n);

    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    sort(x, 0, n / 2 - 1);
    sort(x, n / 2, n - 1);

    cin >> m;

    int y, a, b;
    a = b = 0;
    for (int i = 0; i < m; i++) {
        cin >> y;
        if (y % 2 == 0) {
            if (find(x, 0, n / 2 - 1, y) >= 0) {
                a++;
            }
        } else {
            if (find(x, n / 2, n - 1, y) >= 0) {
                b++;
            }
        }
    }

    cout << a << " " << b << "\n";

    return 0;
}
