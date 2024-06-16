#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MOD = 998244353;

int binpow(int a, int p) {
    if (!p) return 1;
    if (p & 1) return a * binpow(a, p - 1) % MOD;
    auto t = binpow(a, p >> 1);
    return t * t % MOD;
}

void solve() {
    int n, m; cin >> n >> m;
    vector<int> p(n + 1), q(m + 1);
    for (int i = 0; i <= n; ++i) cin >> p[i];
    for (int i = 0; i <= m; ++i) cin >> q[i];
    auto getp = [&](int i) {
        return i <= n ? p[i] : 0;
    };
    auto getq = [&](int i) {
        return i <= m ? q[i] : 0;
    };
    cout << max(n, m) << "\n";
    for (int i = 0; i <= max(n, m); ++i) {
        cout << (getp(i) + getq(i)) % MOD << " ";
    }
    cout << "\n";
    cout << n + m << "\n";
    for (int i = 0; i <= n + m; ++i) {
        int res = 0;
        for (int j = 0; j <= i; ++j) {
            res = (res + getp(j) * getq(i - j) % MOD) % MOD;
        }
        cout << res << " ";
    }
    cout << "\n";
    vector<int> div;
    for (int i = 0; i < 1000; ++i) {
        int res = getp(i);
        for (int j = 0; j < i; ++j) {
            res = (res - div[j] * getq(i - j) % MOD + MOD) % MOD;
        }
        res = res * binpow(getq(0), MOD - 2) % MOD;
        cout << res << " ";
        div.push_back(res);
    }
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.precision(20);

    int T = 1;// cin >> T;
    while (T--)
        solve();

    return 0;
}