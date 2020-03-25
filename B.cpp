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
vector<pair<pii, pair<pii, pii>>> go;
// {    time::{   start; end } place::{   {start}; {end}  }   }
vector<vector<int>> to;
vector<int> l;
vector<int> used;

int parse(const string &s) {
    int h = (s[0] - '0') * 10 + (s[1] - '0'), m = (s[3] - '0') * 10 + (s[4] - '0');
    return h * 60 + m;
}

int dist(const pii &x, const pii &y) {
    return abs(x.X - y.X) + abs(x.Y - y.Y);
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
    freopen("taxi.in", "r", stdin);
    freopen("taxi.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int M, ans = 0;
    cin >> M;
    string t;
    go.resize(M);
    for (int i = 0, a, b; i < M; i++) {
        cin >> t >> go[i].Y.X.X >> go[i].Y.X.Y >> go[i].Y.Y.X >> go[i].Y.Y.Y;
        go[i].X.X = parse(t);
        go[i].X.Y = go[i].X.X + dist(go[i].Y.X, go[i].Y.Y);
    }
    to.assign(M, vector<int>());
    for (int i = 0; i < M; i++) {
        for (int j = i + 1; j < M; j++) {
            if (dist(go[j].Y.X, go[i].Y.Y) < go[j].X.X - go[i].X.Y) {
                to[i].eb(j);
            }
        }
    }
    l.assign(M, -1);
    for (int v = 0; v < M; v++) {
        used.assign(M, 0);
        khun(v);
    }
    for (int v = 0; v < M; v++) if (l[v] != -1) ans++;
    cout << M - ans;
    return 0;
}