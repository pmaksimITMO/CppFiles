//
// Created by Dns56 on 22.10.2023.
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

int n, m, timer;
vc<vi > g;
vi used, tin, up;
set<int> ans;

void dfs(int v, int p = -1) {
    tin[v] = up[v] = timer++;
    used[v] = true;
    int children = 0;
    for (auto u: g[v]) {
        if (u == p) continue;
        if (used[u]) {
            up[v] = min(up[v], tin[u]);
        } else {
            dfs(u, v);
            up[v] = min(up[v], up[u]);
            if (up[u] >= tin[v] && p != -1) {
                ans.insert(v + 1);
            }
            ++children;
        }
    }
    if (p == -1 && children > 1) {
        ans.insert(v + 1);
    }
}

int main() {
    cin >> n >> m;
    g.resize(n);
    used.assign(n, 0);
    tin.assign(n, 0);
    up.assign(n, 0);
    forn(i, 0, m) {
        int v, u;
        cin >> v >> u;
        v--, u--;
        g[v].pb(u);
        g[u].pb(v);
    }
    timer = 0;
    forn(i, 0, n) {
        if (!used[i]) {
            dfs(i);
        }
    }
    cout << ans.size() << '\n';
    for (auto i: ans) cout << i << ' ';
}
