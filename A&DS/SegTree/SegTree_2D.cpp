//
// Created by Dns56 on 03.06.2023.
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

const int MAXN = (1 << 17);
const int INF = INT32_MAX;
const ll INFL = 1e16;
const int MOD = 1e9 + 7;
const int P = 17;
const ld PI = acosl(-1.0);

#ifndef NDEBUG
#define MYASSERT(msg, expr) if (!(expr)) {cerr << (msg); while(1) {cout<<1;}}
#else
#define MYASSERT(expr)
#endif

unsigned int a, b;
unsigned int cur = 0;

unsigned int rnd17() {
    cur = cur * a + b;
    return cur >> 15;
}

unsigned int rnd24() {
    cur = cur * a + b;
    return cur >> 8;
}

struct node {
    int min_, max_, cnt;
    node() = default;
    explicit node(int x): min_(x), max_(x), cnt(1) {}
};

node tree[3 * MAXN];
int f[MAXN];

node merge(node &l, node &r) {
    node res;
    res.min_ = min(l.min_, r.min_);
    res.max_ = max(l.max_, r.max_);
    res.cnt = l.cnt + r.cnt;
    return res;
}

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = node(f[l]);
        return;
    }
    int m = (l + r) / 2;
    build(2 * v + 1, l, m);
    build(2 * v + 2, m, r);
    tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
}

int ask(int v, int vl, int vr, int l, int r, int val) {
    if (r <= vl || vr <= l || val < tree[v].min_) return 0;
    if (l <= vl && vr <= r && tree[v].max_ <= val) return tree[v].cnt;
    int vm = (vl + vr) / 2;
    return ask(2 * v + 1, vl, vm, l, r, val) + ask(2 * v + 2, vm, vr, l, r, val);
}

int main() {
    int q;
    cin >> q >> a >> b;
    forn(i, 0, MAXN) f[i] = rnd24();
    build(0, 0, MAXN);
    ll ans = 0;
    while (q--) {
        int l = rnd17(), r = rnd17();
        if (l > r) swap(l, r);
        int x = rnd24(), y = rnd24();
        if (x > y) swap(x, y);
        int c = ask(0, 0, MAXN, l, r + 1, y) - ask(0, 0, MAXN, l, r + 1, x - 1);
        b += c;
        ans = (ans + c) % (1ll << 32);
    }
    cout << ans;
}
//5 13 239
