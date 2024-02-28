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
#define forn(i,s,n) for(int i = (s); i < (n); ++i)
#define fornr(i,s,n) for(int i = (s); i >= (n); --i)
#define fi first
#define se second
using namespace std;

basic_istream<char> &operator>>(basic_istream<char> &in, vc<long long> &a) {
    forn(i, 0, a.size()) {
        in >> a[i];
    }
    return in;
}

basic_ostream<char> &operator<<(basic_ostream<char> &out, vc<long long> &a) {
    forn(i, 0, a.size()) {
        out << a[i] << ' ';
    }
    return out;
}

basic_istream<char> &operator>>(basic_istream<char> &in, vi &a) {
    forn(i, 0, a.size()) {
        in >> a[i];
    }
    return in;
}

basic_ostream<char> &operator<<(basic_ostream<char> &out, vi &a) {
    forn(i, 0, a.size()) {
        out << a[i] << ' ';
    }
    return out;
}


typedef long long ll;
typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef pair <long long, long long> pll;
typedef long double ld;
typedef pair <ld, ld> pld;
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

int tree[3 * MAXN], a[MAXN];

void build(int v, int vl, int vr) {
    if (vr - vl == 1) {
        tree[v] = a[vl];
        return;
    }
    int vm = (vl + vr) / 2;
    build(2 * v + 1, vl, vm);
    build(2 * v + 2, vm, vr);
    tree[v] = min(tree[2 * v + 1], tree[2 * v + 2]);
}

void update(int v, int vl, int vr, int pos, int val) {
    if (vr - vl == 1) {
        tree[v] = val;
        return;
    }
    int vm = (vl + vr) / 2;
    if (pos < vm) update(2 * v + 1, vl, vm, pos, val);
    else update(2 * v + 2, vm, vr, pos, val);
    tree[v] = min(tree[2 * v + 1], tree[2 * v + 2]);
}

int ask(int v, int vl, int vr, int l, int r) {
    if (r <= vl || vr <= l) return INF;
    if (l <= vl && vr <= r) return tree[v];
    int vm = (vl + vr) / 2;
    return min(ask(2 * v + 1, vl, vm, l, r), ask(2 * v + 2, vm, vr, l, r));
}

int main() {
    int n; cin >> n;
    forn(i, 0, n) cin >> a[i];
    build(0, 0, n);
    string op;
    int x1, x2;
    while (cin >> op >> x1 >> x2) {
        x1--;
        if (op == "min") cout << ask(0, 0, n, x1, x2) << '\n';
        else update(0, 0, n, x1, x2);
    }
}