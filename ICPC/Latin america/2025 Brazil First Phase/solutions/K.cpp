#include <bits/stdc++.h>

const int MOD = 1e9 + 7;

long long h(long long x) { return x == 0 ? 0 : x / 2 + h(x / 2); }

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
    long long A, B;
    std::cin >> A >> B;
    long long min = 0;
    for(long long x = 1; x <= 100 && x <= A; x++) {
        for(long long y = 1; y <= 100 && y <= B; y++) {
            min = std::min(min, h(A-x+B-y)-h(A-x)-h(B-y)-(A-x+B-y));
        }
    }
    long long e = -min + 1;
    long long ans = 1, cur = 2;
    for(; e; e /= 2) {
        if(e & 1) ans = ans * cur % MOD;
        cur = cur * cur % MOD;
    }
    std::cout << ans << '\n';
}
