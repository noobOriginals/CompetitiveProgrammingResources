// https://www.pbinfo.ro/probleme/3349/putere1

#include <iostream>
using namespace std;

long power(long base, long pow, long modulo) {
    if (pow == 0) {
        return 1;
    }
    base %= modulo;
    if (pow == 1) {
        return base;
    }
    if (pow % 2 == 0) {
        return power(base * base, pow / 2, modulo);
    } else {
        return (power(base * base, pow / 2, modulo) * base) % modulo;
    }
}

int main() {
    long b, n, p;
    cin >> b >> n >> p;
    long modulo = 1;
    for (int i = 0; i < p; i++) {
        modulo *= 10;
    }
    cout << power(b, n, modulo) << "\n";
    return 0;
}
