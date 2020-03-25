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
vector<vector<int>> go, og;
vector<bool> used;
vector<int> s;
map<pii, int> num, mun;
vector<int> a, b, edges;
vector<int> to;

//value, to
int dfs(int v) {
    if (used[v])
        return -1;
    used[v] = 1;
    int res = -1, next = -1, save = -1;
    for (auto u : go[v]) {
        if (s[u] == -1) {
            if (b[u] > res) {
                res = b[u];
                next = u;
            }
        } else {
            auto t = dfs(s[u]);
            if (t > res) {
                res = t;
                next = u;
            }
        }
    }
    to[v] = next;
    return res;
}

void khun(int v) {
    if (dfs(v) != -1)
        for (int i = to[v]; v != -1; i = to[v]) {
            int u = s[i];
            s[i] = v;
            v = u;
        }
}

bool comparatorA(const int &x, const int &y) {
    return a[x] > a[y];
}

bool comparatorB(const int &x, const int &y) {
    return b[x] > b[y];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, e;
    cin >> n >> m >> e;
    go.assign(n, vector<int>());
    og.assign(m, vector<int>());
    a.resize(n);
    b.resize(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];
    for (int i = 0, x, y; i < e; i++) {
        cin >> x >> y;
        x--, y--;
        go[x].eb(y);
        og[y].eb(x);
        num[{x, y}] = i;
        mun[{y, x}] = i;
    }

    vector<int> sorted(n);
    for (int i = 0; i < n; i++) sorted[i] = i;
    sort(sorted.begin(), sorted.end(), comparatorA);

    s.assign(m, -1);
    for (int v : sorted) {
        used.assign(n, false);
        to.assign(n, -1);
        khun(v);
    }
    int ans = 0, sz = 0;
    for (int i = 0; i < m; i++) {
        if (s[i] != -1) {
            ans += b[i] + a[s[i]];
            sz++;
        }
    }

    string res1 = "";
    res1 += to_string(ans) + '\n' + to_string(sz) + '\n';
    for (int i = 0; i < m; i++) if (s[i] != -1) res1 += to_string(num[{s[i], i}] + 1) + " ";
    cout << res1;
    return 0;
}