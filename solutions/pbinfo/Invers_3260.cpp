// https://www.pbinfo.ro/probleme/3260/invers

#include <iostream>
#include <cmath>

using namespace std;

#define PRECISION 1000000000.0

double f(double x) {
    return sin(x) + sin(2 * x) + x;
}

int main() {
    double ry;
    cin >> ry;
    long y = PRECISION * ry;
    long xl = 0, xh = PRECISION, xm;
    while (xl <= xh) {
        xm = (xl + xh) / 2;
        long res = f(xm / PRECISION) * PRECISION;
        if (res / 10 == y / 10) {
            printf("%.8lf\n", xm / PRECISION);
            return 0;
        }
        if (res < y) {
            xl = xm + 1;
        } else {
            xh = xm - 1;
        }
    }
    return 0;
}
