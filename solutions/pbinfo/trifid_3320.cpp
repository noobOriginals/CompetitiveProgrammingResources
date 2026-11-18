// https://www.pbinfo.ro/probleme/3320/trifid

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

string recube(string cube) {
    string cp = cube;
    for (int i = 0; i < 27; i++) {
        cube[i] = cp[i / 3 + (i % 3) * 9];
    }
    return cube;
}

struct XYZ {
    int x, y, z;
};

ostream& operator<<(ostream& out, const XYZ& xyz) {
    out << xyz.x << xyz.y << xyz.z;
    return out;
}

XYZ findInCube(char c, string cube) {
    int i = 0;
    while (cube[i] != c) i++;
    return { i / 9, (i / 3) % 3, i % 3 };
}

char getFromCube(const XYZ& xyz, string cube) {
    return cube[xyz.x * 9 + xyz.y * 3 + xyz.z];
}

string encrypt(string msg, string cube) {
    vector<int> indicees(msg.size() * 3);
    for (int i = 0; i < msg.size(); i++) {
        XYZ xyz = findInCube(msg[i], cube);
        indicees[i] = xyz.x;
        indicees[i + msg.size()] = xyz.y;
        indicees[i + 2 * msg.size()] = xyz.z;
    }
    for (int i = 0; i < msg.size(); i++) {
        XYZ xyz;
        xyz.x = indicees[i * 3];
        xyz.y = indicees[i * 3 + 1];
        xyz.z = indicees[i * 3 + 2];
        msg[i] = getFromCube(xyz, cube);
    }
    return msg;
}

string decrypt(string msg, string cube) {
    vector<int> indicees(msg.size() * 3);
    for (int i = 0; i < msg.size(); i++) {
        XYZ xyz = findInCube(msg[i], cube);
        indicees[i * 3] = xyz.x;
        indicees[i * 3 + 1] = xyz.y;
        indicees[i * 3 + 2] = xyz.z;
    }
    for (int i = 0; i < msg.size(); i++) {
        XYZ xyz;
        xyz.x = indicees[i];
        xyz.y = indicees[i + msg.size()];
        xyz.z = indicees[i + 2 * msg.size()];
        msg[i] = getFromCube(xyz, cube);
    }
    return msg;
}

int main() {
    ifstream fin("trifid.in");
    ofstream fout("trifid.out");
    int c;
    string cube, msg;
    fin >> c;
    for (int i = 0; i < 3; i++) {
        fin >> msg;
        cube += msg;
    }
    cube = recube(cube);
    fin >> msg;
    if (c == 1) {
        fout << encrypt(msg, cube) << "\n";
    } else {
        fout << decrypt(msg, cube) << "\n";
    }
    fout.close();
    fin.close();
    return 0;
}
