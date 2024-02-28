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

int n, m;
vc<vi > g, rg;
vi used, top_sort, comp;
map<string, int> name_id;

void dfs(int v) {
    used[v] = true;
    for (auto u: g[v]) {
        if (!used[u]) {
            dfs(u);
        }
    }
    top_sort.pb(v);
}

void makeCSS(int v, int col) {
    comp[v] = col;
    for (auto u: rg[v]) {
        if (comp[u] == -1) {
            makeCSS(u, col);
        }
    }
}

int main() {
    cin >> n >> m;
    g.resize(2 * n);
    rg.resize(2 * n);
    comp.assign(2 * n, -1);
    vc<string> names;
    forn(i, 0, n) {
        string name;
        cin >> name;
        names.pb(name);
        name_id[name] = i;
    }
    forn(i, 0, m) {
        string name1, ar, name2;
        cin >> name1 >> ar >> name2;

        int v = 2 * name_id[name1.substr(1, name1.size())];
        int u = 2 * name_id[name2.substr(1, name2.size())];
        if (name1[0] == '-') ++v;
        if (name2[0] == '-') ++u;

        g[v].push_back(u);
        g[u ^ 1].push_back(v ^ 1);

        rg[u].push_back(v);
        rg[v ^ 1].push_back(u ^ 1);
    }
    used.assign(2 * n, 0);
    forn(i, 0, 2 * n) {
        if (!used[i]) dfs(i);
    }
    int col = 1;
    for (int i = top_sort.size() - 1; i >= 0; --i) {
        int root = top_sort[i];
        if (comp[root] == -1) {
            makeCSS(root, col++);
        }
    }
    for (int i = 0; i < 2 * n; i += 2) {
        if (comp[i] == comp[i ^ 1]) {
            cout << -1;
            return 0;
        }
    }

    vc<string> ans;
    for (int i = 0; i < 2 * n; i += 2) {
        if (comp[i] > comp[i ^ 1]) {
            ans.pb(names[i / 2]);
        }
    }
    cout << ans.size() << "\n";
    for (const auto& x: ans) cout << x << '\n';
}