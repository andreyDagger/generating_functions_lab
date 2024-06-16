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
    int k; cin >> k;
    vector<int> a(k);
    for (int i = 0; i < k; ++i) cin >> a[i];
    vector<int> c(k);
    for (int i = 0; i < k; ++i) cin >> c[i];
    vector<int> p;
    for (int i = 0; i < k; ++i) {
        int cur = 0;
        for (int j = i - 1, c_idx = 0; j >= 0; --j, ++c_idx) {
            cur += c[c_idx] * a[j];
        }
        // cur + x = a[i]
        p.push_back(a[i] - cur);
    }
    while (!p.empty() && p.back() == 0) {
        p.pop_back();
    }
    assert(!p.empty());
    cout << p.size() - 1 << "\n";
    for (int x : p) cout << x << " ";
    cout << "\n";
    cout << k << "\n";
    cout << "1 ";
    for (int i = 0; i < k; ++i) {
        cout << -c[i] << " ";
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