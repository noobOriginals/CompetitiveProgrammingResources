// https://kilonova.ro/problems/3965

#include <iostream>
using namespace std;
int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int t, f, r;
		cin >> t >> f;
        r = (t + 1) / 3 + (t / 3) + 1;
		if (f == r) cout << "draw\n";
		else if (f > r) cout << "filippo\n";
		else cout << "tommaso\n";
	}
	return 0;
}
