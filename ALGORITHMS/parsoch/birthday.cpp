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

vc<bool> used, us;
vll mt;
vc<set<ll>> g, r;

bool try_kuhn(ll v) {
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

void dfs(ll v) {
    us[v] = true;
    for(auto const& u: r[v]) {
        if (!us[u]) dfs(u);
    }
}

void solve() {
    int n, m;
    cin >> m >> n;
    used.assign(m, false);
    mt.assign(n, -1);
    g.resize(m);
    set<ll> q;
    forn(i, 0, n) q.insert(i);
    forn(i, 0, m) {
        ll u = -1;
        g[i] = q;
        while (cin >> u) {
            if (u == 0) break;
            g[i].erase(u - 1);
        }
    }
    forn(i, 0, m) {
        used.assign(m, false);
        try_kuhn(i);
    }
    r.clear();
    r.resize(n + m);
    used.assign(n, false);
    us.assign(n + m, false);
    forn(i, 0, mt.size()) {
        if (mt[i] != -1) {
            used[mt[i]] = true;
            r[i + m].insert(mt[i]);
        }
    }
    forn(i, 0, m) {
        for (auto k: g[i]) {
            if (r[k + m].find(i) == r[k + m].end()) {
                r[i].insert(k + m);
            }
        }
    }
    forn(i, 0, m) if (!used[i]) dfs(i);
    vector <int> am, ag;
    ll ans = 0, cnt = 0;
    forn(i, 0, m)
        if (us[i] == 1)
            am.push_back(i + 1), cnt++;
    forn(i, m, m + n)
        if (us[i] == 0)
            ag.push_back(i + 1 -  m), ans++;
    cout << ans + cnt << "\n" << cnt << " " << ans << "\n";
    cout << am << '\n' << ag << '\n';
}

int main() {
    IOS;
    int t = 1;
    cin >> t;
    while (t--) solve();
}