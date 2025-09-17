#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
    int n, q;
    std::cin >> n >> q;
    const int MOD = 1e9 + 7;
    const int inv2 = (MOD + 1) / 2;
    long long h = 0;
    std::vector<int> a(q);
    std::vector<long long> f(n+1, 0);
    for(int i = 0; i < q; i++) {
        std::cin >> a[i];
    }
    for(int i = q-1; i >= 0; i--) {
        f[a[i]] = (f[a[i]] + h * inv2) % MOD;
        h = (h + a[i]) * inv2 % MOD;
    }
    f[1] = (f[1] + h) % MOD;
    for(int i = 1; i <= n; i++) {
        std::cout << f[i] << '\n';
    }
}
