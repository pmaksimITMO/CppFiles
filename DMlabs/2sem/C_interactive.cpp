//
// Created by Dns56 on 28.10.2023.
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

bool ask(int x, int y) {
    cout << "1 " << x + 1 << ' ' << y + 1 << endl;
    cout.flush();
    string res;
    cin >> res;
    return res == "YES";
}

void add(vi& a, int pos, int item) {
    if (pos >= a.size()) a.pb(item);
    else {
        vi b;
        forn(i, 0, pos) b.pb(a[i]);
        b.pb(item);
        forn(i, pos, a.size()) b.pb(a[i]);
        a = b;
    }
}

int main() {
    int n;
    cin >> n;
    vi ans = {1};
    if (n > 1) {
        add(ans, ask(0, 1) ? 1 : 0, 2);
        while (ans.size() < n) {
            int l = 0, r = ans.size(), cur = ans.size() + 1;
            while (l != r) {
                int m = (l + r) / 2;
                if (ask(cur - 1, ans[m] - 1)) {
                    r = m;
                } else {
                    l = m + 1;
                }
            }
            add(ans, l, cur);
        }
    }
    cout << "0 " << ans;
}