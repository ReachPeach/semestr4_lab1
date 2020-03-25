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
const int N = 250 + 10;
vector<int> go[N];
vector<bool> used;
vector<int> s;

bool khun(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (auto u : go[v]) {
        if (s[u] == -1 || khun(s[u])) {
            s[u] = v;
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;

    for (int i = 0, x; i < n; i++) {
        for (cin >> x; x != 0; cin >> x) {
            x--;
            go[i].eb(x);
        }
    }
    s.assign(m, -1);
    for (int v = 0; v < n; v++) {
        used.assign(n, false);
        khun(v);
    }
    int ans = 0;
    for (int i = 0; i < m; i++) {
        if (s[i] != -1) {
            ans++;
        }
    }
    cout << ans << '\n';
    for (int i = 0; i < m; i++) if (s[i] != -1) cout << s[i] + 1 << " " << i + 1 << "\n";

    return 0;
}