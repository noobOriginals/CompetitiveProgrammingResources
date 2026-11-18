#! /bin/zsh

cd $(dirname "$0")/examples

name="example"
if [[ -n $1 ]]; then name="$1"; fi

touch "$name.cpp"

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
