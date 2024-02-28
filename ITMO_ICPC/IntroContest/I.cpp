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
    IOS;
    int n; cin >> n;
    vi freq(2 * n, 0);
    forn(i, 0, n) {
        int x; cin >> x;
        freq[x - 1]++;
    } // [1 1 2 3] -> [2, 1, 1, 0, 0, 0, 0, 0]
    forn(i, n, 2 * n) freq[i] = freq[i - n];
    vi pref(2 * n, 0), sum(n, 0);
    pref[0] = freq[0];
    sum[0] = freq[0];
    forn(i, 1, 2 * n) {
        pref[i] = pref[i - 1] + freq[i];
        if (i < n) sum[i] = sum[i - 1] + freq[i] * (i + 1);
    }
    int q; cin >> q;
    int st = 1;
    while (q--) {
        int t, z; cin >> t >> z;
        if (t == 1) {
            st += z;
            if (st > n) st = n - st;
        } else {
            int l = 0, r = n;
            auto ok = [pref, st, z](int m) -> bool {
                int cnt = pref[m] - (st == 1 ? 0 : pref[st - 2]);
                return cnt >= z;
            };
            while (r - l > 0) {
                int m = l + (r - l) / 2;
                if (ok(m)) r = m;
                else l = m;
            }
            if (ok(l)) {
                l--;
            }
            int cnt = z - ((l == -1 ? 0 : pref[l]) - (st == 1 ? 0 : pref[st - 2]));
            int ans = 0;
            int ll = 0, rr = l - st;
        }
    }
}
/*
 4
1 1 2 3
10
2 1 [1 1 2 3] -> 1
1 3 [4 4 1 2]
2 1 [4 4 1 2] -> 1
2 2 [4 4 1 2] -> 3
1 1 [1 1 2 3]
2 1 [1 1 2 3] -> 1
1 2 [3 3 4 1]
2 1 [3 3 4 1] -> 1
2 2 [3 3 4 1] -> 4
2 4 [3 3 4 1] -> 11
 */