// https://www.pbinfo.ro/probleme/1464/sir7

#include <iostream>
using namespace std;

int main() {
    long p, k;
    cin >> p >> k;
    cout << p + (k / 2) * 10 + ((k - 1) / 2) * 20 << "\n";
    return 0;
}
