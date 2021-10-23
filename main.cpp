//
// Created by temur on 10/22/2021.
//

#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

#ifdef LOCAL

#include "windows.h"
#include "psapi.h"

#endif

using namespace std;

#ifdef LOCAL
clock_t startTime;

double getCurrentTime() {
    return (double) (clock() - startTime) / CLOCKS_PER_SEC;
}

#endif

const int MAX_RULES = 150000;
const int MAX_KEYS = 15000;
const int MAX_DIM_RANGE = 3;
const int MAX_DIM_MASK = 3;
const int MAX_TOT_DIM = 5;
int R, K, D; //Rules Keys Dimension
int D_mask, D_range;

typedef unsigned short int Mint;
typedef unsigned int Uint;

const int BITS_SIZE = 32; // for Mint
const int MAX_RANGE_LIM = (1 << 16);

Mint first_occ[MAX_DIM_RANGE][MAX_RANGE_LIM + 1];

pair<Uint, Mint> keys_mask[MAX_DIM_MASK][MAX_KEYS];
pair<Mint, Mint> keys_range[MAX_DIM_RANGE][MAX_KEYS];

pair<Uint, Uint> rules_mask[MAX_DIM_MASK][MAX_RULES];
pair<Mint, Mint> rules_range[MAX_DIM_RANGE][MAX_RULES];

Uint keys_mask_orig[MAX_DIM_MASK][MAX_KEYS];
Mint keys_range_orig[MAX_DIM_RANGE][MAX_KEYS];

int result[MAX_KEYS];
int RULE_TYPE[MAX_TOT_DIM];
Uint shift[BITS_SIZE]; // precalced binary shifts




#ifdef LOCAL
double last_time = 0;

void print_time() {
    double current = getCurrentTime();
    cerr << "CurrentTime = " << current << " delta = " << current - last_time << endl;
    last_time = current;
}

#endif


void solve() {

//    print_time();
    for (int i = 0; i < BITS_SIZE; i++) shift[i] = ((Uint) 1 << i);

    auto rule_match = [](int rule_id, int key_id) {
        for (int i = 0; i < D_range; i++) {
            if (rules_range[i][rule_id].first > keys_range_orig[i][key_id] ||
                rules_range[i][rule_id].second < keys_range_orig[i][key_id])
                return false;
        }
        for (int i = 0; i < D_mask; i++) {
            if (rules_mask[i][rule_id].first > keys_mask_orig[i][key_id] ||
                rules_mask[i][rule_id].second < keys_mask_orig[i][key_id])
                return false;
        }
        return true;
    };

    auto get_words = [](vector<string> &WORDS) {
        string text;
        getline(cin, text);
        size_t pos;
        while ((pos = text.find(' ')) != string::npos) {
            WORDS.push_back(text.substr(0, pos));
            text.erase(0, pos + 1);
        }
        WORDS.push_back(text);
    };


    auto get_range_from_mask = [](string str) {
        Uint minx = (Uint) 0;
        Uint maxx = (Uint) 0;
        for (int i = 0; i < BITS_SIZE; i++) {
            if (str[BITS_SIZE - 1 - i] == '*') {
                maxx |= shift[i];
            } else if (str[BITS_SIZE - 1 - i] == '1') {
                minx |= shift[i];
                maxx |= shift[i];
            }
        }
        return make_pair(minx, maxx);
    };

    cin >> R;
    cin.ignore();

    for (int id = 0; id < R; id++) {
        vector<string> words;
        get_words(words);

        if (id == 0) {
            for (int i = 0; i < (int) words.size(); i++) {
                if (words[i].size() == 32) {
                    D_mask++;
                    RULE_TYPE[i] = 0; // mask
                } else {
                    D_range++;
                    RULE_TYPE[i] = 1; // range
                }
            }
            D = D_mask + D_range;
        }
        int range_ptr = 0;
        int mask_ptr = 0;
        for (int i = 0; i < D; i++) {
            const string &str = words[i];
            if (RULE_TYPE[i] == 0) {
                rules_mask[mask_ptr++][id] = get_range_from_mask(str);
            } else {
                int m = str.find('-');
                auto f = make_pair((Mint) stoi(str.substr(0, m)), (Mint) stoi(str.substr(m + 1)));
                rules_range[range_ptr++][id] = f;
            }
        }
    }

    cin >> K;
    cin.ignore();
#ifdef LOCAL
    cerr << "R,K,D_mask, D_range " << R << ' ' << K << ' ' << D_mask << ' ' << D_range << endl;
#endif


    for (int id = 0; id < K; id++) {
        result[id] = -1;
        vector<string> words;
        get_words(words);
        int mask_ptr = 0;
        int range_ptr = 0;
        for (int i = 0; i < D; i++) {
            const string &str = words[i];
            if (RULE_TYPE[i] == 0) {
                keys_mask[mask_ptr][id] = make_pair(get_range_from_mask(str).first, id);
                keys_mask_orig[mask_ptr][id] = keys_mask[mask_ptr][id].first;
                mask_ptr++;
            } else {
                Mint x = (Mint) stoi(str);
                keys_range[range_ptr][id] = {x, id};
                keys_range_orig[range_ptr][id] = x;
                range_ptr++;
            }
        }
    }

#ifdef LOCAL
    print_time();
    cerr << "End of Input:" << endl;
#endif

    for (int d = 0; d < D_mask; d++) {
        sort(keys_mask[d], keys_mask[d] + K);
    }

    for (int d = 0; d < D_range; d++) {
        sort(keys_range[d], keys_range[d] + K);
        int j = 0;
        for (int i = 0; i < K; i++) {
            int k = keys_range[d][i].first;
            for (; j <= k; j++) {
                first_occ[d][j] = i;
            }
        }
        fill(first_occ[d] + j, first_occ[d] + MAX_RANGE_LIM + 1, K);
    }

    long long sum = 0;

    vector<int> intervals;
    int tot_calc = 0;
    for (int r = 0; r < R; r++) {
        int best_lo = -1;
        int best_rg = 1e9;
        int best_d = -1;
        bool MASK_BETTER = true;

        for (int d = 0; d < D_mask; d++) {

            int lo = lower_bound(keys_mask[d], keys_mask[d] + K, make_pair(rules_mask[d][r].first, (Mint) 0)) -
                     keys_mask[d];
            int rg = lower_bound(keys_mask[d], keys_mask[d] + K, make_pair(rules_mask[d][r].second, (Mint) K)) -
                     keys_mask[d];

            if (rg - lo < best_rg - best_lo) {
                best_lo = lo;
                best_rg = rg;
                best_d = d;
            }
        }

        for (int d = 0; d < D_range; d++) {

            int lo = first_occ[d][rules_range[d][r].first];
            int rg = first_occ[d][rules_range[d][r].second + 1];

            if (rg - lo < best_rg - best_lo) {
                best_lo = lo;
                best_rg = rg;
                best_d = d;
                MASK_BETTER = false;
            }
        }
        tot_calc += best_rg - best_lo;
        for (int i = best_lo; i < best_rg; i++) {
            int ind;
            if (MASK_BETTER) {
                ind = keys_mask[best_d][i].second;
            } else {
                ind = keys_range[best_d][i].second;
            }
            if (result[ind] == -1 && rule_match(r, ind)) {
                result[ind] = r;
            }
        }
    }
    for (int i = 0; i < K; i++) cout << result[i] << '\n';
#ifdef LOCAL
    cerr << "Average matching = " << (double) tot_calc / R << endl;
#endif
}


int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifdef LOCAL
    startTime = clock();

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

    cerr << "Memory = " << physMemUsedByMe / 1024 << endl;
    print_time();
#endif

    return 0;
}

