// https://www.pbinfo.ro/probleme/3808/adfgvx

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

template <typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    for (const T& t : v) {
        out << t << "\n";
    }
    return out;
}

struct Code {
    char x, y;
    char& operator[](int i) { return i ? y : x; }
};

const string ADFGVX = "ADFGVX";

Code getCode(const vector<string>& map, char c) {
    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 6; x++) {
            if (c == map[y][x]) {
                return { ADFGVX[x], ADFGVX[y] };
            }
        }
    }
    return { 0, 0 };
}

template <typename T>
void sortByKey(T& v, string key) {
    for (int i = 0; i < key.size() - 1; i++) {
        for (int j = i + 1; j < key.size(); j++) {
            if (key[i] > key[j]) {
                swap(key[i], key[j]);
                swap(v[i], v[j]);
            }
        }
    }
}

string encrypt(const vector<string>& map, const string& msg, const string& key) {
    vector<string> cyph(key.size(), string((msg.size() * 2 + key.size() - 1) / key.size(), ' '));
    int x = 0, y = 0;
    for (const char& c : msg) {
        Code code = getCode(map, c);
        cyph[x++][y] = code.y;
        if (x >= key.size()) {
            x = 0;
            y++;
        }
        cyph[x++][y] = code.x;
        if (x >= key.size()) {
            x = 0;
            y++;
        }
    }
    sortByKey(cyph, key);
    string ret = "";
    for (string& s : cyph) {
        ret += s.substr(0, s.find_last_of(' ')) + " ";
    }
    ret = ret.substr(0, ret.find_last_of(' '));
    return ret;
}

string decrypt(const vector<string>& map, string msg, const string& key) {
    int n = (msg.size() * 2 + key.size() - 1) / key.size();
    vector<string> cyph(key.size(), string(n, ' '));
    msg += " ";
    for (string& s : cyph) {
        int i = msg.find_first_of(' ');
        s = msg.substr(0, i);
        s += string(n - s.size(), ' ');
        msg = msg.substr(i + 1);
    }
    string revKey(key.size(), 0);
    for (int i = 1; i < key.size(); i++) revKey[i] = i;
    sortByKey(revKey, key);
    sortByKey(cyph, revKey);
    string code = "";
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < key.size(); x++) {
            if (cyph[x][y] == ' ') break;
            code += cyph[x][y];
        }
    }
    string ret(code.size() / 2, ' ');
    for (int i = 0; i < ret.size(); i++) {
        ret[i] = map[ADFGVX.find_first_of(code[i * 2])][ADFGVX.find_first_of(code[i * 2 + 1])];
    }
    return ret;
}

int main() {
    fstream fin("adfgvx.in", ios::in);
    fstream fout("adfgvx.out", ios::out);

    int c;
    vector<string> map(6);
    string msg, key;
    fin >> c;
    for (string& s : map) {
        fin >> s;
    }
    msg = "";
    while (fin >> key) {
        msg += " " + key;
    }
    msg = msg.substr(1, msg.find_last_of(' ') - 1);

    if (c == 1) {
        fout << encrypt(map, msg, key) << "\n";
    } else {
        fout << decrypt(map, msg, key) << "\n";
    }

    fout.close();
    fin.close();
    return 0;
}
