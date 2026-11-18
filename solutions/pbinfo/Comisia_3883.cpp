// https://www.pbinfo.ro/probleme/3883/comisia

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Node {
    int x, b, e;
    Node* left, * right;
    Node(int x, int b, int e) : x(x), b(b), e(e), left(nullptr), right(nullptr) {}
    ~Node() { if (left) delete left; if (right) delete right; }
};

Node* Init(const vector<int>& v, int b, int e) {
    int x = v[e];
    for (int i = b; i < e; i++) if (v[i] > x) x = v[i];
    Node* root = new Node(x, b, e);
    if (b == e) return root;
    int mid = (b + e) / 2;
    root->left = Init(v, b, mid);
    root->right = Init(v, mid + 1, e);
    return root;
}

int Query(Node* root, int b, int e) {
    if (b > root->e || e < root->b) return 0;
    if (b <= root->b && e >= root->e) return root->x;
    int l = Query(root->left, b, e);
    int r = Query(root->right, b, e);
    return l > r ? l : r;
}

int getMax(Node* root, int b, int e) {
    return Query(root, b, e);
}

int getEnd(Node* root, const vector<int>& A, int start) {
    int end = start, req = A[start];
    while (req > end - start + 1) {
        end = start + req - 1;
        if (end >= A.size()) return -1;
        int max = getMax(root, start, end);
        if (max > req) req = max;
    }
    return end;
}

int main() {
    ifstream fin("comisia.in");
    ofstream fout("comisia.out");

    long n;
    fin >> n;
    vector<int> A(n);
    vector<long> B(n);
    for (int& x : A) fin >> x;
    n = 0;
    for (long& x : B) {
        fin >> x;
        n += x;
        x = n;
    }
    n = A.size();

    Node* root = Init(A, 0, n - 1);

    long min = B.back();
    for (int i = 0; i < n; i++) {
        int j = getEnd(root, A, i);
        if (j < 0) continue;
        long risk = B[j] - (i > 0 ? B[i - 1] : 0);
        if (risk < min) min = risk;
    }
    fout << min << "\n";

    delete root;

    fout.close();
    fin.close();
    return 0;
}
