#include <bits/stdc++.h>
#include <cassert>
#include <utility>

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

struct node {
    set<int> a;
    int min_, max_;
    node() {
        min_ = INF;
        max_ = 0;
    }
    node(set<int>& a_, int mn_, int mx_) : a(a_), min_(mn_), max_(mx_) {}
    explicit node(int x) : a({x}), min_(x), max_(x) {}
    void insert(int x) { a.insert(x); }
    void erase(int x) { a.erase(x); }
    bool has(int x) const { return a.count(x) != 0; }
    string to_string() {
        string res = "min: ";
        res += std::to_string(min_);
        res += ", max:";
        res += std::to_string(max_);
        res += ", data: ";
        for (auto i : a) {
            res += std::to_string(i);
            res += " ";
        }
        return res;
    }
};

node tree[3 * MAXN];
int a[MAXN];

node merge(node &l, node &r) {
    node res;
    std::merge(l.a.begin(), l.a.end(), r.a.begin(), r.a.end(), inserter(res.a, res.a.end()));
    res.max_ = max(l.max_, r.max_);
    res.min_ = min(l.min_, r.min_);
    return res;
}

void build(int v, int vl, int vr) {
    if (vr - vl == 1) {
        tree[v] = node(a[vl]);
        return;
    }
    int vm = (vl + vr) / 2;
    build(2 * v + 1, vl, vm);
    build(2 * v + 2, vm, vr);
    tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
}

int update(int v, int vl, int vr, int pos, int val) {
    if (vr - vl == 1) {
        int ret = tree[v].min_;
        tree[v] = node(val);
        return ret;
    }
    int vm = (vl + vr) / 2, ret;
    if (pos < vm) ret = update(2 * v + 1, vl, vm, pos, val);
    else ret = update(2 * v + 2, vm, vr, pos, val);
    tree[v].insert(val);
    if (!tree[2 * v + 1].has(ret) && !tree[2 * v + 2].has(ret)) {
        tree[v].erase(ret);
    }
    tree[v].max_ = max(tree[2 * v + 1].max_, tree[2 * v + 2].max_);
    tree[v].min_ = min(tree[2 * v + 1].min_, tree[2 * v + 2].min_);
    return ret;
}

node ask(int v, int vl, int vr, int l, int r) {
    if (r <= vl || vr <= l) return {};
    if (l <= vl && vr <= r) return tree[v];
    int vm = (vl + vr) / 2;
    node l_ = ask(2 * v + 1, vl, vm, l, r), r_ = ask(2 * v + 2, vm, vr, l, r);
    return merge(l_, r_);
}

int main() {
    freopen("permutation.in", "r", stdin);
    freopen("permutation.out", "w", stdout);
    IOS;
    int n;
    cin >> n;
    forn(i, 0, n) cin >> a[i];
    build(0, 0, n);
    int m;
    cin >> m;
    forn(i, 0, m) {
        int op, x1, x2;
        cin >> op >> x1 >> x2;
        x1--;
        if (op == 1) update(0, 0, n, x1, x2);
        else {
            node res = ask(0, 0, n, x1, x2);
            if (res.min_ == 1 && res.max_ == (x2 - x1) && res.a.size() == (x2 - x1)) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
}