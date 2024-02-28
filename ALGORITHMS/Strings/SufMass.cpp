//
// Created by Dns56 on 15.12.2023.
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

struct SuffixArray {
    string s;
    vi perm;

    explicit SuffixArray(const string &st) : s(st) {
        perm.resize(s.size());
        s.pb(0);
        int n = int(s.size());
        vi c(n), p(n), cnt(400001, 0);
        forn(i, 0, n) ++cnt[s[i]];
        forn(i, 1, 256) cnt[i] += cnt[i - 1];
        forn(i, 0, n) p[--cnt[s[i]]] = i;
        c[p[0]] = 0;
        int classes = 1;
        forn(i, 1, n) {
            if (s[p[i]] != s[p[i - 1]]) ++classes;
            c[p[i]] = classes - 1;
        }
        vi pn(n), cn(n);
        for (int h = 0; (1 << h) < n; ++h) {
            forn(i, 0, n) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0) pn[i] += n;
            }
            fill(cnt.begin(), cnt.begin() + classes, 0);
            forn(i, 0, n) ++cnt[c[pn[i]]];
            forn(i, 1, classes) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; --i) p[--cnt[c[pn[i]]]] = pn[i];
            cn[p[0]] = 0;
            classes = 1;
            forn(i, 1, n) {
                int mid1 = (p[i] + (1 << h)) % n, mid2 = (p[i - 1] + (1 << h)) % n;
                if (c[p[i]] != c[p[i - 1]] || c[mid1] != c[mid2])
                    ++classes;
                cn[p[i]] = classes - 1;
            }
            c.swap(cn);
        }
        forn(i, 0, n - 1) perm[i] = p[i + 1];
        s.pop_back();
    }

    vi calcLCP() {
        int n = int(perm.size());
        vi lcp(n - 1, 0), rev_perm(n);
        forn(i, 0, n) rev_perm[perm[i]] = i;
        int cur = 0;
        s.pb(0);
        forn(i, 0, n) {
            if (cur > 0) --cur;
            if (rev_perm[i] == n - 1) {
                cur = 0;
            } else {
                int j = perm[rev_perm[i] + 1];
                while (max(i + cur, j + cur) < n && s[i + cur] == s[j + cur]) ++cur;
                lcp[rev_perm[i]] = cur;
            }
        }
        s.pop_back();
        return lcp;
    }
};

int main() {
    IOS;
    string s;
    cin >> s;
    SuffixArray sa = SuffixArray(s);
    vi lcp = sa.calcLCP();
    for (auto const& i : sa.perm) cout << i + 1 << ' ';
    cout << '\n' << lcp;
}