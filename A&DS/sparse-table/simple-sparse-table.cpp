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

const int MAXN = 1e5;
const int MAXT = (1 << 24);
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

int n, m;
ll x;
int table[26][MAXN];

void build() {
    forn(i, 0, n) {
        table[0][i] = x;
        x = (23 * x + 21563) % 16714589;
    }
    forn(i, 1, 26) {
        for (int j = 0; j + (1 << i) <= n; j++) {
            table[i][j] = min(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
        }
    }
}

int rmq(int l, int r) {
    l--;
    int t = __lg(r - l);
    return min(table[t][l], table[t][r - (1 << t)]);
}

int main() {
    IOS;
    cin >> n >> m >> x;
    build();
    int u, v, r;
    cin >> u >> v;
    vi ans;
    forn(i, 1, m + 1) {
        r = rmq(min(v, u), max(v, u));
        if (i == m) {
            ans = {u, v, r};
        }
        u = (17 * u + 751 + r + 2 * i) % n + 1;
        v = (13 * v + 593 + r + 5 * i) % n + 1;
    }
    cout << ans;
}