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

struct pt {
    pt() = default;
    pt(string name, vector<int> v): name(name), val(v) {}
    string name;
    vector<int> val;
};

vector<int> p;
bool cmp(pt a, pt b) {
    bool res = true;
    for (int i : p) {
        if (a.val[i] != b.val[i]) {
            res = a.val[i] > b.val[i];
            break;
        }
    }
    return res;
}

int main() {
    int n, k;
    cin >> n >> k;
    p.resize(k);
    for (int i = 0; i < k; ++i) {
        cin >> p[i];
        p[i]--;
    }
    vector<pt> a(n);
    for (int i = 0; i < n; ++i) {
        string name; vector<int> v(k);
        cin >> name;
        for (int j = 0; j < k; ++j) cin >> v[j];
        a[i] = pt(name, v);
    }
    sort(a.begin(), a.end(), cmp);
    for (const auto& x : a) {
        cout << x.name << '\n';
    }
}