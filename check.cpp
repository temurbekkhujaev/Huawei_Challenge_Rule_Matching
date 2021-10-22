//
// Created by temur on 10/22/2021.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    vector<int> v1, v2;
    {
        ifstream cin("output_test.txt");
        int x;
        while (cin >> x) {
            v1.push_back(x);
        }
    }

    {

        ifstream cin("output_correct.txt");
        int x;
        while (cin >> x) {
            v2.push_back(x);
        }
    }
    cerr << v1.size() << ' ' << v2.size() << endl;
    int tot = min(v1.size(),v2.size());
//    assert(v1.size() == v2.size());
    int correct = 0;
    for (int i = 0; i < tot; i++) {
        correct += v1[i] == v2[i];
    }
    cerr << "AC = " << fixed << setprecision(2) << (double) correct / tot << endl;

    return 0;
}