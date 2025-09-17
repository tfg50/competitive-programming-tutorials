#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(m, 0);
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
        int x;
        std::cin >> x;
        a[j] = std::max(a[j], x);
    }
    int ans = 0;
    for(int i = 0; i < m; i++) {
        ans += a[i];
    }
    std::cout << ans << '\n';
}
