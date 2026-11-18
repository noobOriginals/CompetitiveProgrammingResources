// https://www.pbinfo.ro/probleme/3009/zts

#include <iostream>
using namespace std;

int rebase(unsigned long x) {
    int rebased = 0, pow = 0;
    unsigned long r;
    while (x > 0) {
        r = x % 3;
        x /= 3;
        for (int i = 0; i < pow; i++) {
            r *= 3;
        }
        rebased += r % 7;
        rebased %= 7;
        pow++;
    }
    return rebased;
}

int main() {
    int n;
    unsigned long x;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        cout << rebase(x) << "\n";
    }
    return 0;
}
