//
// Created by Dns56 on 15.12.2023.
//
#include <bits/stdc++.h>
#include <cassert>

#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define IOS ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pb push_back
#define vc vector
#define vi vector<int>
#define vll vector<long long>
#define forn(i, s, n) for(int i = (s); i < (n); ++i)
#define fornr(i, s, n) for(int i = (s); i >= (n); --i)
#define fi first
#define se second
using namespace std;

template<typename T>
basic_ostream<char> &operator<<(basic_ostream<char> &out, vc<T> &a) {
    forn(i, 0, a.size()) {
        out << a[i] << ' ';
    }
    return out;
}

template<typename T>
basic_istream<char> &operator>>(basic_istream<char> &in, vc<T> &a) {
    forn(i, 0, a.size()) {
        in >> a[i];
    }
    return in;
}

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef vector<vector<int>> matrix;

const int MAXN = 1e6;
const int INF = 2e9;
const ll INFL = 1e18;
const int MOD = 1e9 + 7;
const int P = 17;
const int MOD2 = 1e9 + 11;
const int P2 = 31;
const ld PI = acosl(-1.0);

#ifndef NDEBUG
#define MYASSERT(msg, expr) if (!(expr)) {cerr << (msg); while(1) {cout<<1;}}
#else
#define MYASSERT(expr)
#endif

int main() {
//    IOS;
    int k;
    cin >> k;
    vc<string> a(k);
    cin >> a;
    auto nop = [&](int x) -> string {
        set<string> res;
        forn(j, 0, k) {
            set<string> subs;
            for(int i = 0; i + x <= a[j].size(); ++i) subs.insert(a[j].substr(i, x));
            if (j == 0) res = subs;
            else {
                set<string> tmp;
                for (auto &i: subs) {
                    if (res.find(i) != res.end()) tmp.insert(i);
                }
                res = tmp;
            }
            if (res.empty()) break;
        }
        return (res.empty() ? "" : *res.begin());
    };
    int l = 0, r = 10001;
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (!nop(m).empty()) l = m;
        else r = m;
    }
    cout << (!nop(r).empty() ? nop(r) : nop(l));
}