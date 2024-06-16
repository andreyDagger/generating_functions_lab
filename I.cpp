#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MOD = 104857601;

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

int calc(const poly& p, const poly& q, int n) {
    if (n == 0) {
        return p.get(0);
    }
    poly q1 = q;
    for (int i = 0; i < q1.size(); ++i) {
        if (i % 2 != 0)
            q1[i] = MOD - q1[i];
    }
    poly qq = q * q1;
    poly pp = p * q1;
    poly q_to(qq.size() / 2);
    poly p_to(pp.size() / 2);
    for (int i = 0; i < q_to.size(); ++i) {
        q_to[i] = qq.get(2 * i);
    }
    for (int i = 0; i < p_to.size(); ++i) {
        if (n % 2 == 0)
            p_to[i] = pp.get(2 * i);
        else
            p_to[i] = pp.get(2 * i + 1);
    }
    return calc(p_to, q_to, n / 2);
}

void solve() {
    int k, n; cin >> k >> n;
    vector<int> a(k), c(k);
    for (int i = 0; i < k; ++i) cin >> a[i];
    for (int i = 0; i < k; ++i) cin >> c[i];
    poly p(k + 1);
    for (int i = 0; i < k; ++i) {
        int val = 0;
        int idx = 0;
        for (int j = i - 1; j >= 0; --j, ++idx) {
            val = (val + a[j] * c[idx] % MOD) % MOD;
        }
        p[i] = (a[i] - val + MOD) % MOD;
    }
    poly q(k + 1);
    q[0] = 1;
    for (int i = 1; i <= k; ++i) {
        q[i] = MOD - c[i - 1];
    }
    --n;
    cout << calc(p, q, n) << "\n";
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