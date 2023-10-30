//
// Created by Dns56 on 22.10.2023.
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
const ll INFL = 1e16;
const int MOD = 1e9 + 7;
const int P = 17;
const ld PI = acosl(-1.0);

#ifndef NDEBUG
#define MYASSERT(msg, expr) if (!(expr)) {cerr << (msg); while(1) {cout<<1;}}
#else
#define MYASSERT(expr)
#endif

int n;
vc<vi > g, g1;
vi used;

void check(int v, int type) {
    used[v] = true;
    for (int i = 0; i < n; ++i) {
        if ((type == 1 ? g1[i][v] : g1[v][i]) && !used[i]) {
            check(i, type);
        }
    }
}

bool visit_all() {
    forn(i, 0, n) {
        if (!used[i]) return false;
    }
    return true;
}

int main() {
    cin >> n;
    g.assign(n, vi(n, 0));
    g1.assign(n, vi(n, 0));
    forn(i, 0, n) {
        forn(j, 0, n) {
            cin >> g[i][j];
        }
    }
    int l = 0, r = 1'000'000'000;
    while (r - l > 0) {
        int m = (l + r) / 2;
        forn(i, 0, n) {
            forn(j, 0, n) {
                if (i == j) continue;
                g1[i][j] = (g[i][j] <= m);
            }
        }
        used.assign(n, 0);
        check(0, 0);
        bool f = false;
        if (visit_all()) {
            used.assign(n, 0);
            check(0, 1);
            if (!visit_all()) f = true;
        } else f = true;
        if (!f) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    cout << l;
}