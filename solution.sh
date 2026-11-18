#! /bin/zsh

cd $(dirname "$0")/solutions

name="solution"
if [[ -n "$1" ]]; then name="$1"; fi

touch "$name.cpp"

if [[ "$2" == "io" ]]; then

cat <<EOF > "$name.cpp"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("$name.in"); // Comment for stdio input
    ofstream cout("$name.out"); // Comment for stdio output
    int n, min, x;
    cin >> n;
    for (int i = 0; i < n; i++) { cin >> x; if (x < min) min = x; }
    cout << min << "\n";
    return 0;
}
EOF

exit 0

fi

cat <<EOF > "$name.cpp"
#include <iostream>

using namespace std;

int main() {
    int n, min, x;
    cin >> n;
    for (int i = 0; i < n; i++) { cin >> x; if (x < min) min = x; }
    cout << min << "\n";
    return 0;
}
EOF
