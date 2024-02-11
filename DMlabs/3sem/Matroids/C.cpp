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

int n, k;
vc<vi> g;
vi mt, mt_rev, used;

bool try_kuhn(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (auto const& u : g[v]) {
        if (mt[u] == -1) {
            mt[u] = v;
            mt_rev[v] = u;
            return true;
        }
    }
    for (auto const& u: g[v]) {
        if (try_kuhn(mt[u])) {
            mt[u] = v;
            mt_rev[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    freopen("matching.in", "r", stdin);
    freopen("matching.out", "w", stdout);
    IOS;
    cin >> n;
    vc<pii> w(n);
    forn(i, 0, n) {
        cin >> w[i].first;
        w[i].second = i;
    }

    //read graph
    g.resize(n);
    forn(i, 0, n) {
        int x; cin >> x;
        forn(j, 0, x) {
            int u; cin >> u;
            g[i].pb(--u);
        }
    }

    sort(all(w), [&](pii x, pii y) -> bool {return x.first > y.first;});

    //Kuhn algo
    mt.assign(n, -1);
    mt_rev.assign(n, -1);
    forn(i, 0, n) {
        used.assign(n, false);
        try_kuhn(w[i].second);
    }

    //Print result
    for(auto const& i : mt_rev) cout << i + 1 << ' ';
}