#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    for(int i = 0; i < n; i++) {
        std::cin >> a[n-i-1];
    }
    auto check = [&](int x) {
        int L = 0;
        while(L < n && a[L] >= x) L++;
        auto b = a;
        for(int i = L; i < n && i - L < k; i++) {
            b[i] += k - (i - L);
        }
        for(int i = 0; i < n; i++) {
            if(b[i] < x) {
                return false;
            }
        }
        return true;
    };
    int l = 0, r = 1e9 + 2 * n;
    while(l != r) {
        int mid = (l + r + 1) / 2;
        if(check(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    std::cout << l << '\n';
}
