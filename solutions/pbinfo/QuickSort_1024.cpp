// https://www.pbinfo.ro/probleme/1024/quicksort

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swp(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int part(int* v, int b, int e, int p) {
    int i, j;
    swp(&v[e], &v[p]);
    i = j = b;
    while (j < e) {
        if (v[j] < v[e]) {
            swp(&v[j], &v[i]);
            i++;
        }
        j++;
    }
    swp(&v[i], &v[e]);
    return i;
}

typedef struct {
    int b, e;
} Range;

Range makeRange(int b, int e) {
    Range r;
    r.b = b;
    r.e = e;
    return r;
}

typedef struct {
    Range* data;
    int len;
} RangeStack;

RangeStack makeStack() {
    RangeStack st;
    st.data = NULL;
    st.len = 0;
    return st;
}

void pushToStack(RangeStack* st, Range r) {
    Range* buffer = st->data;
    st->data = (Range*)calloc(st->len + 1, sizeof(Range));
    if (buffer) {
        memcpy(st->data, buffer, sizeof(Range) * st->len);
        free(buffer);
    }
    st->data[st->len] = r;
    st->len += 1;
}

Range stackFront(RangeStack* st) {
    return st->data[st->len - 1];
}

void popStackFront(RangeStack* st) {
    Range* buffer = st->data;
    st->data = (Range*)calloc(st->len - 1, sizeof(Range));
    memcpy(st->data, buffer, sizeof(Range) * (st->len - 1));
    free(buffer);
    st->len -= 1;
}

void quickSort(int* v, int b, int e) {
    RangeStack st = makeStack();
    pushToStack(&st, makeRange(b, e));
    while (st.len > 0) {
        Range stFront = stackFront(&st);
        popStackFront(&st);
        if (stFront.b < stFront.e) {
            int p = part(v, stFront.b, stFront.e, stFront.e);
            pushToStack(&st, makeRange(stFront.b, p - 1));
            pushToStack(&st, makeRange(p + 1, stFront.e));
        }

    }
}

int main() {
    int n, *v;
    scanf("%d", &n);
    v = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i += 1) {
        scanf("%d", &v[i]);
    }
    quickSort(v, 0, n - 1);
    for (int i = 0; i < n; i += 1) {
        printf("%d ", v[i]);
    }
    printf("\n");
    return 0;
}
