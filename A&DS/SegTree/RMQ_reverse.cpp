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

const int MAXN = 2e5;
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

int tree[3 * MAXN], ans[MAXN], lg[MAXN], dsu[MAXN];

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = ans[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * v + 1, l, m);
    build(2 * v + 2, m, r);
    tree[v] = min(tree[2 * v + 1], tree[2 * v + 2]);
}

int ask(int v, int vl, int vr, int l, int r) {
    if (r <= vl || vr <= l) return INF;
    if (l <= vl && vr <= r) return tree[v];
    int vm = (vl + vr) / 2;
    return min(ask(2 * v + 1, vl, vm, l, r), ask(2 * v + 2, vm, vr, l, r));
}

struct seg {
    int l, r, val, id;
    seg() = default;
    seg(int l_, int r_, int val_, int id_): l(l_), r(r_), val(val_), id(id_) {}
};

bool cmp(seg a, seg b) {
    return (a.val > b.val) || (a.val == b.val && a.id < b.id);
}

int get(int v) {
    return (dsu[v] == v ? v : dsu[v] = get(dsu[v]));
}

void init_dsu(int n) {
    lg[1] = 0;
    forn(i, 0, n + 1) {
        lg[i] = lg[i / 2] + 1;
        dsu[i] = i;
        ans[i] = INF;
    }
}

int main() {
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);
    int n, m; cin >> n >> m;
    init_dsu(n);
    vc<seg> a(m);
    forn(i, 0, m) {
        int l, r, x; cin >> l >> r >> x;
        a[i] = seg(l - 1, r - 1, x, i);
    }
    sort(all(a), cmp);
    forn(i, 0, m) {
        for (int j = get(a[i].l); j <= a[i].r; j = get(j)) {
            dsu[j] = j + 1;
            ans[j] = a[i].val;
        }
    }
    build(0, 0, n);
    forn(i, 0, m) {
        if (ask(0, 0, n, a[i].l, a[i].r + 1) != a[i].val) {
            cout << "inconsistent";
            return 0;
        }
    }
    cout << "consistent\n";
    forn(i,0,n) cout << ans[i] << ' ';
}