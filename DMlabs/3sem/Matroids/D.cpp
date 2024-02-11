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

int n, m;
unordered_map<int, vi> a;

bool secondAx() {
    vi masks(1 << n, 1);
    forn(i, 0, 1 << n) {
        masks[i] = (a.find(i) != a.end());
        for (int j = 0; (1 << j) <= i; ++j) {
            masks[i] &= masks[i & (~(1 << j))];
        }
    }
    for (auto const& i: a) {
        if (!masks[i.first]) return false;
    }
    return true;
}

bool thirdAx() {
    for(auto & i : a) {
        for(auto & j : a) {
            vi x = i.second, y = j.second;
            if (x.size() <= y.size()) continue;
            bool flag = false;
            for(auto const& q: x) {
                if (find(all(y), q) == y.end()) {
                    y.pb(q);
                    int w = j.first | (1 << q);
                    flag |= (a.find(w) != a.end());
                }
            }
            if (!flag) return false;
        }
    }
    return true;
}

int main() {
    freopen("check.in", "r", stdin);
    freopen("check.out", "w", stdout);
    IOS;
    cin >> n >> m;

    forn(i, 0, m) {
        int x; cin >> x;
        int number = 0; vi bits;
        forn(j, 0, x) {
            int q; cin >> q;
            q--;
            number |= (1 << q);
            bits.pb(q);
        }
        a[number] = bits;
    }

    if (a.find(0) != a.end() && secondAx() && thirdAx()) cout << "YES";
    else cout << "NO";
}