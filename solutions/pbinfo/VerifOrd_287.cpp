// https://www.pbinfo.ro/probleme/287/veriford

#include <iostream>
#include <vector>
using namespace std;

int checkVec(const vector<int>& v) {
    int last = -1000000;
    for (auto x : v) {
        if (x < last) {
            return 0;
        }
        last = x;
    }
    return 1;
}

void read_arr(std::istream& in, vector<int>& v) {
    for (auto& x : v) {
        in >> x;
    }
}

int main() {
    int n, x;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        vector<int> v(x);
        read_arr(cin, v);
        cout << checkVec(v) << " ";
    }
    cout << "\n";
    return 0;
}
