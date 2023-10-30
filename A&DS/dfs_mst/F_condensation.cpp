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

int n,m,col;
vc<vi> g, rg;
vi used, top_sort, cssNum;

void dfs(int v) {
    used[v] = true;
    for(auto u : g[v]) {
        if (!used[u]) {
            dfs(u);
        }
    }
    top_sort.pb(v);
}

void makeCSS(int v) {
    used[v] = true;
    cssNum[v] = col;
    for(auto u : rg[v]) {
        if (!used[u]) {
            makeCSS(u);
        }
    }
}

int main() {
    cin >> n >> m;
    g.resize(n);
    rg.resize(n);
    used.assign(n, 0);
    forn(i, 0, m) {
        int v,u; cin >> v >> u;
        v--, u--;
        g[v].pb(u);
        rg[u].pb(v);
    }
    forn(i, 0, n) {
        if (!used[i]) dfs(i);
    }
    used.assign(n, 0);
    cssNum.assign(n, 0);
    col = 1;
    for (int i = n - 1; i >= 0; --i) {
        int root = top_sort[i];
        if (!used[root]) {
            makeCSS(root);
            col++;
        }
    }
    set<pii> cssEdges;
    forn(v, 0, n) {
        for(auto u : g[v]) {
            if (cssNum[v] != cssNum[u]) {
                cssEdges.insert({cssNum[v], cssNum[u]});
            }
        }
    }
    cout << cssEdges.size();
}