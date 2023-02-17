#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define IOS ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pb push_back
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef pair <long long, long long> pll;
typedef long double ld;
typedef pair <ld, ld> pld;

const int MAXN = 5 * 1e4 + 100;
const int INF = 1e9 + 7;
const int LOG = 20;
const ll INFL = 1e18;
const ld INFD = 1e12 + .0;
const int MOD = 1e9 + 7;
const int P = 17;
const int PI = acosl(-1.0);

int n;
vector <int> g[MAXN];

int a[MAXN], down[MAXN], up[MAXN], len[MAXN], d[MAXN], sz[MAXN];
vector <int> tree[MAXN], euler, vert[MAXN];
int sparse[LOG + 1][2 * MAXN], logs[2 * MAXN], first[MAXN];

void dfs(int v, int p = -1) {
    d[v] = (p == -1 ? 0 : d[p] + 1);
    sz[v] = 1;
    first[v] = euler.size();
    euler.pb(v);
    for (auto &u : g[v]) {
        if (u != p) {
            dfs(u, v);
            sz[v] += sz[u];
            euler.pb(v);
        }
    }
    down[v] = v;
    up[v] = p;
    len[v] = 1;
    vert[v].pb(v);
    for (auto &u : g[v]) {
        if (u != p && sz[u] * 2 >= sz[v]) {
            down[v] = down[u];
            up[down[v]] = p;
            len[down[v]]++;
            vert[down[v]].pb(v);
            break;
        }
    }
}

inline int Min(int a, int b) {
    return (d[a] < d[b] ? a : b);
}

void make_lca() {
    logs[1] = 0;
    for (int i = 2; i < 2 * MAXN; i++) logs[i] = logs[i/2] + 1;
    int l = 2 * n - 1;
    for (int i = 0; i < l; i++) sparse[0][i] = euler[i];
    for (int level = 1; (1 << level) <= l; level++) {
        for (int i = 0; i + (1 << level) <= l; i++) {
            sparse[level][i] = Min(sparse[level - 1][i], sparse[level - 1][i + (1<< (level - 1))]);
        }
    }
}

int lca(int u, int v) {
    u = first[u], v = first[v];
    if (u > v) swap(u, v);
    int level = logs[v - u + 1];
    return Min(sparse[level][u], sparse[level][v - (1 << level) + 1]);
}

void build(int i, int t, int l, int r) {
    if (l == r - 1) {
        tree[i][t] = a[vert[i][l]];
        return;
    }
    int m = (l + r) / 2;
    build(i, 2 * t + 1, l, m);
    build(i, 2 * t + 2, m, r);
    tree[i][t] = max(tree[i][2 * t + 1], tree[i][2 * t + 2]);
}

void build_hld() {
    for (int i = 0; i < n; i++) {
        if (down[i] == i) {
            tree[i].resize(4 * len[i]);
            build(i, 0, 0, len[i]);
        }
    }
}

int ask(int i, int t, int l, int r, int x, int y) {
    if (x <= l && r <= y) {
        return tree[i][t];
    }
    if (y <= l || r <= x) {
        return -INF;
    }
    int m = (l + r)/2;
    return max(ask(i, 2 * t + 1, l, m, x, y), ask(i, 2 * t + 2, m, r, x, y));
}

void upd(int i, int t, int l, int r, int pos, int val) {
    if (l + 1 == r) {
        tree[i][t] = val;
        return;
    }
    int m = (l + r) / 2;
    if (pos < m) upd(i, 2 * t + 1, l, m, pos, val);
    else upd(i, 2 * t + 2, m, r, pos, val);
    tree[i][t] = max(tree[i][2 * t + 1], tree[i][2 * t + 2]);
}

void upd_hld(int v, int val) {
    upd(down[v], 0, 0, len[down[v]], d[down[v]] - d[v], val);
}

int ask_hld(int u, int v) {
    if (down[u] == down[v]) {
        return ask(down[u], 0, 0, len[down[u]], d[down[u]] - d[u], d[down[u]] - d[v] + 1);
    }
    return max(ask(down[u], 0, 0, len[down[u]], d[down[u]] - d[u], len[down[u]]), ask_hld(up[down[u]], v));
}

int main(){
    IOS;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].pb(v);
        g[v].pb(u);
    }
    dfs(0);
    make_lca();
    build_hld();
    int q;
    cin >> q;
    while (q--) {
        char t;
        cin >> t;
        if (t == '!') {
            int v, val;
            cin >> v >> val;
            upd_hld(v - 1, val);
        } else {
            int u, v;
            cin >> u >> v;
            u--, v--;
            int l = lca(u, v);
            cout << max(ask_hld(u, l), ask_hld(v, l)) << "\n";
        }
    }
}