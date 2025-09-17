#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
    int n;
    std::cin >> n;
    int x = 0;
    for(int i = n; i >= 0; i--) {
        int b;
        std::cin >> b;
        x ^= b << i;
    }
    int ans = 0;
    while(x != 1) {
        if(x & 1) {
            x ^= (x << 1) ^ 1;
        } else {
            x >>= 1;
        }
        ans++;
    }
    std::cout << ans << '\n';
}
