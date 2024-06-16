#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MOD = 1e9 + 7;

int binpow(int a, int p) {
    if (!p) return 1;
    if (p & 1) return a * binpow(a, p - 1) % MOD;
    auto t = binpow(a, p >> 1);
    return t * t % MOD;
}

void solve() {
    int k, m; cin >> k >> m;
    vector<int> c(m);
    for (int i = 0; i < k; ++i) cin >> c[i];
    vector<int> dp(m + 1), conv(m + 1);
    dp[0] = 1;
    conv[0] = 1;
    for (int n = 1; n <= m; ++n) {
        for (int i = 0; i < k; ++i) {
            if (n - c[i] < 0)
                continue;
            dp[n] = (dp[n] + conv[n - c[i]]) % MOD;
        }
        for (int i = 0; i <= n; ++i) {
            conv[n] = (conv[n] + dp[i] * dp[n - i] % MOD) % MOD;
        }
//        for (int i = 0; i < k; ++i) {
//            for (int j = 0; j + c[i] <= n; ++j) {
//                dp[n] = (dp[n] + dp[j] * dp[n - j - c[i]] % MOD) % MOD;
//            }
//        }
        cout << dp[n] << " ";
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