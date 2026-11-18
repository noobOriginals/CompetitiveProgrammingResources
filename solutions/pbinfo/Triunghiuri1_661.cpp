// https://www.pbinfo.ro/probleme/661/triunghiuri1

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());

    int count = 0;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            int diff = v[i] - v[j];
            int end = j - 1, begin = 0;
            int m;
            while (begin <= end) {
                m = (begin + end) / 2;
                if (v[m] <= diff) {
                    begin = m + 1;
                } else {
                    end = m - 1;
                }
            }
            count += j - begin;
        }
    }

    cout << count << "\n";
    return 0;
}
