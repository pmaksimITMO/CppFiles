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

const int MAXN = 1e6;
const int LOG = 26;
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

ll bin_p(ll a, ll n) {
    ll res = 1;
    while (n != 0) {
        if (n & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return res;
}

ll inv(ll x) {
    return bin_p(x, MOD - 2);
}

int main() {
    IOS;
    int t = 1; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        map<int, int> cnt;
        forn(i, 0, n) {
            int x; cin >> x;
            cnt[x]++;
        }
        auto l = cnt.begin(), r = cnt.begin();
        ll ans = 0, cur = l->second, col = 1;
        while(r != cnt.end()) {
            if (col < m) {
                col++;
                r++;
                if (r == cnt.end()) break;
                cur = cur * r->second % MOD;
            } else {
                if (r->first - l->first < m) ans = (ans + cur) % MOD;
                col--;
                cur = cur * inv(l->second) % MOD;
                l++;
            }
//            cout << l->first << ' ' << r->first << " | " << cur << ' ' << col << '\n';
        }
        cout << ans << '\n';
    }
}