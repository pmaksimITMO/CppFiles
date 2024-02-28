//
// Created by Dns56 on 17.02.2024.
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

int main() {
//    IOS;
    int n, d;
    cin >> n >> d;
    vc<pii> a(n);
    vc<vi> g(n + 1);
    forn(i, 0, n) {
        int x, y; cin >> x >> y;
        a[i] = {x, y};
    }
    a.pb({0, 0});
    forn(i, 0, n + 1) {
        forn(j, 0, n + 1) {
            if (i == j || a[j].first - a[i].first > d || a[j].second - a[i].second > d) continue;
            g[i].pb(j);
        }
    }
    int s = n;
    n = int(a.size());
    vector<int> dist(n, INF),  p(n);
    dist[s] = 0;
    vector<char> used(n);
    forn(i, 0, n) {
        int v = -1;
        forn(j, 0, n)
            if (!used[j] && (v == -1 || dist[j] < dist[v]))
                v = j;
        if (dist[v] == INF)
            break;
        used[v] = true;
        for(auto& u: g[v]) {
            if (dist[v] + 1 < dist[u]) {
                dist[u] = dist[v] + 1;
                p[u] = v;
            }
        }
    }

    if (dist[0] == INF) cout << "-1";
    else {
        vector<int> path;
        for (int v = 0; v != s; v = p[v]) path.pb(v);
        reverse(all(path));
        cout << path.size() << '\n';
        for(auto& i : path) cout << i + 1 << ' ';
    }
}