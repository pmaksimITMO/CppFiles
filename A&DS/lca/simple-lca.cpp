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

vi g[MAXN];
int up[LOG][MAXN], tin[MAXN], tout[MAXN], timer = 1;

void dfs(int v, int p = 0) {
    tin[v] = timer++;
    up[0][v] = p;
    forn(i, 1, LOG) {
        up[i][v] = up[i - 1][up[i - 1][v]];
    }
    for(auto u : g[v]) {
        if (u != p) dfs(u, v);
    }
    tout[v] = timer;
}

bool isPar(int a, int b) {
    return tin[a] <= tin[b] && tout[b] <= tout[a];
}

int lca(int v, int u) {
    if (isPar(v, u)) return v;
    if (isPar(u, v)) return u;
    for (int i = LOG - 1; i >= 0; i--) {
        if (!isPar(up[i][v], u)) v = up[i][v];
    }
    return up[0][v];
}

int main() {
    int n; cin >> n;
    forn(i, 1, n) {
        int x; cin >> x;
        g[i].pb(x - 1);
        g[x - 1].pb(i);
    }
    dfs(0);
    int m; cin >> m;
    while(m--) {
        int v, u; cin >> v >> u;
        cout << lca(v - 1, u - 1) + 1 << '\n';
    }
}