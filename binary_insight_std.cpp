// Created by temur on 10/22/2021.
// SC= 22.4kk Mem =9mb Time=531ms

#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

#ifdef LOCAL

#include "windows.h"
#include "psapi.h"

#endif

using namespace std;
const int MAX_RULES = 150000;
const int MAX_KEYS = 15000;
const int MAX_DIM = 5;
int R, K, D; //Rules Keys Dimension


pair<unsigned int, int> keys[MAX_DIM][MAX_KEYS];
pair<unsigned int, unsigned int> rules[MAX_DIM][MAX_RULES];
unsigned int keys_orig[MAX_DIM][MAX_KEYS];
int result[MAX_KEYS];

bool rule_match(int rule_id, int key_id) {
    for (int i = D - 1; i >= 0; i--) {
        if (rules[i][rule_id].first > keys_orig[i][key_id] || rules[i][rule_id].second < keys_orig[i][key_id])
            return false;
    }
    return true;
}

void solve() {


    auto get_words = []() {
        string text;
        getline(cin, text);
        string space_delimiter = " ";
        vector<string> words{};

        size_t pos = 0;
        while ((pos = text.find(space_delimiter)) != string::npos) {
            words.push_back(text.substr(0, pos));
            text.erase(0, pos + space_delimiter.length());
        }
        words.push_back(text);
        return words;
    };

    cin >> R;
    cin.ignore();

    for (int id = 0; id < R; id++) {
        vector<string> words = get_words();
        if (id == 0) {
            D = words.size();
        }

        for (int i = 0; i < D; i++) {
            const string &str = words[i];

            if (str.size() == 32) {

                unsigned int minx = 0u;
                unsigned int maxx = 0u;
                for (int i = 0; i < 32; i++) {
                    if (str[31 - i] == '*') {
                        maxx |= (1u << i);
                    } else if (str[31 - i] == '1') {
                        minx |= (1u << i);
                        maxx |= (1u << i);
                    }
                }
                rules[i][id] = {minx, maxx};
            } else {
                int m = str.find('-');

                auto f = make_pair((unsigned int) stoi(str.substr(0, m)), (unsigned int) stoi(str.substr(m + 1)));
                rules[i][id] = f;
//                if (i == 4 && id == 0)
//                    cerr <<i << ' ' << id << ' '<< rules[i][id].first << ' ' << rules[i][id].second << endl;
            }
        }
//        return;
    }

//    cerr << rules[4][0].first << ' ' << rules[4][0].second << endl ;

    cin >> K;
    cin.ignore();
    cerr << "R,K,D = " << R << ' ' << K << ' ' << D << endl;

    for (int id = 0; id < K; id++) {
        result[id] = -1;
        vector<string> words = get_words();
        for (int i = 0; i < D; i++) {
            const string &str = words[i];
            unsigned int x = 0u;

            if (str.size() == 32) {
                for (int i = 0; i < 32; i++) {
                    if (str[31 - i] == '1') {
                        x |= (1u << i);
                    }
                }
            } else {
                x = (unsigned int) stoi(str);
            }
            keys[i][id] = {x, id};
            keys_orig[i][id] = x;
        }
    }


    for (int d = 0; d < D; d++) {
        sort(keys[d], keys[d] + K);
    }

//    int shit = 60655;
    int shit = -1;
//    cerr << rules[4][shit].first << ' ' << rules[4][shit].second << endl ;

    long long sum = 0;
    for (int r = 0; r < R; r++) {
        int best_lo = -1;
        int best_rg = 1e9;
        int best_d = -1;
        for (int d = 0; d < D; d++) {

            int lo = lower_bound(keys[d], keys[d] + K, make_pair(rules[d][r].first, (int) -1)) - keys[d];
            int rg = lower_bound(keys[d], keys[d] + K, make_pair(rules[d][r].second, (int) 1e9)) - keys[d];
            if (rg - lo < best_rg - best_lo) {
                best_lo = lo;
                best_rg = rg;
                best_d = d;
            }
        }

        for (int i = best_lo, d = best_d; i < best_rg; i++) {
            int ind = keys[d][i].second;
            if (result[ind] == -1 && rule_match(r, ind)) {
                result[ind] = r;
            }
        }

    }
    for (int i = 0; i < K; i++) {
        cout << result[i] << endl;
    }


}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifdef LOCAL
    freopen("input_test.txt", "r", stdin);
    freopen("output_test.txt", "w", stdout);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    solve();

#ifdef LOCAL

    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *) &pmc, sizeof(pmc));
    SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
    SIZE_T physMemUsedByMe = pmc.WorkingSetSize;

    cerr << "Mem = " << physMemUsedByMe / 1024 << endl;
#endif


    return 0;
}


