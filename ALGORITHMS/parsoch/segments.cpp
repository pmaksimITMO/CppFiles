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

struct seg {
    int x_l, x_r, y_l, y_r;

    seg() : x_l(0), x_r(0), y_l(0), y_r(0) {}

    seg(int x1, int y1, int x2, int y2) : x_l(x1), x_r(x2), y_l(y1), y_r(y2) {}
};

vc<bool> used;
vi mt, par;
vc<seg> hor, vert;

matrix g;

bool try_kuhn(int v) {
    if (used[v]) return false;
    used[v] = true;
    forn(i, 0, vert.size()) {
        if (g[v][i] == 1) continue;
        if (mt[i] == -1 || try_kuhn(mt[i])) {
            mt[i] = v;
            par[v] = 1;
            return true;
        }
    }
    return false;
}

int main() {
    IOS;
    int n;
    cin >> n;
    forn(i, 0, n) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 == x2) vert.pb(seg(x1, y1, x2, y2));
        else hor.pb(seg(x1, y1, x2, y2));
    }
    g.assign(hor.size(), vi(vert.size(), 0));
    auto intersect = [](seg x, seg y) -> bool {
        //x - hor, y - vert
        if (x.x_l <= y.x_l && y.x_l <= x.x_r && y.y_l <= x.y_l && x.y_l <= y.y_r) {
            return true;
        }
        return false;
    };
    forn(i, 0, hor.size()) {
        forn(j, 0, vert.size()) {
            if (!intersect(hor[i], vert[j])) {
                g[i][j] = 1;
            }
        }
    }
    mt.assign(vert.size(), -1);
    par.assign(hor.size(), -1);
    for (int run = 1; run;) {
        run = 0;
        used.assign(hor.size(), false);
        forn(i, 0, hor.size()) {
            if (par[i] == -1 && try_kuhn(i)) run = 1;
        }
    }
    int cnt = 0;
    for (auto const &i: mt) {
        if (i != -1) {
            cnt++;
        }
    }
//    forn(i, 0, hor.size()) cout << g[i] << '\n';
//    cout << "-----------\n" << mt << "\n-----------------\n";
    cout << n - cnt;
}