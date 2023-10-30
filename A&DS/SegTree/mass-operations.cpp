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

ll tree[3 * MAXN], mod[3 * MAXN];

void push(int v) {
    if (mod[v] == -1) return;
    mod[2 * v + 1] = mod[2 * v + 2] = mod[v];
    mod[v] = -1;

    tree[2 * v + 1] = tree[2 * v + 2] = mod[v];
}

void upd(int v, int vl, int vr, int l, int r, int val) {
    if (l <= vl && vr <= r) {
        tree[v] = val;
        mod[v] = val;
        return;
    }
    if (r <= vl || vr <= l) return;
    push(v);
    int vm = (vl + vr) / 2;
    upd(2 * v + 1, vl, vm, l, r, val);
    upd(2 * v + 2, vm, vr, l, r, val);
    tree[v] = min(tree[2 * v + 1], tree[2 * v + 2]);
}

ll ask(int v, int vl, int vr, int l, int r) {
    if (r <= vl || vr <= l) return INF;
    if (l <= vl && vr <= r) return (mod[v] == -1 ? tree[v] : mod[v]);
    push(v);
    int vm = (vl + vr) / 2;
    return min(ask(2 * v + 1, vl, vm, l, r), ask(2 * v + 2, vm, vr, l, r));
}

bool cmp(pair<pii, int> x, pair<pii, int> y) {
    return x.second < y.second;
}

int main() {
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);
    int n, m; cin >> n >> m;
    vc<pair<pii, int>> a(m);
    sort(all(a), cmp);
    forn(i, 0, m) {
        cin >> a[i].first.first >> a[i].first.second >> a[i].second;
        upd(0, 0, n, a[i].first.first - 1, a[i].first.second, a[i].second);
    }
    forn(i, 0, m) {
        if (ask(0, 0, n, a[i].first.first - 1, a[i].first.second) != a[i].second) {
            cout << "inconsistent";
            return 0;
        }
    }
    vll ans;
    forn(i, 0, n) {
        ans.pb(ask(0, 0, n, i, i + 1));
    }
    cout << "consistent\n" << ans;
}