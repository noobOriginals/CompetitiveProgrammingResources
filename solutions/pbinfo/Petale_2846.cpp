// https://www.pbinfo.ro/probleme/2846/petale

#include <iostream>
#include <cmath>
using namespace std;

// sin(PI / n) = x / (x + r)
// x * sin(PI / n) + r * sin(PI / n) = x
// r * sin(PI / n) = x * (1 - sin(PI / n))
// x = r * sin(PI / n) / (1 - sin(PI / n))

int main() {
    double n, r;
    cin >> n >> r;
    double s = sin(M_PI / n);
    printf("%.7f\n", (r * s) / (1.0 - s));
    return 0;
}
