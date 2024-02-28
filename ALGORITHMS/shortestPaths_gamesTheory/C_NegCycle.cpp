//
// Created by Dns56 on 28.10.2023.
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

struct edge {
    int a, b, cost;
};

int main() {
    int n;
    cin >> n;
    vc<edge> e;
    forn(i, 0, n) {
        forn(j, 0, n) {
            int w;
            cin >> w;
            if (w != 100'000) {
                e.pb({i, j, w});
            }
        }
    }
    vi d(n, INF), p(n, -1);
    int x;
    forn(i, 0, n) {
        x = -1;
        forn(j, 0, e.size())
            if (d[e[j].b] > d[e[j].a] + e[j].cost) {
                d[e[j].b] = max(-INF, d[e[j].a] + e[j].cost);
                p[e[j].b] = e[j].a;
                x = e[j].b;
            }
    }

    if (x == -1)
        cout << "NO";
    else {
        int y = x;
        forn(i, 0, n) y = p[y];
        vi path;
        for (int cur = y;; cur = p[cur]) {
            path.pb(cur);
            if (cur == y && path.size() > 1) break;
        }
        reverse(all(path));
        cout << "YES\n" << path.size() - 1 << '\n';
        forn(i, 1, path.size()) cout << path[i] + 1 << ' ';
    }
}