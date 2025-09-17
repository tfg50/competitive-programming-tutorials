#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
    int n, k;
    std::cin >> n >> k;
    std::vector<long long> a(1 << k, 0);
    for(int i = 0; i < n; i++) {
        std::string str;
        std::cin >> str;
        int mask = 0;
        for(auto ch : str) mask = (mask * 2) + (ch - '0');
        a[mask]++;
    }
    for(int len = 1; len < (1 << k); len *= 2) for(int i = 0; i < (1 << k); i += 2 * len) for(int j = 0; j < len; j++) a[i+j+len] += a[i+j];
    for(int i = 0; i < (1 << k); i++) a[i] = a[i] * (a[i]-1) * (a[i]-2) / 6;
    for(int len = 1; len < (1 << k); len *= 2) for(int i = 0; i < (1 << k); i += 2 * len) for(int j = 0; j < len; j++) a[i+j+len] -= a[i+j];
    int q;
    std::cin >> q;
    while(q--) {
        std::string str;
        std::cin >> str;
        int mask = 0;
        for(auto ch : str) mask = (mask * 2) + (ch - '0');
        std::cout << a[mask] << '\n';
    }
}
