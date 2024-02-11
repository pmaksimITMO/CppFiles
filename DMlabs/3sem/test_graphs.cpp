//
// Created by Dns56 on 12.11.2023.
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
const ld PI = acosl(-1.0);

#ifndef NDEBUG
#define MYASSERT(msg, expr) if (!(expr)) {cerr << (msg); while(1) {cout<<1;}}
#else
#define MYASSERT(expr)
#endif

const int mod = 1e9 + 7;
vc<vll> mul(vc<vll> &a, vc<vll> &b) {
    vc<vll> res(a.size(), vll(b[0].size()));
    forn(i, 0, 5) {
        forn(j, 0, 5) {
            forn(k, 0, 5) {
                res[i][j] = (res[i][j] + (a[i][k] * b[k][j]) % mod) % mod;
            }
        }
    }
    return res;
}

vc<vll> bin_pow(vc<vll> &a, ll pow) {
    if (pow == 1) return a;
    if (pow % 2 == 0) {
        vc<vll> tmp = bin_pow(a, pow/2);
        return mul(tmp, tmp);
    } else {
        vc<vll> tmp = bin_pow(a, pow - 1);
        return mul(tmp, a);
    }
}

int main() {
    vc<vll> a = {
            {0, 1, 0, 0, 1},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 1, 0},
            {1, 0, 0, 0, 0},
            {0, 1, 1, 0, 0}
    };
    vc<vll> ans = bin_pow(a, 12'328'481'820'353);
    forn(i, 0, 5) cout << ans[i] << '\n';
}