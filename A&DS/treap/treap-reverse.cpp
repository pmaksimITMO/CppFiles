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
    ll val, prior, size;
    bool reversed;
    node *l, *r;

    node(ll n_val, ll n_prior) {
        l = r = nullptr;
        size = 1;
        reversed = false;
        val = n_val;
        prior = n_prior;
    }
};

ll get_size(node *root) {
    return (root == nullptr ? 0 : root->size);
}

void propagate(node *root) {
    if (root == nullptr) return;
    if (root->l != nullptr) root->l->reversed ^= root->reversed;
    if (root->r != nullptr) root->r->reversed ^= root->reversed;
    if (root->reversed) swap(root->l, root->r);
    root->reversed = false;
}

void push(node *root) {
    if (root == nullptr) return;
    propagate(root->l);
    propagate(root->r);
    root->size = get_size(root->l) + get_size(root->r) + 1;
}

node *merge(node *t1, node *t2) {
    propagate(t1);
    propagate(t2);
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
    propagate(root);
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
    propagate(root);
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

node *root = nullptr;

int main() {
    IOS;
    mt19937 gen(time(0));
    int n, m;
    cin >> n >> m;
    forn(i, 0, n) insert(root, i + 1, gen(), i);
    forn(i, 0, m) {
        int l, r;
        cin >> l >> r;
        node *a, *b, *c, *d;
        split(root, l - 1, a, b);
        split(b, r - l + 1, c, d);
        c->reversed ^= 1;
        root = merge(a, merge(c, d));
    }
    print(root);
}