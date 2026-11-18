// https://infoas.ro/problema/frecventa-impara

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    long long int fin = 0, x;
    scanf("%d", &n);
    for (int i = 0; i < n; i += 1) {
    	scanf("%lld", &x);
        fin = fin ^ x;
    }
    printf("%lld\n", fin);
    return 0;
}
