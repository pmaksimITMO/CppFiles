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

int n, m;
vi res; //Contains edges ids
vi p, rang;
vc<bool> free_adding;

void init_dsu() {
    p.resize(n);
    forn(i, 0, n) p[i] = i;
    rang.assign(n, 0);
}

int get_parent(int v) {
    return p[v] == v ? v : p[v] = get_parent(p[v]);
}

void unit(int x, int y) {
    int a = get_parent(x), b = get_parent(y);
    if (a == b) return;
    if (rang[a] < rang[b]) swap(a, b);
    p[b] = a;
    rang[a] += rang[b];
}

struct edge {
    int v, u, color;
    edge() : edge(0, 0, 0) {}
    edge(int v, int u, int color) : v(v), u(u), color(color) {}
};

vc<vi> create_graph(vc<edge> &edges) {
    vi right; // left = res, right = all \ res
    vi colors(100, 0);
    int id = 0;
    forn(i, 0, m) {
        if (id < res.size() && res[id] == i) {
            colors[edges[i].color]++;
            id++;
        } else right.pb(i);
    }

    //Create graph
    vc<vi> graph(m + 1);
    //set '-->' edges
    for (auto const &i: res) {
        for (auto const &j: right) {
            if (colors[edges[j].color] == 0 || edges[i].color == edges[j].color) {
                graph[i].pb(j);
            }
        }
    }
    for (auto const &j: right) {
        if (colors[edges[j].color] == 0) {
            graph[m].pb(j);
        }
    }

    //set '<--' edges
    for (auto const &i: res) {
        //set up dsu
        init_dsu();
        for (auto const &j: res) {
            if (i == j) continue;
            unit(edges[j].v, edges[j].u);
        }
        //check for possible new item
        for (auto const &j: right) {
            if (get_parent(edges[j].v) != get_parent(edges[j].u)) {
                graph[j].pb(i);
            }
        }
        //check for possible addition without erasing 1 item on left
        unit(edges[i].v, edges[i].u);
        for (auto const &j: right) {
            if (get_parent(edges[j].v) != get_parent(edges[j].u)) {
                free_adding[j] = true;
            }
        }
    }
    return graph;
}

void bfs(vc<vi > g, vi &path) {
    vi used(m + 1, 0), par(m + 1, -1);
    queue<int> q;
    used[m] = true;
    q.push(m);
    bool reached = false;
    int last_in_path = -1;
    while (!q.empty() && !reached) {
        int v = q.front();
        q.pop();
        for (auto const &u: g[v]) {
            if (!used[u]) {
                used[u] = true;
                q.push(u);
                par[u] = v;
            }
            if (free_adding[u]) {
                reached = true;
                last_in_path = u;
                break;
            }
        }
    }
    while (last_in_path != -1) {
        path.pb(last_in_path);
        last_in_path = par[last_in_path];
    }
}

int main() {
    freopen("rainbow.in", "r", stdin);
    freopen("rainbow.out", "w", stdout);
    IOS;
    cin >> n >> m;
    vc<edge> edges(m);
    forn(i, 0, m) {
        cin >> edges[i].v >> edges[i].u >> edges[i].color;
        --edges[i].v, --edges[i].u, --edges[i].color;
    }

    res.pb(0);
    while (true) {
        free_adding.assign(m, false);
        vi path;
        vc<vi > g = create_graph(edges);
        bfs(g, path);
        sort(all(path));
        if (path.empty()) break;
        path.pop_back();
        //xor edges in path && result
        int l = 0, r = 0;
        vi tmp;
        while (l < res.size() && r < path.size()) {
            if (res[l] == path[r]) l++, r++;
            else if (res[l] < path[r]) tmp.pb(res[l++]);
            else tmp.pb(path[r++]);
        }
        while (l < res.size()) tmp.pb(res[l++]);
        while (r < path.size()) tmp.pb(path[r++]);
        res = tmp;
    }

    cout << res.size() << '\n';
    for(auto const& i: res) cout << i + 1 << ' ';
}