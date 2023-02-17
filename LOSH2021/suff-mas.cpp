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

const int MAXN = 2e5 + 10;
const int INF = 1e9 + 7;
const int LOG = 20;
const ll INFL = 1e18;
const ld INFD = 1e12 + .0;
const int MOD = 1e9 + 7;
const int P = 17;
const int PI = acosl(-1.0);

int n;

void my_sort(vector <pair <pii, int>> &c1) {
    vector <int> cnt(n, 0);
    for (auto &i : c1) {
        cnt[i.first.second]++;
    }
    vector <int> pref(n, 0);
    for (int i = 1; i < n; i++) pref[i] = pref[i - 1] + cnt[i - 1];
    vector <pair <pii, int>> res(n);
    for (int i = 0; i < n; i++) {
        res[pref[c1[i].first.second]] = c1[i];
        pref[c1[i].first.second]++;
    }
    c1 = res;
    cnt.assign(n, 0);
    pref.assign(n, 0);
    res.assign(n, {{0, 0}, 0});
    for (auto &i : c1) {
        cnt[i.first.first]++;
    }
    for (int i = 1; i < n; i++) pref[i] = pref[i - 1] + cnt[i - 1];
    for (int i = 0; i < n; i++) {
        res[pref[c1[i].first.first]] = c1[i];
        pref[c1[i].first.first]++;
    }
    c1 = res;
}

int main() {
    int w, ww;
    string s;
    cin >> w >> s;
    while (w--) cin >> ww;
    s += '#';
    n = s.size();
    vector <pair <char, int>> base(n);
    for (int i = 0; i < n; i++) {
        base[i] = {s[i], i};
    }
    sort(all(base));
    vector<int> c(n);
    c[base[0].second] = 0;
    for (int i = 1; i < n; i++) {
        if (base[i].first == base[i - 1].first) {
            c[base[i].second] = c[base[i - 1].second];
        } else {
            c[base[i].second] = c[base[i - 1].second] + 1;
        }
    }
    for (int level = 1; (1 << (level - 1)) <= n; level++) {
        vector<pair <pii, int>> c1(n);
        for (int i = 0; i < n; i++) {
            c1[i] = {{c[i], c[(i + (1 << (level - 1))) % n]}, i};
        }
        my_sort(c1);
        c[c1[0].second] = 0;
        for (int i = 1; i < n; i++) {
            if (c1[i].first == c1[i - 1].first) {
                c[c1[i].second] = c[c1[i - 1].second];
            } else {
                c[c1[i].second] = c[c1[i - 1].second] + 1;
            }
        }
        if (*max_element(all(c)) == n - 1) break;
    }
    vector <int> suf(n);
    for (int i = 0; i < n; i++) {
        suf[c[i]] = i;
    }
    vector <int> lcp(n);
    int x = 0;
    for (int i = 0; i < n - 1; i++) {
        x = max(x - 1, 0);
        int s1 = i, s2 = suf[c[i] - 1];
        while (s1 + x < n && s2 + x < n && s[s1 + x] == s[s2 + x]) x++;
        lcp[c[i]] = x;
    }
    for (int i = 1; i < n; i++) {
        cout << lcp[i] << " ";
    }
}