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

vc<pii> a;

ld dist(int v, int u) {
    return sqrt(
            (a[v].first - a[u].first) * (a[v].first - a[u].first)
            + (a[v].second - a[u].second) * (a[v].second - a[u].second)
    );
}

int main() {
    int n; cin >> n;
    a.resize(n);
    forn(i, 0, n) {
        int x, y;
        cin >> x >> y;
        a[i] = {x, y};
    }
    vi used(n, 0), sel_e(n, -1);
    vc<ld> min_e(n, INF);
    min_e[0] = 0;
    ld ans = 0;
    forn(i, 0, n) {
        int v = -1;
        forn(j, 0, n) {
            if (!used[j] && (v == -1 || min_e[j] < min_e[v])) {
                v = j;
            }
        }
        used[v] = true;
        if (sel_e[v] != -1) {
            ans += dist(v, sel_e[v]);
        }
        for(int u = 0; u < n; ++u) {
            ld dst = dist(v, u);
            if (dst < min_e[u]) {
                min_e[u] = dst;
                sel_e[u] = v;
            }
        }
    }
    cout << fixed << setprecision(10) << ans;
}
