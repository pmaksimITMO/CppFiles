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

vc<bool> used;
vi mt;
matrix g;

bool try_kuhn(int v) {
    used[v] = true;
    for (auto const &u: g[v]) {
        if (mt[u] == -1) {
            mt[u] = v;
            return true;
        }
    }
    for (auto const &u: g[v]) {
        if (!used[mt[u]] && try_kuhn(mt[u])) {
            mt[u] = v;
            return true;
        }
    }
    return false;
}

struct pt {
    pll time;
    ll x, y;
    pt(): time({0,0}), x(0), y(0) {}
};

static ll dist_square(const pt &a, const pt &b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

static ll time_diff_minutes(const pt &a, const pt &b) {
    return (b.time.first - a.time.first) * 60ll + (b.time.second - a.time.second);
}

static bool can_add_edge(const pt &a, const pt &b, const int& v) {
    ll len = ll(dist_square(a, b));
    ll t = ll(time_diff_minutes(a, b));
    // [v = km/h], [t = min], [len = km], sqrt(len) = d
    // v * t >= 60 * d
    // (v*t)^2 >= 3600 * len
    if (t * t * v * v >= 3600 * len) return true;
    else return false;
}

int main() {
    IOS;
    int n, v;
    cin >> n >> v;
    g.resize(n);
    vc<pt> a(n);
    forn(i, 0, n) {
        string t;
        int x, y;
        cin >> t >> x >> y;
        a[i].time = {stoi(t.substr(0, 2)), stoi(t.substr(3, 5))};
        a[i].x = x;
        a[i].y = y;
    }
    sort(all(a), [](pt f, pt s) -> bool {
        if (f.time.first == s.time.first) return f.time.second < s.time.second;
        return f.time.first < s.time.first;
    });
    forn(i, 0, n) {
        forn(j, i + 1, n) {
            if (can_add_edge(a[i], a[j], v)) {
                g[i].pb(j);
            }
        }
    }
    mt.assign(n, -1);
    forn(i, 0, n) {
        used.assign(n, false);
        try_kuhn(i);
    }
    vc<pii> ans;
    forn(i, 0, n) {
        if (mt[i] != -1) ans.pb({mt[i] + 1, i + 1});
    }
    int cnt = 0;
    used.assign(n, false);
    forn(i, 0, n) {
        int tmp = i;
        bool is_path = false;
        while (!used[tmp]) {
            is_path = true;
            used[tmp] = true;
            forn(j, 0, n)
                if (mt[j] == tmp) {
                    tmp = j;
                    break;
                }
        }
        if (is_path) cnt++;
    }
    cout << cnt;
}

/*
 1      1
 2      2
 3      3
 4      4

 (1, 2), (1,4), (2,4), (3,4)
 */