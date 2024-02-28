//
// Created by Dns56 on 15.12.2023.
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
const ll INFL = 1e18;
const int MOD = 1e9 + 7;
const int P = 17;
const int MOD2 = 1e9 + 11;
const int P2 = 31;
const ld PI = acosl(-1.0);

#ifndef NDEBUG
#define MYASSERT(msg, expr) if (!(expr)) {cerr << (msg); while(1) {cout<<1;}}
#else
#define MYASSERT(expr)
#endif

struct Trie {
private:
    struct Node {
        int next[26];
        vi term;
        int sufLink, superSufLink;
    };

    vc<Node> nodes;
    int trie_size = 0, cnt_strings = 0;

public:
    Trie() {
        nodes.emplace_back();
        trie_size = 1;
    }

    void add(const string &s) {
        int v = 0;
        for (auto const &i: s) {
            int u = i - 'a';
            if (!nodes[v].next[u]) {
                nodes.emplace_back();
                nodes[v].next[u] = trie_size++;
            }
            v = nodes[v].next[u];
        }
        nodes[v].term.pb(cnt_strings++);
    }

    void buildAvt() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            auto v = q.front();
            q.pop();
            forn(i, 0, 26) {
                if (!nodes[v].next[i]) nodes[v].next[i] = nodes[nodes[v].sufLink].next[i];
                else {
                    int u = nodes[v].next[i];
                    if (v != 0) {
                        nodes[u].sufLink = nodes[nodes[v].sufLink].next[i];
                        nodes[u].superSufLink = !nodes[nodes[u].sufLink].term.empty() ?
                                                nodes[u].sufLink :
                                                nodes[nodes[u].sufLink].superSufLink;
                    }
                    q.push(u);
                }
            }
        }
    }

    void allOccurencies(const string& s, vi& a) {
        int v = 0;
        vi used(trie_size, 0);
        for (auto &i : s) {
            v = nodes[v].next[i - 'a'];
            int tmp = v;
            while (used[tmp] == 0) {
                used[tmp] = 1;
                for (auto& j : nodes[tmp].term) a[j] = 1;
                tmp = nodes[tmp].superSufLink;
            }
        }
    }
};

int main() {
    IOS;
    int n; cin >> n;
    Trie trie;
    forn(i, 0, n) {
        string s; cin >> s;
        trie.add(s);
    }
    trie.buildAvt();
    string text;
    cin >> text;
    vi ans(n, 0);
    trie.allOccurencies(text, ans);
    forn(i, 0, n) cout << (ans[i] == 1 ? "YES" : "NO") << '\n';
}