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

int n, m, s;
vc<vi> g;
vi res, used;

void dfs(int v) {
    used[v] = 1;
    res[v] = 0;
    for (auto const& u: g[v]) {
        if (used[u] == 0) {
            dfs(u);
        }
    }
    for (auto const& u: g[v]) {
        if (used[u] == 2 && !res[u]) {
            res[v] = 1;
        }
    }
    used[v] = 2;
}

int main() {
    cin >> n >> m >> s;
    s--;
    g.resize(n);
    res.assign(n, -1);
    used.assign(n, 0);
    forn(i, 0, m) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].pb(v);
    }
    dfs(s);
    cout << (res[s] ? "First" : "Second") << " player wins";
}