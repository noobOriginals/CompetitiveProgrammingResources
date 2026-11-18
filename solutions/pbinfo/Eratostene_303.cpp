// https://www.pbinfo.ro/probleme/303/eratostene

#include <stdio.h>
#include <stdlib.h>

int *primes;
void genPrimes(int mx) {
    primes = (int*)calloc(mx + 1, sizeof(int));
    for (int i = 2; i <= mx; i += 1) {
        primes[i] = 1;
    }
    for (int i = 2; i * i <= mx; i += 1) {
        if (primes[i]) {
            printf("%d ", i);
            for (int j = i * i; j <= mx; j += i) {
                primes[j] = 0;
            }
        }
    }
}

int main() {
    FILE *fin, *fout;
    fin = fopen("eratostene.in", "r");
    fout = fopen("eratostene.out", "w");
    genPrimes(1000000);
    int n, x, ct = 0;
    fscanf(fin, "%d", &n);
    for (int i = 0; i < n; i += 1) {
        fscanf(fin, "%d", &x);
        if (primes[x]) {
            ct += 1;
        }
    }
    fprintf(fout, "%d\n", ct);
    free(primes);
    fclose(fout);
    fclose(fin);
    return 0;
}
