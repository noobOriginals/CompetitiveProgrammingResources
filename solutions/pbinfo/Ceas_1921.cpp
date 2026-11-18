// https://www.pbinfo.ro/probleme/1921/ceas

#include <stdio.h>
#include <math.h>

int main() {
    double PI = 2 * acos(0.0);
    FILE* fin;
    FILE* fout;
    fin = fopen("ceas.in", "r");
    int r, h, m;
    fscanf(fin, "%d%d%d", &r, &h, &m);
    fclose(fin);
    double angle = 360 * (m + h * 60.0) / 720;
    angle *= PI / 180.0;
    double x = sin(angle) * r;
    double y = cos(angle) * r;
    fout = fopen("ceas.out", "w");
    fprintf(fout, "%lf %lf\n", x, y);
    fclose(fout);
    return 0;
}
