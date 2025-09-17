#include <bits/stdc++.h>

std::vector<int> gen(std::vector<int> a) {
    std::vector<int> ans(1, 0);
    for(auto x : a) {
        for(int i = 0, sz = (int) ans.size(); i < sz; i++) {
            ans.push_back(x ^ ans[i]);
        }
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
    int n;
    std::string txt;
    std::cin >> n >> txt;
    if(txt == std::string(n, '0')) {
        std::cout << "00000000 0\n";
        return 0;
    }
    std::pair<int, int> ans(1e9, 1e9);
    std::reverse(txt.begin(), txt.end());
    for(int mask = (1 << 7); mask < (1 << 8); mask++) {
        std::vector<int> outside;
        for(int i = 0; i < 7; i++) {
            outside.push_back((mask << (i + 1)) & 255);
        }
        int d = 0;
        {
            int x = mask;
            while(x % 2 == 0) {
                x /= 2;
            }
            d = x;
        }
        std::vector<int> cost(1 << 7, 1e9);
        auto vec = gen(outside);
        for(int i = 0; i < (1 << 7); i++) {
            int curCost = __builtin_popcount(i);
            int cur = vec[i] >> 1;
            for(int j = 1; j < 8; j++) {
                if(txt[n-8+j] == '1') cur ^= 1 << (j - 1);
            }
            for(int j = n-8; j >= 0; j--) {
                cur = (cur << 1) + (txt[j] == '1' ? 1 : 0);
                if(cur & (1 << 7)) {
                    cur ^= mask;
                    curCost++;
                }
            }
            for(int j = 7; j >= 0; j--) {
                if(cur & (1 << j)) {
                    cur ^= mask >> (7 - j);
                    curCost++;
                }
            }
            ans = std::min(ans, std::pair<int, int>(curCost, d));
        }
    }
    std::string str;
    for(int i = 7; i >= 0; i--) str += char('0' + (ans.second >> i) % 2);
    std::cout << str << ' ' << ans.first << '\n';
}
