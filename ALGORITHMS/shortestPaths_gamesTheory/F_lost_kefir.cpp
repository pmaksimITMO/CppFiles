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

int n, m, a, b, c;
vc<vc<pair<int, ll>>> g;

vll calc_dist(int s) {
    vll dist(n, INFL);
    dist[s] = 0;
    set<pair<ll, int>> q;
    q.insert({0, s});
    while (!q.empty()) {
        auto top = q.begin();
        int u = top->second;
        q.erase(top);
        for (auto i: g[u]) {
            int v = i.first;
            ll w = i.second;
            if (dist[v] > dist[u] + w) {
                if (q.count({dist[v], v}))
                    q.erase(q.find({dist[v], v}));
                dist[v] = dist[u] + w;
                q.insert({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    cin >> n >> m;
    g.resize(n);
    forn(i, 0, m) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        --u, --v;
        g[u].pb({v, w});
        g[v].pb({u, w});
    }
    cin >> a >> b >> c;
    --a, --b, --c;
    vll dA = calc_dist(a);
    vll dB = calc_dist(b);
    vll dC = calc_dist(c);
    ll res = INFL;
    forn(i, 0, n) {
        ll dAtoX = dA[i], dBtoX = dB[i], dCtoX = dC[i];
        if (dAtoX != INFL || dBtoX != INFL || dCtoX != INFL) {
            res = min(res, dAtoX + dBtoX + dCtoX + min({dAtoX, dBtoX, dCtoX}));
        } else continue;
    }
    cout << (res == INFL ? -1 : res);
}