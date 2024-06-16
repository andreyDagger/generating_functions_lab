#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MOD = 998244353;

struct poly {
    vector<int> a;

    explicit poly(int n) {
        a.assign(n, 0);
    }

    poly() : poly(0) {}

    int size() const {
        return a.size();
    }

    int& operator[](int i) {
        assert(i >= 0 && i < size());
        return a[i];
    }

    const int& operator[](int i) const {
        assert(i >= 0 && i < size());
        return a[i];
    }

    int get(int i) const {
        return i >= 0 && i < size() ? a[i] : 0;
    }

    friend poly operator*(const poly& p1, int x) {
        poly res = p1;
        for (int i = 0; i < res.size(); ++i) {
            res[i] = res[i] * x;
        }
        return res;
    }

    friend poly operator*(const poly& p1, const poly& p2) {
        poly res(p1.size() + p2.size());
        for (int i = 0; i < p1.size(); ++i) {
            for (int j = 0; j < p2.size(); ++j) {
                if (i + j >= res.size())
                    break;
                res[i + j] = (res[i + j] + p1[i] * p2[j] % MOD) % MOD;
            }
        }
        return res;
    }

    friend poly operator+(const poly& p1, const poly& p2) {
        poly res(max(p1.size(), p2.size()));
        for (int i = 0; i < res.size(); ++i) {
            res[i] = (p1.get(i) + p2.get(i)) % MOD;
        }
        return res;
    }

    friend poly operator-(const poly& p1, const poly& p2) {
        poly res(max(p1.size(), p2.size()));
        for (int i = 0; i < res.size(); ++i) {
            res[i] = (p1.get(i) - p2.get(i) + MOD) % MOD;
        }
        return res;
    }

//    friend poly operator/(const poly& p1, const poly& p2) {
//        poly res(m);
//        for (int i = 0; i < m; ++i) {
//            res[i] = p1.get(i);
//            for (int j = 0; j < i; ++j) {
//                res[i] -= res[j] * p2.get(i - j);
//            }
//            res[i] = res[i] * binpow(p2[0], MOD - 2) % MOD;
//        }
//        return res;
//    }
};

void solve() {
    poly t(2);
    t[1] = 1;
    poly ONE(1);
    ONE[0] = 1;

    int kk, nn; cin >> kk >> nn;
    vector<poly> q(kk + 1), p(kk + 1);
    q[1] = ONE;
    for (int k = 2; k <= kk; ++k) {
        p[k] = q[k - 1] * t;
        q[k] = q[k - 1] - p[k - 1];
    }
    vector<int> ans(nn + 1);
    for (int n = 0; n <= nn; ++n) {
        int idx = 1;
        for (int i = n - 1; i >= 0; --i, ++idx) {
            ans[n] = (ans[n] + ans[i] * (MOD - q[kk].get(idx)) % MOD) % MOD;
        }
        ans[n] = (ans[n] + p[kk].get(n)) % MOD;
        if (n > 0)
            cout << ans[n] << "\n";
    }
//    vector<vector<int>> dp(nn + 1, vector<int>(kk + 1));
//    for (int i = 2; i <= kk; ++i)
//        dp[1][i] = 1;
//    for (int n = 2; n <= nn; ++n) {
//        for (int k = 2; k <= kk; ++k) {
//            for (int n1 = 1; n1 < n; ++n1) {
//                dp[n][k] = (dp[n][k] + dp[n1][k - 1] * dp[n - n1][k] % MOD) % MOD;
//            }
//        }
//    }
//    for (int i = 1; i <= nn; ++i) {
//        cout << dp[i][kk] << "\n";
//    }
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