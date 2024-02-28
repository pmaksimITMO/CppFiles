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

int main() {
    int n, m;
    cin >> n >> m;
    vc<vc<pii>> g(n);
    forn(i, 0, m) {
        int v, u, w;
        cin >> v >> u >> w;
        --v, --u;
        g[v].pb({u, w});
        g[u].pb({v, w});
    }
    vll dist(n, INF);
    dist[0] = 0;
    set<pll> q;
    q.insert({0, 0});
    while (!q.empty()) {
        auto top = q.begin();
        int v = top->second;
        q.erase(top);
        for (auto const& i : g[v]) {
            int u = i.first, d = i.second;
            if (dist[u] > dist[v] + d) {
                if (q.count({dist[u], u}))
                    q.erase(q.find({dist[u], u}));
                dist[u] = dist[v] + d;
                q.insert({dist[u], u});
            }
        }
    }
    cout << dist;
}