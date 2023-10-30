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
const ll INFL = static_cast<const ll>(1e20);
const int MOD = 1e9 + 7;
const int P = 17;
const ld PI = acosl(-1.0);

#ifndef NDEBUG
#define MYASSERT(msg, expr) if (!(expr)) {cerr << (msg); while(1) {cout<<1;}}
#else
#define MYASSERT(expr)
#endif

struct edge {
    int v, u;
    ll w;
};

vc<vi> g;
vi used;

void dfs(int v) {
    used[v] = 1;
    for (auto const &u: g[v]) {
        if (!used[u]) {
            dfs(u);
        }
    }
}

int main() {
    IOS;
    int n, m, s;
    cin >> n >> m >> s;
    --s;
    vc<edge> edges;
    vll dist(n, INFL);
    g.resize(n);
    used.assign(n, 0);
    forn(i, 0, m) {
        int u, v;
        ll w;
        cin >> v >> u >> w;
        --u, --v;
        g[v].pb(u);
        edges.pb({v, u, w});
    }
    dist[s] = 0;
    forn(i, 0, n) {
        for (auto const& j : edges) {
            int v = j.v, u = j.u;
            ll w = j.w;
            if ((dist[v] < INFL) && (dist[u] > dist[v] + w)) {
                dist[u] = max(-INFL, dist[v] + w);
            }
        }
    }
    forn(i, 0, n) {
        for (auto const& j : edges) {
            int v = j.v, u = j.u;
            ll w = j.w;
            if ((dist[v] < INFL) && (dist[u] > dist[v] + w) && !used[u]) {
                dfs(u);
            }
        }
    }
    forn(i, 0, n) {
        if (dist[i] == INFL) cout << "*\n";
        else if (used[i]) cout << "-\n";
        else cout << dist[i] << "\n";
    }
}