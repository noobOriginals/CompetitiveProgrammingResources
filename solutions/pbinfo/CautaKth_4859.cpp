// https://www.pbinfo.ro/probleme/4859/cautakth

// Method-only task, no program, just a subprogram

int CautaKth(int a[], int n, int k) {
    unsigned long idx = a[0] - 1;
    if (idx >= k) {
        return a[0] - (idx - k) - 1;
    }
    for (int i = 1; i < n; i++) {
        idx += a[i] - a[i - 1] - 1;
        if (idx >= k) {
            return a[i] - (idx - k) - 1;
        }
    }
    return -1;
}
