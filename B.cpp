#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MOD = 998244353;
int m;

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
        assert(p1.size() <= m);
        assert(x != 0);
        poly res = p1;
        for (int i = 0; i < res.size(); ++i) {
            res[i] = res[i] * x % MOD;
        }
        return res;
    }

    friend poly operator*(const poly& p1, const poly& p2) {
        poly res(min(m, p1.size() + p2.size()));
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
        assert(res.size() <= m);
        for (int i = 0; i < res.size(); ++i) {
            res[i] = (p1.get(i) + p2.get(i)) % MOD;
        }
        return res;
    }
};

int binpow(int a, int p) {
    if (!p) return 1;
    if (p & 1) return a * binpow(a, p - 1) % MOD;
    auto t = binpow(a, p >> 1);
    return t * t % MOD;
}

void solve() {
    int n; cin >> n >> m;
    poly p(n + 1);
    for (int i = 0; i < n + 1; ++i) cin >> p[i];
    vector<poly> pw(m + 1);
    pw[0].a.assign(1, 1);
    for (int i = 1; i <= m; ++i) {
        pw[i] = pw[i - 1] * p;
    }
    poly res = pw[0];
    int coef = binpow(2, MOD - 2);
    for (int k = 1; k <= m; ++k) {
        res = res + pw[k] * coef;
        coef = coef * (2 * (k + 1) - 3) % MOD;
        coef = MOD - coef;
        coef = coef * binpow(k + 1, MOD - 2) % MOD;
        coef = coef * binpow(2, MOD - 2) % MOD;
    }
    for (int i = 0; i < m; ++i) {
        cout << res.get(i) << " ";
    }
    cout << "\n";
    res = poly();
    int fac = 1;
    for (int k = 0; k <= m; ++k) {
        res = res + pw[k] * binpow(fac, MOD - 2);
        fac = fac * (k + 1) % MOD;
    }
    for (int i = 0; i < m; ++i) {
        cout << res.get(i) << " ";
    }
    cout << "\n";
    res = poly();
    for (int k = 1; k <= m; ++k) {
        if (k % 2 != 0)
            res = res + pw[k] * binpow(k, MOD - 2);
        else
            res = res + pw[k] * (MOD - binpow(k, MOD - 2));
    }
    for (int i = 0; i < m; ++i) {
        cout << res.get(i) << " ";
    }
    cout << "\n";
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