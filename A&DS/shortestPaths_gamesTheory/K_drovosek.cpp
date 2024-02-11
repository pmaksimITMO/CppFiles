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
const ll INFL = 1e18;
const int MOD = 1e9 + 7;
const int P = 17;
const ld PI = acosl(-1.0);

#ifndef NDEBUG
#define MYASSERT(msg, expr) if (!(expr)) {cerr << (msg); while(1) {cout<<1;}}
#else
#define MYASSERT(expr)
#endif

int n, r;
vc<vi > g;
vi top_sort, used;

void make_sort(int v) {
    used[v] = true;
    for (auto const &u: g[v]) {
        if (!used[u]) {
            make_sort(u);
        }
    }
    top_sort.pb(v);
}

int main() {
    cin >> n >> r;
    r--;
    g.resize(n);
    map<pii, int> edges;
    forn(i, 1, n) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].pb(v);
        g[v].pb(u);
        edges[{min(u, v), max(u, v)}] = i;
    }
    used.assign(n, 0);
    make_sort(r);
    vi res(n, 0), tmp(n, 0);
    for (auto const &v: top_sort) {
        if (g[v].size() == 1 && v != r) continue;
        for (auto const &u: g[v]) {
            res[v] ^= res[u];
        }
        if (g[v].size() == 1) res[v]++;
    }
    if (res[r] == 0) {
        cout << 2;
    } else {
        cout << "1\n";
        for (auto const &i: g[r]) {
            if (res[i] == 0) {
                cout << edges[{min(r, i), max(r, i)}];
                break;
            }
        }
    }
}

// R(3,4) <= R(3,3) + R(2,4) = 6 + 4 = 10
// R(3,4) > 8, так как можно построить контрпример
// R(3,4) <= C(5, 3) = 5!/(3! * 2!) = (4 * 5)/2 = 10