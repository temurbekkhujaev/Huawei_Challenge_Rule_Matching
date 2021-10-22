//
// Created by temur on 10/22/2021.
//

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;
const int MAX_RULES = 150000;
const int MAX_KEYS = 15000;
int R, K;

struct Rule {
    string mask;
    vector<pair<int, int> > ranges;

    Rule() = default;;

    bool mask_match(const string &other_mask) const {
        assert(mask.size() == other_mask.size());
        for (int i = 0; i < mask.size(); i++) {
            if (mask[i] == '*') continue;
            if (mask[i] != other_mask[i]) {
                return false;
            }
        }
        return true;
    }

    bool range_match(const vector<int> &values) const {
        for (int i = (int) ranges.size() - 1; i >= 0; i--) {
            if (values[i] < ranges[i].first || values[i] > ranges[i].second) return false;
        }
        return true;
    }

};

struct Key {
    string mask;
    vector<int> values;

    Key() = default;
};

vector<Rule> rules;
vector<Key> keys;

void print_key(Key key) {
    cerr << "Mask = " << key.mask << ' ';
    cerr << "Values = ";
    for (auto x: key.values) cerr << x << ' ';
    cerr << endl;
}

void print_rule(Rule rule) {

    cerr << "Mask = " << rule.mask << ' ';
    cerr << "Ranges = ";
    for (auto x: rule.ranges) cerr << x.first << '-' << x.second << ' ';
    cerr << endl;
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

    rules = vector<Rule>(R);

    cin.ignore();
    for (int id = 0; id < R; id++) {
        vector<string> words = get_words();
        for (const auto &str: words) {
            if (str.size() == 32) {
                rules[id].mask += str;
            } else {
                int m = str.find('-');
                assert(m != -1);
                auto f = make_pair(stoi(str.substr(0, m)), stoi(str.substr(m + 1)));

                rules[id].ranges.push_back(f);
            }

        }
    }
    cin >> K;
    cin.ignore();

    keys = vector<Key>(K);
    for (int id = 0; id < K; id++) {
        vector<string> words = get_words();
        for (const auto &str: words) {
            if (str.size() == 32) {
                keys[id].mask += str;
            } else {
                keys[id].values.push_back(stoi(str));
            }
        }
    }
    print_key(keys[0]);
    print_rule(rules[60655]);
    print_rule(rules[89086]);
//    return;
    int now = 0;
    for (const auto &key: keys)
    {
        now++;
        int res = -1;
        for (int id = 0; id < R; id++) {
            Rule rule = rules[id];
            if (rule.mask_match(key.mask) && rule.range_match(key.values)) {
                res = id;
                break;
            }
        }
        cout << res << endl;
    }


}

int main() {
    ios_base::sync_with_stdio(false);
#ifdef LOCAL
    freopen("input_test.txt", "r", stdin);
//    freopen("output_test.txt", "w", stdout);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    solve();
    return 0;
}

