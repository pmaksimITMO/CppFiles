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

vc<bool> used;
vi mt;
matrix g;

bool try_kuhn(int v) {
    used[v] = true;
    for (auto const& u : g[v]) {
        if (mt[u] == -1) {
            mt[u] = v;
            return true;
        }
    }
    for (auto const& u : g[v]) {
        if (!used[mt[u]] && try_kuhn(mt[u])) {
            mt[u] = v;
            return true;
        }
    }
    return false;
}

int main() {
    IOS;
    int n, m, e;
    cin >> n >> m >> e;
    vc<pii> wl(n), wr(m);
    forn(i, 0, n) {
        int v; cin >> v;
        wl[i] = {v, i};
    }
    forn(i, 0, m) {
        int v; cin >> v;
        wr[i] = {v, i};
    }
    matrix g_0(n), g_r(m);
    map<pii, int> edge_to_id;
    vc<pii> in(e);
    forn(i, 0, e) {
        int x, y; cin >> x >> y;
        g_0[x - 1].pb(y - 1);
        g_r[y - 1].pb(x - 1);
        in[i] = {x - 1, y - 1};
        edge_to_id[{x - 1, y - 1}] = i + 1;
    }
    vi L, R;
    {
        g = g_0;
        sort(rall(wl));
        mt.assign(m, -1);
        forn(i, 0, n) {
            used.assign(n, false);
            try_kuhn(wl[i].second);
        }
        forn(i, 0, m) if (mt[i] != -1) L.pb(mt[i]);
    }
    {
        g = g_r;
        sort(rall(wr));
        mt.assign(n, -1);
        forn(i, 0, m) {
            used.assign(m, false);
            try_kuhn(wr[i].second);
        }
        forn(i, 0, n) if (mt[i] != -1) R.pb(mt[i]);
    }
    sort(all(L));
    sort(all(R));
    g.clear();
    g.resize(n);
    for(auto const& cur: in) {
        if (binary_search(all(L), cur.first) && binary_search(all(R), cur.second)) {
            g[cur.first].pb(cur.second);
        }
    }
    mt.assign(m, -1);
    forn(i, 0, L.size()) {
        used.assign(n, false);
        try_kuhn(L[i]);
    }

    ll ans = 0;
    for(auto const &i : L) {
        for(auto const &j : wl) {
            if (j.second == i) ans += j.first;
        }
    }
    for(auto const &i : R) {
        for(auto const &j : wr) {
            if (j.second == i) ans += j.first;
        }
    }
    vi res_mt;
    forn(i, 0, m) {
        if (mt[i] == -1) continue;
        res_mt.pb(edge_to_id[{mt[i], i}]);
    }

    cout << ans << '\n' << res_mt.size() << '\n' << res_mt;
}