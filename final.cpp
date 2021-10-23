//
// Created by temur on 10/24/2021.
//
#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

using namespace std;

constexpr int MAX_RULES = 150000;
constexpr int MAX_KEYS = 15000;
constexpr int MAX_DIM_RANGE = 3;
constexpr int MAX_DIM_MASK = 3;
constexpr int MAX_TOT_DIM = 5;
int R, K, D; //Rules Keys Dimension
int D_mask, D_range;

typedef unsigned short int Mint;
typedef unsigned int Uint;

constexpr int BITS_SIZE = 32; // for Mint
constexpr int MAX_RANGE_LIM = (1 << 16);

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


/** Read */

static constexpr int buf_size = 32 * 4096;

inline char getChar() {
    static char buf[buf_size];
    static int len = 0, pos = 0;
    if (pos == len)
        pos = 0, len = fread(buf, 1, buf_size, stdin);
    if (pos == len)
        return -1;
    return buf[pos++];
}

char buff[50];

Uint minx_mask;
Uint maxx_mask;
Mint minx_range;
Mint maxx_range;
bool range_flag;
bool end_line_flag;

void read_data_range() {
    int len = 0;
    do {
        char c = getChar();
        if (c == ' ') {
            end_line_flag = false;
            break;
        }
        if (c == '\n') {
            end_line_flag = true;
            break;
        }
        buff[len++] = c;
    } while (true);
    range_flag = (len < 32);

    if (range_flag) {
        int i = 0;
        int number1 = 0, number2 = 0;
        for (; buff[i] != '-'; i++) number1 = number1 * 10 + buff[i] - '0';
        i++;
        for (; i < len; i++) number2 = number2 * 10 + buff[i] - '0';
        minx_range = (Mint) number1;
        maxx_range = (Mint) number2;
    } else {
        minx_mask = 0;
        maxx_mask = 0;
        for (int i = 0; i < 32; i++) {
            if (buff[31 - i] == '*') {
                maxx_mask |= shift[i];
            } else if (buff[31 - i] == '1') {
                minx_mask |= shift[i];
                maxx_mask |= shift[i];
            }
        }
    }
}


void read_data_key() {
    int len = 0;

    do {
        char c = getChar();
        if (c == ' ' || c == '\n') break;
        buff[len++] = c;
    } while (true);

    if (range_flag) {
        int i = 0, number2 = 0;
        for (; i < len; i++) number2 = number2 * 10 + buff[i] - '0';
        minx_range = (Mint) number2;
    } else {
        minx_mask = 0;
        for (int i = 0; i < 32; i++) {
            if (buff[31 - i] == '1') {
                minx_mask |= shift[i];
            }
        }
    }

}

inline char readChar() {
    char c = getChar();
    while (c <= 32)
        c = getChar();
    return c;
}

int readInt() {
    char c = readChar();
    int x = 0;
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getChar();
    return x;
}

bool rule_match(int rule_id, int key_id) {
    for (int i = 0; i < D_mask; i++) {
        if (rules_mask[i][rule_id].first > keys_mask_orig[i][key_id] ||
            rules_mask[i][rule_id].second < keys_mask_orig[i][key_id])
            return false;
    }
    for (int i = 0; i < D_range; i++) {
        if (rules_range[i][rule_id].first > keys_range_orig[i][key_id] ||
            rules_range[i][rule_id].second < keys_range_orig[i][key_id])
            return false;
    }
    return true;
}


void solve() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    for (unsigned int i{}; i < 32u; i++) shift[i] = 1u << i;

    R = readInt();

    for (int id = 0; id < R; id++) {
        if (id == 0) {
            end_line_flag = false;
            do {
                read_data_range();
                if (range_flag) {
                    rules_range[D_range][id] = make_pair(minx_range, maxx_range);
                    D_range++;
                } else {
                    rules_mask[D_mask][id] = make_pair(minx_mask, maxx_mask);
                    D_mask++;
                }

                RULE_TYPE[D] = range_flag;
                D++;
            } while (!end_line_flag);
        } else {
            int range_ptr = 0;
            int mask_ptr = 0;
            for (int i = 0; i < D; i++) {
                range_flag = RULE_TYPE[i];
                read_data_range();
                if (RULE_TYPE[i]) { //range
                    rules_range[range_ptr][id] = make_pair(minx_range, maxx_range);
                    range_ptr++;
                } else {
                    rules_mask[mask_ptr][id] = make_pair(minx_mask, maxx_mask);
                    mask_ptr++;
                }
            }
        }
    }

    K = readInt();

    for (int id = 0; id < K; id++) {
        result[id] = -1;
        int range_ptr = 0;
        int mask_ptr = 0;
        for (int i = 0; i < D; i++) {
            range_flag = RULE_TYPE[i];
            read_data_key();
            if (RULE_TYPE[i]) { //range
                keys_range[range_ptr][id] = make_pair(minx_range, id);
                keys_range_orig[range_ptr][id] = minx_range;
                range_ptr++;
            } else {
                keys_mask[mask_ptr][id] = make_pair(minx_mask, id);
                keys_mask_orig[mask_ptr][id] = minx_mask;
                mask_ptr++;
            }
        }
    }

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

    for (int i = 0; i < K; i++) {
        printf("%d\n", result[i]);
    }

}


int main() {
    solve();
    return 0;
}
