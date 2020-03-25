#include <bits/stdc++.h>

#include <random>

#define pb push_back
#define pf push_front
#define eb emplace_back
#define X first
#define Y second
using namespace std;
using pii=pair<int, int>;
using ll=long long;
using pli=pair<ll, int>;
using pll=pair<ll, ll>;
using ull=unsigned long long;
using ld=long double;

//HERE STARTS MAGIC//

using namespace std;
vector<pair<int, pii>> go;
// {    time::{   start; end } place::{   {start}; {end}  }   }
vector<vector<int>> to;
vector<int> l;
vector<int> used;

int parse(const string &s) {
    int h = (s[0] - '0') * 10 + (s[1] - '0'), m = (s[3] - '0') * 10 + (s[4] - '0');
    return h * 60 + m;
}

ld dist(const pii &x, const pii &y) {
    auto z1 = (x.X - y.X), z2 = (x.Y - y.Y);
    return sqrt(z1 * z1 + z2 * z2);
}

int khun(const int &v) {
    if (used[v]) return 0;
    used[v] = 1;
    for (const auto &u : to[v]) {
        if ((l[u] == -1) || khun(l[u])) {
            l[u] = v;
            return true;
        }
    }
    return 0;
}

int main() {
    freopen("ufo.in", "r", stdin);
    freopen("ufo.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, v, ans = 0;
    cin >> n >> v;
    string t;
    go.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> t >> go[i].Y.X >> go[i].Y.Y;
        go[i].X = parse(t);
    }
    sort(go.begin(), go.end());
    to.assign(n, vector<int>());
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((ld) 60 * dist(go[j].Y, go[i].Y) <= (ld) v * (go[j].X - go[i].X)) {
                to[i].eb(j);
            }
        }
    }
    l.assign(n, -1);
    for (int i = 0; i < n; i++) {
        used.assign(n, 0);
        khun(i);
    }
    for (int i = 0; i < n; i++) if (l[i] != -1) ans++;
    cout << n - ans;
    return 0;
}