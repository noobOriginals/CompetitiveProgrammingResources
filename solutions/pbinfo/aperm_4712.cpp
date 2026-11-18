// https://www.pbinfo.ro/probleme/4712/aperm

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *s;
    int i;
} Word;

Word create_word(char *s, int i) {
    Word w;
    w.s = s;
    w.i = i;
    return w;
}

int global_p = 0;
int cmp(Word a, Word b) {
    for (int i = 0; i < global_p; i++) {
        if (a.s[i] != b.s[i]) {
            return a.s[i] < b.s[i];
        }
    }
    return a.i < b.i;
}

void swp(Word *a, Word *b) {
    Word buff = *a;
    *a = *b;
    *b = buff;
}

int part(Word *v, int b, int e, int p_idx) {
    int i, j;
    swp(&v[e], &v[p_idx]);
    i = j = b;
    while (j < e) {
        if (cmp(v[j], v[e])) {
            swp(&v[j], &v[i]);
            i++;
        }
        j++;
    }
    swp(&v[e], &v[i]);
    return i;
}

void quickSort(Word *v, int b, int e) {
    if (b >= e) {
        return;
    }
    int p_idx = e;
    p_idx = part(v, b, e, p_idx);
    quickSort(v, b, p_idx - 1);
    quickSort(v, p_idx + 1, e);
}

int main() {
    FILE *fin, *fout;
    int n, p, x;
    Word *v;

    fin = fopen("aperm.in", "r");
    fout = fopen("aperm.out", "w");

    fscanf(fin, "%d%d", &n, &p);
    global_p = p;

    v = (Word*)calloc(n, sizeof(Word));

    for (int i = 0; i < n; i++) {
        char *s = (char*)calloc(p, sizeof(char));
        for (int j = 0; j < p; j++) {
            fscanf(fin, "%d", &x);
            s[j] = (char)x;
        }
        v[i] = create_word(s, i);
    }

    quickSort(v, 0, n - 1);

    for (int i = 0; i < n; i++) {
        fprintf(fout, "%d\n", v[i].i + 1);
        free(v[i].s);
    }

    free(v);
    fclose(fin);
    fclose(fout);
    return 0;
}
