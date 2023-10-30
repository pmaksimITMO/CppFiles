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

int n, m, k;
vc<vi > g;

int main() {
    freopen("minimization.in", "r", stdin);
    freopen("minimization.out", "w", stdout);
    cin >> n >> m >> k;
    n++;
    g.resize(n);
    set<int> term, all;
    forn(i, 0, n) {
        g[i].assign(26, 0);
        if (i > 0) all.insert(i);
    }
    forn(i, 0, k) {
        int x;
        cin >> x;
        term.insert(x);
        all.erase(x);
    }
    forn(i, 0, m) {
        int v, u;
        char c;
        cin >> v >> u >> c;
        g[v][c - 'a'] = u;
    }
    forn(i, 1, n) {
        int w = 0;
        forn(j, 0, 26) if (g[i][j] > 0 && g[i][j] != i) w++;
        if (w == 0) all.erase(i);
    }
    queue<pair<set<int>, int>> s;
    vc<set<int>> p;
    p.pb(term);
    if (!all.empty()) p.pb(all);
    forn(i, 0, 26) {
        s.push({term, i});
        s.push({all, i});
    }
    while (!s.empty()) {
        auto w = s.front();
        s.pop();
        set<int> c = w.first;
        int a = w.second;
        vc<set<int>> p1;
        for (auto &r: p) {
            set<int> r1, r2;
            for (auto v: r) {
                if (c.find(g[v][a]) == c.end()) r2.insert(v);
                else r1.insert(v);
            }
            if (!r1.empty() && !r2.empty()) {
                p1.pb(r1);
                p1.pb(r2);
                forn(i, 0, 26) {
                    s.push({r1, i});
                    s.push({r2, i});
                }
            } else p1.pb(r);
        }
        p = p1;
    }
//    cout << "-----------\n";
//    for(auto &i : p) {
//        for (auto v : i) cout << v << ' ';
//        cout << "\n-----------\n";
//    }
    vi comp(n, 0);
    forn(i, 0, p.size()) {
        for (auto j : p[i]) {
            comp[j] = i + 1;
        }
    }
    set<int> n_term;
    forn(i, 1, n) {
        if (term.find(comp[i]) != term.end()) n_term.insert(comp[i]);
    }
    vc<vi> rbr(p.size() + 1, vi(26, 0));
    forn(i, 1, n) {
        forn(x, 0, 26) {
            rbr[comp[i]][x] = comp[g[i][x]];
        }
    }
    int n_m = 0;
    forn(i, 1, p.size() + 1) {
        forn(x, 0, 26) {
            if (rbr[i][x] != 0) n_m++;
        }
    }
    cout << p.size() << ' ' << n_m << ' ' << n_term.size() << '\n';
    for (auto i : n_term) cout << i << ' ';
    cout << '\n';
    forn(i, 1, p.size() + 1) {
        forn(x, 0, 26) {
            if (rbr[i][x] != 0) {
                char y = 'a' + x;
                cout << i << ' ' << rbr[i][x] << ' ' << y << '\n';
            }
        }
    }
}
/*
 * Test 1:
5 12 3
2 3 4
1 2 a
2 1 a
5 2 b
2 5 b
1 3 b
3 1 b
5 3 c
3 5 c
1 4 c
4 1 c
5 4 a
4 5 a
 * Test 2:
2 2 2
1 2
1 2 a
2 1 a
 * Test 3:
3 2 2
1 2
1 2 a
2 1 a
 * Test 4:
5 10 3
1 3 4
1 2 a
1 3 b
3 2 a
3 3 b
2 4 a
4 2 a
4 3 b
2 5 b
5 5 b
5 4 a
 * Test 5:
4 8 3
2 3 4
1 2 a
1 3 b
2 2 a
2 2 b
3 4 a
3 4 b
4 3 a
4 3 b
 * Test 6:
6 11 1
5
1 2 a
1 3 b
2 2 a
2 4 b
3 3 b
3 2 a
4 2 a
4 5 b
5 2 a
5 3 b
6 5 a
 Test 7:
8 16 2
6 7
1 2 b
2 1 b
1 8 a
2 8 a
8 3 a
8 3 b
3 5 a
3 6 b
4 5 a
4 6 b
5 6 a
5 7 b
6 6 a
6 6 b
7 7 a
7 6 b
 */