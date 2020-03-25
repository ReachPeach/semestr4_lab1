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
vector<vector<int>> to;
vector<vector<int>> mx;
vector<vector<pii>> cn;

vector<int> l;
vector<int> used;
int lc = 0, rc = 0;
int n, m;

void dfs(int i, int j, int LR) {
    if (cn[i][j].X != -1)
        return;
    int x = LR ? rc++ : lc++;
    cn[i][j] = {LR, x};
    if (i != 0) {
        if (mx[i - 1][j]) {
            dfs(i - 1, j, LR ^ 1);
            if (!LR) to[x].eb(cn[i - 1][j].Y);
        }
    }
    if (i != n - 1) {
        if (mx[i + 1][j]) {
            dfs(i + 1, j, LR ^ 1);
            if (!LR) to[x].eb(cn[i + 1][j].Y);
        }
    }
    if (j != 0) {
        if (mx[i][j - 1]) {
            dfs(i, j - 1, LR ^ 1);
            if (!LR) to[x].eb(cn[i][j - 1].Y);
        }
    }
    if (j != m - 1) {
        if (mx[i][j + 1]) {
            dfs(i, j + 1, LR ^ 1);
            if (!LR) to[x].eb(cn[i][j + 1].Y);
        }
    }
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
    freopen("dominoes.in", "r", stdin);
    freopen("dominoes.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int a, b, spare = 0;
    cin >> n >> m >> a >> b;
    mx.assign(n, vector<int>(m, 0));
    cn.assign(n, vector<pii>(m, {-1, -1}));
    to.assign(100 * 50, vector<int>());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char x;
            cin >> x;
            if (x == '*') {
                mx[i][j] = 1;
                spare++;
            }
        }
    }

    if (2 * b <= a) {
        cout << b * spare;
        return 0;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mx[i][j]) dfs(i, j, 0);

    l.assign(rc, -1);
    for (int i = 0; i < lc; i++) {
        used.assign(lc, 0);
        khun(i);
    }

    int dob = 0;
    for (int i = 0; i < rc; i++) if (l[i] != -1) dob++;
    cout << dob * a + (spare - 2 * dob) * b;
    return 0;
}