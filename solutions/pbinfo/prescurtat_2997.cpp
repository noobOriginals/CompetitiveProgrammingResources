// https://www.pbinfo.ro/probleme/2997/prescurtat

// Method-only task, no program, just a subprogram

void Prescurtat(char s[]) {
    const char* words[4] = {"COLEGIUL", "LICEUL", "NATIONAL", "TEORETIC"};
    char cp[100] = {};
    int len = strlen(s), f = 0, ci = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] == '.') {
            int lim = 8;
            int w = 0;
            if (cp[f] == 'L') { w = 1; lim = 6; }
            else if (cp[f] == 'N') w = 2;
            else if (cp[f] == 'T') w = 3;
            for (int j = ci - f; j < lim; j++) cp[ci++] = words[w][j];
            continue;
        }
        cp[ci++] = s[i];
        if (s[i] == ' ') f = ci;
    }
    memcpy(s, cp, 100);
}
