// https://www.pbinfo.ro/probleme/4914/falternant

// Method-only task, no program, just a subprogram

int FAlternant(int a[], int n) {
    if (n == 1) {
        return 1;
    }
    bool npar = (a[n] % 2 == 0);
    bool nimpar = (a[n - 1] % 2 == 1);
    if ((npar && !nimpar) || (!npar && nimpar)) {
        return 0;
    }
    return FAlternant(a, n - 1);
}
