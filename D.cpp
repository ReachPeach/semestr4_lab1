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
vector<vector<int>> go;
vector<vector<int>> inverted;
vector<int> l;
vector<int> used;
vector<int> in_ans;

int khun(const int &v) {
    if (used[v]) return 0;
    used[v] = 1;
    for (const auto &u : go[v]) {
        if ((l[u] == -1) || khun(l[u])) {
            l[u] = v;
            return 1;
        }
    }
    return 0;
}

void simple_dfs(const int &v) {
    if (used[v]) return;
    used[v] = 1;
    for (auto u : go[v]) {
        in_ans[u] = 1;
        if (l[u] != -1) {
            simple_dfs(l[u]);
        }
    }
}

vector<vector<int>> invert(const vector<vector<int>> &a, const int &n, const int &m) {
    vector<vector<int>> r(n, vector<int>());
    for (int i = 0; i < n; i++) {
        vector<int> x(m, 1);
        for (auto t : a[i]) x[t] = 0;
        for (int j = 0; j < m; j++) if (x[j]) r[i].eb(j);
    }
    return r;
}

void solve() {
    int n, m;
    cin >> n >> m;
    go.assign(n, vector<int>());
    for (int i = 0, x; i < n; i++) {
        for (cin >> x; x; cin >> x) {
            x--;
            go[i].eb(x);
        }
    }
    inverted = invert(go, n, m);
    swap(go, inverted);

    l.assign(m, -1);
    for (int i = 0; i < n; i++) {
        used.assign(n, 0);
        khun(i);
    }

    used.assign(n, 0);
    vector<int> suspects;
    for (int i = 0; i < m; i++) if (l[i] != -1) used[l[i]] = 1;
    for (int i = 0; i < n; i++) if (!used[i]) suspects.eb(i);

    used.assign(n, 0);
    in_ans.assign(m, 0);
    for (auto suspect : suspects) simple_dfs(suspect);

    int N = 0, M = 0;
    for (int i = 0; i < n; i++) if (used[i]) N++;
    for (int i = 0; i < m; i++) if (!in_ans[i]) M++;

    cout << N + M << '\n' << N << " " << M << '\n';
    for (int i = 0; i < n; i++) if (used[i]) cout << i + 1 << " ";
    cout << '\n';
    for (int i = 0; i < m; i++) if (!in_ans[i]) cout << i + 1 << " ";
    cout << "\n\n";

    go.clear(), inverted.clear(), in_ans.clear(), l.clear(), used.clear();
}

int main() {
    freopen("birthday.in", "r", stdin);
    freopen("birthday.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) solve();
    return 0;
}