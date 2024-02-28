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
    node *l, *r;

    node(ll n_val, ll n_prior) {
        l = r = nullptr;
        size = 1;
        val = n_val;
        prior = n_prior;
    }
};

ll get_size(node *root) {
    return (root == nullptr ? 0 : root->size);
}

void push(node *root) {
    if (root == nullptr) return;
    root->size = get_size(root->l) + get_size(root->r) + 1;
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
    ll key = root->val;
    if (key > k) {
        split(root->l, k, res1, root->l);
        res2 = root;
    } else {
        split(root->r, k, root->r, res2);
        res1 = root;
    }
    push(res1);
    push(res2);
}

void insert(node *&root, ll k, ll prior) {
    if (root == nullptr || (root != nullptr && root->prior < prior)) {
        node *tmp = new node(k, prior);
        split(root, k, tmp->l, tmp->r);
        root = tmp;
        push(root);
        return;
    }
    ll key = root->val;
    if (key == k) return;
    if (k < key) {
        insert(root->l, k, prior);
    } else {
        insert(root->r, k, prior);
    }
    push(root);
}

void erase(node *&root, ll x) {
    if (root == nullptr) return;
    if (root->val == x) {
        root = merge(root->l, root->r);
        return;
    }
    if (root->val < x) erase(root->r, x);
    else erase(root->l, x);
    push(root);
}

ll find_kth(node *root, ll x) {
    if (root == nullptr) return 0;
    ll w = get_size(root->r);
    if (w + 1 == x) return root->val;
    if (w + 1 < x) {
        return find_kth(root->l, x - w - 1);
    } else {
        return find_kth(root->r, x);
    }
}

node *root = nullptr;

int main() {
    IOS;
    mt19937 gen(time(0));
    int n;
    cin >> n;
    forn(i, 0, n) {
        int t, x; cin >> t >> x;
        if (t == 1) insert(root, x, gen());
        else if (t == -1) erase(root, x);
        else cout << find_kth(root, x) << '\n';
    }
}