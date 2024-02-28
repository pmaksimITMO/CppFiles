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

struct pt {
    int x, type;
    pt(int x_, int type_): x(x_), type(type_) {}
};

int main() {
    IOS;
    int n;
    cin >> n;
    vc<pt> a;
    vc<pii> inp(n);
    forn(i, 0, n) {
        int s; cin >> s;
        inp[i].first = s;
        a.pb(pt(s + 1, 0));
    }
    forn(i, 0, n) {
        int g; cin >> g;
        inp[i].second = g;
        a.pb(pt(g - 1, 1));
    }
    sort(all(a), [](pt l, pt r) -> bool {
        if (l.x == r.x) return l.type < r.type;
        return l.x < r.x;
    });
    int cnt = 0;
    int ans = -1, ans_cnt = 0;
    forn(i, 0, 2 * n) {
        if (a[i].type == 0) {
            cnt++;
        } else {
            cnt--;
        }
        if (cnt > ans_cnt) {
            ans_cnt = cnt;
            ans = a[i].x;
        }
    }
    cout << ans_cnt << ' ' << ans << '\n';
    forn(j, 0, n) if (inp[j].first < ans && ans < inp[j].second) cout << j + 1 << ' ';
}

/*
 [5,6]
 [2,12]
 [0,8]
 [10,11]
 [6,10]
 [8,10]
 [3,7]
 */