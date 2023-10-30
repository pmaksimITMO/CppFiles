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

struct node {
    ll val, prior, size, sum;
    node *l, *r;

    node(ll n_val, ll n_prior) {
        l = r = nullptr;
        size = 1;
        val = n_val;
        prior = n_prior;
        sum = n_val;
    }
};

ll get_size(node *root) {
    return (root == nullptr ? 0 : root->size);
}

ll get_sum(node *root) {
    return (root == nullptr ? 0 : root->sum);
}

void push(node *root) {
    if (root == nullptr) return;
    root->size = get_size(root->l) + get_size(root->r) + 1;
    root->sum = get_sum(root->l) + get_sum(root->r) + root->val;
}

node *merge(node *t1, node *t2) {
    if (t1 == nullptr) return t2;
    if (t2 == nullptr) return t1;
    if (t1->prior < t2->prior) {
        t2->l = merge(t1, t2->l);
        push(t2);
        return t2;
    } else {
        t1->r = merge(t1->r, t2);
        push(t1);
        return t1;
    }
}

void split(node *root, ll k, node *&res1, node *&res2) {
    if (root == nullptr) {
        res1 = res2 = nullptr;
        return;
    }
    ll key = get_size(root->l);
    if (key >= k) {
        split(root->l, k, res1, root->l);
        res2 = root;
    } else {
        split(root->r, k - key - 1, root->r, res2);
        res1 = root;
    }
    push(res1);
    push(res2);
}

void insert(node *&root, ll k, ll prior, ll id) {
    if (root == nullptr || (root != nullptr && root->prior < prior)) {
        node *tmp = new node(k, prior);
        split(root, id, tmp->l, tmp->r);
        root = tmp;
        push(root);
        return;
    }
    ll key = get_size(root->l);
    if (id <= key) {
        insert(root->l, k, prior, id);
    } else {
        insert(root->r, k, prior, id - key - 1);
    }
    push(root);
}

void print(node *root) {
    if (root == nullptr) return;
    push(root);
    print(root->l);
    cout << root->val << ' ';
    print(root->r);
}

node *root_even, *root_odd;
mt19937 gen(time(0));

void solve(int n, int m) {
    root_even = root_odd = nullptr;
    forn(i, 0, n) {
        ll x;
        cin >> x;
        if (i % 2 == 0) insert(root_even, x, gen(), i);
        else insert(root_odd, x, gen(), i);
    }
    forn(i, 0, m) {
        int l, r, op;
        cin >> op >> l >> r;
        l--, r--;
        node *even_l, *even_m, *even_r;
        node *odd_l, *odd_m, *odd_r;
        int l1 = (l + 1) / 2, r1 = r / 2, l2 = l / 2, r2 = (r + 1) / 2 - 1;
        split(root_even, l1, even_l, even_m);
        split(even_m, r1 - l1 + 1, even_m, even_r);
        split(root_odd, l2, odd_l, odd_m);
        split(odd_m, r2 - l2 + 1, odd_m, odd_r);

        if (op == 1) {
            root_even = merge(merge(even_l, odd_m), even_r);
            root_odd = merge(merge(odd_l, even_m), odd_r);
        } else {
            cout << get_sum(even_m) + get_sum(odd_m) << '\n';
            root_even = merge(merge(even_l, even_m), even_r);
            root_odd = merge(merge(odd_l, odd_m), odd_r);
        }
    }
}

int main() {
    IOS;
    int n = 1, m = 1, i = 1;
    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0) break;
        if (i > 1) cout << "\n";
        cout << "Swapper " << i++ << ":\n";
        solve(n, m);
    }
}