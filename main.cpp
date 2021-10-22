//
// Created by temur on 10/22/2021.
//

//#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

#ifdef LOCAL

//#include "windows.h"
//#include "psapi.h"

#endif

using namespace std;
const int MAX_RULES = 150000;
const int MAX_KEYS = 15000;
const int MAX_DIM = 5;
int R, K, D; //Rules Keys Dimension
#define keys ksdljg
pair<unsigned int, int> keys[MAX_DIM][MAX_KEYS];
pair<unsigned int, unsigned int> rules[MAX_DIM][MAX_RULES];
int result[MAX_KEYS];

bitset<MAX_KEYS> unmatched, mask;
bitset<MAX_KEYS> dp[MAX_DIM][MAX_KEYS + 5];

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
                assert(m != -1);
                auto f = make_pair((unsigned int)stoi(str.substr(0, m)), (unsigned int)stoi(str.substr(m + 1)));
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

            if (str.size() == 32) {
                unsigned int x = 0u;
                for (int i = 0; i < 32; i++) {
                    if (str[31 - i] == '1') {
                        x |= (1u << i);
                    }
                }
                keys[i][id] = {x, id};
            } else {
                keys[i][id] = {(unsigned int)stoi(str), id};
            }
        }
    }


    for (int d = 0; d < D; d++) {
        sort(keys[d], keys[d] + K);
        for (int i = 0; i < K; i++) {
            dp[d][i + 1] = dp[d][i];
            dp[d][i + 1].set(keys[d][i].second);
        }
    }
    for (int i = 0; i < K; i++) unmatched.set(i, true);

//    int shit = 60655;
    int shit = -1;
//    cerr << rules[4][shit].first << ' ' << rules[4][shit].second << endl ;

    for (int r = 0; r < R; r++) {
        mask = unmatched;

        for (int d = 0; d < D; d++) {

            int lo = lower_bound(keys[d], keys[d] + K, make_pair(rules[d][r].first, (int) -1)) - keys[d];
            int rg = lower_bound(keys[d], keys[d] + K, make_pair(rules[d][r].second, (int) 1e9)) - keys[d] ;
            if (r == shit) {
                cerr << keys[d][lo-1].first << ' ' << keys[d][lo].first << ' ' << keys[d][rg-1].first << ' ' << keys[d][rg].first<< endl;
                cerr << rules[d][r].first << ' ' << rules[d][r].second << endl ;
                cerr << lo << ' ' << rg << endl << endl;
            }

            mask &= dp[d][lo] ^ dp[d][rg];
        }
        if (r%15000==0) cerr << unmatched.count() << endl;
        for (int i = 0; i < K; i++) {
            if (mask.test(i)) {
                result[i] = r;
                unmatched.set(i, false);
            }
        }
    }
    cerr << unmatched.count() << endl;

    for (int i = 0; i < K; i++) {
        cout << result[i] << endl;
    }


}

int main() {
    ios_base::sync_with_stdio(false);
#ifdef LOCAL
    freopen("input_test.txt", "r", stdin);
    freopen("output_test.txt", "w", stdout);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    solve();

#ifdef LOCAL

//    PROCESS_MEMORY_COUNTERS_EX pmc;
//    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *) &pmc, sizeof(pmc));
//    SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
//    SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
//
//    cerr << "Mem = " << physMemUsedByMe / 1024 << endl;
#endif


    return 0;
}

