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

struct edge {
    int v, u, id;
    ull w;
    edge(): v(0), u(0), w(0), id(0) {}
    edge(int v, int u, ull w, int id): v(v), u(u), w(w), id(id) {}
};

vi p, rang;

int get_parent(int v) {
    return p[v] == v ? v : p[v] = get_parent(p[v]);
}

void merge(int x, int y) {
    int a = get_parent(x), b = get_parent(y);
    if (a == b) return;
    if (rang[a] < rang[b]) {
        swap(a, b);
    }
    p[b] = a;
    rang[a] += rang[b];
}

bool same_comp(int x, int y) {
    return get_parent(x) == get_parent(y);
}

void init(const int& n) {
    p.resize(n);
    forn(i, 0, n) p[i] = i;
    rang.assign(n, 1);
}

int main() {
    freopen("destroy.in", "r", stdin);
    freopen("destroy.out", "w", stdout);
    IOS;
    int n, m;
    ull s;
    cin >> n >> m >> s;
    vc<edge> a(m);
    ull sum = 0;
    forn(i, 0, m) {
        cin >> a[i].v >> a[i].u >> a[i].w;
        a[i].id = i;
        --a[i].v;
        --a[i].u;
        sum += a[i].w;
    }
    sort(all(a), [&](edge x, edge y) -> bool {return x.w > y.w;});

    //max ost tree
    init(n);
    ull w_all = 0;
    vi used(m, 0);
    forn(i, 0, m) {
        int v = a[i].v, u = a[i].u;
        if (same_comp(v, u)) continue;
        merge(v, u);
        used[a[i].id] = 1;
        w_all += a[i].w;
    }

    //add if can
    int j = 0;
    while(j < m && w_all + s < sum) {
        if (!used[a[j].id]) {
            used[a[j].id] = 1;
            w_all += a[j].w;
        }
        j++;
    }

    //print res
    cout << m - accumulate(all(used), 0) << '\n';
    forn(i, 0, m) if (!used[i]) cout << (i + 1) << ' ';
}