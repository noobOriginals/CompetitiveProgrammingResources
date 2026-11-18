// https://www.pbinfo.ro/probleme/2702/perechisosete

#include <stdio.h>

int main() {
    int n, x, sum, v[101] = {0};
    scanf("%d", &n);
    for (int i = 0; i < n; i += 1) {
        scanf("%d", &x);
        v[x] += 1;
    }
    sum = 0;
    for (int i = 1; i < 101; i += 1) {
        sum += v[i] / 2;
    }
    printf("%d\n", sum);
    return 0;
}
