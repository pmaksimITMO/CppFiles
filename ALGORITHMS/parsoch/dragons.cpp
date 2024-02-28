//
// Created by Dns56 on 22.02.2024.
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

vc<vi> g;
vc<bool> used;
vi mt;

bool try_khun(int v) {
    used[v] = true;
    forn(i, 0, g[v].size()) {
        if (g[v][i] && (mt[i] == -1 || !used[mt[i]] && try_khun(mt[i]))) {
            mt[i] = v;
            return true;
        }
    }
    return false;
}

int main() {
    IOS;
    int m, n, k, t, q;
    cin >> m >> k >> n >> t;
    g.assign(m + k - n, vi(m + k - n, 1));
    forn(i, m, m + k - n) {
        forn(j, k, m + k - n) {
            g[i][j] = 0;
        }
    }
    forn(i, 0, t) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        y -= m;
        g[x][y] = 0;
    }
    cin >> q;
    forn(i, 0, q) {
        int x;
        cin >> x;
        x--;
        if (x < m) {
            forn(j, k, m + k - n) g[x][j] = 0;
        } else {
            forn(j, m, m + k - n) g[j][x - m] = 0;
        }
    }
    mt.assign(m + k - n, -1);
    forn(i, 0, m + k - n) {
        used.assign(200, false);
        try_khun(i);
    }
    int f = 1;
    forn(i, 0, m + k - n) f &= mt[i] >= 0;
    if (!f) cout << "NO";
    else {
        cout << "YES\n";
        forn(i, 0, k) {
            if (mt[i] >= 0 && mt[i] < m)
                cout << mt[i] + 1 << ' ' << i + m + 1 << '\n';
        }
    }
}
