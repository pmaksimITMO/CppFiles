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

const int MAXN = 1e5;
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

struct pt {
    int a, b, c, id;
    pt() {
        a = 0, b = 0, c = 0, id = 0;
    }
    pt(int a_, int b_, int c_, int id_): a(a_), b(b_), c(c_), id(id_) {}
};

bool cmp(pt x, pt y) {
    return (x.a == y.a ? x.id < y.id : x.a < y.a);
}

int lower_or_equal(vi &a, int x) {
    int l = 0, r = a.size();
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (a[m] > x) r = m;
        else l = m;
    }
    return l;
}

int main() {
    int n; cin >> n;
    vc<pt> inp(n);
    forn(i, 0, n) {
        int val; cin >> val; inp[i].a = val;
        inp[i].id = i + 1;
    }
    forn(i, 0, n) {
        int val; cin >> val; inp[i].b = val;
    }
    forn(i, 0, n) {
        int val; cin >> val; inp[i].c = val;
    }
    sort(all(inp), cmp);
    map<int, int> available_for_children;
    vi with_h_edu, id_with_ed, no_h_edu, id_no_ed;
    forn(i, 0, n) {
        available_for_children[inp[i].id] = inp[i].c;
        if (inp[i].b == 0) {
            no_h_edu.pb(inp[i].a);
            id_no_ed.pb(inp[i].id);
        } else {
            with_h_edu.pb(inp[i].a);
            id_with_ed.pb(inp[i].id);
        }
    }
    int q; cin >> q;
    vi x(q), y(q), z(q);
    cin >> x >> y >> z;
    vi res(q);
    vi pr_min_ed(id_with_ed.size(), INF), pr_min_no_ed(id_no_ed.size(), INF);
    if (!pr_min_ed.empty()) {
        pr_min_ed[0] = id_with_ed[0];
        forn(i, 1, id_with_ed.size()) {
            pr_min_ed[i] = min(pr_min_ed[i - 1], id_with_ed[i]);
        }
    }
    if (!pr_min_no_ed.empty()) {
        pr_min_no_ed[0] = id_no_ed[0];
        forn(i, 1, id_no_ed.size()) {
            pr_min_no_ed[i] = min(pr_min_no_ed[i - 1], id_no_ed[i]);
        }
    }

    //    for (int i: id_no_ed) cout << i << ' ';
    //    cout << '\n';
    //    for (int i: pr_min_no_ed) cout << i << ' ';
    //    cout << '\n';
    //    for (int i: id_with_ed) cout << i << ' ';
    //    cout << '\n';
    //    for (int i: pr_min_ed) cout << i << ' ';
    //    cout << '\n';

    forn(i, 0, q) {
        int cur = n + 1;

        //сначала проверка на родителей
        if (available_for_children[z[i]]) cur = z[i];

        //потом на те страны где не надо высшее
        if (!no_h_edu.empty() && no_h_edu[0] <= x[i]) {
            int tmp = lower_or_equal(no_h_edu, x[i]);
            cur = min(cur, pr_min_no_ed[tmp]);
        }

        //потом на те страны где надо высшее
        if (y[i] == 1 && !with_h_edu.empty() && with_h_edu[0] <= x[i]) {
            int tmp = lower_or_equal(with_h_edu, x[i]);
            cur = min(cur, pr_min_ed[tmp]);
        }

        res[i] = (cur == n + 1 ? 0 : cur);
    }
    cout << res;
}