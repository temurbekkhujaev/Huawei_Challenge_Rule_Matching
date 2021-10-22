//
// Created by Abdurasul on 10/22/2021.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <chrono>
#include <cstdio>

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

struct Data {
    std::uint32_t a1{}, mask1{};
    std::uint32_t a2{}, mask2{};
    std::uint16_t r1_l, r1_r, r2_l, r2_r, r3_l, r3_r;
};

struct Data2 {
    std::uint32_t a1{}, a2{}, d1{}, d2{}, d3{};
};
//
//void parseRange(std::string &str, std::int16_t& a, std::int16_t& b) {
//    auto pos = str.find('-');
//    a = std::stoi(str.substr(0, pos));
//    b = std::stoi(str.substr(pos + 1));
//}
//
//void parseString(std::stringstream &stream, std::string &str, Data& d) {
//    stream.clear();
//    stream << str;
//    std::string temp;
//    stream >> temp;
//    int t{};
//    for (int i = int(temp.size()) - 1; i >= 0; i--) {
//        if (temp[i] == '*') {
//            d.mask1 |= (1 << t);
//        } else if (temp[i] == '1') {
//            d.mask1 |= (1 << t);
//            d.a1 |= (1 << t);
//        }
//        t++;
//    }
//
//    t = 0;
//    stream >> temp;
//    for (int i = int(temp.size()) - 1; i >= 0; i--) {
//        if (temp[i] == '*') {
//            d.mask2 |= (1 << t);
//        } else if (temp[i] == '1') {
//            d.mask2 |= (1 << t);
//            d.a2 |= (1 << t);
//        }
//        t++;
//    }
//
//    stream >> temp;
//    parseRange(temp, d.r1_l, d.r1_r);
//    stream >> temp;
//    parseRange(temp, d.r2_l, d.r2_r);
//    stream >> temp;
//    parseRange(temp, d.r3_l, d.r3_r);
//}
//
//void parseString2(char buffer[], Data2& d) {
//
//    stream.clear();
//    stream << str;
//    std::string temp;
//    stream >> temp;
//    std::size_t ttt;
//    d.a1 = std::stoul(temp, &ttt, 2);
//
//    stream >> temp;
//    d.a2 = std::stoul(temp, &ttt, 2);
//
//    stream >> d.d1 >> d.d2 >> d.d3;
//}

std::ostream &operator<<(std::ostream &out, const std::pair<int, int> &p) {
    out << "(" << p.first << ", " << p.second << ") ";
    return out;
}

bool checkMatches(Data &a, Data2 &b) {
    return (a.a1 <= b.a1 && b.a1 <= a.mask1)
           && (a.a2 <= b.a2 && b.a2 <= a.mask2)
           && (a.r1_l <= b.d1 && b.d1 <= a.r1_r)
           && (a.r2_l <= b.d2 && b.d2 <= a.r2_r)
           && (a.r3_l <= b.d3 && b.d3 <= a.r3_r);
}

int main() {

//    auto start = std::chrono::high_resolution_clock::now();

    auto *in = fopen("input_test.txt", "r");
    int n;
    fscanf(in, "%d", &n);
    Data *a = new Data[n];

    char buffer1[1024];
    char buffer2[1024];

    for (int i{}; i < n; i++) {
        fscanf(in, "%s %s %d-%d %d-%d %d-%d\r\n", buffer1, buffer2, &a[i].r1_l, &a[i].r1_r, &a[i].r2_l, &a[i].r2_r,
               &a[i].r3_l, &a[i].r3_r);
        int cnt{}, last{};
        for (char *t = buffer1; *t != '\0'; t++) {
            last ++;
            if (*t == '*') {
                *t = '0';
                cnt ++;
            }
        }
        a[i].a1 = strtol(buffer1, nullptr, 2);
        a[i].mask1 = a[i].a1  | ((1ll << cnt) - 1);

        cnt = 0;last = 0;
        for (char *t = buffer2; *t != '\0'; t++) {
            last ++;
            if (*t == '*') {
                *t = '0';
                cnt ++;
            }
        }
        a[i].a2 = strtol(buffer2, nullptr, 2);
        a[i].mask2 = a[i].a2 | ((1ll << cnt) - 1);

    }

    int k;
    fscanf(in, "%d", &k);
    std::cerr << "k = " << k << std::endl;
    auto *b = new Data2[k];

    for (int i{}; i < k; i++) {

        fscanf(in, "%s %s %d %d %d\r\n", buffer1, buffer2, &b[i].d1, &b[i].d2, &b[i].d3);
        b[i].a1 = strtol(buffer1, nullptr, 2);
        b[i].a2 = strtol(buffer2, nullptr, 2);
    }


    int *ans = new int[k];
    for (int i{}; i < k; i++) {
        ans[i] = -1;
        for (int j{}; j < n; j++) {
            if (checkMatches(a[j], b[i])) {
                ans[i] = j;
                break;
            }
        }
    }


    auto *out = fopen("output_test.txt", "w");
    for (int i{}; i < k; i++) {
        fprintf(out, "%d\n", ans[i]);
    }

    fclose(in);
    fclose(out);
    delete[] a;
    delete[] b;
    delete[] ans;

//    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(
//            std::chrono::high_resolution_clock::now() - start).count();
//    std::cerr << "Time: " << time << std::endl;
//    std::cerr << "Virtual memory usage: " << getValue() << std::endl;
//    std::cerr << "Physical memory usage: " << getValue2() << std::endl;
    return 0;
}