#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

//#define LOCAL

#ifndef LOCAL
#undef USE_BENCHMARK
#define benchmarkStart(a)
#define benchmarkStop(a)
#endif

#ifdef LOCAL
#define USE_BENCHMARK

#include "benchmark.hpp"

#endif

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
std::uint32_t shift[BITS_SIZE]; // precalced binary shifts

inline bool rule_match(int rule_id, int key_id) {
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


#include <cstdio>

/** Interface */

inline char readChar();

template<class T = int>
inline T readInt();

template<class T>
inline void writeInt(T x, char end = 0);

inline void writeChar(int x);

inline void writeWord(const char *s);

/** Read */

static constexpr int buf_size = 1 << 16;

inline char getChar() {
    static char buf[buf_size];
    static int len = 0, pos = 0;
    if (pos == len)
        pos = 0, len = fread(buf, 1, buf_size, stdin);
    if (pos == len)
        return -1;
    return buf[pos++];
}

inline char readChar() {
    char c = getChar();
    while (c <= 32)
        c = getChar();
    return c;
}

template<class T>
inline T readInt() {
    char c = readChar();
    T x = 0;
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getChar();
    return x;
}

/** Write */

static int write_pos = 0;
static char write_buf[buf_size];

inline void writeChar(int x) {
    if (write_pos == buf_size)
        fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
    write_buf[write_pos++] = x;
}

template<class T>
inline void writeInt(T x, char end) {
    if (x < 0)
        writeChar('-'), x = -x;

    char s[24];
    int n = 0;
    while (x || !n)
        s[n++] = '0' + x % 10, x /= 10;
    while (n--)
        writeChar(s[n]);
    if (end)
        writeChar(end);
}

inline void writeWord(const char *s) {
    while (*s)
        writeChar(*s++);
}

struct Flusher {
    ~Flusher() {
        if (write_pos)
            fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
    }
} flusher;


void solve() {


    benchmarkStart("Solution (Input)");

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    for (unsigned int i{}; i < 32u; i++) shift[i] = 1u << i;

    R = readInt();

    D_mask = 2;
    D_range = 3;
    D = 5;
    RULE_TYPE[0] = RULE_TYPE[1] = 0;
    RULE_TYPE[2] = RULE_TYPE[3] = RULE_TYPE[4] = 1;

    benchmarkStart("Solution (Input) (Rules)");
    for (int id = 0; id < R; id++) {

        char c;
        rules_mask[0][id].first = rules_mask[0][id].second = 0;
        for (int i{}; i < 32; i++) {
            c = readChar();
            if (c == '*') {
                rules_mask[0][id].second |= shift[31 - i];
            } else if (c == '1') {
                rules_mask[0][id].first |= shift[31 - i];
                rules_mask[0][id].second |= shift[31 - i];
            }
        }

        auto &x = rules_mask[0][id];
        rules_mask[1][id].first = rules_mask[1][id].second = 0;
        for (int i{}; i < 32; i++) {
            c = readChar();
            if (c == '*') {
                rules_mask[1][id].second |= shift[31 - i];
            } else if (c == '1') {
                rules_mask[1][id].first |= shift[31 - i];
                rules_mask[1][id].second |= shift[31 - i];
            }
        }

        rules_range[0][id].first = readInt();
        rules_range[0][id].second = readInt();
        rules_range[1][id].first = readInt();
        rules_range[1][id].second = readInt();
        rules_range[2][id].first = readInt();
        rules_range[2][id].second = readInt();
    }
    benchmarkStop("Solution (Input) (Rules)");
    K = readInt();
#ifdef LOCAL
    cerr << "R,K,D_mask, D_range " << R << ' ' << K << ' ' << D_mask << ' ' << D_range << endl;
#endif

    benchmarkStart("Solution (Input) (Keys)");
    for (int id = 0; id < K; id++) {
        result[id] = -1;

        unsigned int a{}, b{}, c, d, e;

        for (int i{}; i < 32; i++) {
            if (readChar() == '1') {
                a |= (1u << (31 - i));
            }
        }

        for (int i{}; i < 32; i++) {
            if (readChar() == '1') {
                b |= (1u << (31 - i));
            }
        }

        c = readInt();
        d = readInt();
        e = readInt();

        keys_range[0][id] = {c, id};
        keys_range_orig[0][id] = c;
        keys_range[1][id] = {d, id};
        keys_range_orig[1][id] = d;
        keys_range[2][id] = {e, id};
        keys_range_orig[2][id] = e;

        keys_mask[0][id] = {a, id};
        keys_mask_orig[0][id] = a;
        keys_mask[1][id] = {b, id};
        keys_mask_orig[1][id] = b;
    }
    benchmarkStop("Solution (Input) (Keys)");
    benchmarkStop("Solution (Input)");

    benchmarkStart("Solution (main)");
    benchmarkStart("Solution (main) (preproc)");
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
    benchmarkStop("Solution (main) (preproc)");

    benchmarkStart("Solution (main) (search)");
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
    benchmarkStop("Solution (main) (search)");
    benchmarkStop("Solution (main)");

    benchmarkStart("Solution (output)");
    for (int i = 0; i < K; i++) {
        writeInt(result[i], '\n');
    }

    benchmarkStop("Solution (output)");

#ifdef LOCAL
    cerr << "Average matching = " << (double) tot_calc / R << endl;
#endif
}


int main() {

    benchmarkStart("Solution");
    solve();
    benchmarkStop("Solution");

#ifdef LOCAL
    std::cerr << benchmarkLog(true) << std::endl;
#endif

    return 0;
}