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

template <typename T>
basic_ostream<char> &operator<<(basic_ostream<char> &out, vc<T> &a) {
    forn(i, 0, a.size()) {
        out << a[i] << ' ';
    }
    return out;
}

template <typename T>
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
const int LOG = 26;
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

vc<pii> g[MAXN];
int min_cost[LOG][MAXN], up[LOG][MAXN], tin[MAXN], tout[MAXN], timer = 1;

void dfs(int v, int p = 0) {
    tin[v] = timer++;
    up[0][v] = p;
    forn(i, 1, LOG) {
        up[i][v] = up[i - 1][up[i - 1][v]];
        min_cost[i][v] = min(min_cost[i - 1][v], min_cost[i - 1][up[i - 1][v]]);
    }
    for(auto u : g[v]) {
        if (u.first != p) dfs(u.first, v);
    }
    tout[v] = timer;
}

bool isPar(int a, int b) {
    return tin[a] <= tin[b] && tout[b] <= tout[a];
}

int calc(int v, int u) {
    if (isPar(u, v) || isPar(v, u)) {
        if (isPar(v, u)) swap(v, u);
        int res = INF;
        for (int i = LOG - 1; i >= 0; i--) {
            if (!isPar(up[i][v], u)) res = min(res, min_cost[i][v]), v = up[i][v];
        }
        return min(res, min_cost[0][v]);
    }
    int res = INF;
    for (int i = LOG - 1; i >= 0; i--) {
        if (!isPar(up[i][v], u)) {
            res = min(res, min_cost[i][v]);
            v = up[i][v];
        }
    }
    for (int i = LOG - 1; i >= 0; i--) {
        if (!isPar(up[i][u], v)) {
            res = min(res, min_cost[i][u]);
            u = up[i][u];
        }
    }
    return min({res, min_cost[0][v], min_cost[0][u]});
}

int main() {
    IOS;
    int n; cin >> n;
    forn(i, 1, n) {
        int x, y; cin >> x >> y;
        g[i].pb({x - 1, y});
        g[x - 1].pb({i, y});
        min_cost[0][i] = y;
    }
    min_cost[0][0] = INF;
    dfs(0);
    int m; cin >> m;
    while(m--) {
        int v, u; cin >> v >> u;
        cout << calc(v - 1, u - 1) << '\n';
    }
}