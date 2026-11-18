// https://www.pbinfo.ro/probleme/529/cifre4

#include <stdio.h>

int main() {
    int n, x, sum, v[10] = {0}, s[10] = {0}, v2[10] = {0};
    scanf("%d", &n);
    for (int i = 0; i < n; i += 1) {
        scanf("%d", &x);
        while (x > 0) {
            v[x % 10] += 1;
            v2[x % 10] += 1;
            x /= 10;
        }
    }
    for (int i = 0; i < 10; i += 1) {
        s[i] = i;
    }
    for (int i = 0; i < 9; i += 1) {
        for (int j = i + 1; j < 10; j += 1) {
            if (v[i] > v[j]) {
                x = s[i];
                s[i] = s[j];
                s[j] = x;
                x = v[i];
                v[i] = v[j];
                v[j] = x;
            }
        }
    }
    for (int i = 0, j = 1; i < 9; i += 1, j += 1) {
        if (v2[s[i]] == v2[s[j]] && s[i] > s[j]) {
            x = s[i];
            s[i] = s[j];
            s[j] = x;
            i += 1;
            j += 1;
        }
    }
    for (int i = 0; i < 10; i += 1) {
        if (v2[s[i]] > 0) {
            printf("%d ", s[i]);
        }
    }
    printf("\n");
    return 0;
}
